#include<iostream>
#include<string>
#include<Windows.h>

#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/features2d/features2d.hpp>
#include<photo/photo.hpp>

using namespace std;
using namespace cv;

//全区域阈值处理 + Mask膨胀处理
/*
int main9(int argv, char **argc)
{
	Mat src_gray;
	Mat src = imread("G:123/red.jpg");

	if (!src.data || src.empty()) //两种方式
	{
		cout << "图像读取错误！请检查路径！" << endl;
		return 1;
	}
	if (src.channels() > 1)
	{
		cvtColor(src, src_gray, CV_BGR2GRAY);
	}

	Mat dst_inpa;
	Mat imagemask=Mat(src.size(),CV_8UC1,Scalar::all(0));

	threshold(src_gray,imagemask,240,255,CV_THRESH_BINARY);

	Mat element = getStructuringElement(MORPH_RECT,Size(3,3));

	dilate(imagemask,imagemask,element);

	//imagemask:图像的掩码，单通道图像，大小跟原图像一致，
	//图像上除了需要修复的部分外其他部分的像素值为0
	//第四个参数：修复算法的邻域半径，用于计算当前像素点的差值
	//第五个参数：修复算法，INPAINT_NS,INPAINT_TELEA
	inpaint(src,imagemask, dst_inpa,1, INPAINT_TELEA);

	imshow("dst_inpa",dst_inpa);
	waitKey(0);
	return 0;
}
*/


Point ptL, ptR; //鼠标画出矩形框的起点和终点
Mat imageSource, imageSourceCopy;
Mat ROI,Gray; //原图需要修复区域的ROI

 //鼠标回调函数
void OnMouse(int event, int x, int y, int flag, void *ustg);
//  event 是CV_EVENT_*变量之一
//  x 和 y 是鼠标指针在图像坐标系的坐标
//  flag 是CV_EVENT_FLAG的组合


//CV_EVENT_MOUSEMOVE = 0,
//CV_EVENT_LBUTTONDOWN = 1,
//CV_EVENT_RBUTTONDOWN = 2,
//CV_EVENT_MBUTTONDOWN = 3,
//CV_EVENT_LBUTTONUP = 4,
//CV_EVENT_RBUTTONUP = 5,
//CV_EVENT_MBUTTONUP = 6,
//CV_EVENT_LBUTTONDBLCLK = 7,
//CV_EVENT_RBUTTONDBLCLK = 8,
//CV_EVENT_MBUTTONDBLCLK = 9

//CV_EVENT_FLAG_LBUTTON = 1,
//CV_EVENT_FLAG_RBUTTON = 2,
//CV_EVENT_FLAG_MBUTTON = 4,
//CV_EVENT_FLAG_CTRLKEY = 8,
//CV_EVENT_FLAG_SHIFTKEY = 16,
//CV_EVENT_FLAG_ALTKEY = 32


//鼠标圈定区域阈值处理+Mask膨胀处理
int main9b()
{
	imageSource = imread("G:123/red.jpg");
	if (!imageSource.data)
	{
		return -1;
	}
	imshow("原图", imageSource);
	//鼠标响应
	setMouseCallback("原图", OnMouse);
	waitKey();
}
void OnMouse(int event, int x, int y, int flag, void *ustg)
{
	if (event == CV_EVENT_LBUTTONDOWN)
	{
		ptL = Point(x, y);
		ptR = Point(x, y);
	}
	if (flag == CV_EVENT_FLAG_LBUTTON)
	{
		ptR = Point(x, y);
		imageSourceCopy = imageSource.clone();
		rectangle(imageSourceCopy, ptL, ptR, Scalar(255, 0, 0));
		imshow("原图", imageSourceCopy);
	}
	if (event == CV_EVENT_LBUTTONUP)
	{
		if (ptL != ptR)
		{
			ROI = imageSource(Rect(ptL, ptR));
			imshow("ROI", ROI);
			waitKey();
		}
	}
	//单击鼠标右键开始图像修复
	if (event == CV_EVENT_RBUTTONDOWN)
	{
		imageSourceCopy = ROI.clone();
		Mat imageGray;
		cvtColor(ROI, imageGray, CV_RGB2GRAY); //转换为灰度图
		Mat imageMask = Mat(ROI.size(), CV_8UC1, Scalar::all(0));

		//通过阈值处理生成Mask
		threshold(imageGray, imageMask, 235, 255, CV_THRESH_BINARY);
		Mat Kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
		dilate(imageMask, imageMask, Kernel);  //对Mask膨胀处理
		inpaint(ROI, imageMask, ROI, 9, INPAINT_TELEA);  //图像修复
		imshow("Mask", imageMask);
		imshow("修复后", imageSource);
	}
}

