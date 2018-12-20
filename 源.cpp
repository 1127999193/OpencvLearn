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
	//【0】变量定义
	Mat srcImage, dstImage;
	Mat map_x, map_y;

	//【1】载入原始图
	srcImage = imread("G:/123/456.jpg", 1);
	if (!srcImage.data) { printf("读取图片错误，请确定目录下是否有imread函数指定的图片存在~！ \n"); return false; }
	imshow("原始图", srcImage);

	//【2】创建和原始图一样的效果图，x重映射图，y重映射图
	//dstImage.create(srcImage.size(), srcImage.type());
	map_x.create(srcImage.size(), CV_32FC1);
	map_y.create(srcImage.size(), CV_32FC1);

	//【3】双层循环，遍历每一个像素点，改变map_x & map_y的值
	for (int j = 0; j < srcImage.rows;j++)
	{
	for (int i = 0; i < srcImage.cols;i++)
	{
	//改变map_x & map_y的值.
	map_x.at<float>(j, i) = static_cast<float>(srcImage.cols - i);
	map_y.at<float>(j, i) = static_cast<float>( j);//srcImage.rows -
	}
	}

	//【4】进行重映射操作
	remap(srcImage, dstImage, map_x, map_y, CV_INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0));

	//【5】显示效果图
	imshow("【程序窗口】", dstImage);
	waitKey();

	return 0;
}







/*
//-----------------------------------【宏定义部分】--------------------------------------------  
//  描述：定义一些辅助宏  
//------------------------------------------------------------------------------------------------  
#define WINDOW_NAME1 "【程序窗口1】"        //为窗口标题定义的宏  
#define WINDOW_NAME2 "【程序窗口2】"        //为窗口标题定义的宏  

//-----------------------------------【全局变量声明部分】--------------------------------------
//		描述：全局变量声明
//-----------------------------------------------------------------------------------------------
Mat g_srcImage, g_srcImage1, g_grayImage;
int thresh = 30; //当前阈值
int max_thresh = 175; //最大阈值


					  //-----------------------------------【全局函数声明部分】--------------------------------------
					  //		描述：全局函数声明
					  //-----------------------------------------------------------------------------------------------
void on_CornerHarris(int, void*);//回调函数
static void ShowHelpText();

//-----------------------------------【main( )函数】--------------------------------------------
//		描述：控制台应用程序的入口函数，我们的程序从这里开始执行
//-----------------------------------------------------------------------------------------------
int main(int argc, char** argv)
{
	//【0】改变console字体颜色
	system("color 3F");

	//【0】显示帮助文字
	ShowHelpText();

	//【1】载入原始图并进行克隆保存
	g_srcImage = imread("G:/123/456.jpg", 1);
	resize(g_srcImage, g_srcImage,Size(0,0),0.5,0.5);
	if (!g_srcImage.data) { printf("读取图片错误，请确定目录下是否有imread函数指定的图片存在~！ \n"); return false; }
	imshow("原始图", g_srcImage);
	g_srcImage1 = g_srcImage.clone();

	//【2】存留一张灰度图
	cvtColor(g_srcImage1, g_grayImage, CV_BGR2GRAY);

	//【3】创建窗口和滚动条
	namedWindow(WINDOW_NAME1, CV_WINDOW_AUTOSIZE);
	createTrackbar("阈值: ", WINDOW_NAME1, &thresh, max_thresh, on_CornerHarris);

	//【4】调用一次回调函数，进行初始化
	on_CornerHarris(0, 0);

	waitKey(0);
	return(0);
}

//-----------------------------------【on_HoughLines( )函数】--------------------------------
//		描述：回调函数
//----------------------------------------------------------------------------------------------

void on_CornerHarris(int, void*)
{
	//---------------------------【1】定义一些局部变量-----------------------------
	Mat dstImage;//目标图
	Mat normImage;//归一化后的图
	Mat scaledImage;//线性变换后的八位无符号整型的图

					//---------------------------【2】初始化---------------------------------------
					//置零当前需要显示的两幅图，即清除上一次调用此函数时他们的值
	dstImage = Mat::zeros(g_srcImage.size(), CV_32FC1);
	g_srcImage1 = g_srcImage.clone();

	//---------------------------【3】正式检测-------------------------------------
	//进行角点检测
	cornerHarris(g_grayImage, dstImage, 2, 3, 0.04, BORDER_DEFAULT);

	// 归一化与转换
	normalize(dstImage, normImage, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
	convertScaleAbs(normImage, scaledImage);//将归一化后的图线性变换成8位无符号整型 

											//---------------------------【4】进行绘制-------------------------------------
											// 将检测到的，且符合阈值条件的角点绘制出来
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
	//---------------------------【4】显示最终效果---------------------------------
	imshow(WINDOW_NAME1, g_srcImage1);
	imshow(WINDOW_NAME2, scaledImage);

}

//-----------------------------------【ShowHelpText( )函数】----------------------------------
//		描述：输出一些帮助信息
//----------------------------------------------------------------------------------------------
static void ShowHelpText()
{
	//输出一些帮助信息
	printf("\n\n\n\t\t\t【欢迎来到Harris角点检测示例程序~】\n\n");
	printf("\n\n\n\t请调整滚动条观察图像效果~\n\n");
	printf("\n\n\t\t\t\t\t\t\t\t by浅墨"
	);
}



*/



/*
//-----------------------------------【命名空间声明部分】---------------------------------------  
//      描述：包含程序所使用的命名空间  
//-----------------------------------------------------------------------------------------------   
using namespace cv;
using namespace std;


//-----------------------------------【全局变量声明部分】--------------------------------------  
//      描述：全局变量声明  
//-----------------------------------------------------------------------------------------------  
Mat g_srcImage, g_dstImage, g_grayImage, g_maskImage;//定义原始图、目标图、灰度图、掩模图
int g_nFillMode = 1;//漫水填充的模式
int g_nLowDifference = 20, g_nUpDifference = 20;//负差最大值、正差最大值
int g_nConnectivity = 4;//表示floodFill函数标识符低八位的连通值
int g_bIsColor = true;//是否为彩色图的标识符布尔值
bool g_bUseMask = false;//是否显示掩膜窗口的布尔值
int g_nNewMaskVal = 255;//新的重新绘制的像素值


						//-----------------------------------【ShowHelpText( )函数】----------------------------------  
						//      描述：输出一些帮助信息  
						//----------------------------------------------------------------------------------------------  
static void ShowHelpText()
{
	//输出一些帮助信息  
	printf("\n\n\n\t欢迎来到漫水填充示例程序~\n\n");
	printf("\n\n\t按键操作说明: \n\n"
		"\t\t鼠标点击图中区域- 进行漫水填充操作\n"
		"\t\t键盘按键【ESC】- 退出程序\n"
		"\t\t键盘按键【1】-  切换彩色图/灰度图模式\n"
		"\t\t键盘按键【2】- 显示/隐藏掩膜窗口\n"
		"\t\t键盘按键【3】- 恢复原始图像\n"
		"\t\t键盘按键【4】- 使用空范围的漫水填充\n"
		"\t\t键盘按键【5】- 使用渐变、固定范围的漫水填充\n"
		"\t\t键盘按键【6】- 使用渐变、浮动范围的漫水填充\n"
		"\t\t键盘按键【7】- 操作标志符的低八位使用4位的连接模式\n"
		"\t\t键盘按键【8】- 操作标志符的低八位使用8位的连接模式\n"
		"\n\n\t\t\t\t\t\t\t\t by浅墨\n\n\n"
	);
}


//-----------------------------------【onMouse( )函数】--------------------------------------  
//      描述：鼠标消息onMouse回调函数
//---------------------------------------------------------------------------------------------
static void onMouse(int event, int x, int y, int, void*)
{
	// 若鼠标左键没有按下，便返回
	if (event != CV_EVENT_LBUTTONDOWN)
		return;

	//-------------------【<1>调用floodFill函数之前的参数准备部分】---------------
	Point seed = Point(x, y);
	int LowDifference = g_nFillMode == 0 ? 0 : g_nLowDifference;//空范围的漫水填充，此值设为0，否则设为全局的g_nLowDifference
	int UpDifference = g_nFillMode == 0 ? 0 : g_nUpDifference;//空范围的漫水填充，此值设为0，否则设为全局的g_nUpDifference
	int flags = g_nConnectivity + (g_nNewMaskVal << 8) +
		(g_nFillMode == 1 ? CV_FLOODFILL_FIXED_RANGE : 0);//标识符的0~7位为g_nConnectivity，8~15位为g_nNewMaskVal左移8位的值，16~23位为CV_FLOODFILL_FIXED_RANGE或者0。

														  //随机生成bgr值
	int b = (unsigned)theRNG() & 255;//随机返回一个0~255之间的值
	int g = (unsigned)theRNG() & 255;//随机返回一个0~255之间的值
	int r = (unsigned)theRNG() & 255;//随机返回一个0~255之间的值
	Rect ccomp;//定义重绘区域的最小边界矩形区域

	Scalar newVal = g_bIsColor ? Scalar(b, g, r) : Scalar(r*0.299 + g * 0.587 + b * 0.114);//在重绘区域像素的新值，若是彩色图模式，取Scalar(b, g, r)；若是灰度图模式，取Scalar(r*0.299 + g*0.587 + b*0.114)

	Mat dst = g_bIsColor ? g_dstImage : g_grayImage;//目标图的赋值
	int area;

	//--------------------【<2>正式调用floodFill函数】-----------------------------
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

	imshow("效果图", dst);
	cout << area << " 个像素被重绘\n";
}


//-----------------------------------【main( )函数】--------------------------------------------  
//      描述：控制台应用程序的入口函数，我们的程序从这里开始  
//-----------------------------------------------------------------------------------------------  
int main(int argc, char** argv)
{
	//改变console字体颜色  
	system("color 2F");

	//载入原图
	g_srcImage = imread("G:/123/456.jpg", 1);

	if (!g_srcImage.data) { printf("Oh，no，读取图片image0错误~！ \n"); return false; }

	//显示帮助文字
	ShowHelpText();

	g_srcImage.copyTo(g_dstImage);//拷贝源图到目标图
	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);//转换三通道的image0到灰度图
	g_maskImage.create(g_srcImage.rows + 2, g_srcImage.cols + 2, CV_8UC1);//利用image0的尺寸来初始化掩膜mask

	namedWindow("效果图", CV_WINDOW_AUTOSIZE);

	//创建Trackbar
	createTrackbar("负差最大值", "效果图", &g_nLowDifference, 255, 0);
	createTrackbar("正差最大值", "效果图", &g_nUpDifference, 255, 0);

	//鼠标回调函数
	setMouseCallback("效果图", onMouse, 0);

	//循环轮询按键
	while (1)
	{
		//先显示效果图
		imshow("效果图", g_bIsColor ? g_dstImage : g_grayImage);

		//获取键盘按键
		int c = waitKey(0);
		//判断ESC是否按下，若按下便退出
		if ((c & 255) == 27)
		{
			cout << "程序退出...........\n";
			break;
		}

		//根据按键的不同，进行各种操作
		switch ((char)c)
		{
			//如果键盘“1”被按下，效果图在在灰度图，彩色图之间互换
		case '1':
			if (g_bIsColor)//若原来为彩色，转为灰度图，并且将掩膜mask所有元素设置为0
			{
				cout << "键盘“1”被按下，切换彩色/灰度模式，当前操作为将【彩色模式】切换为【灰度模式】\n";
				cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);
				g_maskImage = Scalar::all(0);	//将mask所有元素设置为0
				g_bIsColor = false;	//将标识符置为false，表示当前图像不为彩色，而是灰度
			}
			else//若原来为灰度图，便将原来的彩图image0再次拷贝给image，并且将掩膜mask所有元素设置为0
			{
				cout << "键盘“1”被按下，切换彩色/灰度模式，当前操作为将【彩色模式】切换为【灰度模式】\n";
				g_srcImage.copyTo(g_dstImage);
				g_maskImage = Scalar::all(0);
				g_bIsColor = true;//将标识符置为true，表示当前图像模式为彩色
			}
			break;
			//如果键盘按键“2”被按下，显示/隐藏掩膜窗口
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
			//如果键盘按键“3”被按下，恢复原始图像
		case '3':
			cout << "按键“3”被按下，恢复原始图像\n";
			g_srcImage.copyTo(g_dstImage);
			cvtColor(g_dstImage, g_grayImage, COLOR_BGR2GRAY);
			g_maskImage = Scalar::all(0);
			break;
			//如果键盘按键“4”被按下，使用空范围的漫水填充
		case '4':
			cout << "按键“4”被按下，使用空范围的漫水填充\n";
			g_nFillMode = 0;
			break;
			//如果键盘按键“5”被按下，使用渐变、固定范围的漫水填充
		case '5':
			cout << "按键“5”被按下，使用渐变、固定范围的漫水填充\n";
			g_nFillMode = 1;
			break;
			//如果键盘按键“6”被按下，使用渐变、浮动范围的漫水填充
		case '6':
			cout << "按键“6”被按下，使用渐变、浮动范围的漫水填充\n";
			g_nFillMode = 2;
			break;
			//如果键盘按键“7”被按下，操作标志符的低八位使用4位的连接模式
		case '7':
			cout << "按键“7”被按下，操作标志符的低八位使用4位的连接模式\n";
			g_nConnectivity = 4;
			break;
			//如果键盘按键“8”被按下，操作标志符的低八位使用8位的连接模式
		case '8':
			cout << "按键“8”被按下，操作标志符的低八位使用8位的连接模式\n";
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

