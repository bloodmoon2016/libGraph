// ImageDLL.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "ImageDLL.h"


// ���ǵ���������һ��ʾ��
IMAGEDLL_API int nImageDLL=0;

// ���ǵ���������һ��ʾ����
IMAGEDLL_API int fnImageDLL(void)
{
	return 42;
}

// �����ѵ�����Ĺ��캯����
// �й��ඨ�����Ϣ������� ImageDLL.h
CImageDLL::CImageDLL()
{
	return;
}
