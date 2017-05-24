#include "Tile.h"
#include <cmath>
#include <string>
#include <allegro5/allegro_ttf.h>
#include "Board.h"
#define TILE_SIZE	BLOCK_SIZE
#define IMG_DEFASAJEX	0
#define IMG_DEFASAJEY	0

using namespace std;

Tile::Tile(char* FileName,unsigned char * img,int x,ALLEGRO_BITMAP * myBitmap)
{
	isImage = true;
	Selected=false;
	this->FileName = FileName;
	this->img = img;
	this->myBitmap = myBitmap;
	imgWidth = x;
	imgHeight = imgWidth;
	this->x = 0;
	this->y = 0;
	font = NULL;
	return;
}

Tile::Tile(string FileName)
{
	Selected = true;
	isImage = false;
	myBitmap = NULL;
	img = NULL;
	imgWidth = 0;
	imgHeight = 0;
	x = 0;
	y = 0;
	this->FileName = FileName;
	font = al_load_ttf_font("resources/myFont.ttf", 0, 0);
	return;
}

bool Tile::toggle(ALLEGRO_BITMAP * selectedImg)
{
	Selected == true ? Selected = false : Selected = true;
	if (isImage == true)
	{
		if (myBitmap == NULL || selectedImg == NULL || x == 0 || y == 0)
			return false;
		al_draw_scaled_bitmap(myBitmap, (float)x, (float)y, imgWidth, imgHeight, (float)x, (float)y, TILE_SIZE, TILE_SIZE, 0);
		if (Selected == true)
			al_draw_bitmap(selectedImg, (x + IMG_DEFASAJEX), (y + IMG_DEFASAJEY), 0);
		return true;
	}
	return false;
}

bool Tile::toggle(int x, int y)
{
	if (x != 0 && y != 0)
	{
		this->x = x;
		this->y = y;
	}
	if (isImage == true)
		return false;
	char * _fileName = new char[FileName.size()];
	for (size_t i = 0; i < FileName.size(); i++)
		_fileName[i] = FileName[i];
	if (font == NULL || x == 0 || y == 0)
		return false;
	if (isSelected == false)
		al_draw_text(font, al_map_rgba(100, 100, 100, 100), x, y, 0, _fileName);
	else
		al_draw_text(font, al_map_rgba(255, 0, 0, 100), x, y, 0, _fileName);
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
	if(myBitmap == NULL || isImage == false)
		return false;
	this->x=x;
	this->y=y;
	al_draw_scaled_bitmap(myBitmap,(float)x,(float)y,imgWidth,imgHeight,(float)x,(float)y,TILE_SIZE,TILE_SIZE,0);
	return true;
}

int Tile::getImgSize()
{

	int answer = 0;
	(imgHeight == imgWidth)&&(isImage==true) ? answer = imgHeight : answer = T_WRONG_SIZE;
	return answer;
}

unsigned char * Tile::getImgPtr()
{
	if (isImage == true)
		return img;
	else
		return NULL;
}

ALLEGRO_BITMAP * Tile::getAllegroBitmap()
{
	if (isImage == true)
		return myBitmap;
	else
		return NULL;
}