#include<iostream>
#include<string>

#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/features2d/features2d.hpp>

using namespace std;
using namespace cv;

//滤波分为两大类；线性滤波和非线性滤波
//线性滤波：方框滤波、均值滤波、高斯滤波
//非线性滤波：中值滤波、双边滤波

int main2()
{
	Mat src = imread("G:123/456.jpg");
	if (src.data == NULL)
	{
		cout << "源文件打开失败" << endl;
		cout << "请检查文件路径" << endl;
		return -1;
	}

	//方框滤波
	Mat dst_boxFliter;
	boxFilter(src,dst_boxFliter,-1,Size(3,3));

	imshow("dst_boxFliter", dst_boxFliter);

	//均值滤波
	Mat dst_blur;
	blur(src,dst_blur,Size(3,3));
	imshow("dst_blur", dst_blur);

	//高斯滤波 其中sigma的值越大，图像越模糊
	Mat dst_gau;
	GaussianBlur(src,dst_gau,Size(3,3),0);
	imshow("dst_gau", dst_gau);

	//中值滤波
	//去除脉冲噪声、椒盐噪声的同时有能
	//保留图像的细节
	Mat dst_median;
	medianBlur(src,dst_median,5);
	imshow("dst_median", dst_median);


	//双边滤波
	//[3] 滤波 N越大越平越模糊(2*N+1) sigmas空间越大越模糊sigmar相似因子
	//平滑图像又能保存边缘
	Mat dst_bila;
	bilateralFilter(src,dst_bila,10,10,10);
	waitKey(0);
	return 0;

}