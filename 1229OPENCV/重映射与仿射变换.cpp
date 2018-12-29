#include<iostream>
#include<string>
#include<Windows.h>

#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/features2d/features2d.hpp>

using namespace std;
using namespace cv;


#define ANGLE_START -45  //��ת�ǶȵĿ�ʼ
#define ANGLE_END  36  //��ת�ǶȵĽ��� 
#define ANGLE_STEP 2 //��ת�ǶȲ���


//��ӳ����ǰ�һ��ͼ���ĳ��λ�õ����ط��õ���һ��ͼƬ��ָ����λ��
//remap()
//����任
int main7(int argv, char **argc)
{
	Mat src_gray;
	Mat src = imread("G:123/456.jpg");

	resize(src, src, Size(0, 0), 0.5, 0.5);
	if (!src.data || src.empty()) //���ַ�ʽ
	{
		cout << "ͼ���ȡ��������·����" << endl;
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


	//����任:�����ռ����һ�����Ա任������һ��ƽ�ƣ��任Ϊ��һ�������ռ�Ĺ���
	//�任Ϊ���ص㣺
	//���λ�ù�ϵ���ֲ��䣬ƽ����������ƽ���룬��ֱ���ϵĵ�λ��˳�򱣳ֲ���
	//һ������ķ���任�����Ա�ʾΪ����һ���������Ա任�������ټ���һ��������ƽ�ƣ�����ʽ
	//��ת�����Ա任
	//ƽ�ƣ�������
	//���ţ����Ա任

	Mat dst_warp, dst_warprotate;

	Point2f srcPoint[3];
	Point2f dstPoint[3];

	//��һ�ֱ任�ĵĵ��÷�ʽ�����㷨
	
	srcPoint[0] = Point2f(0,0);
	srcPoint[1] = Point2f(0, src.rows - 10);
	srcPoint[2] = Point2f(src.rows - 10, 0);

	dstPoint[0] = Point2f(0, src.rows*0.3);
	dstPoint[1] = Point2f(src.cols*0.25, src.rows*0.75);
	dstPoint[2] = Point2f(src.cols*0.75, src.rows*0.25);


	Mat m1 = getAffineTransform(srcPoint, dstPoint);//�����������任����

	warpAffine(src,dst_warp,m1,src.size());
	imshow("dst_warp", dst_warp);


	//�ڶ��ַ���任��ֱ��ָ���ǶȺͱ���
	
	Point2f center(src.cols/2,src.rows/2);

	double angle = 45;//��ʱ����ת45��
	double scale = 0.5;//���ű���

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


