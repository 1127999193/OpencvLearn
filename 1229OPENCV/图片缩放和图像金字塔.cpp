#include<iostream>
#include<string>

#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/features2d/features2d.hpp>

using namespace std;
using namespace cv;


//缩小图像使用CV_INTER_AREA来插值
//放大图像使用CV_INTER_LINEAR来插值


//下采样将步骤：
//对图像进行高斯内核卷积
//将所有偶数行和列去除

//下采样就是图像压缩，会丢失图像信息。

//上采样步骤：
//将图像在每个方向放大为原来的两倍，新增的行和列用0填充；
//使用先前同样的内核（乘以4）与放大后的图像卷积，获得新增像素的近似值。

//上下采样都会让图像变得模糊
int main4(int argv, char **argc)
{
	Mat src_gray;
	Mat src = imread("G:123/456.jpg");

	if (!src.data || src.empty()) //两种方式
	{
		cout << "图像读取错误！请检查路径！" << endl;
	}
	if (src.channels() > 1)
	{
		cvtColor(src, src_gray, CV_BGR2GRAY);
	}
	//图像缩放的两种方式
	
	//resize(src,src,Size(500,500));
	//resize(src, src, Size(0, 0), 0.5, 0.5);

	Mat dst_up, dst_down;

	pyrUp(src,dst_up,Size(src.cols*2,src.rows*2));
	pyrDown(src, dst_down, Size(src.cols * 0.5, src.rows * 0.5));

	imshow("dst_down", dst_down);
	waitKey(0);
	return 0;
}


