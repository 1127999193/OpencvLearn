#include<iostream>
#include<string>
#include<Windows.h>

#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/features2d/features2d.hpp>

using namespace std;
using namespace cv;

//绘制点、直线、几何图形
//绘制点和圆：
//  circle();
//thickness:如果是正数，表示组成圆的线条的粗细程度，否则，表示圆是否被填充
//shift 圆心坐标点和半径值的小数点位数


//  ellipse();
//  axes 轴的长度、angle 偏转的角度
//  start_angle:圆弧的起始角度  end_angle:圆弧终结角度

//rectangle();
//line();

//harris角点检测：
//是一种直接基于灰度图的角点提取算法，稳定性高，尤其对直角检测精度高。
// 缺点就是运算速度慢

//图像特征类型：边缘、角点（感兴趣关键点）、斑点(感兴趣区域)

int threld = 30;
int main15(int argv, char **argc)
{
	Mat src_gray;
	Mat src = imread("G:123/RECT.jpg");

	if (!src.data) //两种方式
	{
		cout << "图像读取错误！请检查路径！" << endl;
		return 1;
	}
	if (src.channels() > 1)
	{
		cvtColor(src, src_gray, CV_BGR2GRAY);
	}

	Mat dst_harrier = Mat::zeros(src.size(),CV_32FC1);
	//第三个参数表示邻域大小，第四个参数表示Sobel算子孔径大小，第五个参数表示Harris参数
	cornerHarris(src_gray, dst_harrier,2,3,0.001);
	normalize(dst_harrier, dst_harrier, 0, 255, NORM_MINMAX, CV_32FC1, Mat());

	convertScaleAbs(dst_harrier,dst_harrier);//转为8位无符号型
	
	for (int j = 0;j < dst_harrier.rows;j++)
	{
		for (int i = 0;i < dst_harrier.cols;i++)
		{
			if (dst_harrier.at<uchar>(j, i) > threld)
			{
				//circle(src,Point(j,i),2,Scalar(0,255,255),2,8);
			}
		}
	}
	imshow("dst_harrier", dst_harrier);
	imshow("src", src);


	//shi-Tomasi角点检测  是harris算法的加强版，性能也有所提高

	Mat src_shi = src.clone();
	Mat srcgray_shi = src_gray.clone();
	vector<Point2f> corners;
	int maxCorners =23;
	double qualityLevel = 0.01;
	double minDistance = 10;
	int blockSize = 3;
	bool useHarrisDetector = false;
	double k = 0.04;
	RNG rng(12345);

	//角点检测
	//corner_count：输出参数，检测到的角点数目
	//quality_level:最大最小特征值的乘法因子，可接受图像角点的最小质量因子
	//min_distance限制因子，得到的角点的最小距离，使用EUCLIDIAN距离
	//mask ROI：感兴趣区域。函数在ROI中计算角点，如果 mask 为 NULL，则选择整个图像
	//block_size : 是计算导数的自相关矩阵时指定点的领域，采用小窗口计算的结果比单点（也就是block_size为1）计算的结果要好
	//useHarrisDetector：当use_harris的值为非0，则函数使用Harris的角点定义；若为0，则使用Shi - Tomasi的定义
	//K：用于设置Hessian自相关矩阵即对Hessian行列式的相对权重的权重系数
	goodFeaturesToTrack(srcgray_shi, corners, maxCorners, qualityLevel, minDistance, Mat(), blockSize, useHarrisDetector, k);

	int r = 4;
	for (int i = 0; i < corners.size(); i++)
	{
		circle(src_shi, corners[i], r, Scalar(rng.uniform(0, 255), rng.uniform(0, 255),
		rng.uniform(0, 255)), -1, 8, 0);
	}
	imshow("src_shi", src_shi);
	waitKey(0);
	return 0;

}



