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
  printf("Image_Grabber connect callback, rc=%d\n", result);
}

int main(int argc, char *argv[])
{
  uint8_t reconnect = true;
  struct mosquitto *mosq;
  int rc = 0;
  printf("running");
  mosquitto_lib_init();
  mosq = mosquitto_new("Image_Grabber", true, 0);
  if (!mosq)
    return 0;
  mosquitto_connect_callback_set(mosq, connect_callback);
  rc = mosquitto_connect(mosq, mqtt_host, mqtt_port, 2);
  if (rc)
    return 0;

  VideoCapture cap(0); // open the default camera
  if (!cap.isOpened()) // check if we succeeded
    return -1;
  //namedWindow("image", 1);

  while (run)
  {
    rc = mosquitto_loop(mosq, -1, 1);

    Mat frame;
    cap >> frame; // get a new frame from camera
    //imshow("image", frame);

    int mid;
    int size = frame.total() * frame.elemSize();
    //printf("%d %d %d\n", frame.elemSize(), frame.cols, frame.rows);
    mosquitto_publish(mosq, &mid, "/image", size, frame.data, 0, false);

    if (waitKey(30) >= 0)
      break;
    if (run && rc)
    {
      printf("Image_Grabber connection error!\n");
      sleep(10);
      mosquitto_reconnect(mosq);
    }
  }

  mosquitto_destroy(mosq);
  mosquitto_lib_cleanup();
  return 0;
}
