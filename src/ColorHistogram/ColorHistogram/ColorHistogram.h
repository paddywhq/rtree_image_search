#pragma once
//提取图片的特征向量(颜色直方图)

//#include "stdafx.h"
#include <memory>
#include <string>
#include <cv.h>
#include <highgui.h>
#include <fstream>

#define OUTPUT 1

using namespace cv;
using std::string;
using std::ifstream;
using std::ofstream;
using std::endl;
using std::cin;
using std::cout;

#define PATH string("A:\\Downloads\\大二下_课件\\数算后八周作业1\\DS&Alg-Project1-Release\\data\\")
#define IMGPATH PATH + "image\\"

#define DIM1 3			   //三个通道(RGB或HSV或别的什么)上各自的维数
#define DIM2 3
#define DIM3 3
#define DIM (DIM1 + DIM2 + DIM3) //总维数
#define 滤波 1             //是否在提取之前进行滤波(平滑)处理
						   //模糊处理有利于消除噪声影响
#define toHSV 0            //是否转为HSV空间
						   //HSV空间对自然图像区分可能更好
#define 分块 1:1	       //是否将图片分块，增大中央椭圆区域权重
#define 标准格式 1        //是否按标准格式输出结果。标准格式: 1，按照老师给的样例那种格式
				           //非标准格式: 0，每行先输出文件名，而且在文件最前端输出总维数
						   //libsvm格式: -1
#define 测试 1             //1:输出结果，0:测试单张图片(在test_show_img's........cpp文件里选择图片路径)
				           //将在屏幕上输出这个图像的颜色分布，暂限于HSV模式，从上到下依次H、S、V

#if toHSV		   		   //代表HSV空间上三个方向取值范围
#define MAX1 180.
#define MAX2 255.
#define MAX3 255.
#else
#define MAX1 255.
#define MAX2 255.
#define MAX3 255.
#endif

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
	int operator [](int t)
	{
		return data[t];
	}
public:
	int data[DIM];
};

class ColorHistogram
{
public:
	ColorHistogram(){}
	~ColorHistogram(){}

	//void init(CString filepath);
	void init(string filepath);//导入图像矩阵到src
	void gaussblur(int size = 5);//对src进行高斯模糊，默认数值是5，取值只能为奇数
	void rgb2hsv();//将src转为HSV格式
	void extract(Vect& v);//提取src的特征向量到v中
	bool inblock(int x, int y);//计算给定像素是否在图像中心区域

	//给定各个图片的路径们(直接可以打开的)，输出各个向量到outpath
	void autowork(string filepaths_of_imgs, string path_of_filenames, string outpath);
public:
	Mat src;//目标图像
};