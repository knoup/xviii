#include "xviii/Headers/stdafx.h"
#include "xviii/Core/Game.h"

/*
    TODO:
    -At some point, perhaps create a function that returns every tile in between 2 given tiles, for less code
    repetition in places (UnitTile::distanceFrom(), UnitTile::moveTo(), UnitTile::rangedAttack()...). At the moment
    there are some complexities (and laziness) which prevent me from creating a unified solution, but it's something
    to look into sometime.

    -Add saving functionality the setup phase

    MISC:
    -Implement a specialised HillAnt class (for slopes and hills)
	-Have a basic readable config file where several simple parameters can be set (resolution, deployment points,
	tile sizes, etc.)
*/

/*
IMPORTANT:
If you are using a custom tile set, make sure tile sizes are set correctly in TextureManager
*/


int main(int argc, char* argv[]){
	Game game;
	return 0;
}

