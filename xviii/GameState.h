#pragma once

#include "World.h"
#include "Player.h"
#include "TextureManager.h"
#include "FontManager.h"
#include "SaveGame.h"
#include "UnitLoader.h"

class Game;

class GameState
{
public:
	Game* game;
	GameState(Game* _game);
	virtual void getInput() = 0;
	virtual void update(float mFT) = 0;
	virtual void draw() = 0;
};

