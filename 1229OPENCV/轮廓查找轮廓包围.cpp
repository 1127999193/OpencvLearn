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

//  ����ָ���㼯���ⲿ���α߽磺 boundingRect()
//  Ѱ�Ҹ����ĵ㼯����ת����С��Χ���Σ�minAreaRect()
//  Ѱ����С��ΧԲ�Σ�minEnclosingCircle()
//  ����Բ��϶�ά�㼯��fitEllipse()
//  �ƽ���������ߣ� approxPolyDP()
//

RNG rng(12345);

int maina(int argv, char **argc)
{
	Mat src_gray;
	Mat src = imread("G:123/456.jpg");

	if (!src.data) //���ַ�ʽ
	{
		cout << "ͼ���ȡ��������·����" << endl;
		return 1;
	}
	if (src.channels() > 1)
	{
		cvtColor(src, src_gray, CV_BGR2GRAY);
	}

	double thresh_size = ( 100 / 4) * 2 + 1; //����Ӧ��ֵ����ֵ
	Mat dst_th;
	threshold(src_gray, dst_th, 150, 255, CV_THRESH_BINARY_INV);
	//blocksize:��Χ����Ĵ�С
	// C ��ȥ��ֵ
	//adaptiveThreshold(src_gray,dst_th,255,CV_ADAPTIVE_THRESH_GAUSSIAN_C,CV_THRESH_BINARY_INV, thresh_size, thresh_size/3);

	vector<vector<Point>> contours;

	findContours(dst_th,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE); //������

	vector<vector<Point>> contours1;
	for (int i = 0; i < contours.size(); ++i)
	{
		contours1.push_back(contours[i]);
	}

	Mat hole(src_gray.size(), CV_8U, Scalar(0)); //����ͼ��
	drawContours(hole, contours1, -1, Scalar(255), CV_FILLED); //������ͼ���ϣ��ð�ɫ��������������õ�MASK
	namedWindow("My hole");
	imshow("My hole", hole);
	Mat crop(src.rows, src.cols, CV_8UC3);
	src.copyTo(crop, hole);//��ԭͼ�񿽱�������ͼ��
	imshow("My warpPerspective", crop);


	/// ����αƽ����� + ��ȡ���κ�Բ�α߽��
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

	/// ����������� + ��Χ�ľ��ο� + Բ�ο�
	Mat drawing = Mat::zeros(src_gray.size(), CV_8UC3);
	for (int i = 0; i< contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(drawing, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point());
		rectangle(drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0);
		circle(drawing, center[i], (int)radius[i], color, 2, 8, 0);
	}
	imshow("Contours", drawing);


	//�أ�ͼ���������Ϣ�������С��λ�á������
	//�ṩ��������ͼ��ľأ�
	//�ص����ġ����ᡢ����������ļ��� moment()
	//���������������contourArea()
	//���������ĳ��ȣ�arcLenggth()
	//��ͼ���м�������ľ�ͨ��������ͼ��ͬ����ļ��������磺��С���Ҷȡ�������״�ȣ�
	//ͼ��ع㷺Ӧ����ģʽʶ��Ŀ����ࡢĿ��ʶ�����α���ơ�ͼ��������ع�������
	

	// moments()����ͼ���е����˾�
	// contoursArea�����������
	// arcLength�������������߳���
	//

	vector<Moments> mu(contours.size());
	for(int i = 0;i < contours.size();i++)
	{
		//array:�������飬�����ǹ�դͼ��(��ͨ����8 - bit�򸡵��Ͷ�ά����), ������һ����ά����(1 X N��N X 1), ��ά��������ΪPoint��Point2f
		//binaryImage : Ĭ��ֵ��false�����Ϊtrue�������з�������ض��ᰴֵ1�Դ���Ҳ����˵�൱�ڶ�ͼ������˶�ֵ��������ֵΪ1���˲�������ͼ����Ч��
			
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
		//contour:��һ����������ά�㣬������vector��Mat����
		//oriented : ��Ĭ��ֵfalse�����������ʶ�������Ϊtrue���ú�������һ�������ŵ������������ȡ���������ķ���(˳ʱ�뻹����ʱ��)��
		//����������Կ��Ը�������ķ�����ȷ��������λ�á������Ĭ��ֵfalse��������Ծ���ֵ����ʽ����.
	
		//arcLength()
		//curve:�����ά�㼯��������vector��Mat����
		//closed:�����Ƿ��յı�־λ��true���շ��򲻷��

		printf(" * Contour[%d] - Area (M_00) = %.2f - Area OpenCV: %.2f - Length: %.2f \n", i, mu[i].m00, contourArea(contours[i]), arcLength(contours[i], true));
	}

	waitKey(0);
	return 0;
}


