// A simple program that computes the square root of a number
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <opencv4/opencv2/opencv.hpp>
#include <Constants/image.h>
#include <CamImageSubscriber.h>

using namespace std;
using namespace cv;

CamImageSubscriber sub = CamImageSubscriber();

int main(int argc, char *argv[])
{
  if (!sub.init(nullptr, nullptr))
    return 0;

  sub.run();
  return 0;
}