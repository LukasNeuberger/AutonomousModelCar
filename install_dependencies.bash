#!/bin/bash
#installs all dependencies for this project

mkdir dependencies
cd dependencies

#ZeroMQ message queueing
git clone https://github.com/zeromq/libzmq.git
cd libzmq 
mkdir build
cd build
cmake ..
sudo make -j4 install
cd ../..

#C++ bindings for ZeroMQ
git clone https://github.com/zeromq/cppzmq.git
cd cppzmq
mkdir build
cd build
cmake ..
sudo make -j4 install
cd ../..