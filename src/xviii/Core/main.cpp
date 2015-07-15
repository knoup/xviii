#include "xviii/Headers/stdafx.h"
#include "xviii/Core/Game.h"

/*
TODO:
	-Have a basic readable config file where several simple parameters can be set (resolution, deployment points,
	tile sizes, etc.)

	-Implement specialised MudAnt and HillAnt classes

    CURRENT:
    -Do something about the abominable UnitTile::distanceFrom() function
	-Add a health indicator to Bridges
    -Make entire TBridge be destroyed if 1 tile is broken
    -Add watercrosser, mudcrosser, and cone width attributes
*/

/*
IMPORTANT:
If you are using a custom tile set, make sure tile sizes are set correctly in TextureManager
*/


int main(int argc, char* argv[]){
	Game game;
	return 0;
}

