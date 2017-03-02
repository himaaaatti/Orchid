#include <iostream>
#include <assert.h>
#include <stdint.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#define height 480
#define width 640

void xcs_lbp(uint8_t im[height][width], uint8_t dst[height/3][width/3]){
  int g[9], s, code, gc;
  int x=0, y=0;

  y = 0;
  for(int i = 1; i < height; i+=3){
    x = 0;
    for(int j = 1; j < width; j+=3){
      g[0] = im[i][j+1];
      g[1] = im[i+1][j+1];
      g[2] = im[i+1][j];
      g[3] = im[i+1][j-1];
      g[4] = im[i][j-1];
      g[5] = im[i-1][j-1];
      g[6] = im[i-1][j];
      g[7] = im[i-1][j+1];
      g[8] = im[i][j];
      
      code = 0;
      
      //XCS-LBP
      for(int k = 0; k < 4; k++){
	s = (g[k] - g[k+4]) + g[8] + (g[k] - g[8])*(g[k+4] - g[8]);
	if(s >= 0) code += pow(2.0, (double)k);
      }
      dst[y][x] = code;
      x++;
    }
    y++;
  }
  return;
}

int main(int argc, char const* argv[])
{
  uint8_t src_im[height][width], dst_im[height/3][width/3];
  IplImage *im = NULL, *dst = NULL;
  
    std::string image_file = "cat.jpg";
    if(argc == 2) 
    {
        image_file = std::string(argv[1]);
    }

    im = cvLoadImage(image_file.c_str(), CV_LOAD_IMAGE_GRAYSCALE);
    assert(im);
    dst = cvCreateImage(cvSize(width/3, height/3), im->depth, 1);
    
    for(int i = 0; i < height; i++){
      for(int j = 0; j < width; j++){
	src_im[i][j] = im->imageData[i*im->widthStep + j];
      }
    }
    
    xcs_lbp(src_im, dst_im);

     for(int i = 0; i < height/3; i++){
      for(int j = 0; j < width/3; j++){
        dst->imageData[i*dst->widthStep + j] = dst_im[i][j];
      }
    }

     cvSaveImage("result.jpg",dst);
    /*cvNamedWindow("Image",CV_WINDOW_AUTOSIZE);
    cvShowImage("Image", dst);
    cvWaitKey(0);
    cvDestroyAllWindows();
    cvReleaseImage(&im);*/
}
