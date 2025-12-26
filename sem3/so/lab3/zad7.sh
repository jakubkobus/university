#!/bin/bash

GREEN="$(tput setaf 2)"
YELLOW="$(tput setaf 3)"
RESET="$(tput sgr0)"

CELL_ALIVE="o"
CELL_DEAD=" "

DELAY=0.1

MAX_HISTORY=50

trap cleanup EXIT

function cleanup() {
  tput cnorm
  stty echo
  clear
  exit 0
}

tput civis
stty -echo

TERM_ROWS=$(tput lines)

ROWS=$((TERM_ROWS - 2))
COLS=$(tput cols)

GENERATION=0
ALIVE_COUNT=0
PAUSED=false
GEN_TIME=0

declare -a GRID
declare -a NEW_CELLS
declare -a NEXT_GRID

declare -a GRID_HISTORY
declare -a GENERATION_HISTORY
declare -a ALIVE_HISTORY

function updateHistory() {
  local flat_grid="${GRID[*]}"
  
  GRID_HISTORY+=("$flat_grid")
  GENERATION_HISTORY+=("$GENERATION")
  HIST_ALIVE_STORE+=("$ALIVE_COUNT")

  if [ "${#GRID_HISTORY[@]}" -gt "$MAX_HISTORY" ]; then
    GRID_HISTORY=("${GRID_HISTORY[@]:1}")
    GENERATION_HISTORY=("${GENERATION_HISTORY[@]:1}")
    HIST_ALIVE_STORE=("${HIST_ALIVE_STORE[@]:1}")
  fi
}

function loadPreviousGeneration() {
  local count=${#GRID_HISTORY[@]}
  if [ "$count" -eq 0 ]; then return; fi

  local last_idx=$((count - 1))

  GRID=(${GRID_HISTORY[$last_idx]})
  GENERATION=${GENERATION_HISTORY[$last_idx]}
  ALIVE_COUNT=${ALIVE_HISTORY[$last_idx]}

  unset 'GRID_HISTORY[last_idx]'
  unset 'GENERATION_HISTORY[last_idx]'
  unset 'ALIVE_HISTORY[last_idx]'
  
  for ((i=0; i<ROWS*COLS; i++)); do NEW_CELLS[$i]=0; done
}

function initializeRandomGrid() {
  local size=$((ROWS * COLS))
  local i
  for ((i=0; i<size; i++)); do
    if (( RANDOM % 5 == 0 )); then
      GRID[$i]=1
      NEW_CELLS[$i]=0
      ((ALIVE_COUNT++))
    else
      GRID[$i]=0
      NEW_CELLS[$i]=0
    fi
  done
}

function draw() {
  tput cup 0 0

  local pausedText="Pause"
  if $PAUSED; then pausedText="Unpause"; fi
  
  HUD1="Generation: $GENERATION  Alive cells: $ALIVE_COUNT  History count: ${#GRID_HISTORY[@]}  Generation time: ${GEN_TIME}s"
  HUD2="[q] Quit  [p] $pausedText  ["$'\u2190'"] Previous generation  [+/-] Additional delay ($(printf "%.2f" $DELAY)s)   "
  HUD1_LEN=${#HUD1}
  HUD2_LEN=${#HUD2}

  local padding1=$(( (COLS - HUD1_LEN) / 2 ))
  tput cup 0 0
  printf "%*s%s" $padding1 "" "$HUD1"
  tput el
  printf "\n"
  
  local buffer=""
  local idx=0
  
  for ((r=0; r<ROWS; r++)); do
    for ((c=0; c<COLS; c++)); do
      idx=$((r * COLS + c))
      if (( GRID[idx] == 1 )); then
        if (( NEW_CELLS[idx] == 1 )); then
          buffer+="${YELLOW}${CELL_ALIVE}${RESET}"
        else
          buffer+="${GREEN}${CELL_ALIVE}${RESET}"
        fi
      else
        buffer+="${CELL_DEAD}"
      fi
    done
    if (( r < ROWS - 1 )); then
      buffer+=$'\n'
    fi
  done
  
  echo -ne "$buffer"

  local padding2=$(( (COLS - HUD2_LEN) / 2 ))
  tput cup $((TERM_ROWS-1)) 0
  printf "%*s%s" $padding2 "" "$HUD2"
  tput el

}

function evolve() {
  updateHistory

  local idx=0
  local neighbors=0
  local new_alive_count=0
  local r c n_idx
  
  for ((i=0; i<ROWS*COLS; i++)); do
    NEW_CELLS[$i]=0
  done

  NEXT_GRID=("${GRID[@]}")

  for ((r=0; r<ROWS; r++)); do
    for ((c=0; c<COLS; c++)); do
      idx=$((r * COLS + c))
      neighbors=0

      # up-left
      if (( r-1 >= 0 && c-1 >= 0 )); then
        n_idx=$(((r-1) * COLS + (c-1)))
        if (( GRID[n_idx] == 1 )); then ((neighbors++)); fi
      fi
      # up
      if (( r-1 >= 0 )); then
        n_idx=$(((r-1) * COLS + c))
        if (( GRID[n_idx] == 1 )); then ((neighbors++)); fi
      fi
      # up-right
      if (( r-1 >= 0 && c+1 < COLS )); then
        n_idx=$(((r-1) * COLS + (c+1)))
        if (( GRID[n_idx] == 1 )); then ((neighbors++)); fi
      fi
      # left
      if (( c-1 >= 0 )); then
        n_idx=$((r * COLS + (c-1)))
        if (( GRID[n_idx] == 1 )); then ((neighbors++)); fi
      fi
      # right
      if (( c+1 < COLS )); then
        n_idx=$((r * COLS + (c+1)))
        if (( GRID[n_idx] == 1 )); then ((neighbors++)); fi
      fi
      # down-left
      if (( r+1 < ROWS && c-1 >= 0 )); then
        n_idx=$(((r+1) * COLS + (c-1)))
        if (( GRID[n_idx] == 1 )); then ((neighbors++)); fi
      fi
      # down
      if (( r+1 < ROWS )); then
        n_idx=$(((r+1) * COLS + c))
        if (( GRID[n_idx] == 1 )); then ((neighbors++)); fi
      fi
      # down-right
      if (( r+1 < ROWS && c+1 < COLS )); then
        n_idx=$(((r+1) * COLS + (c+1)))
        if (( GRID[n_idx] == 1 )); then ((neighbors++)); fi
      fi
      
      if (( GRID[idx] == 1 )); then
        if (( neighbors == 2 || neighbors == 3 )); then
          NEXT_GRID[$idx]=1
          ((new_alive_count++))
          NEW_CELLS[$idx]=0
        else
          NEXT_GRID[$idx]=0
        fi
      else
        if (( neighbors == 3 )); then
          NEXT_GRID[$idx]=1
          ((new_alive_count++))
          NEW_CELLS[$idx]=1
        else
          NEXT_GRID[$idx]=0
        fi
      fi
    done
  done
  
  GRID=("${NEXT_GRID[@]}")
  ALIVE_COUNT=$new_alive_count
  ((GENERATION++))
}

initializeRandomGrid

while true; do
  draw
  
  if $PAUSED; then
    read -s -n 1 -t 1 key || key=""
  else
    read -s -n 1 -t "$DELAY" key || key=""
  fi
  if [ "$key" = $'\e' ]; then
    read -s -n 2 -t 0.01 rest 2>/dev/null || rest=""
    key="$key$rest"
  fi
  
  case "$key" in
    q|Q)
      break
    ;;
    p|P)
      if $PAUSED; then 
        PAUSED=false 
      else
        PAUSED=true
      fi
    ;;
    $'\e[D')
      PAUSED=true
      loadPreviousGeneration
    ;;
    +)
      DELAY=$(awk "BEGIN {print $DELAY - 0.05}")
    ;;
    -)
      DELAY=$(awk "BEGIN {print $DELAY + 0.05}")
    ;;
  esac
  
  if ! $PAUSED; then
    START_TIME=$(date +%s%N)
    evolve
    END_TIME=$(date +%s%N)
    GEN_TIME=$(awk -v start=$START_TIME -v end=$END_TIME 'BEGIN { printf "%.4f", (end-start)/1000000000 }')
    sleep "$DELAY"
  fi
done