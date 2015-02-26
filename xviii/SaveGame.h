#pragma once

#include <iostream>
#include <fstream>

#include "World.h"
#include "Player.h"

class Game;

class SaveGame
{
public:
	SaveGame(Game* _game);
	void create();
	void parse();

private:
	Game* game;
};

