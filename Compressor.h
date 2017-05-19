#pragma once
#include <fstream>
typedef struct 
{
	char *img;
	unsigned int x0,y0,xf,yf;
	FILE * myFile;
}params_s;

class Compressor
{
public:
	Compressor(void);
	~Compressor(void);
	void quadTree(params_s * _myStruct);
protected:
	params_s myStruct;
};

