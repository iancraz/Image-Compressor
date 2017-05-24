/*Se debe ingesar por linea de comandos:
	./TP8 -mode compressor
	o
	./TP8 -mode decomressor
*/

#include <iostream>
#include "Board.h"
#include "Tile.h"
#include "lodepng.h"
#include "FileSystem.h"
#include "Compressor.h"
#include "ParseCommandLine.h"
#include <string>
#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#define DISPLAY_SIZE	640
#define TH 30
#define M_ERROR -1
#define EXTENTION	".png"
#define EXTENTION_C		".eda"
#define IMAGES_PATH	"wallpapers"
#define COMPRESSED_PATH	"compressed"

uint checkPosition(ALLEGRO_MOUSE_STATE state);
void selectTile(Board * myBoard);
bool Callback(char * key, char * value, void * structure);
bool initCompressorMode(Board * _myBoard);


using namespace std;
typedef struct 
{
	bool isCompressor;
}UserData_s;

int main(int argc, char* argv[])
{
	UserData_s UserData;
	ParseCommandLine myParse(argc, argv);
	if (myParse.PCL(Callback, &UserData) == false)
	{
		cout << "Invalid parameters" << endl;
		return M_ERROR;
	}
	ALLEGRO_DISPLAY * display;
	ALLEGRO_MOUSE_STATE state;
	if (!al_init())
	{
		cout << "Error, could not init allegro!" << endl;
		return M_ERROR;
	}
	if (!al_init_image_addon())
	{
		cout << "Error, could not init image addon!" << endl;
		return M_ERROR;
	}
	al_init_font_addon();

	display = al_create_display(DISPLAY_SIZE, DISPLAY_SIZE);
	if (!display)
	{
		cout << "Could Not Create Display!" << endl;
		return M_ERROR;
	}

	if (UserData.isCompressor)
	{
		Board myBoard;
		initCompressorMode(&myBoard);
		if (!myBoard.draw())
		{
			cout << "Could Not Display Images" << endl;
			return M_ERROR;
		}

		/*//selectTile(&myBoard);
		myBoard.selectItem(3);					SELECT TILES VIA KEYBOARD
		myBoard.selectItem(4);*/

		for (size_t i = 0; i < myBoard.files.size(); i++)
		{
			if ((myBoard.files[i].isSelected()) && (myBoard.files[i].getImgSize() != T_WRONG_SIZE))
			{
				string fileName = myBoard.files[i].getFileName();
				Compressor myCompress(myBoard.files[i].getImgSize(), myBoard.files[i].getImgPtr(), TH);
				myCompress.quadTree(&myCompress.getStructure());
				size_t i;
				for (i = 0; fileName[i] != '.'; i++);
				fileName[i + 1] = 'e';
				fileName[i + 2] = 'd';
				fileName[i + 3] = 'a';
				ofstream fout = ocreatefile(COMPRESSED_PATH, fileName);
				//Agregar el header de la imagen antes de guardarla!!!
				fout << (myCompress.myList);
			}
		}
	}
	else
	{
		Board myBoard;
		initDecompressorMode(&myBoard);
		for (size_t i = 0; i < myBoard.files.size(); i++)
		{
			myBoard.files[i].toggle()
		}
	}
	getchar();
	al_destroy_display(display);
	return EXIT_SUCCESS;
}


void selectTile(Board * myBoard)
{
	ALLEGRO_MOUSE_STATE state;
	uint tileNumber = 0;
	while(tileNumber != 11)
	{
		al_get_mouse_state(&state);
		if(state.buttons & 1)
		{
			tileNumber = checkPosition(state);
			myBoard->selectItem(tileNumber);
			myBoard->draw();
		}
		state.buttons = 0;
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

bool Callback(char * key, char * value, void * structure)
{
	if ((key == NULL && value == NULL) || structure == NULL)
		return false;
	UserData_s * UserData = (UserData_s *)structure;
	if (key == "mode")
	{
		if (value == "compressor")
			UserData->isCompressor = true;
		else if (value == "decompressor")
			UserData->isCompressor = false;
		else
			return false;
	}
	else
		return false;
	return true;
}

bool initCompressorMode(Board * _myBoard)
{
	vector<string> images = FileSystem(IMAGES_PATH, EXTENTION);
	if (images.size() == 0)
	{
		cout << "No images on the folder" << IMAGES_PATH << endl;
		return false;
	}
	vector<Tile> myTiles;
	for (size_t i = 0; i < images.size(); i++)
	{
		unsigned w = 0, h = 0;
		char * fileName = NULL;
		unsigned char * img = NULL;
		fileName = Convert2CharPointer(images[i]);
		lodepng_decode32_file(&img, &w, &h, fileName);
		if ((fileName != NULL) && (img != NULL) && (w == h) && (w != 0))
			myTiles.push_back(Tile(fileName, img, w, al_load_bitmap(fileName)));
		free(img);
	}
	_myBoard->initBoard(&myTiles);
	myTiles.clear();
	return true;
}

bool initDecompressorMode(Board * _myBoard)
{
	vector<string> compressedImgs = FileSystem(COMPRESSED_PATH, EXTENTION_C);
	if (compressedImgs.size() == 0)
	{
		cout << "No compressed images on the folder" << COMPRESSED_PATH << endl;
		return false;
	}
	vector<Tile> myTiles;
	for (size_t i = 0; i < compressedImgs.size(); i++)
		myTiles.push_back(Tile(compressedImgs[i]));
	_myBoard->initBoard(&myTiles);
	myTiles.clear();
	return true;
}