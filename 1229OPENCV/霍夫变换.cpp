#include<iostream>
#include<string>

#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/features2d/features2d.hpp>

using namespace std;
using namespace cv;

// ����任��ʶ��ͼ���еļ�����״

// HoughLines  ��׼�����߱任����߶Ȼ����߱任
// HoughLinesP �ۼƸ��ʻ����߱任
// HoughCircles ����Բ�任

int main6(int argv, char **argc)
{
	Mat src_gray;
	Mat src = imread("G:123/line.jpg");

	resize(src, src, Size(0, 0), 0.5, 0.5);
	if (!src.data || src.empty()) //���ַ�ʽ
	{
		cout << "ͼ���ȡ��������·����" << endl;
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
	
	//���λ���ÿ���߶�
	for (size_t i = 0; i < lines.size(); i++)
	{
		float rho = lines[i][0]; //����Բ�İ뾶r
		float theta = lines[i][1]; //����ֱ�ߵĽǶ�
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a * rho, y0 = b * rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));

		line(dst_hou, pt1, pt2, Scalar(55, 100, 195), 1, LINE_AA); //Scalar�������ڵ����߶���ɫ�����������⵽���߶���ʾ����ʲô��ɫ
	}
	imshow("��Ե�����ͼ", dst_can);
	imshow("����Ч��ͼ", dst_hou);


	vector<Vec4i> lines_i;
	//��HoughLines��ͬ���ǣ�HoughLinesP�õ�lines���Ǻ���ֱ���ϵ������ģ�����������л���ʱ�Ͳ�����Ҫ�Լ������������ȷ��Ψһ��ֱ����
	HoughLinesP(dst_can, lines_i, 1, CV_PI / 360, 80, 0, 0);//ע������������Ϊ��ֵ

	//���λ���ÿ���߶�
	for (size_t i = 0; i < lines_i.size(); i++)
	{
		Vec4i l = lines_i[i];

		line(dst_houp, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(186, 88, 255), 1, LINE_AA); //Scalar�������ڵ����߶���ɫ
		imshow("����Ч��ͼp", dst_houp);
	}


	//��4�����л���Բ�任  
	vector<Vec3f> circles;
	HoughCircles(dst_can, circles, CV_HOUGH_GRADIENT, 1.5, 10, 200, 150, 0, 0); //ע����ߵĲ���Ϊ��ֵ���������е�����ֵԽ�󣬼���Բ����׼

																				 //��5��������ͼ�л��Ƴ�Բ  
	for (size_t i = 0; i < circles.size(); i++)
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		//����Բ��  
		circle(dst_cir, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		//����Բ����  
		circle(dst_cir, center, radius, Scalar(155, 50, 255), 3, 8, 0);
	}

	//��6����ʾЧ��ͼ    
	imshow("��Ч��ͼ��", dst_cir);


	waitKey(0);
	return 0;

}





