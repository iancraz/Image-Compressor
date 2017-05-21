#pragma once
#include <iostream>
#include <allegro5/allegro.h>
#define TILE_SIZE	50

class Tile
{
public:
	Tile(const char* FileName,ALLEGRO_BITMAP * img);
	bool toggle(ALLEGRO_BITMAP * selectedImg);
	bool isSelected ();
	std::string getFileName ();
	bool Draw (int x, int y);
protected:
	std::string FileName;
	bool Selected;
	ALLEGRO_BITMAP * img;
	int imgHeight,imgWidth;
	int x,y;
};

