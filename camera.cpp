#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

int main() {
    int c = 0; // キーボード入力用
    CvCapture *capture=0; // カメラキャプチャ用
    IplImage *frame=0; // キャプチャ画像用
    int g[9], s, code, gc;
    IplImage *im = NULL, *dst = NULL;
	
    // カメラキャプチャ取得用
    capture = cvCreateCameraCapture(0);

    // キャプチャ画像を表示するためのウィンドウを作成
    cvNamedWindow("Capture", CV_WINDOW_AUTOSIZE);

    while (1) {
        // キャプチャ画像を取得
        frame = cvQueryFrame(capture);
	im = cvCreateImage(cvSize(frame->width, frame->height), frame->depth, 1);
	cvCvtColor(frame, im, CV_BGR2GRAY);
	dst = cvCreateImage(cvSize(im->width, im->height), im->depth, im->nChannels);
	
	for(int i = 1; i < (im->height-im->height%3); i++){
	  for(int j = 1; j < (im->widthStep-im->widthStep%3); j++){
	    gc = i*im->widthStep + j;
	    g[0] = (uchar)im->imageData[ gc + 1];
	    g[1] = (uchar)im->imageData[ gc + im->widthStep + 1];
	    g[2] = (uchar)im->imageData[ gc + im->widthStep];
	    g[3] = (uchar)im->imageData[ gc + im->widthStep - 1];
	    g[4] = (uchar)im->imageData[ gc - 1];
	    g[5] = (uchar)im->imageData[ gc - im->widthStep - 1];
	    g[6] = (uchar)im->imageData[ gc - im->widthStep];
	    g[7] = (uchar)im->imageData[ gc - im->widthStep + 1];
	    g[8] = (uchar)im->imageData[ gc];
	    
	    code = 0;
	    /*for(int k = 0; k < 8; k++){
	      s = g[k] - g[8];
	      if(s >= 0) code += pow(2.0, (double)k);
	      }*/
	    for(int k = 0; k < 4; k++){
	      s = (g[k] - g[k+4]) + g[8] + (g[k] - g[8])*(g[k+4] - g[8]);
	      if(s >= 0) code += pow(2.0, (double)k);
	    }
	    
	    dst->imageData[i*im->widthStep + j] = (uchar)(code*255/16);
	  }
	}

	
        // 取得したキャプチャ画像を表示
        cvShowImage("Capture", dst);
	
        // キーボード入力を待つ
        c = cvWaitKey (2);
        if (c == '\x1b') { // Escキー
            break;
        }
    }
}
