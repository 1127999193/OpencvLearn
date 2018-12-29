#include<iostream>
#include<string>

#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/features2d/features2d.hpp>

using namespace std;
using namespace cv;

//�˲���Ϊ�����ࣻ�����˲��ͷ������˲�
//�����˲��������˲�����ֵ�˲�����˹�˲�
//�������˲�����ֵ�˲���˫���˲�

int main2()
{
	Mat src = imread("G:123/456.jpg");
	if (src.data == NULL)
	{
		cout << "Դ�ļ���ʧ��" << endl;
		cout << "�����ļ�·��" << endl;
		return -1;
	}

	//�����˲�
	Mat dst_boxFliter;
	boxFilter(src,dst_boxFliter,-1,Size(3,3));

	imshow("dst_boxFliter", dst_boxFliter);

	//��ֵ�˲�
	Mat dst_blur;
	blur(src,dst_blur,Size(3,3));
	imshow("dst_blur", dst_blur);

	//��˹�˲� ����sigma��ֵԽ��ͼ��Խģ��
	Mat dst_gau;
	GaussianBlur(src,dst_gau,Size(3,3),0);
	imshow("dst_gau", dst_gau);

	//��ֵ�˲�
	//ȥ����������������������ͬʱ����
	//����ͼ���ϸ��
	Mat dst_median;
	medianBlur(src,dst_median,5);
	imshow("dst_median", dst_median);


	//˫���˲�
	//[3] �˲� NԽ��ԽƽԽģ��(2*N+1) sigmas�ռ�Խ��Խģ��sigmar��������
	//ƽ��ͼ�����ܱ����Ե
	Mat dst_bila;
	bilateralFilter(src,dst_bila,10,10,10);
	waitKey(0);
	return 0;

}