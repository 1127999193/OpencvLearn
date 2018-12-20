#include<iostream>
#include<string>

#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/features2d/features2d.hpp>

using namespace std;
using namespace cv;



Mat Src;
int main()
{
	//��0����������
	Mat srcImage, dstImage;
	Mat map_x, map_y;

	//��1������ԭʼͼ
	srcImage = imread("G:/123/456.jpg", 1);
	if (!srcImage.data) { printf("��ȡͼƬ������ȷ��Ŀ¼���Ƿ���imread����ָ����ͼƬ����~�� \n"); return false; }
	imshow("ԭʼͼ", srcImage);

	//��2��������ԭʼͼһ����Ч��ͼ��x��ӳ��ͼ��y��ӳ��ͼ
	//dstImage.create(srcImage.size(), srcImage.type());
	map_x.create(srcImage.size(), CV_32FC1);
	map_y.create(srcImage.size(), CV_32FC1);

	//��3��˫��ѭ��������ÿһ�����ص㣬�ı�map_x & map_y��ֵ
	for (int j = 0; j < srcImage.rows;j++)
	{
	for (int i = 0; i < srcImage.cols;i++)
	{
	//�ı�map_x & map_y��ֵ.
	map_x.at<float>(j, i) = static_cast<float>(srcImage.cols - i);
	map_y.at<float>(j, i) = static_cast<float>( j);//srcImage.rows -
	}
	}

	//��4��������ӳ�����
	remap(srcImage, dstImage, map_x, map_y, CV_INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0));

	//��5����ʾЧ��ͼ
	imshow("�����򴰿ڡ�", dstImage);
	waitKey();

	return 0;
}







/*
//-----------------------------------���궨�岿�֡�--------------------------------------------  
//  ����������һЩ������  
//------------------------------------------------------------------------------------------------  
#define WINDOW_NAME1 "�����򴰿�1��"        //Ϊ���ڱ��ⶨ��ĺ�  
#define WINDOW_NAME2 "�����򴰿�2��"        //Ϊ���ڱ��ⶨ��ĺ�  

//-----------------------------------��ȫ�ֱ����������֡�--------------------------------------
//		������ȫ�ֱ�������
//-----------------------------------------------------------------------------------------------
Mat g_srcImage, g_srcImage1, g_grayImage;
int thresh = 30; //��ǰ��ֵ
int max_thresh = 175; //�����ֵ


					  //-----------------------------------��ȫ�ֺ����������֡�--------------------------------------
					  //		������ȫ�ֺ�������
					  //-----------------------------------------------------------------------------------------------
void on_CornerHarris(int, void*);//�ص�����
static void ShowHelpText();

//-----------------------------------��main( )������--------------------------------------------
//		����������̨Ӧ�ó������ں��������ǵĳ�������￪ʼִ��
//-----------------------------------------------------------------------------------------------
int main(int argc, char** argv)
{
	//��0���ı�console������ɫ
	system("color 3F");

	//��0����ʾ��������
	ShowHelpText();

	//��1������ԭʼͼ�����п�¡����
	g_srcImage = imread("G:/123/456.jpg", 1);
	resize(g_srcImage, g_srcImage,Size(0,0),0.5,0.5);
	if (!g_srcImage.data) { printf("��ȡͼƬ������ȷ��Ŀ¼���Ƿ���imread����ָ����ͼƬ����~�� \n"); return false; }
	imshow("ԭʼͼ", g_srcImage);
	g_srcImage1 = g_srcImage.clone();

	//��2������һ�ŻҶ�ͼ
	cvtColor(g_srcImage1, g_grayImage, CV_BGR2GRAY);

	//��3���������ں͹�����
	namedWindow(WINDOW_NAME1, CV_WINDOW_AUTOSIZE);
	createTrackbar("��ֵ: ", WINDOW_NAME1, &thresh, max_thresh, on_CornerHarris);

	//��4������һ�λص����������г�ʼ��
	on_CornerHarris(0, 0);

	waitKey(0);
	return(0);
}

//-----------------------------------��on_HoughLines( )������--------------------------------
//		�������ص�����
//----------------------------------------------------------------------------------------------

void on_CornerHarris(int, void*)
{
	//---------------------------��1������һЩ�ֲ�����-----------------------------
	Mat dstImage;//Ŀ��ͼ
	Mat normImage;//��һ�����ͼ
	Mat scaledImage;//���Ա任��İ�λ�޷������͵�ͼ

					//---------------------------��2����ʼ��---------------------------------------
					//���㵱ǰ��Ҫ��ʾ������ͼ���������һ�ε��ô˺���ʱ���ǵ�ֵ
	dstImage = Mat::zeros(g_srcImage.size(), CV_32FC1);
	g_srcImage1 = g_srcImage.clone();

	//---------------------------��3����ʽ���-------------------------------------
	//���нǵ���
	cornerHarris(g_grayImage, dstImage, 2, 3, 0.04, BORDER_DEFAULT);

	// ��һ����ת��
	normalize(dstImage, normImage, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
	convertScaleAbs(normImage, scaledImage);//����һ�����ͼ���Ա任��8λ�޷������� 

											//---------------------------��4�����л���-------------------------------------
											// ����⵽�ģ��ҷ�����ֵ�����Ľǵ���Ƴ���
	for (int j = 0; j < normImage.rows; j++)
	{
		for (int i = 0; i < normImage.cols; i++)
		{
			if ((int)normImage.at<float>(j, i) > thresh + 80)
			{
				circle(g_srcImage1, Point(i, j), 5, Scalar(10, 10, 255), 2, 8, 0);
				circle(scaledImage, Point(i, j), 5, Scalar(0, 10, 255), 2, 8, 0);
			}
		}
	}
	//---------------------------��4����ʾ����Ч��---------------------------------
	imshow(WINDOW_NAME1, g_srcImage1);
	imshow(WINDOW_NAME2, scaledImage);

}

//-----------------------------------��ShowHelpText( )������----------------------------------
//		���������һЩ������Ϣ
//----------------------------------------------------------------------------------------------
static void ShowHelpText()
{
	//���һЩ������Ϣ
	printf("\n\n\n\t\t\t����ӭ����Harris�ǵ���ʾ������~��\n\n");
	printf("\n\n\n\t������������۲�ͼ��Ч��~\n\n");
	printf("\n\n\t\t\t\t\t\t\t\t byǳī"
	);
}



*/



/*
//-----------------------------------�������ռ��������֡�---------------------------------------  
//      ����������������ʹ�õ������ռ�  
//-----------------------------------------------------------------------------------------------   
using namespace cv;
using namespace std;


//-----------------------------------��ȫ�ֱ����������֡�--------------------------------------  
//      ������ȫ�ֱ�������  
//-----------------------------------------------------------------------------------------------  
Mat g_srcImage, g_dstImage, g_grayImage, g_maskImage;//����ԭʼͼ��Ŀ��ͼ���Ҷ�ͼ����ģͼ
int g_nFillMode = 1;//��ˮ����ģʽ
int g_nLowDifference = 20, g_nUpDifference = 20;//�������ֵ���������ֵ
int g_nConnectivity = 4;//��ʾfloodFill������ʶ���Ͱ�λ����ֵͨ
int g_bIsColor = true;//�Ƿ�Ϊ��ɫͼ�ı�ʶ������ֵ
bool g_bUseMask = false;//�Ƿ���ʾ��Ĥ���ڵĲ���ֵ
int g_nNewMaskVal = 255;//�µ����»��Ƶ�����ֵ


						//-----------------------------------��ShowHelpText( )������----------------------------------  
						//      ���������һЩ������Ϣ  
						//----------------------------------------------------------------------------------------------  
static void ShowHelpText()
{
	//���һЩ������Ϣ  
	printf("\n\n\n\t��ӭ������ˮ���ʾ������~\n\n");
	printf("\n\n\t��������˵��: \n\n"
		"\t\t�����ͼ������- ������ˮ������\n"
		"\t\t���̰�����ESC��- �˳�����\n"
		"\t\t���̰�����1��-  �л���ɫͼ/�Ҷ�ͼģʽ\n"
		"\t\t���̰�����2��- ��ʾ/������Ĥ����\n"
		"\t\t���̰�����3��- �ָ�ԭʼͼ��\n"
		"\t\t���̰�����4��- ʹ�ÿշ�Χ����ˮ���\n"
		"\t\t���̰�����5��- ʹ�ý��䡢�̶���Χ����ˮ���\n"
		"\t\t���̰�����6��- ʹ�ý��䡢������Χ����ˮ���\n"
		"\t\t���̰�����7��- ������־���ĵͰ�λʹ��4λ������ģʽ\n"
		"\t\t���̰�����8��- ������־���ĵͰ�λʹ��8λ������ģʽ\n"
		"\n\n\t\t\t\t\t\t\t\t byǳī\n\n\n"
	);
}


//-----------------------------------��onMouse( )������--------------------------------------  
//      �����������ϢonMouse�ص�����
//---------------------------------------------------------------------------------------------
static void onMouse(int event, int x, int y, int, void*)
{
	// ��������û�а��£��㷵��
	if (event != CV_EVENT_LBUTTONDOWN)
		return;

	//-------------------��<1>����floodFill����֮ǰ�Ĳ���׼�����֡�---------------
	Point seed = Point(x, y);
	int LowDifference = g_nFillMode == 0 ? 0 : g_nLowDifference;//�շ�Χ����ˮ��䣬��ֵ��Ϊ0��������Ϊȫ�ֵ�g_nLowDifference
	int UpDifference = g_nFillMode == 0 ? 0 : g_nUpDifference;//�շ�Χ����ˮ��䣬��ֵ��Ϊ0��������Ϊȫ�ֵ�g_nUpDifference
	int flags = g_nConnectivity + (g_nNewMaskVal << 8) +
		(g_nFillMode == 1 ? CV_FLOODFILL_FIXED_RANGE : 0);//��ʶ����0~7λΪg_nConnectivity��8~15λΪg_nNewMaskVal����8λ��ֵ��16~23λΪCV_FLOODFILL_FIXED_RANGE����0��

														  //�������bgrֵ
	int b = (unsigned)theRNG() & 255;//�������һ��0~255֮���ֵ
	int g = (unsigned)theRNG() & 255;//�������һ��0~255֮���ֵ
	int r = (unsigned)theRNG() & 255;//�������һ��0~255֮���ֵ
	Rect ccomp;//�����ػ��������С�߽��������

	Scalar newVal = g_bIsColor ? Scalar(b, g, r) : Scalar(r*0.299 + g * 0.587 + b * 0.114);//���ػ��������ص���ֵ�����ǲ�ɫͼģʽ��ȡScalar(b, g, r)�����ǻҶ�ͼģʽ��ȡScalar(r*0.299 + g*0.587 + b*0.114)

	Mat dst = g_bIsColor ? g_dstImage : g_grayImage;//Ŀ��ͼ�ĸ�ֵ
	int area;

	//--------------------��<2>��ʽ����floodFill������-----------------------------
	if (g_bUseMask)
	{
		threshold(g_maskImage, g_maskImage, 1, 128, CV_THRESH_BINARY);
		area = floodFill(dst, g_maskImage, seed, newVal, &ccomp, Scalar(LowDifference, LowDifference, LowDifference),
			Scalar(UpDifference, UpDifference, UpDifference), flags);
		imshow("mask", g_maskImage);
	}
	else
	{
		area = floodFill(dst, seed, newVal, &ccomp, Scalar(LowDifference, LowDifference, LowDifference),
			Scalar(UpDifference, UpDifference, UpDifference), flags);
	}

	imshow("Ч��ͼ", dst);
	cout << area << " �����ر��ػ�\n";
}


//-----------------------------------��main( )������--------------------------------------------  
//      ����������̨Ӧ�ó������ں��������ǵĳ�������￪ʼ  
//-----------------------------------------------------------------------------------------------  
int main(int argc, char** argv)
{
	//�ı�console������ɫ  
	system("color 2F");

	//����ԭͼ
	g_srcImage = imread("G:/123/456.jpg", 1);

	if (!g_srcImage.data) { printf("Oh��no����ȡͼƬimage0����~�� \n"); return false; }

	//��ʾ��������
	ShowHelpText();

	g_srcImage.copyTo(g_dstImage);//����Դͼ��Ŀ��ͼ
	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);//ת����ͨ����image0���Ҷ�ͼ
	g_maskImage.create(g_srcImage.rows + 2, g_srcImage.cols + 2, CV_8UC1);//����image0�ĳߴ�����ʼ����Ĥmask

	namedWindow("Ч��ͼ", CV_WINDOW_AUTOSIZE);

	//����Trackbar
	createTrackbar("�������ֵ", "Ч��ͼ", &g_nLowDifference, 255, 0);
	createTrackbar("�������ֵ", "Ч��ͼ", &g_nUpDifference, 255, 0);

	//���ص�����
	setMouseCallback("Ч��ͼ", onMouse, 0);

	//ѭ����ѯ����
	while (1)
	{
		//����ʾЧ��ͼ
		imshow("Ч��ͼ", g_bIsColor ? g_dstImage : g_grayImage);

		//��ȡ���̰���
		int c = waitKey(0);
		//�ж�ESC�Ƿ��£������±��˳�
		if ((c & 255) == 27)
		{
			cout << "�����˳�...........\n";
			break;
		}

		//���ݰ����Ĳ�ͬ�����и��ֲ���
		switch ((char)c)
		{
			//������̡�1�������£�Ч��ͼ���ڻҶ�ͼ����ɫͼ֮�以��
		case '1':
			if (g_bIsColor)//��ԭ��Ϊ��ɫ��תΪ�Ҷ�ͼ�����ҽ���Ĥmask����Ԫ������Ϊ0
			{
				cout << "���̡�1�������£��л���ɫ/�Ҷ�ģʽ����ǰ����Ϊ������ɫģʽ���л�Ϊ���Ҷ�ģʽ��\n";
				cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);
				g_maskImage = Scalar::all(0);	//��mask����Ԫ������Ϊ0
				g_bIsColor = false;	//����ʶ����Ϊfalse����ʾ��ǰͼ��Ϊ��ɫ�����ǻҶ�
			}
			else//��ԭ��Ϊ�Ҷ�ͼ���㽫ԭ���Ĳ�ͼimage0�ٴο�����image�����ҽ���Ĥmask����Ԫ������Ϊ0
			{
				cout << "���̡�1�������£��л���ɫ/�Ҷ�ģʽ����ǰ����Ϊ������ɫģʽ���л�Ϊ���Ҷ�ģʽ��\n";
				g_srcImage.copyTo(g_dstImage);
				g_maskImage = Scalar::all(0);
				g_bIsColor = true;//����ʶ����Ϊtrue����ʾ��ǰͼ��ģʽΪ��ɫ
			}
			break;
			//������̰�����2�������£���ʾ/������Ĥ����
		case '2':
			if (g_bUseMask)
			{
				destroyWindow("mask");
				g_bUseMask = false;
			}
			else
			{
				namedWindow("mask", 0);
				g_maskImage = Scalar::all(0);
				imshow("mask", g_maskImage);
				g_bUseMask = true;
			}
			break;
			//������̰�����3�������£��ָ�ԭʼͼ��
		case '3':
			cout << "������3�������£��ָ�ԭʼͼ��\n";
			g_srcImage.copyTo(g_dstImage);
			cvtColor(g_dstImage, g_grayImage, COLOR_BGR2GRAY);
			g_maskImage = Scalar::all(0);
			break;
			//������̰�����4�������£�ʹ�ÿշ�Χ����ˮ���
		case '4':
			cout << "������4�������£�ʹ�ÿշ�Χ����ˮ���\n";
			g_nFillMode = 0;
			break;
			//������̰�����5�������£�ʹ�ý��䡢�̶���Χ����ˮ���
		case '5':
			cout << "������5�������£�ʹ�ý��䡢�̶���Χ����ˮ���\n";
			g_nFillMode = 1;
			break;
			//������̰�����6�������£�ʹ�ý��䡢������Χ����ˮ���
		case '6':
			cout << "������6�������£�ʹ�ý��䡢������Χ����ˮ���\n";
			g_nFillMode = 2;
			break;
			//������̰�����7�������£�������־���ĵͰ�λʹ��4λ������ģʽ
		case '7':
			cout << "������7�������£�������־���ĵͰ�λʹ��4λ������ģʽ\n";
			g_nConnectivity = 4;
			break;
			//������̰�����8�������£�������־���ĵͰ�λʹ��8λ������ģʽ
		case '8':
			cout << "������8�������£�������־���ĵͰ�λʹ��8λ������ģʽ\n";
			g_nConnectivity = 8;
			break;
		}
	}

	return 0;
}
*/
/*

Mat Candst,Houdst,Contrast;

cvtColor(src, src,CV_BGR2GRAY);

Canny(src, Candst,50,150,3);
Houdst = Candst.clone();

Contrast = Mat::zeros(src.size(),src.depth());

//cvtColor(Candst, Candst, CV_GRAY2BGR);

vector<Vec4i> lines;

HoughLinesP(Candst,lines,1,CV_PI/360,80,50,10);

for (size_t i = 0;i < lines.size();i++)
{
Vec4i yu = lines[i];
line(Contrast, Point(yu[0],yu[1]), Point(yu[2], yu[3]), Scalar(55, 100, 195), 1, CV_AA);
}
imshow("canny",Candst);
imshow("Houdst", Houdst);
imshow("Contrast", Contrast);
waitKey(0);



HoughLines(Candst,lines,1,CV_PI/360,125,0,0);

for (size_t i = 0;i < lines.size();i++)
{
float rho = lines[i][0], theta = lines[i][1];
Point pt1, pt2;
double a = cos(theta), b = sin(theta);
double x0 = a * rho, y0 = b * rho;
pt1.x = cvRound(x0 + 1000 * (-b));
pt1.y = cvRound(y0 + 1000 * (a));
pt2.x = cvRound(x0 - 1000 * (-b));
pt2.y = cvRound(y0 - 1000 * (a));
line(Contrast, pt1, pt2, Scalar(55, 100, 195), 1, CV_AA);
}


//	Mat src = Mat::zeros(512,512,CV_8UC3);

VideoCapture cap("G:/123/123.mp4");

if (!cap.isOpened())
{
return 1;
}

Mat FirstFrame, Frame;

cap >> Frame;

imshow("First", Frame);
setMouseCallback();
while (1)
{


}
waitKey(0);

*/

