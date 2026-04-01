#!/bin/bash

cargo build
cp target/debug/wrapper_rust ./main_static

cargo build --features dynamic
cp target/debug/wrapper_rust ./main_dynamic
