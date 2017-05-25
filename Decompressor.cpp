#include "Decompressor.h"
#include "FileSystem.h"
#include "lodepng.h"
#include <cmath>


Decompressor::Decompressor(string filePath)
{
	initDecompressor(filePath);
	return;
}

Decompressor::~Decompressor()
{
	if(img != NULL)
		delete img;
	if (outImg != NULL)
		delete outImg;
}

bool Decompressor::extract(void)
{
	outImg = new char[imgSize*imgSize*4];
	imageCounter = 0;
	recursive(0, 0, imgSize, imgSize);
	if (error == D_FILE_CORRUPTED)
	{
		delete outImg;
		delete img;
		FileRaw.close();
		return false;
	}
	else if (error == D_FILE_NO_EXISTS)
		return false;
	else
		return true;
}

bool Decompressor::extract(string filePath)
{
	initDecompressor(filePath);
	return extract();
}	
	
void Decompressor::recursive(int x0, int x1, int y0, int y1)
{
	char byte;
	byte = img[imageCounter];
	imageCounter++;
	if (imageCounter == imgSize || error == D_FILE_CORRUPTED)
		return;
	if (byte == 0)
	{
		unsigned char red = img[imageCounter];
		imageCounter++;
		unsigned char green = img[imageCounter];
		imageCounter++;
		unsigned char blue = img[imageCounter];
		drawSqare(red, green, blue, x0, x1, y0, y1);
		imageCounter++;
		unsigned char alpha = img[imageCounter];
		imageCounter++;
		return;
	}
	else if (byte == 1)
	{

		recursive(x0, ((x1 - x0) / 2) + x0, y0, ((y1 - y0) / 2) + y0);
		recursive(((x1 - x0) / 2) + x0, x1, y0, ((y1 - y0) / 2) + y0);
		recursive(x0, ((x1 - x0) / 2) + x0, ((y1 - y0) / 2) + y0, y1);
		recursive(((x1 - x0) / 2) + x0, x1, ((y1 - y0) / 2) + y0, y1);
		return;
	}
	else
	{
		error = D_FILE_CORRUPTED;
		return;
	}
}

void Decompressor::drawSqare(char r, char g, char b, int x0, int x1,int y0, int y1)
{
	int size = x1 - x0;
	for (j=y0;j <= y1; j++)
	{
		for (int i = 0; i <= size; i++)
		{
			outImg[((i * 4) + (4 * imgSize * j)) + 0] = r;
			outImg[((i * 4) + (4 * imgSize* j)) + 1] = g;
			outImg[((i * 4) + (4 * imgSize* j)) + 2] = b; 
			outImg[((i * 4) + (4 * imgSize* j)) + 3] = 0xff; //alpha en 100
		}
	}
	return;
}

void Decompressor::initDecompressor(string filePath)
{
	FileRaw.open(filePath, fstream::in);
	error = D_NO_ERROR;
	outImg = NULL;
	img = NULL;
	imageCounter = 0;
	imgSize = 0;
	if (!FileRaw.is_open())
	{
		error = D_FILE_NO_EXISTS;
		return;
	}
	vector<char> FileVector;
	while (!FileRaw.eof())
	{
		char c;
		FileRaw.get(c);
		FileVector.push_back(c);
	}
	img = new unsigned char[FileVector.size()];
	for (size_t i = 0; i < FileVector.size(); i++)
		img[i] = FileVector[i + 4];
	imgSize = (FileVector[0] + FileVector[1] + FileVector[2] +FileVector[3]);
	return;
}

int Decompressor::getError(void)
{
	return error;
}