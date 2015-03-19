#pragma once

#include <iostream>
#include <fstream>

#include "boost/filesystem.hpp"
#include "boost/filesystem/fstream.hpp"

#include "World.h"
#include "Player.h"

class Game;

class SaveGame
{
public:
	SaveGame(Game* _game);
	//returns true on success
	bool create();
	void parse(boost::filesystem::path _dir);

private:
	Game* game;
};

