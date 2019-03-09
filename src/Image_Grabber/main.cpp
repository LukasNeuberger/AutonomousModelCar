// A simple program that computes the square root of a number
#include <stdio.h>
#include <stdlib.h>
#include <mosquitto.h>
#include <opencv4/opencv2/opencv.hpp>
#include <Constants/image.h>
#include <msg.h>

using namespace std;
using namespace cv;

#define FREQ (5)
VideoCapture *cap;
std::chrono::system_clock::time_point lastPic;
void handle(struct mosquitto *mosq)
{
  Mat frame;
  *cap >> frame;
  auto now = chrono::system_clock::now();
  auto timeSinceLast = chrono::duration_cast<chrono::microseconds>(now - lastPic);
  if (timeSinceLast.count() > (1000000.0 / FREQ))
  {
    lastPic = now;
    mosquitto_publish(mosq, nullptr, "/image", IMAGE_SIZE, frame.data, 0, false);
  }
}

int main(int argc, char *argv[])
{
  struct mosquitto *mosq = MessagingInit("Image_Grabber");
  if (!mosq)
    return 0;

  cap = new VideoCapture(0); // open the default camera
  if (!cap->isOpened())      // check if we succeeded
    return -1;

  MessagingLoop(mosq, handle);

  mosquitto_destroy(mosq);
  mosquitto_lib_cleanup();

  return 0;
}
