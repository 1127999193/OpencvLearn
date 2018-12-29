#include<iostream>
#include<string>
#include<Windows.h>

#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/features2d/features2d.hpp>
#include<photo/photo.hpp>

using namespace std;
using namespace cv;

//ȫ������ֵ���� + Mask���ʹ���
/*
int main9(int argv, char **argc)
{
	Mat src_gray;
	Mat src = imread("G:123/red.jpg");

	if (!src.data || src.empty()) //���ַ�ʽ
	{
		cout << "ͼ���ȡ��������·����" << endl;
		return 1;
	}
	if (src.channels() > 1)
	{
		cvtColor(src, src_gray, CV_BGR2GRAY);
	}

	Mat dst_inpa;
	Mat imagemask=Mat(src.size(),CV_8UC1,Scalar::all(0));

	threshold(src_gray,imagemask,240,255,CV_THRESH_BINARY);

	Mat element = getStructuringElement(MORPH_RECT,Size(3,3));

	dilate(imagemask,imagemask,element);

	//imagemask:ͼ������룬��ͨ��ͼ�񣬴�С��ԭͼ��һ�£�
	//ͼ���ϳ�����Ҫ�޸��Ĳ������������ֵ�����ֵΪ0
	//���ĸ��������޸��㷨������뾶�����ڼ��㵱ǰ���ص�Ĳ�ֵ
	//������������޸��㷨��INPAINT_NS,INPAINT_TELEA
	inpaint(src,imagemask, dst_inpa,1, INPAINT_TELEA);

	imshow("dst_inpa",dst_inpa);
	waitKey(0);
	return 0;
}
*/


Point ptL, ptR; //��껭�����ο�������յ�
Mat imageSource, imageSourceCopy;
Mat ROI,Gray; //ԭͼ��Ҫ�޸������ROI

 //���ص�����
void OnMouse(int event, int x, int y, int flag, void *ustg);
//  event ��CV_EVENT_*����֮һ
//  x �� y �����ָ����ͼ������ϵ������
//  flag ��CV_EVENT_FLAG�����


//CV_EVENT_MOUSEMOVE = 0,
//CV_EVENT_LBUTTONDOWN = 1,
//CV_EVENT_RBUTTONDOWN = 2,
//CV_EVENT_MBUTTONDOWN = 3,
//CV_EVENT_LBUTTONUP = 4,
//CV_EVENT_RBUTTONUP = 5,
//CV_EVENT_MBUTTONUP = 6,
//CV_EVENT_LBUTTONDBLCLK = 7,
//CV_EVENT_RBUTTONDBLCLK = 8,
//CV_EVENT_MBUTTONDBLCLK = 9

//CV_EVENT_FLAG_LBUTTON = 1,
//CV_EVENT_FLAG_RBUTTON = 2,
//CV_EVENT_FLAG_MBUTTON = 4,
//CV_EVENT_FLAG_CTRLKEY = 8,
//CV_EVENT_FLAG_SHIFTKEY = 16,
//CV_EVENT_FLAG_ALTKEY = 32


//���Ȧ��������ֵ����+Mask���ʹ���
int main9b()
{
	imageSource = imread("G:123/red.jpg");
	if (!imageSource.data)
	{
		return -1;
	}
	imshow("ԭͼ", imageSource);
	//�����Ӧ
	setMouseCallback("ԭͼ", OnMouse);
	waitKey();
}
void OnMouse(int event, int x, int y, int flag, void *ustg)
{
	if (event == CV_EVENT_LBUTTONDOWN)
	{
		ptL = Point(x, y);
		ptR = Point(x, y);
	}
	if (flag == CV_EVENT_FLAG_LBUTTON)
	{
		ptR = Point(x, y);
		imageSourceCopy = imageSource.clone();
		rectangle(imageSourceCopy, ptL, ptR, Scalar(255, 0, 0));
		imshow("ԭͼ", imageSourceCopy);
	}
	if (event == CV_EVENT_LBUTTONUP)
	{
		if (ptL != ptR)
		{
			ROI = imageSource(Rect(ptL, ptR));
			imshow("ROI", ROI);
			waitKey();
		}
	}
	//��������Ҽ���ʼͼ���޸�
	if (event == CV_EVENT_RBUTTONDOWN)
	{
		imageSourceCopy = ROI.clone();
		Mat imageGray;
		cvtColor(ROI, imageGray, CV_RGB2GRAY); //ת��Ϊ�Ҷ�ͼ
		Mat imageMask = Mat(ROI.size(), CV_8UC1, Scalar::all(0));

		//ͨ����ֵ��������Mask
		threshold(imageGray, imageMask, 235, 255, CV_THRESH_BINARY);
		Mat Kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
		dilate(imageMask, imageMask, Kernel);  //��Mask���ʹ���
		inpaint(ROI, imageMask, ROI, 9, INPAINT_TELEA);  //ͼ���޸�
		imshow("Mask", imageMask);
		imshow("�޸���", imageSource);
	}
}

