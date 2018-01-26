//#include "ManhattanDistance.h"
//#include <cmath>
//int dis(Vect& v1, Vect& v2)
//{
//	int i;
//	int s = 0;
//	for (i = 0; i < DIM; i++)
//	{
//		s += abs(v1[i] - v2[i]);
//	}
//	return s;
//}
//
//void searchVect(Vect& v)
//{
//	//	string file = "A:\\vs\\ColorHistogram\\ColorHistogram\\output_5_2_2_user.txt";
//	string file = "C:\\Users\\Zhou Bowei\\Desktop\\color_feature2.txt";
//
//	ifstream fin(file);
//	string s;
//	getline(fin, s);
//	int i, j;
//	unsigned d[5613];
//	string names[5613];
//
//	int min = 1000000000;
//	int t;
//
//	for (i = 0; i < 5613; i++)
//	{
//		fin >> names[i];
//		Vect v2;
//		for (j = 0; j < DIM; j++)
//		{
//			fin >> v2.data[j];
//		}
//		d[i] = dis(v, v2);
//		if (d[i] < min)
//		{
//			min = d[i];
//			t = i;
//		}
//	}
//
//	for (i = 0; i < 5613; i++)
//	{
//		for (j = 5612; j >i; j--)
//		{
//			if (d[j - 1] > d[j])
//			{
//				int c = d[j - 1];
//				d[j - 1] = d[j];
//				d[j] = c;
//				string na = names[j - 1];
//				names[j - 1] = names[j];
//				names[j] = na;
//			}
//		}
//	}
//	for (i = 0; i < 5; i++)
//		imshow(names[i], imread(IMGPATH + names[i], 1));
//	cvWaitKey();
//}