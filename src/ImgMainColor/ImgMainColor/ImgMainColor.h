#include <cv.h>
#include <highgui.h>
#define TEST 0
#include <fstream>
#include <string>

using namespace std;
using namespace cv;

#define DIM 9

#define PATH string("A:\\Downloads\\大二下_课件\\数算后八周作业1\\DS&Alg-Project1-Release\\data\\")
#define IMGPATH PATH + "image\\"

#define _3 .at<Vec3b>(i,j)[2]
#define _2 .at<Vec3b>(i,j)[1]
#define _1 .at<Vec3b>(i,j)[0]
//用于读取图像的某个像素的颜色的第一、二、三通道的数值
//使用方法:
//for (i=0;i<img.rows;i++)
//for (j=0;j<img.cols;j++)
//double h=src _3;

class Vect    //向量的类，其维数由之前的DIM决定，即DIM1+DIM2+DIM3，存储这些数
{
public:
	Vect()
	{
		memset(data, 0, DIM*sizeof(int));
	}
	Vect(Vect& v)
	{
		for (int i = 0; i < DIM; i++)
		{
			data[i] = v.data[i];
		}
	}
	double operator [](int t)
	{
		return data[t];
	}
public:
	double data[DIM];
};

class Color
{
public:
	Color(int hh=0,int ss=0,int vv=0):h(hh),s(ss),v(vv){}
public:
	double h, s, v;
};

class MainColor
{
public:
	void init(string filepath);//导入图像矩阵到src
	void gaussblur(int size = 5);//对src进行高斯模糊，默认数值是5，取值只能为奇数
	void rgb2hsv();//将src转为HSV格式
	void extract(Vect& v,string name="");//提取src的特征向量到v中
	void twoMainColors(Color& c1, Color& c2);
	double dis(Color& c1, Color& c2);
public:
	Mat src;//目标图像
	Color s1, s2;
};