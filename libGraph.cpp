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

void corners(string& src_path, string& dest_path)
{
	auto newImg = getImg(src_path);
	IplImage* dst = new IplImage;
	dst = instance->corners(newImg, dst);
	saveImg(dest_path, dst);
	return;
} 										                                                      

void Houghline(string& src_path, string& dest_path)
{
	auto newImg = getImg(src_path);
	IplImage* dst = new IplImage;
	dst = instance->Houghline(newImg, dst);
	saveImg(dest_path, dst);
	return;
}
 
void Houghcircle(string& src_path, string& dest_path)
{
	auto newImg = getImg(src_path);
	IplImage* dst = new IplImage;
	dst = instance->Houghcircle(newImg, dst);
	saveImg(dest_path, dst);
	return;
}

void Edgehistogram(string& src_path)
{
	auto newImg = getImg(src_path);
	IplImage* dst = new IplImage;
	return instance->Edgehistogram(newImg);
}

void Textureextraction(string& src_path, string& dest_path)
{
	 auto newImg = getImg(src_path);
	 IplImage* dst = new IplImage;
	 dst =instance->Textureextraction(newImg, dst);
	 saveImg(dest_path, dst);
	 return;
}

void LogEnhance(string& src_path, string& dest_path)
{
	 auto newImg = getImg(src_path);
	 IplImage* dst = new IplImage;
	 dst =  instance->LogEnhance(newImg, dst);
	 saveImg(dest_path, dst);
	return;
}

void ExpEnhance(string& src_path, string& dest_path)
{
	auto newImg = getImg(src_path);
	IplImage* dst = new IplImage;
	dst = instance->ExpEnhance(newImg, dst);
	saveImg(dest_path, dst);
	return;
}

void ExporeOver(string& src_path, string& dest_path)
{
	auto newImg = getImg(src_path);
	IplImage* dst = new IplImage;
	dst = instance->ExporeOver(newImg, dst);
	saveImg(dest_path, dst);
	return;
}

void OnEqialization(string& src_path, string& dest_path)
{
	auto newImg = getImg(src_path);
	IplImage* dst = new IplImage;
	dst = instance->OnEqialization(newImg, dst);
	saveImg(dest_path, dst);
	return;
}

void GrayLinearTransform(string& src_path, string& dest_path, uchar dstStart, uchar dstEnd)
{
	 auto newImg = getImg(src_path);
	 IplImage* dst = new IplImage;
	 dst = instance->GrayLinearTransform(newImg, dst, dstStart, dstEnd);
	 saveImg(dest_path, dst);
	 return;
}

