#!/bin/bash

for f in *; do
  if [ -f "$f" ]; then
    new_name=$(echo "$f" | tr '[:upper:]' '[:lower:]')
    if [ "$f" != "$new_name" ]; then
      mv -- "$f" "$new_name"
    fi
  fi
done
