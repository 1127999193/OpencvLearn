#include<iostream>
#include<string>
#include<Windows.h>

#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/features2d/features2d.hpp>

using namespace std;
using namespace cv;

//����ROI���������ַ�����
//��һ�֣�ָ�����ε����ꡢ���ҹ涨�����ĳ���
//�ڶ���;ָ������Ȥ���л��еķ�Χ

int main11(int argv, char **argc)
{
	Mat src_gray;
	Mat src = imread("G:123/bask.jpeg");
	Mat logo = imread("G:123/logoroi.jpg");

	if (!src.data || logo.empty()) //���ַ�ʽ
	{
		cout << "ͼ���ȡ��������·����" << endl;
		return 1;
	}
	if (src.channels() > 1)
	{
		cvtColor(src, src_gray, CV_BGR2GRAY);
	}

	resize(logo,logo,Size(200,200));
	Mat ROI = src(Rect(200,200,100,300));
	//rect��x���꣬y���꣬������
	Mat ROI2 = src(Range(200,200+100),Range(200,200+300));
	//Range�����βηֱ��ǣ��С���+ƫ�������С���+ƫ����

	rectangle(src,Rect(200,200,100,50),Scalar(0,255,0),4,10);


	Mat dst_ROI;
	//����Ȥ���򿽱���
	src(Rect(200, 200, 100, 50)).copyTo(dst_ROI);

	Mat dst_ROI2;
	dst_ROI2 = src(Rect(200, 200, 100, 50));

	imshow("ROI", ROI);
	imshow("ROI2", ROI2);
	imshow("src", src);
	imshow("dst_ROI", dst_ROI);
	imshow("dst_ROI2", dst_ROI2);



	//���logo
	Mat imageROI = src(Rect(10,10,logo.cols,logo.rows));

	if (logo.depth() != imageROI.depth())
	{
		cout << "��Ȳ�ͬ" << endl;
		waitKey(0);

	}
	Mat dst_logo;
	addWeighted(logo,0.3,imageROI,0.7,0, imageROI);

	imshow("dst_logo", src);

	waitKey(0);
	return 0;


}
