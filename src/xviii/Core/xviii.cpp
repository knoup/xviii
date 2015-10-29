#include "xviii/Headers/stdafx.h"
#include "xviii/Core/Game.h"

/*
TODO:
    TOFIX:
    -The "out of max range" message for terrain attacks also showing up when a unit attacks an enemy (possibly fixed?)

    TODO:
    -CURRENT: moveTo() should move a unit to the furthest distance they can see an enemy unit from,
    if there is one in the way

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

