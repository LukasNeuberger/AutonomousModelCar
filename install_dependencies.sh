#!/bin/bash
#installs all dependencies for this project

#make sure system is up to date
sudo apt-get update
sudo apt-get upgrade -y

#CMake
sudo apt-get install build-essential cmake -y

#make directory for git repositories
mkdir dependencies
cd dependencies

#ZeroMQ message queueing
#git clone https://github.com/zeromq/libzmq.git
#cd libzmq
#mkdir build
#cd build
#cmake ..
#sudo make -j4 install
#cd ../..

#C++ bindings for ZeroMQ
#git clone https://github.com/zeromq/cppzmq.git
#cd cppzmq
#mkdir build
#cd build
#cmake ..
#sudo make -j4 install
#cd ../..

#OpenSplice
#git clone https://github.com/ADLINK-IST/opensplice.git
#cd opensplice

#sudo apt-get install -y gawk flex bison perl gsoap
#source ./configure armv6l.linux-dev
#echo "alias ospl=\"source $HOME/opensplice/install/HDE/$TARGET/release.com\"" >> ~/.bashrc
#source $HOME/.bashrc
#source $HOME/opensplice/install/HDE/$TARGET/release.com
#make
#sudo make install
#cd ..

#RabbitMQ
sudo apt-get install rabbitmq-server -y
sudo rabbitmq-plugins enable rabbitmq_mqtt

#RabbitMQ C++
git clone https://github.com/CopernicaMarketingSoftware/AMQP-CPP.git
cd AMQP-CPP
sudo apt-get install libssl-dev -y
make
sudo make install
cd ../..

#Mosquitto MQTT
sudo apt-get install libmosquitto-dev -y

#Paho MQTT
workon cv
pip install paho-mqtt