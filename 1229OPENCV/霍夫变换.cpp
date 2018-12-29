#include<iostream>
#include<string>

#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/features2d/features2d.hpp>

using namespace std;
using namespace cv;

// 霍夫变换：识别图像中的几何形状

// HoughLines  标准霍夫线变换、多尺度霍夫线变换
// HoughLinesP 累计概率霍夫线变换
// HoughCircles 霍夫圆变换

int main6(int argv, char **argc)
{
	Mat src_gray;
	Mat src = imread("G:123/line.jpg");

	resize(src, src, Size(0, 0), 0.5, 0.5);
	if (!src.data || src.empty()) //两种方式
	{
		cout << "图像读取错误！请检查路径！" << endl;
	}
	if (src.channels() > 1)
	{
		cvtColor(src, src_gray, CV_BGR2GRAY);
	}

	Mat dst_gau, dst_can,dst_hou,dst_houp,dst_cir;

	GaussianBlur(src_gray,dst_gau,Size(3,3),0);

	Canny(dst_gau,dst_can,6,18);
	dst_hou = dst_can.clone();
	dst_houp = dst_can.clone();
	dst_cir = dst_can.clone();


	vector<Vec2f> lines;
	HoughLines(dst_can,lines,1,CV_PI/180,100);
	
	//依次画出每条线段
	for (size_t i = 0; i < lines.size(); i++)
	{
		float rho = lines[i][0]; //就是圆的半径r
		float theta = lines[i][1]; //就是直线的角度
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a * rho, y0 = b * rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));

		line(dst_hou, pt1, pt2, Scalar(55, 100, 195), 1, LINE_AA); //Scalar函数用于调节线段颜色，就是你想检测到的线段显示的是什么颜色
	}
	imshow("边缘检测后的图", dst_can);
	imshow("最终效果图", dst_hou);


	vector<Vec4i> lines_i;
	//与HoughLines不同的是，HoughLinesP得到lines的是含有直线上点的坐标的，所以下面进行划线时就不再需要自己求出两个点来确定唯一的直线了
	HoughLinesP(dst_can, lines_i, 1, CV_PI / 360, 80, 0, 0);//注意第五个参数，为阈值

	//依次画出每条线段
	for (size_t i = 0; i < lines_i.size(); i++)
	{
		Vec4i l = lines_i[i];

		line(dst_houp, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(186, 88, 255), 1, LINE_AA); //Scalar函数用于调节线段颜色
		imshow("最终效果图p", dst_houp);
	}


	//【4】进行霍夫圆变换  
	vector<Vec3f> circles;
	HoughCircles(dst_can, circles, CV_HOUGH_GRADIENT, 1.5, 10, 200, 150, 0, 0); //注意第七的参数为阈值，可以自行调整，值越大，检测的圆更精准

																				 //【5】依次在图中绘制出圆  
	for (size_t i = 0; i < circles.size(); i++)
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		//绘制圆心  
		circle(dst_cir, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		//绘制圆轮廓  
		circle(dst_cir, center, radius, Scalar(155, 50, 255), 3, 8, 0);
	}

	//【6】显示效果图    
	imshow("【效果图】", dst_cir);


	waitKey(0);
	return 0;

}





