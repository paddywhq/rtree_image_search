#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "RTree.h"
using namespace std;

#define DIMS 9 //更改维数
#define DATACOUNT 5613 //更改数据量
#define SEARCHCOUNT 10 //更改查找数

struct ImageData
{
	string name;
	double eigen[DIMS];
};

int main()
{
	RTree<ImageData*, double, DIMS> tree;
	
	ImageData** data = new(ImageData*[DATACOUNT]);

	string stringtemp;
	char chartemp;

	ifstream filelist;
	ifstream eigenlist;
	
	filelist.open("imagelist.txt");
	eigenlist.open("color_feature.txt"); //更改特征向量文件

	getline(eigenlist, stringtemp);
	getline(eigenlist, stringtemp);

	for(int i = 0; i < DATACOUNT; i++)
	{
		ImageData* newImage = new ImageData;

		getline(filelist, newImage->name);
		eigenlist.get(chartemp);
		eigenlist.get(chartemp);
		eigenlist.get(chartemp);
		eigenlist.get(chartemp);
		for(int j = 0; j < DIMS; j++)
		{
			eigenlist>>newImage->eigen[j];
		}
		getline(eigenlist, stringtemp);
		tree.Insert(newImage->eigen, newImage->eigen, newImage);
		data[i] = newImage;
	}

	filelist.sync();
	filelist.clear();
	filelist.close();
	eigenlist.sync();
	eigenlist.clear();
	eigenlist.close();

	ofstream io;
	io.open("IO_count.txt"); //更改输出次数文件
	io.clear();
	io.close();

	double searchDot[DIMS];
	ImageData** result = new(ImageData*[SEARCHCOUNT]);

	for(int i = 0; i < DATACOUNT; i++)
	{
		for(int j = 0; j < DIMS; j++)
		{
			searchDot[j] = data[i]->eigen[j];
		}
		tree.KSearch(searchDot, searchDot, SEARCHCOUNT, result);

		ofstream iolist;
		iolist.open("IO_count.txt", ios::app|ios::out); //更改输出次数文件
		iolist<<tree.iocount<<endl;
		iolist.clear();
		iolist.close();
	}

	ifstream iolist;
	iolist.open("IO_count.txt"); //更改输出次数文件
	int iocount = 0, counttemp;
	for(int i = 0; i < DATACOUNT; i++)
	{
		iolist>>counttemp;
		iocount += counttemp;
	}
	cout<<double(iocount)/DATACOUNT<<endl;
	iolist.sync();
	iolist.clear();
	iolist.close();

	return 0;
}