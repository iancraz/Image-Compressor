#include "Compressor.h"

using namespace std;

Compressor::Compressor(int _width,unsigned char* _img, int _th)
{
	th= _th;
	img=_img;
	width=_width;
	myStruct.x0 = myStruct.y0=0;
	myStruct.xf = myStruct.yf=width;
}

Compressor::~Compressor(void)
{
	free(img);
}

void Compressor::quadTree(params_s * _myStruct)
{
	unsigned int x0 =_myStruct->x0, y0=_myStruct->y0,xf=_myStruct->xf,yf=_myStruct->yf;

	double Rmed= 0.0, Gmed= 0.0, Bmed= 0.0;
	unsigned char Rmax= 0, Gmax= 0, Bmax = 0;
	unsigned char Rmin= 255, Gmin = 255, Bmin = 255;
	unsigned int p = 0;
	int sumX = 4*(xf -x0);
	int sumY = 4*(yf -y0);
	for (int j=y0; j<yf; j++)
	{
		for(int i=x0; i<xf;i=i+4)
		{
			if (img[(j*width+ i)*4]>Rmax)
				Rmax = img[(j*width + i)*4];

			else if (img[(j*width + i)*4]<Rmin)
				Rmin = img[(j*width + i)*4];

			if (img[(j*width + i)*4 + 1]>Gmax)
				Gmax = img[(j*width + i)*4 + 1];

			else if (img[(j*width + i)*4 + 1]<Gmin)
				Gmin = img[(j*width + i) * 4 + 1];

			if (img[(j*width + i)*4 + 2] >Bmax)
				Bmax = img[(j*width + i) * 4 + 2];

			else if (img[(j*width + i)*4 + 2] < Bmin)
				Bmin = img[(j*width + i)*4 + 2] ;

			Rmed += img[4*(width*j+i)];
			Gmed += img[4*(width*j+i+1)];
			Bmed += img[4*(width*j+i+2)];
		}
	}
	Rmed = (Rmax + Rmin) / 2;
	Gmed = (Gmax + Gmin) / 2;
	Bmed = (Bmax + Bmin) / 2;
	
	p=((Rmax-Rmin)+(Gmax-Gmin)+(Bmax-Bmin))/3;
	if(p>th && sumX>= 1)
	{
		myList.push_back(1);
		quadTree (&changeParams (_myStruct, FIRSTBLOCK));
		quadTree (&changeParams (_myStruct, SECONDBLOCK));
		quadTree (&changeParams (_myStruct, THIRDBLOCK));
		quadTree (&changeParams (_myStruct, FOURTHBLOCK));
	}
	else
	{
		myList.push_back(0);
		myList.push_back((unsigned char)Rmed);
		myList.push_back((unsigned char)Gmed);
		myList.push_back((unsigned char)Bmed);
	}
}


params_s Compressor::changeParams(params_s * st, int type)
{
	params_s s;
	switch(type){
	case FIRSTBLOCK:
		s.x0 = st->x0;
		s.xf = ((st->x0 + st->xf)/2);
		s.y0 = st->y0;
		s.yf = ((st->y0 + st->yf)/2);
		
		return s;
		break;
	case SECONDBLOCK:
		s.x0 = ((st->x0 + st->xf)/2)+1;
		s.xf =  st->xf;
		s.y0 = st->y0;
		s.yf = ((st->y0 + st->yf)/2);
	
		return s;
		break;
	case THIRDBLOCK:
		s.x0 = st->x0;
		s.xf = ((st->x0 + st->xf)/2);
		s.y0 = ((st->y0 + st->yf)/2)+1;
		s.yf = st->yf;
		
		return s;
		break;
	case FOURTHBLOCK:
		s.x0 = ((st->x0 + st->xf)/2)+1;
		s.xf = st->xf;
		s.y0 = ((st->y0 + st->yf)/2);
		s.yf = st->yf;

		return s;
		break;

	}
}

params_s Compressor::getStructure()
{
	return myStruct;
}