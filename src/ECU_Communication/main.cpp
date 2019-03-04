// A simple program that computes the square root of a number
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include "Config.h"
#include <zmq.hpp>

int main(int argc, char *argv[])
{
  zmq::context_t contect(1);
  zmq::socket_t socket(contect, ZMQ_REP);
  socket.bind("tcp://*:5555");
  while (true)
  {
    zmq::message_t request;
    socket.recv(&request);
    std::cout << "Received Hello" << std::endl;

    zmq::message_t reply(5);
    memcpy(reply.data(), "World", 5);
    socket.send(reply);
  }
  return 0;
}
