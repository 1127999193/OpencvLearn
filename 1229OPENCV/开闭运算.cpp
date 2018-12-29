#include<iostream>
#include<string>

#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/features2d/features2d.hpp>

using namespace std;
using namespace cv;

//���͡���ʴ����������

//�����㣺�ȸ�ʴ�����ͣ���������С����  MORPH_OPEN
//�����㣺����ײ�ٸ�ʴ�������ų�С�ͺڶ�  MORPH_CLOSE
//��̬ѧ�ݶȣ�����ͼ�븯ʴͼ֮����ڱ�������ı�Ե����  MORPH_GRADIENT
//��ñ��ԭͼ���뿪����ͼ֮����ڷ�����ڽ������İ߿�    MORPH_TOPHAT
//��ñ����������ԭͼ��֮����ڷ�����ٽ��㰵һЩ�İ߿�  MORPH_BLACKHAT

//MORPH_ERODE   
//MORPH_DILATE
int main3(int argv,char **argc)
{
	Mat src = imread("G:123/456.jpg");
	
	if(src.data == NULL)
	{
		cout << "Դ�ļ���ʧ��" << endl;
		cout << "�����ļ�·��" << endl;
		return -1;
	}

	cvtColor(src, src, CV_BGR2GRAY);

	Mat element = getStructuringElement(MORPH_RECT,Size(9,9));
	Mat dst_mor;
	morphologyEx(src,dst_mor, MORPH_GRADIENT,element);

	imshow("dst_mor", dst_mor);

	waitKey(0);
	return 0;

}

