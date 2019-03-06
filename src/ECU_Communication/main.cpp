// A simple program that computes the square root of a number
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include "Config.h"
#include <mosquitto.h>
#include <unistd.h>
#include <opencv4/opencv2/opencv.hpp>

#define mqtt_host "localhost"
#define mqtt_port 1883

using namespace cv;

static int run = 1;

void handle_signal(int s)
{
  run = 0;
}

void connect_callback(struct mosquitto *mosq, void *obj, int result)
{
  printf("ECU_Communication connect callback, rc=%d\n", result);
}

void message_callback(struct mosquitto *mosq, void *obj, const struct mosquitto_message *message)
{
  bool match = 0;
  //printf("got message '%d' for topic '%s'\n", message->payloadlen, message->topic);
  Mat frame = Mat(480, 640, CV_8UC3, message->payload);
  //std::cout << frame << std::endl;
  imshow("image", frame);
  waitKey(10);
}

int main(int argc, char *argv[])
{
  uint8_t reconnect = true;
  struct mosquitto *mosq;
  int rc = 0;

  mosquitto_lib_init();
  mosq = mosquitto_new("ECU_Communication", true, 0);

  namedWindow("image", 1);

  if (mosq)
  {
    mosquitto_connect_callback_set(mosq, connect_callback);
    mosquitto_message_callback_set(mosq, message_callback);

    rc = mosquitto_connect(mosq, mqtt_host, mqtt_port, 60);

    mosquitto_subscribe(mosq, NULL, "/image", 0);

    while (run)
    {
      rc = mosquitto_loop(mosq, -1, 1);
      if (run && rc)
      {
        printf("ECU_Communication connection error!\n");
        sleep(10);
        mosquitto_reconnect(mosq);
      }
    }
    mosquitto_destroy(mosq);
  }

  mosquitto_lib_cleanup();

  return rc;
}