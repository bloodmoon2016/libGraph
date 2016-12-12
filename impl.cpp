#include "stdafx.h"
#include "impl.h"

ImageDLL::ImageDLL(){}

ImageDLL::~ImageDLL(){}

void ImageDLL::ResizeImage(IplImage* img)
{
	
	// 读取图片的宽和高
	int w = img->width;
	int h = img->height;

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

	// 设置 TheImage 的 ROI 区域，用来存入图片 img
	cvSetImageROI(TheImage, cvRect(tlx, tly, nw, nh));

	// 对图片 img 进行缩放，并存入到 TheImage 中
	cvResize(img, TheImage);

	// 重置 TheImage 的 ROI 准备读入下一幅图片
	cvResetImageROI(TheImage);
}