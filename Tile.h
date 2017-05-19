#pragma once
#include <iostream>
//#include <allegro>

class Tile
{
public:
	Tile(const char* FileName);
	void toggle ();
	bool isSelected ();
	std::string getFileName ();
	void Draw (int x, int y);

protected:
	std::string FileName;
	bool Selected;
	//ALLEGRO BIT MAP* img;


};

