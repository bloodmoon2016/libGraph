#ifndef __LIB_GRAPH_H__
#define __LIB_GRAPH_H__

#include<string>

extern "C" {
	__declspec(dllexport) void init();

	__declspec(dllexport) void Gray(string& src_path, string& dest_path, int flag);	//灰度化，src_path载入图像路径，dest_path图像保存路径，flag灰度化选择方式（1.B分量2.G分量3.R分量4.最大值法5.平均值法6.加权平均值法）

	__declspec(dllexport) void Threshold(string& src_path, string& dest_path, double thresh, double maxval, int type);	   //二值化，src_path载入图像路径，dest_path图像保存路径，thresh 阈值，maxval最大值，type运算方法

	__declspec(dllexport) void ImageDenoising(string& src_path, string& dest_path, int flag); // 去噪，src_path载入图像路径，dest_path图像保存路径，flag方式（1.高斯滤波2.中值滤波3.均值滤波4.双边滤波5.维纳滤波）

	__declspec(dllexport) void sharpen(string& src_path, string& dest_path );	//锐化

	__declspec(dllexport) void colorhistogram(string& src_path );	//颜色直方图提取

	__declspec(dllexport) void Canny(string& src_path, string& dest_path );		//Canny算子对边缘提取
	__declspec(dllexport) void corners(string& src_path,string& dest_path);
	__declspec(dllexport) void Houghline(string& src_path, string& dest_path);
	__declspec(dllexport) void Houghcircle(string& src_path, string& dest_path);
	__declspec(dllexport) void Hougrectangular(string& src_path, string& dest_path);
	__declspec(dllexport) void Edgehistogram(string& src_path, string& dest_path);
	__declspec(dllexport) void vidstreamEdgedet(string& src_path, string& dest_path);
	__declspec(dllexport) void Textureextraction(string& src_path, string& dest_path);

	__declspec(dllexport) void GetPTileThreshold(int *HistGram);
	__declspec(dllexport) void GetOSTUThreshold(int *HistGram);
	__declspec(dllexport) void Get1DMaxEntropyThreshold(int* HistGram);
	__declspec(dllexport) void GetMeanThreshold(int *HistGram);

	__declspec(dllexport) void LogEnhance(string& src_path, string& dest_path);
	__declspec(dllexport) void ExpEnhance(string& src_path, string& dest_path);
	__declspec(dllexport) void ExporeOver(string& src_path, string& dest_path);
	__declspec(dllexport) void OnEqialization(string& src_path, string& dest_path);
	__declspec(dllexport) void HistogramSpecification(int* src, int* dst, int* histMap);
	__declspec(dllexport) void CDM(int M, int N, CvMat *mat);
	__declspec(dllexport) void GrayLinearTransform(string& src_path, string& dest_path, uchar dstStart, uchar dstEnd);
	__declspec(dllexport) void HighPass(string& src_path, string& dest_path);
}

#endif