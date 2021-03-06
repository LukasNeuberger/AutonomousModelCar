#include <opencv4/opencv2/opencv.hpp>

#define IMAGE_WIDTH (640)
#define IMAGE_HEIGHT (480)
#define IMAGE_CV_TYPE (CV_8UC3)
#define IMAGE_ELEMENT_SIZE (CV_MAT_CN(IMAGE_CV_TYPE) * (1 + CV_MAT_DEPTH(IMAGE_CV_TYPE) / 2))
#define IMAGE_SIZE (IMAGE_WIDTH * IMAGE_HEIGHT * IMAGE_ELEMENT_SIZE)