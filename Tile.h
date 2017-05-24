#pragma once
#include <iostream>
#include <allegro5/allegro.h>
#define T_WRONG_SIZE	-1

class Tile
{
public:
	Tile(char* FileName,unsigned char * img,int x,ALLEGRO_BITMAP * myBitmap);
	bool toggle(ALLEGRO_BITMAP * selectedImg);
	bool isSelected ();
	std::string getFileName ();
	bool draw (int x, int y);
	int getImgSize(void);
	unsigned char * getImgPtr(void);
	ALLEGRO_BITMAP * getAllegroBitmap();
protected:
	int imgHeight, imgWidth;
	unsigned char * img;
	ALLEGRO_BITMAP	* myBitmap;
	std::string FileName;
	bool Selected;
	int x,y;
};

