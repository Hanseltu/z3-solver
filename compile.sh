#!/bin/bash

g++ test.cc Expr.cpp z3/libz3.so -I ./z3/include -o z3-test
./z3-test
# g++ test.cc  -o z3-test