#include "stdafx.h"
#include "impl.h"


void ImageDLL::Gray(IplImage *ColorImage, int flag) //IplImage* GrayImage,
{	  
	CvSize size = cvSize((*ColorImage).width, (*ColorImage).height);

	IplImage    *GrayImage1 = NULL;                        //从1~5代表5中不同权值的结果  
	IplImage    *GrayImage2 = NULL;
	IplImage    *GrayImage3 = NULL;
	IplImage    *GrayImage4 = NULL;
	IplImage    *GrayImage5 = NULL;
	IplImage    *GrayImage6 = NULL;
	IplImage    *GrayImage7 = NULL;


	if (ColorImage == NULL)
		return;

	GrayImage1 = cvCreateImage(size, IPL_DEPTH_8U, 1);
	GrayImage2 = cvCreateImage(size, IPL_DEPTH_8U, 1);
	GrayImage3 = cvCreateImage(size, IPL_DEPTH_8U, 1);
	GrayImage4 = cvCreateImage(size, IPL_DEPTH_8U, 1);
	GrayImage5 = cvCreateImage(size, IPL_DEPTH_8U, 1);
	GrayImage6 = cvCreateImage(size, IPL_DEPTH_8U, 1);
	GrayImage7 = cvCreateImage(size, IPL_DEPTH_8U, 1);

	CvMat* pGrayMat1 = NULL;         //定义与图像关联的数据指针  
	CvMat* pGrayMat2 = NULL;
	CvMat* pGrayMat3 = NULL;
	CvMat* pGrayMat4 = NULL;
	CvMat* pGrayMat5 = NULL;
	CvMat* pGrayMat6 = NULL;
	CvMat* pGrayMat7 = NULL;

	pGrayMat1 = cvCreateMat((*ColorImage).height, (*ColorImage).width, IPL_DEPTH_8U);
	pGrayMat2 = cvCreateMat((*ColorImage).height, (*ColorImage).width, IPL_DEPTH_8U);
	pGrayMat3 = cvCreateMat((*ColorImage).height, (*ColorImage).width, IPL_DEPTH_8U);
	pGrayMat4 = cvCreateMat((*ColorImage).height, (*ColorImage).width, IPL_DEPTH_8U);
	pGrayMat5 = cvCreateMat((*ColorImage).height, (*ColorImage).width, IPL_DEPTH_8U);
	pGrayMat6 = cvCreateMat((*ColorImage).height, (*ColorImage).width, IPL_DEPTH_8U);
	pGrayMat7 = cvCreateMat((*ColorImage).height, (*ColorImage).width, IPL_DEPTH_8U);

	BYTE data1;       //中间过程变量  
	BYTE data2;
	BYTE data3;
	BYTE data4;
	BYTE data5;
	BYTE data6;
	BYTE data7;
	for (int j = 0; j < (*ColorImage).height; j++)
	{
		for (int i = 0; i < (*ColorImage).width; i++)
		{
			data1 = (BYTE)ColorImage->imageData[j*ColorImage->widthStep + i * 3];     //B分量  
			data2 = (BYTE)ColorImage->imageData[j*ColorImage->widthStep + i * 3 + 1]; //G分量  
			data3 = (BYTE)ColorImage->imageData[j*ColorImage->widthStep + i * 3 + 2]; //R分量  
			data4 = max(data1, max(data2, data3));    //最大值  
			data5 = (BYTE)((data1 + data2 + data3) / 3);
			data6 = (BYTE)(0.072169*data1 + 0.715160*data2 + 0.212671*data3);
			data7 = (BYTE)(0.11*data1 + 0.59*data2 + 0.30*data3);
			
			cvmSet(pGrayMat1, j, i, data1);
			cvmSet(pGrayMat2, j, i, data2);
			cvmSet(pGrayMat3, j, i, data3);
			cvmSet(pGrayMat4, j, i, data4);
			cvmSet(pGrayMat5, j, i, data5);
			cvmSet(pGrayMat6, j, i, data6);
			cvmSet(pGrayMat7, j, i, data7);
		}
	}
	cvConvert(pGrayMat1, GrayImage1);
	cvConvert(pGrayMat2, GrayImage2);
	cvConvert(pGrayMat3, GrayImage3);
	cvConvert(pGrayMat4, GrayImage4);
	cvConvert(pGrayMat5, GrayImage5);
	cvConvert(pGrayMat6, GrayImage6);
	cvConvert(pGrayMat7, GrayImage7);

	switch (flag)
	{
	case 1:TheImage = GrayImage1; break;
	case 2:TheImage = GrayImage2; break;
	case 3:TheImage = GrayImage3; break;
	case 4:TheImage = GrayImage4; break;
	case 5:TheImage = GrayImage5; break;
	case 6:TheImage = GrayImage6; break;
	case 7:TheImage = GrayImage7; break;

	default:
		break;
	}


	cvReleaseImage(&ColorImage);
	cvReleaseImage(&GrayImage1);
	cvReleaseImage(&GrayImage2);
	cvReleaseImage(&GrayImage3);
	cvReleaseImage(&GrayImage4);
	cvReleaseImage(&GrayImage5);
	cvReleaseImage(&GrayImage6);
	cvReleaseImage(&GrayImage7);

	cvReleaseMat(&pGrayMat1);
	cvReleaseMat(&pGrayMat2);
	cvReleaseMat(&pGrayMat3);
	cvReleaseMat(&pGrayMat4);
	cvReleaseMat(&pGrayMat5);
	cvReleaseMat(&pGrayMat6);
	cvReleaseMat(&pGrayMat7);
}