// A simple program that computes the square root of a number
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <mosquitto.h>
#include <opencv4/opencv2/opencv.hpp>
#include <Constants/image.h>
#include <msg.h>

using namespace std;
using namespace cv;

static int run = 1;

void message_callback(struct mosquitto *mosq, void *obj, const struct mosquitto_message *message)
{
  Mat frame = Mat(IMAGE_HEIGHT, IMAGE_WIDTH, IMAGE_CV_TYPE, message->payload);
  imshow("image", frame);
  waitKey(1);
}

int main(int argc, char *argv[])
{
  struct mosquitto *mosq = MessagingInit("ECU_Communication");
  if (!mosq)
    return 0;

  MessagingSetMessageCallback(mosq, message_callback);
  MessagingSubscribe(mosq, NULL, "/image", 0);

  namedWindow("image", 1);

  MessagingLoop(mosq);

  mosquitto_destroy(mosq);
  mosquitto_lib_cleanup();

  return 0;
}