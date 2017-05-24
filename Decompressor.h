#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
typedef enum {D_NO_ERROR, D_FILE_CORRUPTED,D_FILE_NO_EXISTS}errorTypes_t;
using namespace std;
class Decompressor
{
public:
	Decompressor(string filePath);
	~Decompressor();
	bool extract();
	bool extract(string filePath);
	int getError();
protected:
	void recursive(int x0, int x1,int y0, int y1);
	void drawSqare(char r, char g, char b, int x0, int x1, int y0, int y1);
	int imgSize;
	char * img;
	char * outImg;
	fstream FileRaw;
private:
	void initDecompressor(string filePath);
	int error;
	int imageCounter;
};

