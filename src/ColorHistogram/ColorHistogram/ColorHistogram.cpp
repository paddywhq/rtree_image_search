#include "ColorHistogram.h"
#include <cmath>
void ColorHistogram::init(string filepath)
{
	src = imread(filepath, 1);
	//imshow(path,img);
	//cvWaitKey(0);
	//if (!src.data)
	//	AfxMessageBox(_T("error: 无法读取图片~~"));
}

void ColorHistogram::gaussblur(int size)
{
	Mat s = src;
	GaussianBlur(s, src, Size(size, size), 0, 0, 4);//使用高斯模糊
}

void ColorHistogram::rgb2hsv()
{
	Mat s = src;
	cv::cvtColor(s, src, CV_BGR2HSV);
}

bool ColorHistogram::inblock(int x, int y)
{
	double w = (double)src.cols;
	double h = (double)src.rows;
	double x1 = (double)x;
	double y1 = (double)y;
	y1 *= w / h;
	h = w;
	double d = (x1 - w / 2)*(x1 - w / 2) + (y1 - h / 2)*(y1 - h / 2);
	if (d < (w * 3 / 8)*(w * 3 / 8))
		return true;
	return false;
}

void ColorHistogram::extract(Vect& v)
{
	v = Vect();
	int i, j;
	int d1[DIM1], d2[DIM2], d3[DIM3];
	memset(d1, 0, sizeof(d1));
	memset(d2, 0, sizeof(d2));
	memset(d3, 0, sizeof(d3));

	double p1, p2, p3;//三个色彩维度
	double r1, r2, r3;//每个维度被等分成若干份，其中每份的数量

	r1 = double(MAX1) / DIM1;
	r2 = double(MAX2) / DIM2;
	r3 = double(MAX3) / DIM3;

	for (i = 0; i < src.rows; i++)
	{
		for (j = 0; j < src.cols; j++)
		{
			p1 = src _1;
			p2 = src _2;
			p3 = src _3;
			d1[(int(p1 / r1) < DIM1 - 1 ? int(p1 / r1) : DIM1 - 1)] += inblock(j, i) ? 分块;
			d2[(int(p2 / r2) < DIM2 - 1 ? int(p2 / r2) : DIM2 - 1)] += inblock(j, i) ? 分块;
			d3[(int(p3 / r3) < DIM3 - 1 ? int(p3 / r3) : DIM3 - 1)] += inblock(j, i) ? 分块;
		}
	}
	int sum1 = 0, sum2 = 0, sum3 = 0;

	for (i = 0; i < DIM1; i++)
	{
		v.data[i] = d1[i];
		sum1 += d1[i];
	}
	for (i = 0; i < DIM2; i++)
	{
		v.data[i + DIM1] = d2[i];
		sum2 += d2[i];
	}
	for (i = 0; i < DIM3; i++)
	{
		v.data[i + DIM1 + DIM2] = d3[i];
		sum3 += d3[i];
	}
	for (i = 0; i < DIM1; i++)
	{
		v.data[i] *= 100000. / sum1;
	}
	for (i = 0; i < DIM2; i++)
	{
		v.data[i + DIM1] *= 100000. / sum2;
	}
	for (i = 0; i < DIM3; i++)
	{
		v.data[i + DIM1 + DIM2] *= 100000. / sum3;
	}
}

void ColorHistogram::autowork(string filepaths, string filenames, string outpath)
{
	int i;
	ifstream fin(filenames);
	ofstream fout(outpath);

	//int n;
	//fin >> n;
	string path;
	Vect v;
#if 标准格式==1
	fout << "tech nmos\n<< polysilicon >>\n";
	//for (i = 0; i < n; i++)
	i = 0;
	while (!fin.fail())
	{
		fin >> path;
		init(filepaths + path);
		if (滤波)
			gaussblur();
		if (toHSV)
			rgb2hsv();
		extract(v);
		fout << "rect";
		for (int j = 0; j < DIM; j++)
		{
			fout << " " << v[j];
		}
		fout << endl;
		std::cout << std::setbase(16) << i << endl;
		i++;
	}
	fout<<"<< end >>\n";
#endif
#if 标准格式==0
	fout << DIM << endl;
	//for (i = 0; i < n; i++)
	while (!fin.fail())
	{
		fin >> path;
		init(filepaths + path);
		if (滤波)
			gaussblur();
		if (toHSV)
			rgb2hsv();
		extract(v);
		fout << std::setw(25) << path;
		for (int j = 0; j < DIM; j++)
		{
			fout << std::setw(10) << v[j];
		}
		fout << endl;
		std::cout << std::setbase(16) << i << endl;
	}

#endif
#if 标准格式==-1
	//for (i = 0; i < n; i++)

	while (!fin.fail())
	{
		fin >> path;
		init(filepaths + path);
		if (滤波)
			gaussblur();
		if (toHSV)
			rgb2hsv();
		extract(v);
		string label = "";
		int j = 1;
		while (path[j] != '_')
		{
			label += path[j];
			j++;
		}
		fout << label;
		for (j = 0; j < DIM; j++)
		{
			fout << ' ' << j + 1 << ':' << v[j];
		}
		fout << endl;
		std::cout << std::setbase(16) << i << "\t" << path << endl;
	}
#endif
	fin.close();
	fout.close();
}