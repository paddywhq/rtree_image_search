#pragma once
//��ȡͼƬ����������(��ɫֱ��ͼ)

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

#define PATH string("A:\\Downloads\\�����_�μ�\\����������ҵ1\\DS&Alg-Project1-Release\\data\\")
#define IMGPATH PATH + "image\\"

#define DIM1 3			   //����ͨ��(RGB��HSV����ʲô)�ϸ��Ե�ά��
#define DIM2 3
#define DIM3 3
#define DIM (DIM1 + DIM2 + DIM3) //��ά��
#define �˲� 1             //�Ƿ�����ȡ֮ǰ�����˲�(ƽ��)����
						   //ģ��������������������Ӱ��
#define toHSV 0            //�Ƿ�תΪHSV�ռ�
						   //HSV�ռ����Ȼͼ�����ֿ��ܸ���
#define �ֿ� 1:1	       //�Ƿ�ͼƬ�ֿ飬����������Բ����Ȩ��
#define ��׼��ʽ 1        //�Ƿ񰴱�׼��ʽ����������׼��ʽ: 1��������ʦ�����������ָ�ʽ
				           //�Ǳ�׼��ʽ: 0��ÿ��������ļ������������ļ���ǰ�������ά��
						   //libsvm��ʽ: -1
#define ���� 1             //1:��������0:���Ե���ͼƬ(��test_show_img's........cpp�ļ���ѡ��ͼƬ·��)
				           //������Ļ��������ͼ�����ɫ�ֲ���������HSVģʽ�����ϵ�������H��S��V

#if toHSV		   		   //����HSV�ռ�����������ȡֵ��Χ
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

//���ڶ�ȡͼ���ĳ�����ص���ɫ�ĵ�һ��������ͨ������ֵ
//ʹ�÷���:
//for (i=0;i<img.rows;i++)
//for (j=0;j<img.cols;j++)
//double h=src _3;


class Vect    //�������࣬��ά����֮ǰ��DIM��������DIM1+DIM2+DIM3���洢��Щ��
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
	void init(string filepath);//����ͼ�����src
	void gaussblur(int size = 5);//��src���и�˹ģ����Ĭ����ֵ��5��ȡֵֻ��Ϊ����
	void rgb2hsv();//��srcתΪHSV��ʽ
	void extract(Vect& v);//��ȡsrc������������v��
	bool inblock(int x, int y);//������������Ƿ���ͼ����������

	//��������ͼƬ��·����(ֱ�ӿ��Դ򿪵�)���������������outpath
	void autowork(string filepaths_of_imgs, string path_of_filenames, string outpath);
public:
	Mat src;//Ŀ��ͼ��
};