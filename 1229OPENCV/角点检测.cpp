#include<iostream>
#include<string>
#include<Windows.h>

#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/features2d/features2d.hpp>

using namespace std;
using namespace cv;

//���Ƶ㡢ֱ�ߡ�����ͼ��
//���Ƶ��Բ��
//  circle();
//thickness:�������������ʾ���Բ�������Ĵ�ϸ�̶ȣ����򣬱�ʾԲ�Ƿ����
//shift Բ�������Ͱ뾶ֵ��С����λ��


//  ellipse();
//  axes ��ĳ��ȡ�angle ƫת�ĽǶ�
//  start_angle:Բ������ʼ�Ƕ�  end_angle:Բ���ս�Ƕ�

//rectangle();
//line();

//harris�ǵ��⣺
//��һ��ֱ�ӻ��ڻҶ�ͼ�Ľǵ���ȡ�㷨���ȶ��Ըߣ������ֱ�Ǽ�⾫�ȸߡ�
// ȱ����������ٶ���

//ͼ���������ͣ���Ե���ǵ㣨����Ȥ�ؼ��㣩���ߵ�(����Ȥ����)

int threld = 30;
int main15(int argv, char **argc)
{
	Mat src_gray;
	Mat src = imread("G:123/RECT.jpg");

	if (!src.data) //���ַ�ʽ
	{
		cout << "ͼ���ȡ��������·����" << endl;
		return 1;
	}
	if (src.channels() > 1)
	{
		cvtColor(src, src_gray, CV_BGR2GRAY);
	}

	Mat dst_harrier = Mat::zeros(src.size(),CV_32FC1);
	//������������ʾ�����С�����ĸ�������ʾSobel���ӿ׾���С�������������ʾHarris����
	cornerHarris(src_gray, dst_harrier,2,3,0.001);
	normalize(dst_harrier, dst_harrier, 0, 255, NORM_MINMAX, CV_32FC1, Mat());

	convertScaleAbs(dst_harrier,dst_harrier);//תΪ8λ�޷�����
	
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


	//shi-Tomasi�ǵ���  ��harris�㷨�ļ�ǿ�棬����Ҳ�������

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

	//�ǵ���
	//corner_count�������������⵽�Ľǵ���Ŀ
	//quality_level:�����С����ֵ�ĳ˷����ӣ��ɽ���ͼ��ǵ����С��������
	//min_distance�������ӣ��õ��Ľǵ����С���룬ʹ��EUCLIDIAN����
	//mask ROI������Ȥ���򡣺�����ROI�м���ǵ㣬��� mask Ϊ NULL����ѡ������ͼ��
	//block_size : �Ǽ��㵼��������ؾ���ʱָ��������򣬲���С���ڼ���Ľ���ȵ��㣨Ҳ����block_sizeΪ1������Ľ��Ҫ��
	//useHarrisDetector����use_harris��ֵΪ��0������ʹ��Harris�Ľǵ㶨�壻��Ϊ0����ʹ��Shi - Tomasi�Ķ���
	//K����������Hessian����ؾ��󼴶�Hessian����ʽ�����Ȩ�ص�Ȩ��ϵ��
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



