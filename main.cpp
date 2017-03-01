#include <iostream>
#include <assert.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "lbp.hpp"

int main(int argc, char const* argv[])
{
    std::string image_file = "image.jpg";
    if(argc == 2) 
    {
        image_file = std::string(argv[1]);
    }

    auto im = cvLoadImage(image_file.c_str(), CV_LOAD_IMAGE_GRAYSCALE);
    assert(im);
//     auto dst = cvCreateImage(cvSize(im->width, im->height), im->depth, im->nChannels);
//     assert(dst);

    auto dst = xcs_lbp(im);
    assert(dst);

    cvNamedWindow("Image",CV_WINDOW_AUTOSIZE);
    cvShowImage("Image", dst);
    cvWaitKey(0);
    cvDestroyAllWindows();
    cvReleaseImage(&im);
}
