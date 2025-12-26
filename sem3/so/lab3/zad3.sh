#!/bin/bash

LOGFILE="monitor.log"
TARGET_DIR="${1:-.}" 

RED="$(tput setaf 1)"
GREEN="$(tput setaf 2)"
YELLOW="$(tput setaf 3)"
BLUE="$(tput setaf 4)"
CYAN="$(tput setaf 6)"
RESET="$(tput sgr0)"

if ! command -v inotifywait &> /dev/null; then
  echo "${RED}Bład: Nie znaleziono polecenia inotifywait.${RESET}"
  exit 1
fi

if [ ! -d "$TARGET_DIR" ]; then
  echo -e "${RED}Bład: Katalog '$TARGET_DIR' nie istnieje.${RESET}"
  exit 1
fi

echo -e "Rozpoczynam monitorowanie katalogu: ${BLUE}$TARGET_DIR${RESET}"

declare -A STATS
STATS["CREATE"]=0
STATS["DELETE"]=0
STATS["MODIFY"]=0
STATS["MOVE"]=0
TOTAL_EVENTS=0

LAST_STATS_TIME=$(date +%s)

inotify_cmd="inotifywait -m -r --exclude \"$LOGFILE\" -e create,delete,modify,moved_to,moved_from --format '%e|%w%f' \"$TARGET_DIR\" 2>/dev/null"

eval "$inotify_cmd" | while read -r line; do
  CURRENT_TIME=$(date +%s)
  TIMESTAMP=$(date "+%Y-%m-%d %H:%M:%S")

  EVENT_RAW=$(echo "$line" | cut -d'|' -f1)
  FILEPATH=$(echo "$line" | cut -d'|' -f2-)
  
  if [[ "$FILEPATH" == *"$LOGFILE" ]]; then
    continue
  fi

  EVENT_TYPE=""
  COLOR=""

  if [[ "$EVENT_RAW" == *"CREATE"* || "$EVENT_RAW" == *"MOVED_TO"* ]]; then
    EVENT_TYPE="CREATED"
    COLOR=$GREEN
    STATS["CREATE"]=$((STATS["CREATE"]+1))
      
  elif [[ "$EVENT_RAW" == *"DELETE"* || "$EVENT_RAW" == *"MOVED_FROM"* ]]; then
    EVENT_TYPE="DELETED"
    COLOR=$RED
    STATS["DELETE"]=$((STATS["DELETE"]+1))
      
  elif [[ "$EVENT_RAW" == *"MODIFY"* ]]; then
    EVENT_TYPE="MODIFIED"
    COLOR=$YELLOW
    STATS["MODIFY"]=$((STATS["MODIFY"]+1))
      
  else
    EVENT_TYPE="OTHER"
    COLOR=$CYAN
  fi

  TOTAL_EVENTS=$((TOTAL_EVENTS+1))

  printf "[%s] ${COLOR}%-10s${RESET} %s\n" "$TIMESTAMP" "$EVENT_TYPE" "$FILEPATH"

  echo "[$TIMESTAMP] $EVENT_TYPE $FILEPATH" >> "$LOGFILE"

  TIME_DIFF=$((CURRENT_TIME - LAST_STATS_TIME))
  
  if (( TIME_DIFF >= 10 )); then
    echo "---------------------------------------------------"
    echo -e "STATYSTYKI"
    echo -e "${GREEN}Utworzono: ${STATS["CREATE"]}"
    echo -e "${RED}Usunieto: ${STATS["DELETE"]}"
    echo -e "${YELLOW}Zmodyfikowano: ${STATS["MODIFY"]}"
    echo -e "${RESET}Lacznie: $TOTAL_EVENTS"
    echo "---------------------------------------------------"
    
    LAST_STATS_TIME=$CURRENT_TIME
  fi
done