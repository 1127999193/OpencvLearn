#include<iostream>
#include<string>

#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/features2d/features2d.hpp>

using namespace std;
using namespace cv;


//��Сͼ��ʹ��CV_INTER_AREA����ֵ
//�Ŵ�ͼ��ʹ��CV_INTER_LINEAR����ֵ


//�²��������裺
//��ͼ����и�˹�ں˾��
//������ż���к���ȥ��

//�²�������ͼ��ѹ�����ᶪʧͼ����Ϣ��

//�ϲ������裺
//��ͼ����ÿ������Ŵ�Ϊԭ�����������������к�����0��䣻
//ʹ����ǰͬ�����ںˣ�����4����Ŵ���ͼ����������������صĽ���ֵ��

//���²���������ͼ����ģ��
int main4(int argv, char **argc)
{
	Mat src_gray;
	Mat src = imread("G:123/456.jpg");

	if (!src.data || src.empty()) //���ַ�ʽ
	{
		cout << "ͼ���ȡ��������·����" << endl;
	}
	if (src.channels() > 1)
	{
		cvtColor(src, src_gray, CV_BGR2GRAY);
	}
	//ͼ�����ŵ����ַ�ʽ
	
	//resize(src,src,Size(500,500));
	//resize(src, src, Size(0, 0), 0.5, 0.5);

	Mat dst_up, dst_down;

	pyrUp(src,dst_up,Size(src.cols*2,src.rows*2));
	pyrDown(src, dst_down, Size(src.cols * 0.5, src.rows * 0.5));

	imshow("dst_down", dst_down);
	waitKey(0);
	return 0;
}


