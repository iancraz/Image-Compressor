#include <iostream>
#define DISPLAY_SIZE	210
#define TH 30
#define ERROR -1
#define EXTENTION	".png"
#include "Board.h"
#include "Tile.h"
#include "lodepng.h"
#include "FileSystem.h"
#include "Compressor.h"
#include <vector>
#include <allegro5/allegro.h>

uint checkPosition(ALLEGRO_MOUSE_STATE state);

using namespace std;

int main (int argc, char* argv [])
{
	ALLEGRO_DISPLAY * display;
	ALLEGRO_MOUSE_STATE state;
	if(!al_init())
	{
		cout << "Error, could not init allegro!" << endl;
		return ERROR;
	}
	al_install_mouse();

	display = al_create_display(DISPLAY_SIZE,DISPLAY_SIZE);
	if(!display)
		return ERROR;
	vector<string> images = FilesSystem(".\\resources\\",EXTENTION);
	vector<Tile> myTiles;
	unsigned char * img;
	unsigned w,h,
	char * fileName; 
	for(int i = 0 ; i < images.size(); i++)
	{
		fileName = convert2CharPointer(images[i]);
		lodepng_decode32_file(&img,&w,&h,fileName);
		myTiles.push_back(Tile(fileName,img,w));
	}
	Board myBoard(&myTiles);
	myTiles.clear();
	myBoard.draw();
	selectTile(&myBoard);
	for(int i = 0; i < myBoard.files.size(); i++)
	{
		if(myBoard.files[i].isSelected())
		{
			Compressor myCarlos(myBoard.files[i].imgHeight, myBoard.files[i].img, TH);
			myCarlos.quadTree(&myCarlos.myStruct);
			myCarlos.
		}
	}


	al_destroy_display(display);
}


void selectTile(Board * myBoard)
{
	uint tileNumber = 11;
	al_get_mouse_state(&state);
	while(tileNumber != 11)
	{
		if(state.buttons & 1)
		{
			tileNumber = checkPosition(&state);
			myBoard->selectItem(tileNumber);
			myBoard->draw();
		}
	}
	return;
}

/*Funcion que chequea en que bloque o boton clickeo el mouse, si clickeo en el primer bloque
devuelve un 1, asi sucesivamente. Si cliqueo en el boton "anterior", devuelve un 10,
si clickeo en eñl boton "OK" devuelve un 11, si qclickeo en pasar a la siguiente pagina
devuevle un 12, y si no clickeo nada valido devuelve un 0*/

uint checkPosition(ALLEGRO_MOUSE_STATE state)
{
	uint answer = 0;
	if((state.x > FIRST_POSITION)&&(state.x < (FIRST_POSITION+BLOCK_SIZE)))
	{
		if((state.y > FIRST_POSITION)&&(state.y <(FIRST_POSITION+BLOCK_SIZE)))
			answer = 1;
		else if((state.y > SECOND_POSITION)&&(state.y <(SECOND_POSITION+BLOCK_SIZE)))
			answer = 4;
		else if((state.y > THIRD_POSITION)&&(state.y <(THIRD_POSITION+BLOCK_SIZE)))
			answer = 7;
		else 
			answer = 0;
	}
	else if ((state.x > SECOND_POSITION)&&(state.x < (SECOND_POSITION+BLOCK_SIZE)))
	{
		if((state.y > FIRST_POSITION)&&(state.y <(FIRST_POSITION+BLOCK_SIZE)))
			answer = 2;
		else if((state.y > SECOND_POSITION)&&(state.y <(SECOND_POSITION+BLOCK_SIZE)))
			answer = 5;
		else if((state.y > THIRD_POSITION)&&(state.y <(THIRD_POSITION+BLOCK_SIZE)))
			answer = 8;
		else 
			answer = 0;
	}
	else if ((state.x > THIRD_POSITION)&&(state.x < (THIRD_POSITION+BLOCK_SIZE)))
	{
		if((state.y > FIRST_POSITION)&&(state.y <(FIRST_POSITION+BLOCK_SIZE)))
			answer = 3;
		else if((state.y > SECOND_POSITION)&&(state.y <(SECOND_POSITION+BLOCK_SIZE)))
			answer = 6;
		else if((state.y > THIRD_POSITION)&&(state.y <(THIRD_POSITION+BLOCK_SIZE)))
			answer = 9;
		else 
			answer = 0;
	}
	else if((answer == 0)&&(state.x < SPACE_BETWEEN)&&(state.y > (BLOCK_SIZE*3+SPACE_BETWEEN*3)))
		return 10;
	else if((answer == 0)&&(state.x > SECOND_POSITION)&&(state.x < (SECOND_POSITION+BLOCK_SIZE))&&(state.y > (BLOCK_SIZE*3+SPACE_BETWEEN*3)))
		return 11;
	else if((answer == 0)&&(state.x > (THIRD_POSITION+BLOCK_SIZE))&&(state.y > (BLOCK_SIZE*3+SPACE_BETWEEN*3)))
		return 12;
	return answer;
}
