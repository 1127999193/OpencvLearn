#include<iostream>
#include<string>
#include<Windows.h>

#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/features2d/features2d.hpp>

using namespace std;
using namespace cv;

//findContours ���ԴӶ�ֵͼ�����ҵ�����
//drawContours ��������

int main10(int argv, char **argc)
{
	Mat src_gray;
	Mat src = imread("G:123/bask.jpeg");

	if (!src.data || src.empty()) //���ַ�ʽ
	{
		cout << "ͼ���ȡ��������·����" << endl;
		return 1;
	}
	if (src.channels() > 1)
	{
		cvtColor(src, src_gray, CV_BGR2GRAY);
	}




	waitKey(0);
	return 0;

}



