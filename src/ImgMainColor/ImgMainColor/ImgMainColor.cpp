#include"ImgMainColor.h"
#include<cmath>

void MainColor::init(string filepath)
{
	src = imread(filepath, 1);
}

void MainColor::gaussblur(int size)
{
	Mat s = src;
	GaussianBlur(s, src, Size(size, size), 0, 0, 4);//使用高斯模糊
}

void MainColor::rgb2hsv()
{
	Mat s = src;
	//imshow("", src);
	cv::cvtColor(s, src, CV_BGR2HSV);
}

void MainColor::twoMainColors(Color&r1, Color&r2)
{
	int w, h;
	w = src.cols;
	h = src.rows;
	double colors[24][20][20];
	memset(colors, 0, sizeof(colors));
	int i, j;
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w; j++)
		{
			int h0 = src _1 / 9 + 2;
			int s0 = src _2 / 16 + 2;
			int v0 = src _3 / 16 + 2;
			colors[h0][s0][v0] += 0.22508352;
			colors[h0 - 1][s0][v0] += 0.11098164;
			colors[h0][s0 - 1][v0] += 0.11098164;
			colors[h0][s0][v0 - 1] += 0.11098164;
			colors[h0 - 2][s0][v0] += 0.01330373;
			colors[h0][s0 - 2][v0] += 0.01330373;
			colors[h0][s0][v0 - 2] += 0.01330373;
			colors[h0 - 1][s0 - 1][v0] += 0.01330373;
			colors[h0][s0 - 1][v0 - 1] += 0.01330373;
			colors[h0 - 1][s0][v0 - 1] += 0.01330373;
			colors[h0 + 1][s0][v0] += 0.11098164;
			colors[h0][s0 + 1][v0] += 0.11098164;
			colors[h0][s0][v0 + 1] += 0.11098164;
			colors[h0 + 2][s0][v0] += 0.01330373;
			colors[h0][s0 + 2][v0] += 0.01330373;
			colors[h0][s0][v0 + 2] += 0.01330373;
			colors[h0 + 1][s0 + 1][v0] += 0.01330373;
			colors[h0][s0 + 1][v0 + 1] += 0.01330373;
			colors[h0 + 1][s0][v0 + 1] += 0.01330373;
		}
	}
	double color[20][16][16];
	int k;
	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < 16; j++)
		{
			for (k = 0; k < 16; k++)
			{
				color[i][j][k] = colors[i + 2][j + 2][k + 2];
			}
		}
	}
	for (j = 0; j < 16; j++)
	{
		for (k = 0; k < 16; k++)
		{
			color[0][j][k] += colors[22][j][k];
			color[1][j][k] += colors[23][j][k];
			color[18][j][k] += colors[0][j][k];
			color[19][j][k] += colors[1][j][k];
		}
	}
	double max1 = 0, max2 = 0;
	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < 16; j++)
		{
			for (k = 0; k < 16; k++)
			{
				if (max1 < color[i][j][k])
				{
					max1 = color[i][j][k];
					r1.h = i;
					r1.s = j;
					r1.v = k;
				}
			}
		}
	}
	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < 16; j++)
		{
			for (k = 0; k < 16; k++)
			{
				if (dis(Color(i*9,j*16,k*16),Color(r1.h*9,r1.s*16,r1.v*16))>0.36)//((abs(i - r1.h)>2) && (abs(i - r1.h + 20)>2) && (abs(i - r1.h - 20)>2))|| (r1.v<2&&k>3))// && ((j<r1.s - 1)|| (j>r1.s + 1)) && ((k<r1.v - 1) || (k>r1.v + 1)))
				if (max2 < color[i][j][k])
				{
					max2 = color[i][j][k];
					r2.h = i;
					r2.s = j;
					r2.v = k;
				}
			}
		}
	}
	r1.h *= 9;
	r1.s *= 16;
	r1.v *= 16;
	r2.h *= 9;
	r2.s *= 16;
	r2.v *= 16;
	s1 = r1;
	s2 = r2;
	//cout << r1.h * 2 << ' ' << r1.s * 100 / 255 << ' ' << r1.v * 100 / 255 << endl;
	//cout << r2.h * 2 << ' ' << r2.s * 100 / 255 << ' ' << r2.v * 100 / 255 << endl;
}

double MainColor::dis(Color& c1, Color& c2)
{
	//double t = abs(c1.h - c2.h);
	//if (t > 180-t) t = 180-t;
	//return 3*pow(t, 2) + pow(c1.s - c2.s, 2) + pow(c1.v - c2.v, 2);
	double x1, x2, y1, y2, z1, z2;
	x1 = c1.v / 256 * c1.s / 256 * cos(c1.h / 180 * 3.141592654 * 2);
	y1 = c1.v / 256 * c1.s / 256 * sin(c1.h / 180 * 3.141592654 * 2);
	x2 = c2.v / 256 * c2.s / 256 * cos(c2.h / 180 * 3.141592654 * 2);
	y2 = c2.v / 256 * c2.s / 256 * sin(c2.h / 180 * 3.141592654 * 2);
	z1 = c1.v / 256;
	z2 = c2.v / 256;
	return pow(x1 - x2, 2) + pow(y1 - y2, 2) + pow(z1 - z2, 2);
}

double cvt(Color& c1, int a)
{
	double x = c1.v / 256 * c1.s / 256 * cos(c1.h / 180 * 3.141592654 * 2);
	double y = c1.v / 256 * c1.s / 256 * sin(c1.h / 180 * 3.141592654 * 2);
	double z = c1.v / 256;
	if (a == 1) return x;
	if (a == 2) return y;
	return z;
}

void cvt2(Color& c, Color&s)
{
	s.v = 256 * c.v;
	s.s = 256 * sqrt(c.h*c.h + c.s*c.s) / c.v;
	/*double t = atan(c.s / c.h);
	s.h = 180*t/3.141592654;
	if (s.h < 0) s.h += 180;
	if (c.h < 0) s.h += 180;*/
	double t = atan2(c.s, c.h);
	s.h = 180 * t / 3.141592654;
	if (s.h < 0) s.h += 360;
	s.h /= 2;
}

void MainColor::extract(Vect& v,string name)
{
	int w, h;
	w = src.cols;
	h = src.rows;
	int i, j;
	double cx = (double)w / 2, cy = (double)h / 2;
	/*int** r;
	r = new int*[h];
	for (i = 0; i < h; i++)
	r[i] = new int[w];*/

	int p1=0, p2=0;//用于计算归为两种颜色的像素数
	double q1=0, q2=0;//每种颜色到对应平均色的距离的平均值即方差
	double d1=0, d2=0;//计算每个像素到中心点曼哈顿距离的均值
	Color c1,c2;
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w; j++)
		{
			int h0 = src _1;
			int s0 = src _2;
			int v0 = src _3;
			double dis1 = dis(Color(h0, s0, v0), s1);
			double dis2 = dis(Color(h0, s0, v0), s2);
			if (dis1<dis2)
			{
				//r[i][j] = 2;
				p1++;
				c1.h += cvt(Color(h0,s0,v0),1);
				c1.s += cvt(Color(h0,s0,v0),2);
				c1.v += cvt(Color(h0,s0,v0),3);
			}
			else
			{
				//r[i][j] = 1;
				p2++;
				c2.h += cvt(Color(h0, s0, v0), 1);
				c2.s += cvt(Color(h0, s0, v0), 2);
				c2.v += cvt(Color(h0, s0, v0), 3);
			}
		}
	}
	c1.h/=p1;
	c1.s/=p1;
	c1.v/=p1;
	c2.h/=p2;
	c2.s/=p2;
	c2.v/=p2;
	cvt2(c1, s1);
	cvt2(c2, s2);
#if TEST
	cout << s1.h << ' ' << s1.s << ' ' << s1.v << endl;
	cout << s2.h << ' ' << s2.s << ' ' << s2.v << endl;
#endif

	p1 = p2 = 0;
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w; j++)
		{
			int h0 = src _1;
			int s0 = src _2;
			int v0 = src _3;
			double dis1 = dis(Color(h0, s0, v0), s1);
			double dis2 = dis(Color(h0, s0, v0), s2);
			if (dis1<dis2)
			{
				//r[i][j] = 2;
				p1++;
				q1 += dis1;
				d1 += double(abs(i-cx))/cx + double(abs(j-cy))/cy;
#if TEST
				src _1 = s1.h;
				src _2 = s1.s;
				src _3 = s1.v;
#endif
			}
			else
			{
				//r[i][j] = 1;
				p2++;
				q2 += dis2;
				d2 += double(abs(i - cx))/cx + double(abs(j - cy))/cy;
#if TEST
				src _1 = s2.h;
				src _2 = s2.s;
				src _3 = s2.v;
#endif
			}
		}
	}
	d1 /= (0.001 + p1);
	d2 /= (0.001 + p2);
	if (d1 > d2)
	{
		double c = d1;
		d1 = d2;
		d2 = c;
		c = p1;
		p1 = p2;
		p2 = c;
		Color s = s1;
		s1 = s2;
		s2 = s;
	}
	q1 /= (0.001+p1);//防止除以0
	q2 /= (0.001+p2);
	double x1, x2, y1, y2, z1, z2;
	x1 = s1.v / 256 * s1.s / 256 * cos(s1.h / 180 * 3.141592654 * 2);
	y1 = s1.v / 256 * s1.s / 256 * sin(s1.h / 180 * 3.141592654 * 2);
	x2 = s2.v / 256 * s2.s / 256 * cos(s2.h / 180 * 3.141592654 * 2);
	y2 = s2.v / 256 * s2.s / 256 * sin(s2.h / 180 * 3.141592654 * 2);
	z1 = s1.v / 256;
	z2 = s2.v / 256;
	//0~5: 中心特征色/边缘特征色在xyz坐标系的位置
	//6~7: 中心特征色/边缘特征色区域的颜色差距方差
	//8: 中心特征色区的聚集程度: 所有颜色到中心L1距离和/(像素个数)^2
	v.data[0] = x1;
	v.data[1] = y1;
	v.data[2] = z1;
	v.data[3] = x2;
	v.data[4] = y2;
	v.data[5] = z2;
	v.data[6] = q1;
	v.data[7] = q2;
	v.data[8] = d1;
	//for (i = 0; i < 8; i++)
	//	cout << v[i] << endl;
#if TEST
	Mat s = src;
	cv::cvtColor(s, src, CV_HSV2BGR);
	cv::imshow(name, src);
	cvWaitKey(0);
#endif
	/*for (i = 0; i < h; i+=10)
	{
	for (j = 0; j < w; j+=5)
	{
	cout << r[i][j];
	}
	cout << endl;
	}*/
}
