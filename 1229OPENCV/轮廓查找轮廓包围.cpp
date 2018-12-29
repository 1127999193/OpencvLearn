#include<iostream>
#include<string>
#include<Windows.h>

#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/features2d/features2d.hpp>

using namespace std;
using namespace cv;


// findContours
// drawContours
//

//  返回指定点集最外部矩形边界： boundingRect()
//  寻找给定的点集可旋转的最小包围矩形：minAreaRect()
//  寻找最小包围圆形：minEnclosingCircle()
//  用椭圆拟合二维点集：fitEllipse()
//  逼近多边形曲线： approxPolyDP()
//

RNG rng(12345);

int maina(int argv, char **argc)
{
	Mat src_gray;
	Mat src = imread("G:123/456.jpg");

	if (!src.data) //两种方式
	{
		cout << "图像读取错误！请检查路径！" << endl;
		return 1;
	}
	if (src.channels() > 1)
	{
		cvtColor(src, src_gray, CV_BGR2GRAY);
	}

	double thresh_size = ( 100 / 4) * 2 + 1; //自适应二值化阈值
	Mat dst_th;
	threshold(src_gray, dst_th, 150, 255, CV_THRESH_BINARY_INV);
	//blocksize:周围领域的大小
	// C 减去改值
	//adaptiveThreshold(src_gray,dst_th,255,CV_ADAPTIVE_THRESH_GAUSSIAN_C,CV_THRESH_BINARY_INV, thresh_size, thresh_size/3);

	vector<vector<Point>> contours;

	findContours(dst_th,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE); //找轮廓

	vector<vector<Point>> contours1;
	for (int i = 0; i < contours.size(); ++i)
	{
		contours1.push_back(contours[i]);
	}

	Mat hole(src_gray.size(), CV_8U, Scalar(0)); //遮罩图层
	drawContours(hole, contours1, -1, Scalar(255), CV_FILLED); //在遮罩图层上，用白色像素填充轮廓，得到MASK
	namedWindow("My hole");
	imshow("My hole", hole);
	Mat crop(src.rows, src.cols, CV_8UC3);
	src.copyTo(crop, hole);//将原图像拷贝进遮罩图层
	imshow("My warpPerspective", crop);


	/// 多边形逼近轮廓 + 获取矩形和圆形边界框
	vector<vector<Point> > contours_poly(contours.size());
	vector<Rect> boundRect(contours.size());
	vector<Point2f>center(contours.size());
	vector<float>radius(contours.size());

	for (int i = 0; i < contours.size(); i++)
	{
		approxPolyDP(Mat(contours[i]), contours_poly[i], 3, true);
		boundRect[i] = boundingRect(Mat(contours_poly[i]));
		minEnclosingCircle(contours_poly[i], center[i], radius[i]);
	}

	/// 画多边形轮廓 + 包围的矩形框 + 圆形框
	Mat drawing = Mat::zeros(src_gray.size(), CV_8UC3);
	for (int i = 0; i< contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(drawing, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point());
		rectangle(drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0);
		circle(drawing, center[i], (int)radius[i], color, 2, 8, 0);
	}
	imshow("Contours", drawing);


	//矩：图像的特征信息，比如大小、位置、方向等
	//提供函数计算图像的矩：
	//矩的重心、主轴、面积等特征的计算 moment()
	//计算轮廓的面积：contourArea()
	//计算轮廓的长度：arcLenggth()
	//从图像中计算出来的矩通常描述了图像不同种类的几何特征如：大小、灰度、方向、形状等，
	//图像矩广泛应用于模式识别、目标分类、目标识别与防伪估计、图像编码与重构等领域。
	

	// moments()计算图像中的中兴矩
	// contoursArea计算轮廓面积
	// arcLength计算轮廓或曲线长度
	//

	vector<Moments> mu(contours.size());
	for(int i = 0;i < contours.size();i++)
	{
		//array:输入数组，可以是光栅图像(单通道，8 - bit或浮点型二维数组), 或者是一个二维数组(1 X N或N X 1), 二维数组类型为Point或Point2f
		//binaryImage : 默认值是false，如果为true，则所有非零的像素都会按值1对待，也就是说相当于对图像进行了二值化处理，阈值为1，此参数仅对图像有效。
			
		mu[i] = moments(contours[i], false);
	}

	vector<Point2f> mc(contours.size());

	for (int i = 0;i < contours.size();i++)
	{
		mc[i] = Point2f(mu[i].m10/mu[i].m00,mu[i].m01/mu[i].m00);
	}

	for (int i = 0; i < contours.size(); i++)
	{
		//contourArea()
		//contour:是一个向量，二维点，可以是vector或Mat类型
		//oriented : 有默认值false，面向区域标识符，如果为true，该函数返回一个带符号的面积，其正负取决于轮廓的方向(顺时针还是逆时针)。
		//根据这个特性可以根据面积的符号来确定轮廓的位置。如果是默认值false，则面积以绝对值的形式返回.
	
		//arcLength()
		//curve:输入二维点集，可以是vector或Mat类型
		//closed:曲线是否封闭的标志位，true则封闭否则不封闭

		printf(" * Contour[%d] - Area (M_00) = %.2f - Area OpenCV: %.2f - Length: %.2f \n", i, mu[i].m00, contourArea(contours[i]), arcLength(contours[i], true));
	}

	waitKey(0);
	return 0;
}


