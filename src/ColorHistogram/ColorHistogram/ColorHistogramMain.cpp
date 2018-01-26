
#include "ColorHistogram.h"
#include "ManhattanDistance.h"
#if ≤‚ ‘

//#define SEARCH

#ifndef SEARCH 
int main()
{
	string imgpath = IMGPATH;
	string filename = PATH + "imagelist.txt";

	ColorHistogram ch;
	ch.autowork(imgpath, filename, "output.txt");

	return 0;
}
#else
int main()
{
	int i;
	Vect v;
	for (i = 0; i < DIM; i++)
	{
		cin >> v.data[i];
	}
	searchVect(v);
}
#endif
#endif