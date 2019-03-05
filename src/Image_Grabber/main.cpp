// A simple program that computes the square root of a number
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include "Config.h"
#include <mosquitto.h>
#include <unistd.h>

#define mqtt_host "localhost"
#define mqtt_port 1883

static int run = 1;

void handle_signal(int s)
{
  run = 0;
}

void connect_callback(struct mosquitto *mosq, void *obj, int result)
{
  printf("Image_Grabber connect callback, rc=%d\n", result);
}

int main(int argc, char *argv[])
{
  uint8_t reconnect = true;
  struct mosquitto *mosq;
  int rc = 0;

  mosquitto_lib_init();
  mosq = mosquitto_new("Image_Grabber", true, 0);

  if (mosq)
  {
    mosquitto_connect_callback_set(mosq, connect_callback);

    rc = mosquitto_connect(mosq, mqtt_host, mqtt_port, 2);

    while (run)
    {
      rc = mosquitto_loop(mosq, -1, 1);
      int mid;
      mosquitto_publish(mosq, &mid, "/test", 5, "abcd", 0, false);
      sleep(1);
      if (run && rc)
      {
        printf("Image_Grabber connection error!\n");
        sleep(10);
        mosquitto_reconnect(mosq);
      }
    }
    mosquitto_destroy(mosq);
  }

  mosquitto_lib_cleanup();

  return rc;
}