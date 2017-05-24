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
	char Rmax= 0, Gmax= 0, Bmax = 0;
	char Rmin= 255, Gmin = 255, Bmin = 255;
	int p = 0;
	int sumX = 4*(xf -x0);
	int sumY = 4*(yf -y0);
	for (int j=y0; j<yf; j++)
	{
		for(int i=x0; i<xf;i++)
		{
			Rmax = fmax(Rmax,img[4*(width*j+i)]);
			Gmax = fmax(Gmax,img[4*(width*j+i)+1]);
			Bmax = fmax(Bmax,img[4*(width*j+i)+2]);
			Rmin = fmin(Rmin,img[4*(width*j+i)]);
			Gmin = fmin(Gmin,img[4*(width*j+i)+1]);
			Bmin = fmin(Bmin,img[4*(width*j+i)+2]);
			Rmed += img[4*(width*j+i)];
			Gmed += img[4*(width*j+i)+1];
			Bmed += img[4*(width*j+i)+2];
		}
	}
	Rmed /= (xf-x0)*(yf-y0);
	Gmed /= (xf-x0)*(yf-y0);
	Bmed /= (xf-x0)*(yf-y0);
	
	p=(Rmax-Rmin)+(Gmax-Gmin)+(Bmax-Bmin);
	if(p>th)
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
		myList.push_back((char)Rmed);
		myList.push_back((char)Gmed);
		myList.push_back((char)Bmed);
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