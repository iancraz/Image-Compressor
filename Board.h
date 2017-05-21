#pragma once
#include "Tile.h"
#include <vector>
#include <allegro5/allegro.h>
#define	B_DISPLAY_SIZE	DISPLAY_SIZE
#define FIRST_POSITION	20
#define SECOND_POSITION (FIRST_POSITION+20)
#define THIRD_POSITION	(SECOND_POSITION+20)

typedef unsigned int uint;
class Board
{
public:
	Board(std::vector<char> * files);
	void addTile(Tile * newTile);
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

