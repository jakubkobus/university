#!/bin/bash

MY_UID=$(id -u)

REFRESH_RATE=1

RED=$(tput setaf 1)
GREEN=$(tput setaf 2)
YELLOW=$(tput setaf 3)
BLUE=$(tput setaf 4)
CYAN=$(tput setaf 6)
RESET=$(tput sgr0)

clear
tput civis

function cleanup() {
  echo -ne "$SHOW_CURSOR"
  stty echo icanon
  clear
  exit 0
}

trap cleanup SIGINT SIGTERM EXIT

drawHeader() {
  tput cup 0 0
  printf "${BLUE}%-6s %-6s %-6s %-8s %-5s %-5s %-6s %-6s %s${RESET}\033[K\n" \
  "PID" "PPID" "STAT" "RSS(pg)" "FILES" "TTY" "PGID" "SID" "COMMAND"
}

ask() {
  local prompt="$1"
  local var_name="$2"
  
  tput cup $(($(tput lines)-2)) 0
  echo -ne "\033[K"
  echo -ne "$prompt"
  
  tput cnorm; stty echo icanon
  read -r input_val
  tput civis; stty -echo -icanon
  
  eval "$var_name='$input_val'"
  
  tput cup $(($(tput lines)-2)) 0
  echo -ne "\033[K"
}

showStatus() {
    tput cup $(($(tput lines)-1)) 0
    echo -ne "\033[K$1"
    sleep 0.5
}

stty -echo -icanon time 0 min 0

while true; do
  drawHeader
  
  ROW=1
  MAX_ROWS=$(tput lines)
  MAX_ROWS=$((MAX_ROWS - 2))
  
  for pid_path in /proc/[0-9]*; do
    [ -d "$pid_path" ] || continue
    
    if [ -O "$pid_path" ]; then
      PID=${pid_path##*/}
      
      if [ -r "$pid_path/stat" ]; then
        stat_content=$(< "$pid_path/stat")
        
        rest="${stat_content##*)}"
        comm_temp="${stat_content%)*}"
        comm="${comm_temp#*(}"
        
        stats=($rest)
        
        STATE=${stats[0]}
        PPID_VAL=${stats[1]}
        PGRP=${stats[2]}
        SID=${stats[3]}
        TTY=${stats[4]}
        RSS=${stats[21]}
        
        STATE_COLOR=$GREEN
        [ "$STATE" == "R" ] && STATE_COLOR=$GREEN
        [ "$STATE" == "S" ] && STATE_COLOR=$RESET
        [ "$STATE" == "T" ] && STATE_COLOR=$RED
        [ "$STATE" == "Z" ] && STATE_COLOR=$YELLOW
        
        shopt -s nullglob
        fds=( "$pid_path/fd/"* )
        OPEN_FILES=${#fds[@]}
        shopt -u nullglob
        
        if [ $ROW -lt $MAX_ROWS ]; then
          printf "%-6s %-6s ${STATE_COLOR}%-6s${RESET} %-8s %-5s %-5s %-6s %-6s ${BOLD}%s${RESET}\033[K\n" \
          "$PID" "$PPID_VAL" "$STATE" "$RSS" "$OPEN_FILES" "$TTY" "$PGRP" "$SID" "$comm"
          ((ROW++))
        fi
      fi
    fi
  done
  
  while [ $ROW -lt $MAX_ROWS ]; do
    echo -ne "\033[K\n"
    ((ROW++))
  done
  
  tput cup $(($(tput lines)-1)) 0
  printf "${CYAN}[q] Wyjście  [s] Sygnal  [r] Renice${RESET}\033[K"
  
  read -t "$REFRESH_RATE" -n 1 key
  
  case "$key" in
    q|Q)
        break
    ;;
    s|S)
      ask "Podaj PID do wysłania sygnału: " target_pid
      if [[ -n "$target_pid" && -d "/proc/$target_pid" ]]; then
        ask "Wybierz akcję [t]erm, [k]ill, [s]top, [c]ont: " sig_choice
        case "$sig_choice" in
          t) kill -TERM "$target_pid" 2>/dev/null && showStatus "Wysłano SIGTERM do $target_pid" ;;
          k) kill -KILL "$target_pid" 2>/dev/null && showStatus "Wysłano SIGKILL do $target_pid" ;;
          s) kill -STOP "$target_pid" 2>/dev/null && showStatus "Zatrzymano proces $target_pid" ;;
          c) kill -CONT "$target_pid" 2>/dev/null && showStatus "Wznowiono proces $target_pid" ;;
          *) showStatus "Nieznana akcja." ;;
        esac
      else
          showStatus "Błędny PID."
      fi
    ;;
    r|R)
      ask "Podaj PID: " target_pid
      if [[ -n "$target_pid" && -d "/proc/$target_pid" ]]; then
        ask_user "Nowa wartosc: " nice_val
        renice -n "$nice_val" -p "$target_pid" >/dev/null 2>&1
        if [ $? -eq 0 ]; then
          showStatus "Zmieniono priorytet $target_pid na $nice_val"
        else
          showStatus "Błąd renice (może brak uprawnień?)"
        fi
      else
        showStatus "Błędny PID."
      fi
    ;;
  esac
done