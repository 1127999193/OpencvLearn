#include<iostream>
#include<string>
#include<Windows.h>

#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/features2d/features2d.hpp>

using namespace std;
using namespace cv;

//抠图

int main12(int argv, char **argc)
{
	Mat src_gray;
	Mat src = imread("G:123/bask.jpeg");

	if (!src.data ) //两种方式
	{
		cout << "图像读取错误！请检查路径！" << endl;
		return 1;
	}
	if (src.channels() > 1)
	{
		cvtColor(src, src_gray, CV_BGR2GRAY);
	}

	Mat dst_ROI,dst_mask,dst_mask2;
	Rect ri(100,100,300,200);

	dst_ROI = Mat::zeros(src.size(),CV_8UC1);  //全是零、黑色
	dst_ROI(ri).setTo(255);                    //感兴趣区域设置为白色


	src.copyTo(dst_mask,dst_ROI);
	imshow("dst_mask", dst_mask);


	src.copyTo(dst_mask2);
	dst_mask2.setTo(0,dst_ROI);

	imshow("dst_mask2", dst_mask2);
	waitKey(0);
	return 0;

}



