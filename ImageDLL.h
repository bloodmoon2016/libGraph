// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� IMAGEDLL_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// IMAGEDLL_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef IMAGEDLL_EXPORTS
#define IMAGEDLL_API __declspec(dllexport)
#else
#define IMAGEDLL_API __declspec(dllimport)
#endif

// �����Ǵ� ImageDLL.dll ������
class IMAGEDLL_API CImageDLL {
public:
	CImageDLL(void);
	// TODO:  �ڴ�������ķ�����
};

extern IMAGEDLL_API int nImageDLL;

IMAGEDLL_API int fnImageDLL(void);
