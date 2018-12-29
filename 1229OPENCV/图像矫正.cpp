#include<iostream>
#include<string>
#include<Windows.h>

#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/features2d/features2d.hpp>

using namespace std;
using namespace cv;

//基于轮廓提取的矫正算法
//基于直线探测的矫正算法

//图像矫正：
//轮廓提取
//霍夫变换
//ROI感兴趣区域

//总结处理步骤：
//1、图片灰度化
//2、阈值二值化
//3、检测轮廓
//4、寻找轮廓的包围矩阵，并且获取角度
//5、根据角度进行旋转矫正
//6、对旋转后的图像进行轮廓提取
//7、对轮廓内的图像区域抠出来，成为一张独立图像

//
int main(int argv, char **argc)
{
	Mat src_gray;
	Mat src = imread("G:123/100.jpg");

	if (!src.data) //两种方式
	{
		cout << "图像读取错误！请检查路径！" << endl;
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
		cvBoxPoints(rect, rectpoint);   //获取4个顶点的坐标

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


