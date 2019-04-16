// A simple program that computes the square root of a number
#include <stdio.h>
#include <stdlib.h>
#include <opencv4/opencv2/opencv.hpp>
#include <Constants/image.h>
#include <CamImagePublisher.h>
#include <thread> // std::this_thread::sleep_for
#include <chrono> // std::chrono::seconds

using namespace std;
using namespace cv;

CamImagePublisher pub = CamImagePublisher();

int frequency = 5;
VideoCapture *cap;
std::chrono::system_clock::time_point lastPic;
void handle()
{
  Mat frame;
  *cap >> frame;
  auto now = chrono::system_clock::now();
  auto timeSinceLast = chrono::duration_cast<chrono::microseconds>(now - lastPic);
  if (timeSinceLast.count() > (1000000.0 / frequency))
  {
    lastPic = now;
  }
}

int main(int argc, char *argv[])
{
  if (!pub.init(nullptr))
    return 0;
  pub.run();

  cap = new VideoCapture(0); // open the default camera
  if (!cap->isOpened())      // check if we succeeded
    return -1;

  chrono::microseconds loop_time(0);
  if (frequency > 0)
    loop_time = chrono::microseconds(1000000 / frequency);

  for (;;)
  {
    auto start = chrono::system_clock::now();
    handle();

    auto elapsed = chrono::duration_cast<chrono::microseconds>(chrono::system_clock::now() - start);
    auto rest = loop_time - elapsed;
    if (rest.count() > 0)
      this_thread::sleep_for(rest);
  }
  return 0;
}
