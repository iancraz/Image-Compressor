#pragma once
#include "Tile.h"
#include <vector>
#define	B_DISPLAY_SIZE	DISPLAY_SIZE
#define FIRST_POSITION	
#define SECOND_POSITION 
#define THIRD_POSITION

typedef unsigned int uint;
class Board
{
public:
	Board(std::vector<char> * files);
	void addTile();
	void nextPage();
	void previousPage();
	bool draw();
	void selectItem(uint tileNumber);
protected:
	std::vector<Tile> files;
	uint pageNumber;
	uint numberOfTiles;
	ALLEGRO_BITMAP * selectTile;
};

