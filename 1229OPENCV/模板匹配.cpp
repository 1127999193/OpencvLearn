#include<iostream>
#include<string>
#include<Windows.h>

#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/features2d/features2d.hpp>

using namespace std;
using namespace cv;

//模板匹配就是在一幅图像中寻找另一幅模板图像最匹配的部分的技术
int main8(int argv, char **argc)
{
	Mat src_gray;
	Mat src = imread("G:123/bask.jpeg");
	Mat mask = imread("G:123/hu.jpg");

	if (!src.data || src.empty()) //两种方式
	{
		cout << "图像读取错误！请检查路径！" << endl;
		return 1;
	}
	if (src.channels() > 1)
	{
		cvtColor(src, src_gray, CV_BGR2GRAY);
	}
	//resize(src, src, Size(0, 0), 0.5, 0.5);
	Mat result;
	int result_cols = src.cols - mask.cols + 1;
	int result_rows = src.rows - mask.rows + 1;
	
	result.create(result_cols, result_rows,CV_32FC1);


	//  CV_TM_SQDIFF 平方差匹配法，最好的匹配为0，值越大匹配越差
	//	CV_TM_SQDIFF_NORMED 归一化平方差匹配法
	//	CV_TM_CCORR 相关匹配法，采用乘法操作，数值越大表明匹配越好
	//	CV_TM_CCORR_NORMED 归一化相关匹配法
	//	CV_TM_CCOEFF 相关系数匹配法，最好的匹配为1， - 1表示最差的匹配
	//	CV_TM_CCOEFF_NORMED 归一化相关系数匹配法
	//比较结果的映射图像,其必须为单通道，32位浮点数
	//原图为W * H，模板为 w * h，result尺寸为（W-w+1）*（H-h+1）

	matchTemplate(src,mask,result,CV_TM_SQDIFF_NORMED);

	//矩阵归一化
	//alpha:归一化后的最小值，默认值0
	//beta:归一化后的最大值，默认0
	//norm_type:归一化类型
	//dtype默认值-1，此数为负，输出矩阵和src有同样类型
	normalize(result,result,0,1,NORM_MINMAX,-1,Mat());

	double minval = -1;
	double maxval;

	Point minLoc;
	Point maxLoc;
	Point matLoc;

	cout << "匹配度" << minval << endl;
	
	//寻找最值
	//minval ：返回最小值的指针
	//minLoc：返回最小值位置的指针

	minMaxLoc(result,&minval,&maxval,&minLoc,&maxLoc,Mat());

	cout << "匹配度" << minval << endl;

	matLoc = minLoc;

	rectangle(src,matLoc,Point(matLoc.x+mask.cols,matLoc.y+mask.rows),Scalar(255,0,255),10,0);

	imshow("src",src);

	waitKey(0);
	return 0;

}