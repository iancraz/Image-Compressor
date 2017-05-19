#include "Tile.h"


Tile::Tile(const char* FileName)
{
	Selected=false;
	this->FileName= FileName;
}

void Tile::toggle ()
{
	Selected==true?Selected=false:Selected=true;
	//animacion que se selecciono 
}

bool Tile::isSelected ()
{
	return Selected;
}

std::string Tile::getFileName ()
{
	return FileName;
}
void Tile::Draw (int x, int y)
{
}