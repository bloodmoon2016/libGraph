#ifndef __LIB_GRAPH_H__
#define __LIB_GRAPH_H__

#include<string>

extern "C" {
	__declspec(dllexport) void init();

	__declspec(dllexport) void Gray(string& src_path, string& dest_path, int flag);	//�ҶȻ���src_path����ͼ��·����dest_pathͼ�񱣴�·����flag�ҶȻ�ѡ��ʽ��1.B����2.G����3.R����4.���ֵ��5.ƽ��ֵ��6.��Ȩƽ��ֵ����

	__declspec(dllexport) void Threshold(string& src_path, string& dest_path, double thresh, double maxval, int type);	   //��ֵ����src_path����ͼ��·����dest_pathͼ�񱣴�·����thresh ��ֵ��maxval���ֵ��type���㷽��

	__declspec(dllexport) void ImageDenoising(string& src_path, string& dest_path, int flag); // ȥ�룬src_path����ͼ��·����dest_pathͼ�񱣴�·����flag��ʽ��1.��˹�˲�2.��ֵ�˲�3.��ֵ�˲�4.˫���˲�5.ά���˲���

	__declspec(dllexport) void sharpen(string& src_path, string& dest_path );	//��

	__declspec(dllexport) void colorhistogram(string& src_path );	//��ɫֱ��ͼ��ȡ

	__declspec(dllexport) void Canny(string& src_path, string& dest_path );		//Canny���ӶԱ�Ե��ȡ
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