#include "xviii/Headers/stdafx.h"
#include "xviii/Core/Game.h"

/*
    TODO:

    ////////////////////////////////////////////////////////////////////////
                                [PRIORITY - high]
    ////////////////////////////////////////////////////////////////////////

        (*) Improve UI

        (*) Allow terrain tiles to affect movement. Note that this should work even for terrain tiles in between
            the current and destination tiles, not just tiles manually moved on.

    ////////////////////////////////////////////////////////////////////////
                                [PRIORITY - medium]
    ////////////////////////////////////////////////////////////////////////

        (*) Implement a specialised HillAnt class (for slopes and hills)

        (*) Have a basic readable config file where several simple parameters can be set (resolution, deployment points, etc.)

        (*) Make rivers have a chance to bend, perhaps by giving each tile a minor chance to do a 90 degree turn

    ////////////////////////////////////////////////////////////////////////
                                [PRIORITY - low/none]
    ////////////////////////////////////////////////////////////////////////

        (*) Make some of the rain logic in GameState_Play::update() be updated turnly instead of constantly

        (*) Seperate movement and attack logic so that classes can, for example, be given movement rules of CAV but
        attack rules of INF (TODO later, after the upcoming UI update)

        (*) At some point, perhaps create a function that returns every tile in between 2 given tiles, for less code
        repetition in places (UnitTile::distanceFrom(), UnitTile::moveTo(), UnitTile::rangedAttack()...). At the moment
        there are some complexities (and laziness) which prevent me from creating a unified solution, but it's something
        to look into sometime.

*/

int main(){
    sf::RenderWindow mWindow{{xResolution, yResolution}, "xviii - Dong Bong Military Board Game"};

	Game* game = new Game(mWindow);

    while(game->gameLoop() == true){
        delete game;
        game = new Game(mWindow);
    }

    mWindow.close();

	return 0;
}

