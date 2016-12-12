#ifndef __IMPL_H__
#define __IMPL_H__

#include "stdlib.h"
#include "stdio.h"
#include "math.h"

#include "opencv2\opencv.hpp"
#include "opencv\cv.h"
#include "opencv\highgui.h"
#include "opencv\cxcore.h"


#include "opencv2\highgui.hpp"
#include "opencv2\imgproc\imgproc.hpp"
#include "opencv2\core\base.hpp"
#include "opencv2\core\mat.hpp"
#include "opencv2\core\mat.inl.hpp"
#include "opencv2\core\types_c.h"


#include <vector>
#include "string.h"
#include <iostream>
#include <algorithm>
#include "time.h"
#include <Windows.h>

using namespace std;
using namespace cv;
#define PI 3.14

#define IMAGE_WIDTH 256
#define IMAGE_HEIGHT 256
#define IMAGE_CHANNELS 3




class ImageDLL{
public:
	ImageDLL();
	~ImageDLL();
	static IplImage* TheImage;

	void ResizeImage(IplImage* img);
	 void Gray(IplImage *ColorImage,int flag);//

	 void Threshold(Mat src, Mat dst, double thresh, double maxval, int type);

	 void  ImageDenoising(Mat src, Mat dst, int chose);

	 void sharpen(const Mat& img, Mat& result);

	 void colorhistogram(IplImage * src);
	 void Canny(IplImage* pImg, IplImage* pCannyImg);
	 void corners(IplImage *srcImage, IplImage *dstImage);
	 void Houghline(IplImage* src, IplImage* color_dst);
	 void Houghcircle(IplImage* img, IplImage* dst);
	 CvSeq* Hougrectangular(IplImage* img, CvMemStorage* storage);
	 void Edgehistogram(IplImage *src);
	 int vidstreamEdgedet(int argc, char ** argv);
	 void Textureextraction(IplImage* img, IplImage* dst);

	 int GetPTileThreshold(int *HistGram);
	 int GetOSTUThreshold(int *HistGram);
	 int Get1DMaxEntropyThreshold(int* HistGram);
	 int GetMeanThreshold(int *HistGram);

	 void LogEnhance(IplImage* img, IplImage* dst);
	 void ExpEnhance(IplImage* img, IplImage* dst);
	 void ExporeOver(IplImage* img, IplImage* dst);
	 void OnEqialization(IplImage* img, IplImage* dst);
	 void HistogramSpecification(int* src, int* dst, int* histMap);
	 void CDM(int M, int N, CvMat *mat);
	 bool GrayLinearTransform(IplImage* src, IplImage* dst, uchar dstStart, uchar dstEnd);
	 Mat HighPass(Mat img);
};

#endif