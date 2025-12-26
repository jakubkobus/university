#!/bin/bash

RESET=$(tput sgr0)
GREEN=$(tput setaf 2)
YELLOW=$(tput setaf 3)
CYAN=$(tput setaf 6)
tput civis

MAX_HISTORY=40
declare -a RX_HISTORY
declare -a TX_HISTORY
for ((i=0; i<MAX_HISTORY; i++)); do RX_HISTORY[$i]=0; TX_HISTORY[$i]=0; done

declare -a PREV_IDLE
declare -a PREV_TOTAL

PREV_RX=0
PREV_TX=0

BARS=(" " "▂" "▃" "▄" "▅" "▆" "▇" "█")

cleanup() {
  tput cnorm
  tput sgr0
  tput clear
  exit 0
}
trap cleanup SIGINT SIGTERM EXIT

formatBytes() {
  local bytes=$1
  if (( bytes < 1024 )); then
    echo "${bytes} B/s"
  elif (( bytes < 1048576 )); then
    echo "$(( bytes / 1024 )) KB/s"
  else
    printf "%.1f MB/s" $(echo "$bytes / 1048576" | bc -l)
  fi
}

drawGraph() {
  local -n arr=$1
  local color=$2
  local max=1
  
  for val in "${arr[@]}"; do
    (( val > max )) && max=$val
  done

  local graph_str=""
  for val in "${arr[@]}"; do
    local index=$(( val * 8 / max ))
    (( index > 8 )) && index=8
    graph_str+="${BARS[$index]}"
  done
  
  echo -ne "${color}${graph_str}${RESET}"
}

getMemory() {
  awk '
    /MemTotal/ {total=$2}
    /MemAvailable/ {avail=$2}
    END {
      used = total - avail
      perc = int(used * 100 / total)
      bar=""
      for (i=0; i<perc/5; i++) bar = bar "|"
      printf "RAM: [%-20s] %3d%% (%d/%d MB)\n", 
          bar, perc, int(used/1024), int(total/1024)
    }
  ' /proc/meminfo
}

initializeNetwork() {
  local r=0 t=0
  while read -r line; do
    if [[ $line =~ : ]] && [[ ! $line =~ "lo:" ]]; then
      line=$(echo $line | tr -s ' ')
      r=$((r + $(echo $line | cut -d' ' -f2)))
      t=$((t + $(echo $line | cut -d' ' -f10)))
    fi
  done < /proc/net/dev
  PREV_RX=$r
  PREV_TX=$t
}

initializeNetwork

while true; do
  tput cup 0 0
  
  echo -e "${CYAN}--- SYSTEM ---${RESET}\033[K"
  
  up_seconds=$(cut -d. -f1 /proc/uptime)
  d=$((up_seconds / 86400)); h=$(( (up_seconds % 86400) / 3600 ))
  m=$(( (up_seconds % 3600) / 60)); s=$((up_seconds % 60))
  printf "Uptime : %dd %02dh %02dm %02ds\033[K\n" $d $h $m $s
  
  read -r l1 l2 l3 _ < /proc/loadavg
  echo -e "Load   : $l1 $l2 $l3\033[K"

  bat_path_glob=(/sys/class/power_supply/BAT*/capacity)
  if [ -r "${bat_path_glob[0]}" ]; then
    echo -e "Battery: $(< "${bat_path_glob[0]}")%\033[K"
  fi

  echo -e "${CYAN}--- PAMIEC ---${RESET}\033[K"
  getMemory
  
  echo -e "${CYAN}--- CPU ---${RESET}\033[K"
  cpu_idx=0
  while read -r line; do
    if [[ $line =~ ^cpu[0-9]+ ]]; then
      fields=($line)
      idle_val=$(( ${fields[4]} + ${fields[5]} ))
      total=$(( ${fields[1]}+${fields[2]}+${fields[3]}+${fields[4]}+${fields[5]}+${fields[6]}+${fields[7]} ))
      
      diff_idle=$(( idle_val - ${PREV_IDLE[$cpu_idx]:-0} ))
      diff_total=$(( total - ${PREV_TOTAL[$cpu_idx]:-0} ))
      
      [ $diff_total -eq 0 ] && diff_total=1
      
      cpu_usage=$(( (diff_total - diff_idle) * 100 / diff_total ))
      
      PREV_IDLE[$cpu_idx]=$idle_val
      PREV_TOTAL[$cpu_idx]=$total
      
      freq_raw=$(cat "/sys/devices/system/cpu/${fields[0]}/cpufreq/cpuinfo_cur_freq" 2>/dev/null)
      
      if [ -z "$freq_raw" ]; then
        freq_raw=$(cat "/sys/devices/system/cpu/${fields[0]}/cpufreq/scaling_cur_freq" 2>/dev/null)
      fi
      
      freq_mhz=$(( ${freq_raw:-0} / 1000 ))
      
      bar_str=$(printf "%0.s|" $(seq 1 $((cpu_usage / 5)) ))
      printf "%-5s: [%-20s] %3d%%  %4d MHz\033[K\n" "${fields[0]}" "$bar_str" "$cpu_usage" "$freq_mhz"
      
      ((cpu_idx++))
    fi
  done < /proc/stat
  
  echo -e "${CYAN}--- SIEC ---${RESET}\033[K"
  curr_rx=0; curr_tx=0
  while read -r line; do
    if [[ $line =~ : ]] && [[ ! $line =~ "lo:" ]]; then
      line=$(echo $line | tr -s ' ')
      curr_rx=$((curr_rx + $(echo $line | cut -d' ' -f2)))
      curr_tx=$((curr_tx + $(echo $line | cut -d' ' -f10)))
    fi
  done < /proc/net/dev
  
  rx_speed=$(( curr_rx - PREV_RX )); [ $rx_speed -lt 0 ] && rx_speed=0
  tx_speed=$(( curr_tx - PREV_TX )); [ $tx_speed -lt 0 ] && tx_speed=0
  
  PREV_RX=$curr_rx; PREV_TX=$curr_tx
  
  RX_HISTORY=("${RX_HISTORY[@]:1}" "$rx_speed")
  TX_HISTORY=("${TX_HISTORY[@]:1}" "$tx_speed")
  
  printf "DL: %-12s | UP: %-12s\033[K\n" "$(formatBytes $rx_speed)" "$(formatBytes $tx_speed)"
  
  echo -n "DL: "
  drawGraph RX_HISTORY $GREEN
  echo -e "\033[K"
  echo -n "UP: "
  drawGraph TX_HISTORY $YELLOW
  echo -e "\033[K"

  tput ed
  sleep 1
done