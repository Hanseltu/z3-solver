#!/bin/bash

# g++ -g test-merge.cc Expr.cpp Z3Handler.cpp z3/libz3.so -I ./z3/include -o z3-test
# export LD_FLAGS="-Wl --rpath=./z3"
g++ -g test-merge.cc Expr.cpp Z3Handler.cpp -lz3 -L./z3/ -I./z3/include -o z3-test
./z3-test
# g++ test.cc  -o z3-test
