#include "stdafx.h"
#include "libGraph.h"
#include "impl.h"

#include <string>
using namespace std;

ImageDLL* instance;


static IplImage* getImg(string &path){	
	IplImage* newImg = cvLoadImage(path.c_str(), -1);
	IplImage* TheImage = cvCreateImage({ 256, 256 }, IPL_DEPTH_8U, 3);
	// 读取图片的宽和高
	int w = newImg->width;
	int h = newImg->height;

	// 找出宽和高中的较大值者
	int max = (w > h) ? w : h;

	// 计算将图片缩放到TheImage区域所需的比例因子
	float scale = (float)((float)max / 256.0f);

	// 缩放后图片的宽和高
	int nw = (int)(w / scale);
	int nh = (int)(h / scale);

	// 为了将缩放后的图片存入 TheImage 的正中部位，需计算图片在 TheImage 左上角的期望坐标值
	int tlx = (nw > nh) ? 0 : (int)(256 - nw) / 2;
	int tly = (nw > nh) ? (int)(256 - nh) / 2 : 0;

	// 设置 TheImage 的 ROI 区域，用来存入图片 newImg
	cvSetImageROI(TheImage, cvRect(tlx, tly, nw, nh));

	// 对图片 newImg 进行缩放，并存入到 TheImage 中
	cvResize(newImg, TheImage);
	return TheImage;
}

static void saveImg(string& path,IplImage* to_be_saved){
	cvSaveImage(path.c_str(), to_be_saved);
}

void init(){
	instance = new ImageDLL;
}


void Gray(string& src_path, string& dest_path, int flag)
{
	auto TheImage = getImg(src_path);
	//IplImage* GrayImage = new IplImage;
	instance->Gray(TheImage, flag);//GrayImage,
	saveImg(dest_path, TheImage);
	//delete GrayImage;
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