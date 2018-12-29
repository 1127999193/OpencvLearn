#include<iostream>
#include<string>
#include<Windows.h>

#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/features2d/features2d.hpp>

using namespace std;
using namespace cv;

//ģ��ƥ�������һ��ͼ����Ѱ����һ��ģ��ͼ����ƥ��Ĳ��ֵļ���
int main8(int argv, char **argc)
{
	Mat src_gray;
	Mat src = imread("G:123/bask.jpeg");
	Mat mask = imread("G:123/hu.jpg");

	if (!src.data || src.empty()) //���ַ�ʽ
	{
		cout << "ͼ���ȡ��������·����" << endl;
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


	//  CV_TM_SQDIFF ƽ����ƥ�䷨����õ�ƥ��Ϊ0��ֵԽ��ƥ��Խ��
	//	CV_TM_SQDIFF_NORMED ��һ��ƽ����ƥ�䷨
	//	CV_TM_CCORR ���ƥ�䷨�����ó˷���������ֵԽ�����ƥ��Խ��
	//	CV_TM_CCORR_NORMED ��һ�����ƥ�䷨
	//	CV_TM_CCOEFF ���ϵ��ƥ�䷨����õ�ƥ��Ϊ1�� - 1��ʾ����ƥ��
	//	CV_TM_CCOEFF_NORMED ��һ�����ϵ��ƥ�䷨
	//�ȽϽ����ӳ��ͼ��,�����Ϊ��ͨ����32λ������
	//ԭͼΪW * H��ģ��Ϊ w * h��result�ߴ�Ϊ��W-w+1��*��H-h+1��

	matchTemplate(src,mask,result,CV_TM_SQDIFF_NORMED);

	//�����һ��
	//alpha:��һ�������Сֵ��Ĭ��ֵ0
	//beta:��һ��������ֵ��Ĭ��0
	//norm_type:��һ������
	//dtypeĬ��ֵ-1������Ϊ������������src��ͬ������
	normalize(result,result,0,1,NORM_MINMAX,-1,Mat());

	double minval = -1;
	double maxval;

	Point minLoc;
	Point maxLoc;
	Point matLoc;

	cout << "ƥ���" << minval << endl;
	
	//Ѱ����ֵ
	//minval ��������Сֵ��ָ��
	//minLoc��������Сֵλ�õ�ָ��

	minMaxLoc(result,&minval,&maxval,&minLoc,&maxLoc,Mat());

	cout << "ƥ���" << minval << endl;

	matLoc = minLoc;

	rectangle(src,matLoc,Point(matLoc.x+mask.cols,matLoc.y+mask.rows),Scalar(255,0,255),10,0);

	imshow("src",src);

	waitKey(0);
	return 0;

}