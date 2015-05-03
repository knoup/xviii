#include "stdafx.h"
#include "Game.h"

#include <Windows.h>

/*
TODO:
	-Artillery guard unit & artillery limber features
	-Malus on movement if too far from general
	-Split global.h into several files and include only where needed, to reduce the executable size
	-Implement specialised MudAnt and HillAnt classes
*/

/*
IMPORTANT:
If you are using a custom tile set, make sure tile sizes are set correctly in TextureManager
*/

//Release version

/*
int CALLBACK WinMain(_In_  HINSTANCE hInstance, _In_  HINSTANCE hPrevInstance, _In_  LPSTR lpCmdLine, _In_  int nCmdShow)
{
	Game game;	
	return 0;
}	
*/

//Debug version:
int main(int argc, char* argv[]){
	Game game;
	return 0;
}

