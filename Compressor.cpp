#include "Compressor.h"


Compressor::Compressor(void)
{
}


Compressor::~Compressor(void)
{
}

void Compressor::quadTree(params_s * _myStruct)
{
	int i = 0;
	double Rmean= 0.0, Gmean= 0.0, Bmean= 0.0;
	char Rmax= 0, Gmax= 0, Bmax = 0;
	char Rmin= 255, Gmin = 255, Bmin = 255;

	for (i=0; i <   ; i++ )
	{
		Rmax = max(Rmax, Img(i+_myStruct->x0));
		Gmax = max(Gmax, Img(i));
		Bmax = max(Bmax, Img(i));
		Rmin = min(Rmin, Img(i));
		Gmin = min(Gmin, Img(i));
		Bmin = min(Bmin, Img(i));
	}
}