#!/bin/bash
g++ -O2 -o run src/main.cpp src/beta.cpp src/ui.cpp src/search.cpp src/bb.cpp src/eval.cpp src/moves.cpp
g++ -O3 -o run_optimized src/optimized.cpp
