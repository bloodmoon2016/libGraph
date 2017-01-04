#include "stdafx.h"
#include "impl.h"
#include "libGraph.h"


#include <string>
using namespace std;

ImageDLL* instance;


static IplImage* getImg(string &path){	
	IplImage* newImg = cvLoadImage(path.c_str(), -1);
	return newImg;
}

static Mat getMat(string &path){
	Mat newMat = imread(path.c_str(), -1);
	return newMat;
}

static void saveImg(string& path,IplImage* to_be_saved){
	cvSaveImage(path.c_str(), to_be_saved);
}

static void saveMat(string& path, Mat to_be_saved){
	imwrite(path.c_str(), to_be_saved);
}

void init(){
	instance = new ImageDLL;
}

void Gray(string& src_path, string& dest_path, int flag)
{
	auto newImg = getImg(src_path);
	IplImage* dst = new IplImage;
	dst=instance->Gray(newImg, flag);
	saveImg(dest_path, dst);
	return;
}

void Threshold(string& src_path, string& dest_path, double thresh, double maxval, int type)
{
	auto newMat = getMat(src_path);
	Mat dst;
	dst = instance->Threshold(newMat, dst, thresh, maxval, type);
	saveMat(dest_path, dst);
	return;
}

void  ImageDenoising(string& src_path, string& dest_path, int flag)
{
	auto newMat = getMat(src_path);
	Mat dst;
	dst = instance->ImageDenoising(newMat, dst, flag);
	saveMat(dest_path, dst);
	return;
}

void sharpen(string& src_path, string& dest_path)
{
	auto newMat = getMat(src_path);
	Mat dst;
	dst = instance->sharpen(newMat, dst);
	saveMat(dest_path, dst);
	return;
}

void colorhistogram(string& src_path)
{
	auto newImg = getImg(src_path);
	return instance->colorhistogram(newImg);
}

void Canny(string& src_path, string& dest_path)
{
	auto newImg = getImg(src_path);
	IplImage* dst = new IplImage;
	dst = instance->Canny(newImg, dst);
	saveImg(dest_path, dst);
	return;
}

 										                                                      

/*
 
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