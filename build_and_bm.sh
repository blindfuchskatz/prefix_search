#!/bin/bash

export TOPDIR
TOPDIR=$(realpath $(dirname $0)/.)

cmake -S . -B build
cmake --build build && ./build/prefix_search_bm