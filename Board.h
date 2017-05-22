#pragma once
#include "Tile.h"
#include <vector>
#include <allegro5/allegro.h>
#define	B_DISPLAY_SIZE	DISPLAY_SIZE
#define SPACE_BETWEEN 	20
#define BLOCK_SIZE	((B_DISPLAY_SIZE - 4*SPACE_BETWEEN)/3)
#define FIRST_POSITION	SPACE_BETWEEN
#define SECOND_POSITION (FIRST_POSITION+BLOCK_SIZE+SPACE_BETWEEN)
#define THIRD_POSITION	(SECOND_POSITION+BLOCK_SIZE+SPACE_BETWEEN)

typedef unsigned int uint;
class Board
{
public:
	Board(std::vector<Tile> * files);
	void addTile(Tile * newTile);
	void nextPage();
	void previousPage();
	bool draw();
	void selectItem(uint tileNumber);
	std::vector<Tile> files;
protected:
	uint pageNumber;
	uint numberOfTiles;
	ALLEGRO_BITMAP * selectedTile;
};

