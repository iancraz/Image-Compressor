#pragma once
#include "Tile.h"
typedef unsigned int uint;
class Board
{
public:
	Board(void);
	~Board(void);
	void addTile();
	void nextPage();
	void previousPage();
	void draw();
	void selectItem(uint tileNumber);
protected:
	EDAList<Tile> files;
	uint pageNumber;
};

