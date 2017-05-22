#include <iostream>
#include <boost\asio.hpp>
#include <boost\filesystem.hpp>
#include <vector>
#include <string>

using namespace std;
//abajo esta como funcionan el programas
vector<string> FileSystem(string path, string extension);
char* Convert2CharPointer(string s);
void createfile(string path, string name);
ofstream ocreatefile(string path, string name);
ostream& operator<<(ostream& o, vector<string> c);

/*El magiafile lo que hace es recibir en path de donde querés 
sacar las cosas y en extension la extensión que querés filtrar 
que puede ser de cualquier tamaño.
La extensión la podés poner como ".txt" o ".png", la que quieras,
pero lo importante es el path.
El path se tiene que poner como "c:\\carpetaprueba", por ejemplo,
si tenés una carpeta en c que se llame carpetaprueba o
podés poner "c:\\carpeta1\\carpeta2" si en c tenés una carpeta
que se llame carpeta1 y dentro de esa carpeta otra que se llame
carpeta2 y asi seguis hasta donde la cosa dé. También en path,
si lo necesitás, podes crear una carpeta nueva, por ejemplo,
si agarras el caso anterior de "c:\\carpeta1\\carpeta2",
pero con la particularidad de que carpeta2 no existe,
el programa te la crea. El tema está en que no se pueden
crear mas de 2 carpetas al mismo tiempo de esta forma, de
ser así tendrías que hacer primero 1 carpeta, y después otra*/

/*El createfile es un programa que te crea un archivo cualquiera
en donde quieras.
El path funciona exactamente igual que el path del magiafile, así
que arriba se explica todo, y en pos colocás el nombre del archivo
que querés con su extensión correspondiente, incluso si es una ex_
tensión inventada como ".eda".*/

/*El ocreatefile es igual al createfile pero te devuelte un ofstream
para poder colocarle cosas si necesitamos, nada más*/