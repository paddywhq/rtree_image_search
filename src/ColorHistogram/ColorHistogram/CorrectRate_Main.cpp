#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "RTree.h"
using namespace std;

#define DIMS 9 //更改维数
#define DATACOUNT 5613 //更改数据量
#define SEARCHCOUNT 11 //更改查找数

struct ImageData
{
	string name;
	double eigen[DIMS];
};

int main()
{
	int resultcount = 0, correctresult = 0;

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
			newImage->eigen[j] /= 100;
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

	double searchDot[DIMS];
	ImageData** result = new(ImageData*[SEARCHCOUNT]);

	for(int i = 0; i < DATACOUNT; i++)
	{
		for(int j = 0; j < DIMS; j++)
		{
			searchDot[j] = data[i]->eigen[j];
		}
		tree.KSearch(searchDot, searchDot, SEARCHCOUNT, result);

		resultcount += 10;

		for(int j = 0; j < SEARCHCOUNT; j++)
		{
			if(data[i]->name.substr(0, 9) == result[j]->name.substr(0, 9))
				correctresult++;
		}
		correctresult--;
	}

	cout<<(double)correctresult/(double)resultcount<<endl;

	return 0;
}