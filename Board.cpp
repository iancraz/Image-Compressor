#include "Board.h"


Board::Board(std::vector<char> * files)
{
	pageNumber =0;
	this->files = *files;
	numberOfTiles = files.size();
	return;
}


Board::~Board(void)
{
}

void Board::nextPage()
{
	if(numberOfTiles/9 == 1 && numberOfTiles % 9 == 0)
		return;
	pageNumber++;
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
	return no_error;
}