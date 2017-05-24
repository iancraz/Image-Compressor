#include "ParseCommandLine.h"
#include <iostream>



ParseCommandLine::ParseCommandLine(int argc, char *argv[])
{
	this->argc = argc;
	this->argv = argv;
	return;
}

int ParseCommandLine::PCL(pCallback p, void *userData)
{
	int i = 1, parsedArgs = 0;
	bool status = true;
	while (i < argc && status != false)
	{
		if ((*(argv[i])) == '-')			// Deteccion del comienzo de una opcion.
		{
			if (*((argv[i]) + 1) != 0 && i + 1 < argc)				// Verificar que haya una clave y un valor.
			{
				status = p((argv[i]) + 1, argv[i + 1], userData);	// Verificar contenido.
				i++;
				parsedArgs++;
			}
			else
			{
				status = false;
			}
		}
		else
		{
			status = p(NULL, argv[i], userData);		// Los parametros solo pueden tener errores de contenido.
			parsedArgs++;
		}
		i++;
	}
	if (status == false)
		parsedArgs = -1;
	return parsedArgs;
}