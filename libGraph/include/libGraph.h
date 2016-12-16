#ifndef __LIB_GRAPH_H__
#define __LIB_GRAPH_H__

#include<string>
//class IplImage;
//class Mat;

extern "C" {
	__declspec(dllexport) void init();

	__declspec(dllexport) void Gray(std::string& src_path, std::string& dest_path, int flag);

/*	__declspec(dllexport) void Threshold(Mat src, Mat dst, double thresh, double maxval, int type);

	__declspec(dllexport) void ImageDenoising(Mat src, Mat dst, int chose);

	__declspec(dllexport) void sharpen(const Mat& img, Mat& result);

	__declspec(dllexport) void colorhistogram(IplImage * src);
	__declspec(dllexport) void Canny(IplImage* pImg, IplImage* pCannyImg);
	__declspec(dllexport) void corners(IplImage *srcImage, IplImage *dstImage);
	__declspec(dllexport) void Houghline(IplImage* src, IplImage* color_dst);
	__declspec(dllexport) void Houghcircle(IplImage* img, IplImage* dst);
	__declspec(dllexport) CvSeq* Hougrectangular(IplImage* img, CvMemStorage* storage);
	__declspec(dllexport) void Edgehistogram(IplImage *src);
	__declspec(dllexport) int vidstreamEdgedet(int argc, char ** argv);
	__declspec(dllexport) void Textureextraction(IplImage* img, IplImage* dst);

	__declspec(dllexport) int GetPTileThreshold(int *HistGram);
	__declspec(dllexport) int GetOSTUThreshold(int *HistGram);
	__declspec(dllexport) int Get1DMaxEntropyThreshold(int* HistGram);
	__declspec(dllexport) int GetMeanThreshold(int *HistGram);

	__declspec(dllexport) void LogEnhance(IplImage* img, IplImage* dst);
	__declspec(dllexport) void ExpEnhance(IplImage* img, IplImage* dst);
	__declspec(dllexport) void ExporeOver(IplImage* img, IplImage* dst);
	__declspec(dllexport) void OnEqialization(IplImage* img, IplImage* dst);
	__declspec(dllexport) void HistogramSpecification(int* src, int* dst, int* histMap);
	__declspec(dllexport) void CDM(int M, int N, CvMat *mat);
	__declspec(dllexport) bool GrayLinearTransform(IplImage* src, IplImage* dst, uchar dstStart, uchar dstEnd);
	__declspec(dllexport) Mat HighPass(Mat img);*/
}

#endif