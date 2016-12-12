#include "stdafx.h"
#include "impl.h"


void ImageDLL::Gray(IplImage *ColorImage, int flag)//
{	  
	CvSize ImgSize;
	ImgSize.height = IMAGE_HEIGHT;
	ImgSize.width = IMAGE_WIDTH;
	TheImage = cvCreateImage(ImgSize, IPL_DEPTH_8U, IMAGE_CHANNELS);

	IplImage  *GrayImage;
	ResizeImage(ColorImage);

	IplImage    *GrayImage1;                        //从1~5代表5中不同权值的结果  
	IplImage    *GrayImage2;
	IplImage    *GrayImage3;
	IplImage    *GrayImage4;
	IplImage    *GrayImage5;
	IplImage    *GrayImage6;
	IplImage    *GrayImage7;


	if (ColorImage == NULL)
		return;

	GrayImage1 = cvCreateImage(cvGetSize(TheImage), 8, 1);
	GrayImage2 = cvCreateImage(cvGetSize(TheImage), 8, 1);
	GrayImage3 = cvCreateImage(cvGetSize(TheImage), 8, 1);
	GrayImage4 = cvCreateImage(cvGetSize(TheImage), 8, 1);
	GrayImage5 = cvCreateImage(cvGetSize(TheImage), 8, 1);
	GrayImage6 = cvCreateImage(cvGetSize(TheImage), 8, 1);
	GrayImage7 = cvCreateImage(cvGetSize(TheImage), 8, 1);

	CvMat* pGrayMat1 = NULL;         //定义与图像关联的数据指针  
	CvMat* pGrayMat2 = NULL;
	CvMat* pGrayMat3 = NULL;
	CvMat* pGrayMat4 = NULL;
	CvMat* pGrayMat5 = NULL;
	CvMat* pGrayMat6 = NULL;
	CvMat* pGrayMat7 = NULL;

	pGrayMat1 = cvCreateMat(TheImage->height, TheImage->width, IPL_DEPTH_8U);
	pGrayMat2 = cvCreateMat(TheImage->height, TheImage->width, IPL_DEPTH_8U);
	pGrayMat3 = cvCreateMat(TheImage->height, TheImage->width, IPL_DEPTH_8U);
	pGrayMat4 = cvCreateMat(TheImage->height, TheImage->width, IPL_DEPTH_8U);
	pGrayMat5 = cvCreateMat(TheImage->height, TheImage->width, IPL_DEPTH_8U);
	pGrayMat6 = cvCreateMat(TheImage->height, TheImage->width, IPL_DEPTH_8U);
	pGrayMat7 = cvCreateMat(TheImage->height, TheImage->width, IPL_DEPTH_8U);

	BYTE data1;       //中间过程变量  
	BYTE data2;
	BYTE data3;
	BYTE data4;
	BYTE data5;
	BYTE data6;
	BYTE data7;
	for (int j = 0; j < TheImage->height; j++)
	{
		for (int i = 0; i < TheImage->width; i++)
		{
			data1 = (BYTE)TheImage->imageData[j*TheImage->widthStep + i * 3];     //B分量  
			data2 = (BYTE)TheImage->imageData[j*TheImage->widthStep + i * 3 + 1]; //G分量  
			data3 = (BYTE)TheImage->imageData[j*TheImage->widthStep + i * 3 + 2]; //R分量  
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
			cvmSet(pGrayMat7, j, i, data6);
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
	case 1:GrayImage = GrayImage1; break;
	case 2:GrayImage = GrayImage2; break;
	case 3:GrayImage = GrayImage3; break;
	case 4:GrayImage = GrayImage4; break;
	case 5:GrayImage = GrayImage5; break;
	case 6:GrayImage = GrayImage6; break;
	case 7:GrayImage = GrayImage7; break;

	default:
		break;
	}
	ResizeImage(GrayImage);

	cvReleaseImage(&ColorImage);
	cvReleaseImage(&GrayImage);
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