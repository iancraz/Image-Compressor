#pragma once
#include <iostream>
#include <allegro5/allegro.h>
#define TILE_SIZE	50

class Tile
{
public:
	Tile(char* FileName,unsigned char * img,int x);
	bool toggle(ALLEGRO_BITMAP * selectedImg);
	bool isSelected ();
	std::string getFileName ();
	bool draw (int x, int y);
	int imgHeight,imgWidth;
	unsigned char * img;
protected:
	std::string FileName;
	bool Selected;
	int x,y;
};

