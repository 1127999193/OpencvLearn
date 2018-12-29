#include<iostream>
#include<string>

#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/features2d/features2d.hpp>

using namespace std;
using namespace cv;

//膨胀、腐蚀、开闭运算

//开运算：先腐蚀再膨胀，用于消除小物体  MORPH_OPEN
//闭运算：先碰撞再腐蚀，用于排除小型黑洞  MORPH_CLOSE
//形态学梯度：膨胀图与腐蚀图之差，用于保留物体的边缘轮廓  MORPH_GRADIENT
//顶帽：原图像与开运算图之差，用于分离比邻近点亮的斑块    MORPH_TOPHAT
//黑帽：闭运算与原图像之差，用于分离比临近点暗一些的斑块  MORPH_BLACKHAT

//MORPH_ERODE   
//MORPH_DILATE
int main3(int argv,char **argc)
{
	Mat src = imread("G:123/456.jpg");
	
	if(src.data == NULL)
	{
		cout << "源文件打开失败" << endl;
		cout << "请检查文件路径" << endl;
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

