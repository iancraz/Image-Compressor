#include "Tile.h"
#include <cmath>
#include "Board.h"
#define TILE_SIZE	BLOCK_SIZE
#define IMG_DEFASAJEX	0
#define IMG_DEFASAJEY	0

Tile::Tile(char* FileName,unsigned char * img,int x,ALLEGRO_BITMAP * myBitmap)
{
	Selected=false;
	this->FileName = FileName;
	this->img = img;
	this->myBitmap = myBitmap;
	imgWidth = x;
	imgHeight = imgWidth;
	x = 0;
	y = 0;
	return;
}

bool Tile::toggle(ALLEGRO_BITMAP * selectedImg)
{
	Selected==true?Selected=false:Selected=true;
	if(myBitmap == NULL || selectedImg==NULL || x==0 || y == 0)
		return false;
	al_draw_scaled_bitmap(myBitmap,(float)x,(float)y,imgWidth,imgHeight,(float)x,(float)y,TILE_SIZE,TILE_SIZE,0);
	if(Selected==true)
		al_draw_bitmap(selectedImg,(x+IMG_DEFASAJEX),(y+IMG_DEFASAJEY),0);
	return true;
}

bool Tile::isSelected()
{
	return Selected;
}

std::string Tile::getFileName()
{
	return FileName;
}
bool Tile::draw (int x, int y)
{
	if(myBitmap == NULL)
		return false;
	this->x=x;
	this->y=y;
	al_draw_scaled_bitmap(myBitmap,(float)x,(float)y,imgWidth,imgHeight,(float)x,(float)y,TILE_SIZE,TILE_SIZE,0);
	return true;
}

int Tile::getImgSize()
{
	int answer = 0;
	imgHeight == imgWidth ? answer = imgHeight : answer = T_WRONG_SIZE;
	return answer;
}

unsigned char * Tile::getImgPtr()
{
	return img;
}

ALLEGRO_BITMAP * Tile::getAllegroBitmap()
{
	return myBitmap;
}