#include "ImgMainColor.h"

//把偏红的颜色放前面(从300°开始计算的)，然后两个的中心度都表示出来
//或者可以将两个颜色反着写，重复两个
int main()
{
#if TEST
	Color c1, c2;
	MainColor mc;
	string path = IMGPATH + "test\\lena.bmp";
	mc.init(path);
	imshow("", mc.src);
	mc.gaussblur();
	mc.rgb2hsv();
	mc.twoMainColors(c1, c2);
	Vect v;
	mc.extract(v);
#else
	Color c1, c2;
	MainColor mc;
	ifstream fin(PATH + "imagelist.txt");
	int n;
	string name;
	//fin >> n;
	ofstream fout(PATH + "output.txt");
	int i = 0;
	while (!fin.fail())
	{
		fin >> name;
		cout << name << endl;
		string path = IMGPATH + name;
		mc.init(path);
		//imshow("", mc.src);
		mc.gaussblur();
		mc.rgb2hsv();
		mc.twoMainColors(c1, c2);
		Vect v;
		mc.extract(v,name);
		string type="";

		int j = 1;
		while (name[j] != '_')
		{
			type += name[j];
			j++;
		}

		fout << type;
		for (j = 0; j < DIM; j++)
		{
			fout << ' ' <</* j + 1 << ':'<<*/v[j];
		}
		fout << endl;
		i++;
	}
#endif
	return 0;
}