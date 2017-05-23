#pragma once
#include <iostream>
#include <allegro5/allegro.h>
#define TILE_SIZE	50

class Tile
{
public:
	Tile(char* FileName,unsigned char * img,int x,ALLEGRO_BITMAP * myBitmap);
	bool toggle(ALLEGRO_BITMAP * selectedImg);
	bool isSelected ();
	std::string getFileName ();
	bool draw (int x, int y);
	int imgHeight,imgWidth;
	unsigned char * img;
	ALLEGRO_BITMAP	* myBitmap;
protected:
	std::string FileName;
	bool Selected;
	int x,y;
};

