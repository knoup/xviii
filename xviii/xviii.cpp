#include "stdafx.h"
#include "Game.h"

#include <Windows.h>

/*
TODO:
	-Implement specialised MudAnt and HillAnt classes
	-Seperate UI from implementation
	-Make save text formatting less rigid so that a space doesn't break everything
	-Improve mapping system between terrain and unit tiles; both need to be able to easily
	 reference each other
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

