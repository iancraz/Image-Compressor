#include "Tile.h"
#include <cmath>
#define IMG_DEFASAJEX	0
#define IMG_DEFASAJEY	0

Tile::Tile(char* FileName,unsigned char * img,int x)
{
	Selected=false;
	this->FileName = FileName;
	this->img = img;
	imgWidth = x;
	imgHeight = imgWidth;
	x = 0;
	y = 0;
	return;
}

bool Tile::toggle(ALLEGRO_BITMAP * selectedImg)
{
	Selected==true?Selected=false:Selected=true;
	if(img == NULL || selectedImg==NULL || x==0 || y == 0)
		return false;
	al_draw_scaled_bitmap(img,(float)x,(float)y,imgWidth,imgHeight,(float)x,(float)y,TILE_SIZE,TILE_SIZE,0);
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
bool Tile::Draw (int x, int y)
{
	if(img == NULL)
		return false;
	this->x=x;
	this->y=y;
	al_draw_scaled_bitmap(img,(float)x,(float)y,imgWidth,imgHeight,(float)x,(float)y,TILE_SIZE,TILE_SIZE,0);
	return true;
}