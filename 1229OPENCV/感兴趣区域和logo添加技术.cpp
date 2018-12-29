#include<iostream>
#include<string>
#include<Windows.h>

#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/features2d/features2d.hpp>

using namespace std;
using namespace cv;

//定义ROI区域有两种方法：
//第一种：指定矩形的坐标、并且规定好他的长宽
//第二种;指定感兴趣的行或列的范围

int main11(int argv, char **argc)
{
	Mat src_gray;
	Mat src = imread("G:123/bask.jpeg");
	Mat logo = imread("G:123/logoroi.jpg");

	if (!src.data || logo.empty()) //两种方式
	{
		cout << "图像读取错误！请检查路径！" << endl;
		return 1;
	}
	if (src.channels() > 1)
	{
		cvtColor(src, src_gray, CV_BGR2GRAY);
	}

	resize(logo,logo,Size(200,200));
	Mat ROI = src(Rect(200,200,100,300));
	//rect：x坐标，y坐标，长，高
	Mat ROI2 = src(Range(200,200+100),Range(200,200+300));
	//Range两个形参分别是，行、行+偏移量，列、列+偏移量

	rectangle(src,Rect(200,200,100,50),Scalar(0,255,0),4,10);


	Mat dst_ROI;
	//感兴趣区域拷贝：
	src(Rect(200, 200, 100, 50)).copyTo(dst_ROI);

	Mat dst_ROI2;
	dst_ROI2 = src(Rect(200, 200, 100, 50));

	imshow("ROI", ROI);
	imshow("ROI2", ROI2);
	imshow("src", src);
	imshow("dst_ROI", dst_ROI);
	imshow("dst_ROI2", dst_ROI2);



	//添加logo
	Mat imageROI = src(Rect(10,10,logo.cols,logo.rows));

	if (logo.depth() != imageROI.depth())
	{
		cout << "深度不同" << endl;
		waitKey(0);

	}
	Mat dst_logo;
	addWeighted(logo,0.3,imageROI,0.7,0, imageROI);

	imshow("dst_logo", src);

	waitKey(0);
	return 0;


}
