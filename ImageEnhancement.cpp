#include "stdafx.h"
 #include "impl.h"


IplImage *ImageDLL::LogEnhance(IplImage* img, IplImage* dst)		 //对数图像增强算法
{
	// 由于oldPixel:[1,256],则可以先保存一个查找表  
	uchar lut[256] = { 0 };

	double temp = 255 / log(256);

	for (int i = 0; i < 255; i++)
	{
		lut[i] = (uchar)(temp* log(i + 1) + 0.5);
	}

	for (int row = 0; row < img->height; row++)
	{
		uchar *data = (uchar*)img->imageData + row* img->widthStep;
		uchar *dstData = (uchar*)dst->imageData + row* dst->widthStep;

		for (int col = 0; col < img->width; col++)
		{
			for (int k = 0; k < img->nChannels; k++)
			{
				uchar t1 = data[col*img->nChannels + k];
				dstData[col*img->nChannels + k] = lut[t1];
			}
		}
	}
	return dst;
}

IplImage *ImageDLL::ExpEnhance(IplImage* img, IplImage* dst)	 //指数图像增强算法
{
	// 由于oldPixel:[1,256],则可以先保存一个查找表  
	uchar lut[256] = { 0 };

	double temp = 1.0 / 255.0;

	for (int i = 0; i < 255; i++)
	{
		lut[i] = (uchar)(temp*i*i + 0.5);
	}

	for (int row = 0; row < img->height; row++)
	{
		uchar *data = (uchar*)img->imageData + row* img->widthStep;
		uchar *dstData = (uchar*)dst->imageData + row* dst->widthStep;

		for (int col = 0; col < img->width; col++)
		{
			for (int k = 0; k < img->nChannels; k++)
			{
				uchar t1 = data[col*img->nChannels + k];
				dstData[col*img->nChannels + k] = lut[t1];
			}
		}
	}
	return dst;
}

IplImage *ImageDLL::ExporeOver(IplImage* img, IplImage* dst)	// 曝光过度处理算法（图像反转）
{
	for (int row = 0; row < img->height; row++)
	{
		uchar *data = (uchar*)img->imageData + row* img->widthStep;
		uchar *dstData = (uchar*)dst->imageData + row* dst->widthStep;
		for (int col = 0; col < img->width; col++)
		{
			for (int k = 0; k < img->nChannels; k++)
			{
				uchar t1 = data[col*img->nChannels + k];
				uchar t2 = 255 - t1;
				dstData[col*img->nChannels + k] = t1 - t2;
			}
		}
	}
	return dst;
}

IplImage *ImageDLL::OnEqialization(IplImage* img, IplImage* dst)		   //直方图均衡化算法
{
	IplImage *gray = 0;
	cvCvtColor(img, gray, CV_BGR2GRAY);
	cvEqualizeHist(gray, dst);
	cvReleaseImage(&gray);
	return dst;
}

void ImageDLL::HistogramSpecification(int* src, int* dst, int* histMap)		  //直方图规定化算法
{
	int x = 0, y = 0, i = 0;
	int minX = 0;
	int minValue = 0;
	int srcMin[256][256];
	short lastStartY = 0, lastEndY = 0, startY = 0, endY = 0;
	//计算原始图像到目标图像累积直方图各灰度级的差的绝对值  
	for (y = 0; y < 256; y++)
	{
		for (x = 0; x < 256; x++)
		{
			srcMin[x][y] = abs(src[y] - dst[x]);
		}
	}

	//GML映射  
	for (x = 0; x < 256; x++)
	{
		minValue = srcMin[x][0];
		for (y = 0; y < 256; y++)
		{
			if (minValue > srcMin[x][y])
			{
				endY = y;
				minValue = srcMin[x][y];
			}
		}

		if (startY != lastStartY || endY != lastEndY)
		{
			for (i = startY; i <= endY; i++)
			{
				histMap[i] = x;//建立映射关系  
			}
			lastStartY = startY;
			lastEndY = endY;
			startY = lastEndY + 1;
		}
	}
}


void ImageDLL::CDM(int M, int N, CvMat *mat)							//同态滤波
{
	int width = mat->rows;
	int height = mat->cols;

	if (M != width && N != height)
	{
		//	cout $amp;
		return;
	}

	if (cvGetElemType(mat) < CV_32F)
	{
		//cout $amp;
		return;
	}

	CvMat *U, *V;
	U = cvCreateMat(M, N, CV_32FC1);
	V = cvCreateMat(M, N, CV_32FC1);

	for (int u = 0; u < M; ++u)
	for (int v = 0; v < N; ++v)
	{
		float tm1, tm2;
		tm1 = (float)((u > cvRound(M / 2))*u - M);
		tm2 = (float)((v > cvRound(N / 2))*v - N);

		*((float *)CV_MAT_ELEM_PTR(*U, u, v)) = tm1;

		*((float *)CV_MAT_ELEM_PTR(*V, u, v)) = tm2;
	}

	for (int u = 0; u < M; ++u)
	for (int v = 0; v < N; ++v)
	{
		float t1, t2;
		t1 = CV_MAT_ELEM(*U, float, u, v);
		t2 = CV_MAT_ELEM(*V, float, u, v);
		*((float *)CV_MAT_ELEM_PTR(*mat, u, v)) = sqrt(t1*t1 + t2*t2);

	}

}
////////////////////////////create high pass filter//////////////////////////////////////////////
// for using gaussian high pass filter
void lpfilter(CvMat *matD, CvMat *matH, float D0, float rH, float rL, float c)
{
	if (D0 < 0)
	{
		//cout$amp;	return;
	}

	int w = matD->rows;
	int h = matD->cols;

	for (int u = 0; u < w; ++u)
	for (int v = 0; v < h; ++v)
	{
		float Elem_D, h;
		Elem_D = CV_MAT_ELEM(*matD, float, u, v);

		h = exp(-(c*Elem_D*Elem_D) / (2 * D0*D0));
		h = (rH - rL)*(1 - h) + rL;

		*((float *)CV_MAT_ELEM_PTR(*matH, u, v)) = h;


	}
}
//////////////////////////fftshift////////////////////////////////////////////////
// Rearrange the quadrants of Fourier image so that the origin is at
// the image center
// src & dst arrays of equal size & type
// code comes from 
void cvShiftDFT(CvArr * src_arr, CvArr * dst_arr)
{
	CvMat * tmp;
	CvMat q1stub, q2stub;
	CvMat q3stub, q4stub;
	CvMat d1stub, d2stub;
	CvMat d3stub, d4stub;
	CvMat * q1, *q2, *q3;
//	CvMat * d1, *d2, *d3, *d4;

	CvSize size = cvGetSize(src_arr);
	CvSize dst_size = cvGetSize(dst_arr);
	int cx, cy;

	if (dst_size.width != size.width ||
		dst_size.height != size.height){
		cvError(CV_StsUnmatchedSizes, "cvShiftDFT", "Source and Destination arrays must have equal sizes", __FILE__, __LINE__);
	}

	if (src_arr == dst_arr){
		tmp = cvCreateMat(size.height / 2, size.width / 2, cvGetElemType(src_arr));
	}

	cx = size.width / 2;
	cy = size.height / 2; // image center

	q1 = cvGetSubRect(src_arr, &q1stub, cvRect(0, 0, cx, cy));
	q2 = cvGetSubRect(src_arr, &q2stub, cvRect(cx, 0, cx, cy));
	q3 = cvGetSubRect(src_arr, &q3stub, cvRect(cx, cy, cx, cy));
}

//线性灰度增强 g(x,y)=[(d-c)/(b-a)]*(f(x,y)-a)+c
IplImage *ImageDLL::GrayLinearTransform(IplImage* src, IplImage* dst, uchar dstStart, uchar dstEnd)
{
	uchar* srcData = (uchar*)src->imageData;
	//获取图像最大最小灰度(分情况可简化为255-0)
	int imageMax, imageMin;
	imageMax = imageMin = srcData[0];
	for (int x = 0; x < src->height; x++)
	for (int y = 0; y < src->width; y++)
	{
		int value = srcData[x*src->widthStep + y];
		if (imageMax < value)
			imageMax = value;
		else
		if (imageMin>value)
			imageMin = value;
	}
	float linearRatio = float(dstEnd - dstStart) / (imageMax - imageMin);
	for (int x = 0; x < src->height; x++)
	for (int y = 0; y < src->width; y++)
	{
		int step = src->widthStep;
		int a = srcData[x*step + y];
		int bb = linearRatio*(a - imageMin) + dstStart;
		dst->imageData[x*step + y] = bb;
	}
	return dst;
}

