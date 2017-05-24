#pragma once
#include <fstream>
#include <vector>
#include <cmath>
typedef enum {FIRSTBLOCK,SECONDBLOCK,THIRDBLOCK,FOURTHBLOCK}blocks_t;
typedef struct 
{
	unsigned int x0,y0,xf,yf;
}params_s;

class Compressor
{
public:
	Compressor(int _width,unsigned char* _img, int _th);
	~Compressor(void);
	void quadTree(params_s * _myStruct);
	params_s getStructure();
	std::vector<char> myList;
protected:
	params_s myStruct;
	int th;
	params_s changeParams(params_s * st, int type);
	unsigned char * img = NULL;
	int width;
};


