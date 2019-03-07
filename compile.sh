#!/bin/bash
set -e

mkdir -p build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=..
make -j4
make install