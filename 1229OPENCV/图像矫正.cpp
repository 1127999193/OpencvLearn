#include<iostream>
#include<string>
#include<Windows.h>

#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/features2d/features2d.hpp>

using namespace std;
using namespace cv;

//����������ȡ�Ľ����㷨
//����ֱ��̽��Ľ����㷨

//ͼ�������
//������ȡ
//����任
//ROI����Ȥ����

//�ܽᴦ���裺
//1��ͼƬ�ҶȻ�
//2����ֵ��ֵ��
//3���������
//4��Ѱ�������İ�Χ���󣬲��һ�ȡ�Ƕ�
//5�����ݽǶȽ�����ת����
//6������ת���ͼ�����������ȡ
//7���������ڵ�ͼ������ٳ�������Ϊһ�Ŷ���ͼ��

//
int main(int argv, char **argc)
{
	Mat src_gray;
	Mat src = imread("G:123/100.jpg");

	if (!src.data) //���ַ�ʽ
	{
		cout << "ͼ���ȡ��������·����" << endl;
		return 1;
	}
	if (src.channels() > 1)
	{
		cvtColor(src, src_gray, CV_BGR2GRAY);
	}
	Mat dst_th;
	threshold(src_gray, dst_th, 10, 255, CV_THRESH_BINARY_INV);

	vector<vector<Point>> contours;
	findContours(dst_th, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

	cout << contours.size() << endl;

	for (int i = 0;i < contours.size();i++)
	{
		CvPoint2D32f rectpoint[4];

		CvBox2D rect = minAreaRect(Mat(contours[i]));
		cvBoxPoints(rect, rectpoint);   //��ȡ4�����������

		float angle = rect.angle;
		cout << angle << endl;

		int liney = sqrt((rectpoint[1].y - rectpoint[0].y)*(rectpoint[1].y - rectpoint[0].y) + (rectpoint[1].x - rectpoint[0].x)*(rectpoint[1].x - rectpoint[0].x));
		int linex = sqrt((rectpoint[3].y - rectpoint[0].y)*(rectpoint[3].y - rectpoint[0].y) + (rectpoint[3].x - rectpoint[0].x)*(rectpoint[3].x - rectpoint[0].x));
	
		if(liney * linex < 600)
		{
			continue;
		}

		if (liney > linex)
		{
			angle = angle + 90;
		}

		Mat  dst_roi = Mat::zeros(src.size(), CV_8UC3);
		Mat  dst_draw;
		drawContours(dst_draw,contours,-1,Scalar(255),CV_FILLED);

		src.copyTo(dst_roi, dst_draw);

		imshow("dst_roi", dst_roi);
		
		Mat dst_roation;

		dst_roation.create(src.size(),CV_8UC1);
		dst_roation.setTo(0);

		Point2f center = rect.center;
		Mat M = getRotationMatrix2D(center, angle, 0);
		warpAffine(src, dst_roation,M,src.size());
		imshow("dst_roation", dst_roation);
	}

 

	waitKey(0);
	return 0;
}


