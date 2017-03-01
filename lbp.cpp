#include "lbp.hpp"

#include <opencv2/highgui/highgui.hpp>

auto xcs_lbp(IplImage* im) -> IplImage *
{
    int g[9], s, code, gc;
    auto dst =
        cvCreateImage(cvSize(im->width, im->height), im->depth, im->nChannels);
    for (int i = 1; i < (im->height - im->height % 3); i++) {
        for (int j = 1; j < (im->widthStep - im->widthStep % 3); j++) {
            gc = i * im->widthStep + j;
            g[0] = (uchar)im->imageData[gc + 1];
            g[1] = (uchar)im->imageData[gc + im->widthStep + 1];
            g[2] = (uchar)im->imageData[gc + im->widthStep];
            g[3] = (uchar)im->imageData[gc + im->widthStep - 1];
            g[4] = (uchar)im->imageData[gc - 1];
            g[5] = (uchar)im->imageData[gc - im->widthStep - 1];
            g[6] = (uchar)im->imageData[gc - im->widthStep];
            g[7] = (uchar)im->imageData[gc - im->widthStep + 1];
            g[8] = (uchar)im->imageData[gc];

            code = 0;
            // LBP
            /*for(int k = 0; k < 8; k++){
              s = g[k] - g[8];
              if(s >= 0) code += pow(2.0, (double)k);
              }*/

            // XCS-LBP
            for (int k = 0; k < 4; k++) {
                s = (g[k] - g[k + 4]) + g[8] +
                    (g[k] - g[8]) * (g[k + 4] - g[8]);
                if (s >= 0)
                    code += pow(2.0, (double)k);
            }

            dst->imageData[i * im->widthStep + j] = (uchar)(code * 255 / 16);
        }
    }

    return dst;
}
