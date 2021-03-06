﻿#include "stdafx.h"
 #include "impl.h"

#define WIDTHBYTES(bits) (((bits) + 31) / 32 * 4)

Mat ImageDLL::sharpen(const Mat& img, Mat& result)		  //拉普拉斯算子
{
	result.create(img.size(), img.type());
	//处理边界内部的像素点, 图像最外围的像素点应该额外处理
	for (int row = 1; row < img.rows - 1; row++)
	{
		//前一行像素点
		const uchar* previous = img.ptr<const uchar>(row - 1);
		//待处理的当前行
		const uchar* current = img.ptr<const uchar>(row);
		//下一行
		const uchar* next = img.ptr<const uchar>(row + 1);
		uchar *output = result.ptr<uchar>(row);
		int ch = img.channels();
		int starts = ch;
		int ends = (img.cols - 1) * ch;
		for (int col = starts; col < ends; col++)
		{
			//输出图像的遍历指针与当前行的指针同步递增, 以每行的每一个像素点的每一个通道值为一个递增量, 因为要考虑到图像的通道数
			*output++ = saturate_cast<uchar>(5 * current[col] - current[col - ch] - current[col + ch] - previous[col] - next[col]);
		}
	} //end loop
	//处理边界, 外围像素点设为 0
	result.row(0).setTo(Scalar::all(0));
	result.row(result.rows - 1).setTo(Scalar::all(0));
	result.col(0).setTo(Scalar::all(0));
	result.col(result.cols - 1).setTo(Scalar::all(0));
	return result;
}



