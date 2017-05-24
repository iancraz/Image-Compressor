#pragma once
#include <iostream>
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#define T_WRONG_SIZE	-1

class Tile
{
public:
	Tile(char* FileName,unsigned char * img,int x,ALLEGRO_BITMAP * myBitmap);
	Tile(string FileName);
	bool toggle(ALLEGRO_BITMAP * selectedImg);
	bool toggle(int x = 0, int y = 0);
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
	ALLEGRO_FONT *font;
	std::string FileName;
	bool Selected;
	int x,y;
	bool isImage;
};

