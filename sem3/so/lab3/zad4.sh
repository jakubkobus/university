#!/bin/bash

TEMP_IMAGE_PATH=$(mktemp /tmp/random_cat.XXXXX)

cleanup() {
  rm -f "$TEMP_IMAGE_PATH"
}

trap cleanup EXIT

CAT_URL=$(curl -s "https://api.thecatapi.com/v1/images/search" | jq -r '.[0].url')
curl -s -L "$CAT_URL" -o "$TEMP_IMAGE_PATH"
catimg "$TEMP_IMAGE_PATH"

CHUCK_NORRIS_JOKE=$(curl -s -L "https://api.chucknorris.io/jokes/random" | jq -r '.value')
echo "$CHUCK_NORRIS_JOKE"