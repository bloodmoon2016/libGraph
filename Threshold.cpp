#include "stdafx.h"
#include <cstdlib>
 #include "impl.h"

void ImageDLL::Threshold(Mat src, Mat dst, double thresh, double maxval, int type)
{
	threshold(src,  dst, thresh,  maxval,  type);
	//第一个参数，src，输入数组，填单通道, 8或32位浮点类型的Mat即可。
	//第二个参数，dst，函数调用后的运算结果存在这里，即这个参数用于存放输出结果，且和第一个参数中的Mat变量有一样的尺寸和类型。
	//第三个参数，double类型的thresh，阈值的具体值。
	//第四个参数，double类型的maxval，当第五个参数阈值类型type取 THRESH_BINARY 或THRESH_BINARY_INV阈值类型时的最大值.
	//第五个参数，int类型的type，阈值类型
	//其它参数很好理解，我们来看看第五个参数，第五参数有以下几种类型
	//0 : THRESH_BINARY  当前点值大于阈值时，取Maxval, 也就是第四个参数，下面再不说明，否则设置为0
	//1 : THRESH_BINARY_INV 当前点值大于阈值时，设置为0，否则设置为Maxval
	//2 : THRESH_TRUNC 当前点值大于阈值时，设置为阈值，否则不改变
	//3 : THRESH_TOZERO 当前点值大于阈值时，不改变，否则设置为0
	//4 : THRESH_TOZERO_INV  当前点值大于阈值时，设置为0，否则不改变
}