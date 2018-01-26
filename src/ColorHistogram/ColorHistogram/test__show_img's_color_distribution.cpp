//#include "ColorHistogram.h"
//#define FILE "n01923025_8235.JPEG"
//#if 测试
//#else
//int hsv2rgb(int kind, int h, int s, int v)
//{
//	int h1 = h * 2;
//	double s1 = double(s) / 255;
//	double v1 = double(v) / 255;
//	int hh = h1 / 60;
//	double a[3];
//	double f = double(h1) / 60 - hh;
//	double p = v1*(1 - s1);
//	double q = v1*(1 - f*s1);
//	double t = v1*(1 - (1 - f)*s1);
//	switch (hh)
//	{
//	case 0:a[0] = v1; a[1] = t; a[2] = p; break;
//	case 1:a[0] = q; a[1] = v1; a[2] = p; break;
//	case 2:a[0] = p; a[1] = v1; a[2] = t; break;
//	case 3:a[0] = p; a[1] = q; a[2] = v1; break;
//	case 4:a[0] = t; a[1] = p; a[2] = v1; break;
//	case 5:a[0] = v1; a[1] = p; a[2] = q; break;
//	}
//	return a[kind] * 255;
//}
//
//int hsv2rgb2(int kind, int h)
//{
//	if (h == 360)
//		h = 359;
//	int h1 = h;
//	double s1 = 1, v1 = 1;
//	int hh = h1 / 60;
//	double a[3];
//	double f = double(h1) / 60 - hh;
//	double p = v1*(1 - s1);
//	double q = v1*(1 - f*s1);
//	double t = v1*(1 - (1 - f)*s1);
//	switch (hh)
//	{
//	case 0:a[0] = v1; a[1] = t; a[2] = p; break;
//	case 1:a[0] = q; a[1] = v1; a[2] = p; break;
//	case 2:a[0] = p; a[1] = v1; a[2] = t; break;
//	case 3:a[0] = p; a[1] = q; a[2] = v1; break;
//	case 4:a[0] = t; a[1] = p; a[2] = v1; break;
//	case 5:a[0] = v1; a[1] = p; a[2] = q; break;
//	}
//	return a[kind] * 255;
//}
//
//int main()
//{
//	ColorHistogram ch;
//	string file;
//	//std::cin >> file;
//	file = FILE;
//	ch.init(IMGPATH + file);
//	ch.gaussblur();
//	Mat src1 = ch.src;
//
//	for (int i = 0; i < ch.src.rows; i++)
//	{
//		for (int j = 0; j < ch.src.cols; j++)
//		{
//			if (ch.inblock(j, i))
//			{
//				src1 _1 = 255 < src1 _1 + 40 ? 255 : src1 _1 + 40;
//				src1 _2 = 255 < src1 _2 + 40 ? 255 : src1 _2 + 40;
//				src1 _3 = 255 < src1 _3 + 40 ? 255 : src1 _3 + 40;
//			}
//		}
//	}
//
//	imshow("模糊后的图像&分块区域", src1);
//
//	ch.rgb2hsv();
//	Vect v;
//	ch.extract(v);
//	Mat img;
//	img = Mat(540, 960, CV_8UC3);
//	int h1 = 180;
//	int h2 = 360;
//	int h3 = 540;
//	int s1, s2, s3;
//	s1 = s2 = s3 = 0;
//	int i;
//	for (i = 0; i < DIM1; i++)
//		s1 += v[i];
//	for (i = 0; i < DIM2; i++)
//		s2 += v[DIM1 + i];
//	for (i = 0; i < DIM3; i++)
//		s3 += v[DIM1 + DIM2 + i];
//
//	double t = 0, t1;
//	int sum = 0, sum1;
//
//
//	double z = 0;
//	int z0;
//	for (i = 0; i < DIM1; i++)
//	{
//		if (z < v[i])
//		{
//			z = v[i];
//			z0 = i;
//		}
//	}
//	z = z0;
//	//z /= s1;
//	z *= 180. / DIM1;
//	double y = 0;
//	int y0;
//	for (i = 0; i < DIM1; i++)
//	{
//		if (y < v[DIM1 + i])
//		{
//			y = v[DIM1 + i];
//			y0 = i;
//		}
//	}
//	y = y0;
//	//y /= s2;
//	y *= 255. / DIM2;
//	if (y < 50) y = 50;
//
//	double x = 0;
//	int x0;
//	for (i = 0; i < DIM3; i++)
//	{
//		if (x < v[DIM1 + DIM2 + i])
//		{
//			x = v[DIM1 + DIM2 + i];
//			x0 = i;
//		}
//	}
//	x = x0;
//	//x /= s3;
//	x *= 255. / DIM3;
//	if (x < 50) x = 50;
//	if (x>200) x = 200;
//	//int r0 = hsv2rgb2(0, z);
//	//int g0 = hsv2rgb2(1, z);
//	//int b0 = hsv2rgb2(2, z);
//
//	for (i = 0; i < DIM1; i++)
//	{
//		sum1 = sum;
//		t1 = t;
//		t = v[i];
//		t *= 960;
//		t /= s1;
//		t += t1;
//		sum += v[i];
//		rectangle(img, Point(t1, 0), Point(t, h1),
//			cvScalar(
//			hsv2rgb(2, double(i) / DIM1 * 180, y, x),
//			hsv2rgb(1, double(i) / DIM1 * 180, y, x),
//			hsv2rgb(0, double(i) / DIM1 * 180, y, x)
//			), -1);
//		//if (v[i]>1000)
//		//	std::cout << v[i] << ' ' << double(sum + sum1) / s1 * 360 / 2  << ' ' << hsv2rgb2(0, double(sum + sum1) / s1 * 360 / 2) << ' ' << hsv2rgb2(1, double(sum + sum1) / s1 * 360 / 2) << " " << hsv2rgb2(2, double(sum + sum1) / s1 * 360 / 2) << endl;
//	}
//	sum = sum1 = 0;
//	t = t1 = 0;
//	for (i = 0; i < DIM2; i++)
//	{
//		sum1 = sum;
//		t1 = t;
//		t = v[i + DIM1];
//		t *= 960;
//		t /= s2;
//		t += t1;
//		sum += v[i + DIM1];
//		rectangle(img, Point(t1, h1), Point(t, h2),
//			cvScalar(
//			hsv2rgb(2, z, double(i + 1) / DIM2 * 255, x),
//			hsv2rgb(1, z, double(i + 1) / DIM2 * 255, x),
//			hsv2rgb(0, z, double(i + 1) / DIM2 * 255, x)
//			), -1);
//		//if (v[i]>1000)
//		//	std::cout << v[i] << ' ' << double(sum + sum1) / s1 * 360 / 2  << ' ' << hsv2rgb2(0, double(sum + sum1) / s1 * 360 / 2) << ' ' << hsv2rgb2(1, double(sum + sum1) / s1 * 360 / 2) << " " << hsv2rgb2(2, double(sum + sum1) / s1 * 360 / 2) << endl;
//	}
//	sum = sum1 = 0;
//	t = t1 = 0;
//	for (i = 0; i < DIM3; i++)
//	{
//		sum1 = sum;
//		t1 = t;
//		t = v[i + DIM1 + DIM2];
//		t *= 960;
//		t /= s2;
//		t += t1;
//		sum += v[i + DIM1 + DIM2];
//		rectangle(img, Point(t1, h2), Point(t, h3),
//			cvScalar(
//			hsv2rgb(2, z, y, double(i + 1) / DIM3 * 255),
//			hsv2rgb(1, z, y, double(i + 1) / DIM3 * 255),
//			hsv2rgb(0, z, y, double(i + 1) / DIM3 * 255)
//			), -1);
//		//if (v[i]>1000)
//		//	std::cout << v[i] << ' ' << double(sum + sum1) / s1 * 360 / 2  << ' ' << hsv2rgb2(0, double(sum + sum1) / s1 * 360 / 2) << ' ' << hsv2rgb2(1, double(sum + sum1) / s1 * 360 / 2) << " " << hsv2rgb2(2, double(sum + sum1) / s1 * 360 / 2) << endl;
//	}
//	for (i = 0; i < DIM; i++)
//		std::cout << v[i] << ' ';
//	Mat src = imread(IMGPATH + file);
//	imshow("", img);
//
//	imshow("src", src);
//	cvWaitKey();
//	return 0;
//}
//
//#endif 