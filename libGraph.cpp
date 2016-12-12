#include "stdafx.h"
#include "libGraph.h"
#include "impl.h"

#include <string>
using namespace std;

ImageDLL* instance;

static IplImage* getImg(string &path){	
	IplImage* newImg = cvLoadImage(path.c_str());
	return newImg;
}

static void saveImg(string& path,IplImage* to_be_saved){
	cvSaveImage(path.c_str(), to_be_saved);
}

void init(){
	instance = new ImageDLL;
}

void Gray(string& src_path, string& dest_path, int flag)//
{
	auto newImg = getImg(src_path);
	IplImage* GrayImage = new IplImage;
	instance->Gray(newImg, flag);//
	saveImg(dest_path, newImg);
	delete GrayImage;
	return;
}

/*void Threshold(Mat src, Mat dst, double thresh, double maxval, int type)
{
	return instance->Threshold(src, dst, thresh,  maxval, type);
}

 void  ImageDenoising(Mat src, Mat dst, int chose)
{
	return instance->ImageDenoising(src, dst, chose);
}

 void sharpen(const Mat& img, Mat& result)
{
	return instance->sharpen(img, result);
}

 void colorhistogram(IplImage * src)
{
	return instance->colorhistogram(src);
}
 void Canny(IplImage* pImg, IplImage* pCannyImg)
{
	return instance->Canny(pImg, pCannyImg);
}
 void corners(IplImage *srcImage, IplImage *dstImage)
{
	return instance->corners(srcImage, dstImage);
}
 void Houghline(IplImage* src, IplImage* color_dst)
{
	return instance->Houghline(src, color_dst);
}
 void Houghcircle(IplImage* img, IplImage* dst)
{
	return instance->Houghcircle(img, dst);
}
 CvSeq* Hougrectangular(IplImage* img, CvMemStorage* storage)
{
	return instance->Hougrectangular(img,  storage);
}
 void Edgehistogram(IplImage *src)
{
	return instance->Edgehistogram(src);
}
 int vidstreamEdgedet(int argc, char ** argv)
{
	return instance->vidstreamEdgedet(argc, argv);
}
 void Textureextraction(IplImage* img, IplImage* dst)
{
	return instance->Textureextraction(img, dst);
}

 int GetPTileThreshold(int *HistGram)
{
	return instance->GetPTileThreshold(HistGram);
}
 int GetOSTUThreshold(int *HistGram)
{
	return instance->GetOSTUThreshold(HistGram);
}
 int Get1DMaxEntropyThreshold(int* HistGram)
{
	return instance->Get1DMaxEntropyThreshold(HistGram);
}
 int GetMeanThreshold(int *HistGram)
{
	return instance->GetMeanThreshold(HistGram);
}

 void LogEnhance(IplImage* img, IplImage* dst)
{
	return instance->LogEnhance( img, dst);
}
 void ExpEnhance(IplImage* img, IplImage* dst)
{
	return instance->ExpEnhance(img,dst);
}
 void ExporeOver(IplImage* img, IplImage* dst)
{
	return instance->ExporeOver(img, dst);
}
 void OnEqialization(IplImage* img, IplImage* dst)
{
	return instance->OnEqialization(img, dst);
}
 void HistogramSpecification(int* src, int* dst, int* histMap)
{
	return instance->HistogramSpecification(src,  dst, histMap);
}
 void CDM(int M, int N, CvMat *mat)
{
	return instance->CDM(M,  N,  *mat);
}
 bool GrayLinearTransform(IplImage* src, IplImage* dst, uchar dstStart, uchar dstEnd)
{
	return instance->GrayLinearTransform(src,dst, dstStart, dstEnd);
}
 Mat HighPass(Mat img)
{
	return instance->HighPass(img);
}
*/