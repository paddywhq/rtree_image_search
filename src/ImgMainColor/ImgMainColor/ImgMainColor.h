#include <cv.h>
#include <highgui.h>
#define TEST 0
#include <fstream>
#include <string>

using namespace std;
using namespace cv;

#define DIM 9

#define PATH string("A:\\Downloads\\�����_�μ�\\����������ҵ1\\DS&Alg-Project1-Release\\data\\")
#define IMGPATH PATH + "image\\"

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
	void init(string filepath);//����ͼ�����src
	void gaussblur(int size = 5);//��src���и�˹ģ����Ĭ����ֵ��5��ȡֵֻ��Ϊ����
	void rgb2hsv();//��srcתΪHSV��ʽ
	void extract(Vect& v,string name="");//��ȡsrc������������v��
	void twoMainColors(Color& c1, Color& c2);
	double dis(Color& c1, Color& c2);
public:
	Mat src;//Ŀ��ͼ��
	Color s1, s2;
};