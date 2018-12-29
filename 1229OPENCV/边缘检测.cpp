#include<iostream>
#include<string>

#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/features2d/features2d.hpp>

using namespace std;
using namespace cv;

//边缘检测（canny，sobel，laplacian）
//边缘检测的步骤：
//1、滤波  消除噪声
//2、增强  是边界轮廓更加明显
//3、检测  选出边缘点

int main5(int argv, char **argc)
{
	Mat src_gray;
	Mat src = imread("G:123/123.jpg");

	resize(src,src,Size(0,0),0.3,0.3);
	if (!src.data || src.empty()) //两种方式
	{
		cout << "图像读取错误！请检查路径！" << endl;
	}
	if (src.channels() > 1)
	{
		cvtColor(src, src_gray, CV_BGR2GRAY);
	}

	Mat dst_canny;
	Mat dst_blur;
	Mat dst_gau;

	blur(src_gray,dst_blur,Size(3,3));
	GaussianBlur(src,dst_gau,Size(3,3),0);

	Canny(dst_blur,dst_canny,3,9);
	
	for (int i = 0;i < dst_canny.rows;i++)
	{
		for (int j = 0;j < dst_canny.cols;j++)
		{
			dst_canny.at<uchar>(i, j) = 255 - dst_canny.at<uchar>(i, j);
		}
	}
	imshow("dst_canny", dst_canny);
	
	Mat grad_x, grad_y;
	Mat dst_sobel;
	Sobel(src_gray,grad_x,-1,1,0);
	convertScaleAbs(grad_x,grad_x);

	Sobel(src_gray,grad_y,-1,0,1);
	convertScaleAbs(grad_y,grad_y);

	addWeighted(grad_x,0.5,grad_y,0.5,0, dst_sobel);
	
	for (int i = 0;i < dst_sobel.rows;i++)
	{
		for (int j = 0;j < dst_sobel.cols;j++)
		{
			dst_sobel.at<uchar>(i, j) = 255 - dst_sobel.at<uchar>(i, j);
		}
	}

	imshow("dst_sobel", dst_sobel);

	waitKey(0);


	return  0;
}

