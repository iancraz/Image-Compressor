#include "Board.h"
#include <iostream>
#include <allegro5/allegro.h>

using namespace std;

Board::Board(std::vector<Tile> * files)
{
	pageNumber =0;
	this->files = *files;
	numberOfTiles = files->size();
	char * fileName = "resources/selectedTile.bmp";
	selectedTile = al_load_bitmap(fileName);
	if(selectedTile == NULL)
		cout << "Could Not Load Image: " << fileName << endl;
	return;
}

void Board::nextPage()
{
	if(numberOfTiles/9 == 1 && numberOfTiles % 9 == 0)
		return;
	pageNumber++;
	draw();
	return;
}
void Board::previousPage()
{
	if(pageNumber == 0)
		return;
	pageNumber--;
	draw();
	return;
}

bool Board::draw()
{
	int x,y;
	x=FIRST_POSITION;
	y=x;
	bool no_error = true;
	for(int i = 0; i<=9;i++)
	{
		if(x==THIRD_POSITION)
		{
			x =	FIRST_POSITION;
			if (y==FIRST_POSITION)
				y = SECOND_POSITION;
			else if( y== SECOND_POSITION)
				y=THIRD_POSITION;
		}
		else if(x==SECOND_POSITION)
			x = THIRD_POSITION;
		else
			x = SECOND_POSITION;
		no_error = files[pageNumber+i].draw(x,y);
		if(no_error == false)
			return no_error;
	}
	al_flip_display();
	return no_error;
}

void Board::selectItem(uint tileNumber)
{
	if(selectedTile == NULL)
		return;
	files[tileNumber].toggle(selectedTile);
	return;
}

void Board::addTile(Tile * newTile)
{
	if (newTile == NULL)
		return;
	files.push_back(*newTile);
	return;
}