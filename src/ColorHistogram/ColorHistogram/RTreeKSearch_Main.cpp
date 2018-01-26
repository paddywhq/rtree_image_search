#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "RTree.h"
#include "ColorHistogram.h"
#include "ManhattanDistance.h"
using namespace std;

#define DIMS 9 //����ά��
#define DATACOUNT 5613 //����������
#define SEARCHCOUNT 11 //���Ĳ�����(����ԭͼ)

struct ImageData
{
	string name;
	double eigen[DIMS];
};

int main()
{
	//LoaDIMage&ExtractFeatures
	//string imgpath = IMGPATH;
	//string filename = PATH + "imagelist.txt";

#if 0
	ColorHistogram ch;
	ch.autowork(imgpath, filename, "features.txt");
#endif
	//
	RTree<ImageData*, double, DIMS> tree;

	ImageData** data = new(ImageData*[DATACOUNT]);

	string stringtemp;
	char chartemp;

	ifstream filelist;
	ifstream eigenlist;

	filelist.open("imagelist.txt");
	eigenlist.open("color_feature.txt"); //�������������ļ�

	getline(eigenlist, stringtemp);
	getline(eigenlist, stringtemp);

	for (int i = 0; i < DATACOUNT; i++)
	{
		ImageData* newImage = new ImageData;

		getline(filelist, newImage->name);
		eigenlist.get(chartemp);
		eigenlist.get(chartemp);
		eigenlist.get(chartemp);
		eigenlist.get(chartemp);
		for (int j = 0; j < DIMS; j++)
		{
			eigenlist >> newImage->eigen[j];
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

	ifstream searchlist;
	searchlist.open("color_feature.query"); //���Ĳ����ļ�

	getline(searchlist, stringtemp);
	getline(searchlist, stringtemp);
	searchlist.get(chartemp);
	searchlist.get(chartemp);
	searchlist.get(chartemp);
	searchlist.get(chartemp);

	double searchDot[DIMS];
	for(int i = 0; i < DIMS; i++)
	{
	searchlist>>searchDot[i];
	}

	searchlist.sync();
	searchlist.clear();
	searchlist.close();

	ofstream resultlist;
	resultlist.open("result.txt"); //���Ľ������ļ�

	ImageData** result = new(ImageData*[SEARCHCOUNT]);
	tree.KSearch(searchDot, searchDot, SEARCHCOUNT, result);

	for(int i = 0; i < SEARCHCOUNT; i++)
	{
	resultlist<<result[i]->name<<endl;
	}

	resultlist.clear();
	resultlist.close();

	return 0;
}