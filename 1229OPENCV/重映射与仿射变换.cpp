#include<iostream>
#include<string>
#include<Windows.h>

#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/features2d/features2d.hpp>

using namespace std;
using namespace cv;


#define ANGLE_START -45  //旋转角度的开始
#define ANGLE_END  36  //旋转角度的结束 
#define ANGLE_STEP 2 //旋转角度步长


//重映射就是把一幅图像的某个位置的像素放置到另一个图片中指定的位置
//remap()
//仿射变换
int main7(int argv, char **argc)
{
	Mat src_gray;
	Mat src = imread("G:123/456.jpg");

	resize(src, src, Size(0, 0), 0.5, 0.5);
	if (!src.data || src.empty()) //两种方式
	{
		cout << "图像读取错误！请检查路径！" << endl;
	}
	if (src.channels() > 1)
	{
		cvtColor(src, src_gray, CV_BGR2GRAY);
	}
	Mat map_x, map_y;
	
	map_x.create(src.size(),CV_32FC1);
	map_y.create(src.size(), CV_32FC1);
	
	Mat dst_remap;

	for (int i = 0; i < src.rows;i++)
	{
		for (int j = 0;j < src.cols;j++)
		{
			//(rows,cols)
			map_y.at<float>(i, j) = static_cast<float>(src.rows - i);
			map_x.at<float>(i, j) = static_cast<float>(src.cols - j);
		}
	}
	remap(src,dst_remap,map_x,map_y,CV_INTER_LINEAR);
	imshow("dst_remap",dst_remap);


	//仿射变换:向量空间进行一次线性变换并接上一个平移，变换为另一个向量空间的过程
	//变换为的特点：
	//相对位置关系保持不变，平行线依旧是平行想，且直线上的点位置顺序保持不变
	//一个任意的仿射变换都可以表示为乘以一个矩阵（线性变换）接着再加上一个向量（平移）的形式
	//旋转：线性变换
	//平移：向量加
	//缩放：线性变换

	Mat dst_warp, dst_warprotate;

	Point2f srcPoint[3];
	Point2f dstPoint[3];

	//第一种变换的的调用方式；三点法
	
	srcPoint[0] = Point2f(0,0);
	srcPoint[1] = Point2f(0, src.rows - 10);
	srcPoint[2] = Point2f(src.rows - 10, 0);

	dstPoint[0] = Point2f(0, src.rows*0.3);
	dstPoint[1] = Point2f(src.cols*0.25, src.rows*0.75);
	dstPoint[2] = Point2f(src.cols*0.75, src.rows*0.25);


	Mat m1 = getAffineTransform(srcPoint, dstPoint);//由三个点计算变换矩阵

	warpAffine(src,dst_warp,m1,src.size());
	imshow("dst_warp", dst_warp);


	//第二种仿射变换，直接指定角度和比例
	
	Point2f center(src.cols/2,src.rows/2);

	double angle = 45;//逆时针旋转45度
	double scale = 0.5;//缩放比例

	for(int i = ANGLE_START;i<ANGLE_END;i+=ANGLE_STEP)
	{
		angle = i;
		Mat m2 = getRotationMatrix2D(center, angle, scale);
		warpAffine(src, dst_warprotate, m2, src.size());
		imshow("dst_warprotate", dst_warprotate);
	}

	waitKey(0);
	return 0;

}


