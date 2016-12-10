#include "stdafx.h" 
 #include "impl.h"

#define cvCvtPixToPlane cvSplit
#define cvQueryHistValue_2D( hist, idx0, idx1 )   cvGetReal2D( (hist)->bins, (idx0), (idx1) )
#define cvCvtPlaneToPix cvMerge

void ImageDLL::colorhistogram(IplImage * src)                     //颜色直方图提取
{
	IplImage* hsv = cvCreateImage(cvGetSize(src), 8, 3);
	IplImage* h_plane = cvCreateImage(cvGetSize(src), 8, 1);
	IplImage* s_plane = cvCreateImage(cvGetSize(src), 8, 1);
	IplImage* v_plane = cvCreateImage(cvGetSize(src), 8, 1);
	IplImage* planes[] = { h_plane, s_plane };

	/** H 分量划分为16个等级，S分量划分为8个等级*/
	int h_bins = 16, s_bins = 8;
	int hist_size[] = { h_bins, s_bins };

	/** H 分量的变化范围*/
	float h_ranges[] = { 0, 180 };

	/** S 分量的变化范围*/
	float s_ranges[] = { 0, 255 };
	float* ranges[] = { h_ranges, s_ranges };

	/** 输入图像转换到HSV颜色空间*/
	cvCvtColor(src, hsv, CV_BGR2HSV);
	cvCvtPixToPlane(hsv, h_plane, s_plane, v_plane, 0);

	/** 创建直方图，二维, 每个维度上均分*/
	CvHistogram * hist = cvCreateHist(2, hist_size, CV_HIST_ARRAY, ranges, 1);
	/** 根据H,S两个平面数据统计直方图*/
	cvCalcHist(planes, hist, 0, 0);

	/** 获取直方图统计的最大值，用于动态显示直方图*/
	float max_value;
	cvGetMinMaxHistValue(hist, 0, &max_value, 0, 0);


	/** 设置直方图显示图像*/
	int height = 240;
	int width = (h_bins*s_bins * 6);
	IplImage *hist_img = cvCreateImage(cvSize(width, height), 8, 3);
	cvZero(hist_img);

	/** 用来进行HSV到RGB颜色转换的临时单位图像*/
	IplImage * hsv_color = cvCreateImage(cvSize(1, 1), 8, 3);
	IplImage * rgb_color = cvCreateImage(cvSize(1, 1), 8, 3);
	int bin_w = width / (h_bins * s_bins);
	for (int h = 0; h < h_bins; h++)
	{
		for (int s = 0; s < s_bins; s++)
		{
			int i = h*s_bins + s;
			/** 获得直方图中的统计次数，计算显示在图像中的高度*/
			float bin_val = cvQueryHistValue_2D(hist, h, s);
			int intensity = cvRound(bin_val*height / max_value);

			/** 获得当前直方图代表的颜色，转换成RGB用于绘制*/
			cvSet2D(hsv_color, 0, 0, cvScalar(h*180.f / h_bins, s*255.f / s_bins, 255, 0));
			cvCvtColor(hsv_color, rgb_color, CV_HSV2BGR);
			CvScalar color = cvGet2D(rgb_color, 0, 0);

			cvRectangle(hist_img, cvPoint(i*bin_w, height),
			cvPoint((i + 1)*bin_w, height - intensity),color, -1, 8, 0);
		}
	}
	cvNamedWindow("H-S Histogram", 1);
	cvShowImage("H-S Histogram", hist_img);

	cvWaitKey(0);
}

void ImageDLL::Canny(IplImage* pImg, IplImage* pCannyImg)               //Canny算子对边缘提取
{
	//canny边缘检测
	cvCanny(pImg, pCannyImg, 50, 150, 3);
}

#define MAX_CORNERS 100

void ImageDLL::corners(IplImage *srcImage, IplImage *dstImage)             //角点提取
{
	int cornersCount = MAX_CORNERS;//得到的角点数目
	CvPoint2D32f corners[MAX_CORNERS];//输出角点集合
	IplImage *grayImage = 0, *corners1 = 0, *corners2 = 0;
	int i;
	CvScalar color = CV_RGB(255, 0, 0);
	grayImage = cvCreateImage(cvGetSize(srcImage), IPL_DEPTH_8U, 1);

	//copy the source image to copy image after converting the format
	//复制并转为灰度图像
	cvCvtColor(srcImage, grayImage, CV_BGR2GRAY);

	//create empty images os same size as the copied images
	//两幅临时位浮点图像，cvGoodFeaturesToTrack会用到
	corners1 = cvCreateImage(cvGetSize(srcImage), IPL_DEPTH_32F, 1);
	corners2 = cvCreateImage(cvGetSize(srcImage), IPL_DEPTH_32F, 1);

	cvGoodFeaturesToTrack(grayImage, corners1, corners2, corners, &cornersCount, 0.05,
		30,//角点的最小距离是
		0,//整个图像
		3, 0, 0.4);

	//开始画出每个点
	if (cornersCount>0)
	{
		for (i = 0; i<cornersCount; i++)
		{
			cvCircle(srcImage, cvPoint((int)(corners[i].x), (int)(corners[i].y)), 2, color, 2, CV_AA, 0);
		}
	}
	dstImage = srcImage;

	cvReleaseImage(&grayImage);
	cvReleaseImage(&corners1);
	cvReleaseImage(&corners2);
}

void ImageDLL::Houghline(IplImage* src, IplImage* color_dst)            //Hough直线提取
{
	IplImage* dst;
	CvMemStorage* storage = cvCreateMemStorage(0);
	CvSeq* lines = 0;
	int i;

	dst = cvCreateImage(cvGetSize(src), 8, 1);
	color_dst = cvCreateImage(cvGetSize(src), 8, 3);

	cvCanny(src, dst, 50, 200, 3);
	cvCvtColor(dst, color_dst, CV_GRAY2BGR);

	lines = cvHoughLines2(dst, storage, CV_HOUGH_PROBABILISTIC, 1, CV_PI / 180, 50, 50, 10);
	for (i = 0; i < lines->total; i++)
	{
		CvPoint* line = (CvPoint*)cvGetSeqElem(lines, i);
		cvLine(color_dst, line[0], line[1], CV_RGB(255, 0, 0), 3, CV_AA, 0);
	}
}


void  ImageDLL::Houghcircle(IplImage* img, IplImage* dst)      //Hough圆提取
{
	IplImage* gray = cvCreateImage(cvGetSize(img), 8, 1);
	CvMemStorage* storage = cvCreateMemStorage(0);
	cvCvtColor(img, gray, CV_BGR2GRAY);
	cvSmooth(gray, gray, CV_GAUSSIAN, 5, 15);
	// smooth it, otherwise a lot of false circles may be detected
	CvSeq* circles = cvHoughCircles(gray, storage, CV_HOUGH_GRADIENT, 2, gray->height / 4, 200, 100);
	int i;
	for (i = 0; i < circles->total; i++)
	{
		float* p = (float*)cvGetSeqElem(circles, i);
		cvCircle(img, cvPoint(cvRound(p[0]), cvRound(p[1])), 3, CV_RGB(0, 255, 0), -1, 8, 0);
		cvCircle(img, cvPoint(cvRound(p[0]), cvRound(p[1])), cvRound(p[2]), CV_RGB(255, 0, 0), 3, 8, 0);
		//cout << "圆心坐标x= " << cvRound(p[0]) << endl << "圆心坐标y= " << cvRound(p[1]) << endl;
		//cout << "半径=" << cvRound(p[2]) << endl;
	}
	//cout << "圆数量=" << circles->total << endl;
	dst = img;
}


int thresh = 50;
IplImage* img = 0;
IplImage* img0 = 0;
CvMemStorage* storage = 0;
CvPoint pt[4]; const char* wndname = "Square Detection Demo";

double angle(CvPoint* pt1, CvPoint* pt2, CvPoint* pt0)             //Hough矩形提取
{
	double dx1 = pt1->x - pt0->x;
	double dy1 = pt1->y - pt0->y;
	double dx2 = pt2->x - pt0->x;
	double dy2 = pt2->y - pt0->y;
	return (dx1*dx2 + dy1*dy2) / sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}
CvSeq* ImageDLL::Hougrectangular(IplImage* img, CvMemStorage* storage)
{
	CvSeq* contours;
	int i, c, l, N = 11;
	CvSize sz = cvSize(img->width & -2, img->height & -2);
	IplImage* timg = cvCloneImage(img);
	IplImage* gray = cvCreateImage(sz, 8, 1);
	IplImage* pyr = cvCreateImage(cvSize(sz.width / 2, sz.height / 2), 8, 3);
	IplImage* tgray;
	CvSeq* result;
	double s, t;
	CvSeq* squares = cvCreateSeq(0, sizeof(CvSeq), sizeof(CvPoint), storage);
	cvSetImageROI(timg, cvRect(0, 0, sz.width, sz.height));
	// down-scale and upscale the image to filter out the noise
	cvPyrDown(timg, pyr, 7);
	cvPyrUp(pyr, timg, 7);
	tgray = cvCreateImage(sz, 8, 1);
	// find squares in every color plane of the image
	for (c = 0; c < 3; c++)
	{
		cvSetImageCOI(timg, c + 1);
		cvCopy(timg, tgray, 0);
		for (l = 0; l < N; l++)
		{
			if (l == 0)
			{
				cvCanny(tgray, gray, 0, thresh, 5);
				cvDilate(gray, gray, 0, 1);
			}
			else
			{
				cvThreshold(tgray, gray, (l + 1) * 255 / N, 255, CV_THRESH_BINARY);
			}
			cvFindContours(gray, storage, &contours, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0, 0));
			while (contours)
			{
				result = cvApproxPoly(contours, sizeof(CvContour), storage, CV_POLY_APPROX_DP, cvContourPerimeter(contours)*0.02, 0);
				if (result->total == 4 && fabs(cvContourArea(result, CV_WHOLE_SEQ)) > 1000 && cvCheckContourConvexity(result))
				{
					s = 0;
					for (i = 0; i < 5; i++)
					{
						if (i >= 2)
						{
							t = fabs(angle((CvPoint*)cvGetSeqElem(result, i), (CvPoint*)cvGetSeqElem(result, i - 2), (CvPoint*)cvGetSeqElem(result, i - 1)));
							s = s > t ? s : t;
						}
					}
					if (s < 0.3)
					for (i = 0; i < 4; i++)
						cvSeqPush(squares,
						(CvPoint*)cvGetSeqElem(result, i));
				}
				contours = contours->h_next;
			}
		}
	}
	cvReleaseImage(&gray);
	cvReleaseImage(&pyr);
	cvReleaseImage(&tgray);
	cvReleaseImage(&timg);
	return squares;
}

void ImageDLL::Edgehistogram(IplImage *src)                      //边缘直方图提取
{
	CvHistogram *hist = 0; // define multi_demention histogram
	IplImage* canny;
	CvMat* canny_m;
	IplImage* dx; // the sobel x difference
	IplImage* dy; // the sobel y difference
	CvMat* gradient; // value of gradient
	CvMat* gradient_dir; // direction of gradient
	CvMat* dx_m; // format transform to matrix
	CvMat* dy_m;
	CvMat* mask;
	CvSize  size;
	IplImage* gradient_im;
	int i, j;
	float theta;

	int hdims = 8;     // 划分HIST的个数，越高越精确
	float hranges_arr[] = { -PI / 2, PI / 2 }; // 直方图的上界和下界
	float* hranges = hranges_arr;

	float max_val;  //
	int bin_w;


	cvNamedWindow("Histogram", 0);
	//cvNamedWindow( "src", 0);
	size = cvGetSize(src);
	canny = cvCreateImage(cvGetSize(src), 8, 1);//边缘图像
	dx = cvCreateImage(cvGetSize(src), 32, 1);//x方向上的差分//此处的数据类型为U 不怕溢出吗？
	dy = cvCreateImage(cvGetSize(src), 32, 1);
	gradient_im = cvCreateImage(cvGetSize(src), 32, 1);//梯度图像
	canny_m = cvCreateMat(size.height, size.width, CV_32FC1);//边缘矩阵
	dx_m = cvCreateMat(size.height, size.width, CV_32FC1);
	dy_m = cvCreateMat(size.height, size.width, CV_32FC1);
	gradient = cvCreateMat(size.height, size.width, CV_32FC1);//梯度矩阵
	gradient_dir = cvCreateMat(size.height, size.width, CV_32FC1);//梯度方向矩阵
	mask = cvCreateMat(size.height, size.width, CV_32FC1);//掩码

	cvCanny(src, canny, 60, 180, 3);//边缘检测
	cvConvert(canny, canny_m);//把图像转换为矩阵
	cvSobel(src, dx, 1, 0, 3);// 一阶X方向的图像差分:dx
	cvSobel(src, dy, 0, 1, 3);// 一阶Y方向的图像差分:dy
	cvConvert(dx, dx_m);
	cvConvert(dy, dy_m);
	cvAdd(dx_m, dy_m, gradient); // value of gradient//梯度不是等于根号下x的导数的平方加上y导数的平方吗？
	cvDiv(dx_m, dy_m, gradient_dir); // direction
	for (i = 0; i<size.height; i++)
	for (j = 0; j<size.width; j++)
	{
		if (cvmGet(canny_m, i, j) != 0 && cvmGet(dx_m, i, j) != 0)//此行是什么意思？只看边缘上的方向？
		{
			theta = cvmGet(gradient_dir, i, j);
			theta = atan(theta);
			cvmSet(gradient_dir, i, j, theta);
		}
		else
		{
			cvmSet(gradient_dir, i, j, 0);
		}

	}
	hist = cvCreateHist(1, &hdims, CV_HIST_ARRAY, &hranges, 1);
	// 创建一个指定尺寸的直方图，并返回创建的直方图指针
	IplImage* histimg = cvCreateImage(cvSize(320, 200), 8, 3); // 创建一个图像，通道
	cvZero(histimg); // 清；
	cvConvert(gradient_dir, gradient_im);//把梯度方向矩阵转化为图像
	cvCalcHist(&gradient_im, hist, 0, canny); // 计算直方图
	cvGetMinMaxHistValue(hist, 0, &max_val, 0, 0);  // 只找最大值
	cvConvertScale(hist->bins, hist->bins, max_val ? 255. / max_val : 0., 0);
	// 缩放bin 到区间[0,255] ，比例系数
	cvZero(histimg);
	bin_w = histimg->width / 16;  // hdims: 条的个数，则bin_w 为条的宽度

	// 画直方图
	for (i = 0; i < hdims; i++)
	{
		double val = (cvGetReal1D(hist->bins, i)*histimg->height / 255);
		// 返回单通道数组的指定元素， 返回直方图第i条的大小，val为histimg中的i条的高度
		CvScalar color = CV_RGB(255, 255, 0); //(hsv2rgb(i*180.f/hdims);//直方图颜色
		cvRectangle(histimg, cvPoint(100 + i*bin_w, histimg->height), cvPoint(100 + (i + 1)*bin_w, (int)(histimg->height - val)), color, 1, 8, 0); // 画直方图——画矩形，左下角，右上角坐标
	}
	cvShowImage("Histogram", histimg);
	cvWaitKey(0);

	cvDestroyWindow("Histogram");
	cvReleaseImage(&histimg);
	cvReleaseHist(&hist);
}


int ImageDLL::vidstreamEdgedet(int argc, char ** argv)                // 视频流中边缘检测
{
	IplImage * laplace = 0;
	IplImage * colorlaplace = 0;
	IplImage * planes[3] = { 0, 0, 0 };

	CvCapture *capture = 0;

	//从摄像头读取
	/*if(argc == 1 ||( argc==2 && strlen(argv[1])==1 && isdigit(argv[1][0]) ))
	capture = cvCaptureFromCAM(argc == 2 ? argv[1][0] -'0':0);*/
	//从文件中读取
	/* else if(argc == 2)*/
	capture = cvCaptureFromAVI("1.avi");
	if (!capture)
	{
		fprintf(stderr, "Could not initialize capturing...\n");
		return -1;
	}
	cvNamedWindow("Laplacian", 1);
	cvNamedWindow("video", 1);
	//循环捕捉，直到用户按键跳出循环体
	for (;;)
	{
		IplImage * frame = 0;    //抓起一祯
		frame = cvQueryFrame(capture);
		if (!frame)
			break;
		if (!laplace)
		{
			//创建图像
			for (int i = 0; i<3; i++)
				planes[i] = cvCreateImage(cvSize(frame->width, frame->height), IPL_DEPTH_8U, 1);
			laplace = cvCreateImage(cvSize(frame->width, frame->height), IPL_DEPTH_16S, 1);
			colorlaplace = cvCreateImage(cvSize(frame->width, frame->height), IPL_DEPTH_8U, 3);
		}
		cvCvtPixToPlane(frame, planes[0], planes[1], planes[2], 0);
		for (int i = 0; i<3; i++)
		{
			//交换，如通道变换
			cvLaplace(planes[i], laplace, 3);
			//使用线性变换转换输入函数元素成为无符号整形
			cvConvertScaleAbs(laplace, planes[i], 1, 0);
		}
		cvCvtPlaneToPix(planes[0], planes[1], planes[2], 0, colorlaplace);
		//结构相同（- 顶—左结构,1 - 底—左结构）
		colorlaplace->origin = frame->origin;
		//高斯滤波，平滑图像
		// cvSmooth(colorlaplace, colorlaplace, CV_GAUSSIAN, 1, 0, 0);
		//形态学滤波,闭运算
		cvDilate(colorlaplace, colorlaplace, 0, 1);//膨胀
		cvErode(colorlaplace, colorlaplace, 0, 1);//腐蚀
		cvShowImage("video", frame);
		cvShowImage("Laplacian", colorlaplace);
		if (cvWaitKey(10)>0)
			break;
	}
	cvReleaseCapture(&capture);
	cvDestroyWindow("Laplacian");
	cvDestroyWindow("video");
	return 0;
}


void ImageDLL::Textureextraction(IplImage* img, IplImage* dst)     //纹理提取
{
	int tmp[8] = { 0 };
	int sum = 0; int k = 0;
	CvScalar s;

	uchar* data = (uchar*)img->imageData;
	int step = img->widthStep;
	dst = cvCreateImage(cvSize(img->width, img->height), img->depth, 1);
	dst->widthStep = img->widthStep;
	for (int i = 1; i<img->height - 1; i++)
	for (int j = 1; j<img->width - 1; j++)
	{
		if (data[(i - 1)*step + j - 1]>data[i*step + j]) tmp[0] = 1;
		else tmp[0] = 0;
		if (data[i*step + (j - 1)]>data[i*step + j]) tmp[1] = 1;
		else tmp[1] = 0;
		if (data[(i + 1)*step + (j - 1)]>data[i*step + j]) tmp[2] = 1;
		else tmp[2] = 0;
		if (data[(i + 1)*step + j]>data[i*step + j]) tmp[3] = 1;
		else tmp[3] = 0;
		if (data[(i + 1)*step + (j + 1)]>data[i*step + j]) tmp[4] = 1;
		else tmp[4] = 0;
		if (data[i*step + (j + 1)]>data[i*step + j]) tmp[5] = 1;
		else tmp[5] = 0;
		if (data[(i - 1)*step + (j + 1)]>data[i*step + j]) tmp[6] = 1;
		else tmp[6] = 0;
		if (data[(i - 1)*step + j]>data[i*step + j]) tmp[7] = 1;
		else tmp[7] = 0;
		for (k = 0; k <= 7; k++)
			sum += abs(tmp[k] - tmp[k + 1]);
		sum = sum + abs(tmp[7] - tmp[0]);
		if (sum <= 2)
			s.val[0] = (tmp[0] * 128 + tmp[1] * 64 + tmp[2] * 32 + tmp[3] * 16 + tmp[4] * 8 + tmp[5] * 4 + tmp[6] * 2 + tmp[7]);
		else s.val[0] = 59;
		cvSet2D(dst, i, j, s);
	}
}