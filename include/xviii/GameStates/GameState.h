#pragma once

#include "xviii/Core/World.h"
#include "xviii/Core/Player.h"
#include "xviii/Core/TextureManager.h"
#include "xviii/Core/FontManager.h"
#include "xviii/Core/SaveGame.h"
#include "xviii/Core/UnitLoader.h"

class Game;

class GameState
{
public:
	Game* game;
	GameState(Game* _game);
	virtual void getInput() = 0;
	virtual void update(float mFT) = 0;
	virtual void draw() = 0;

	//To be called whenever we switch to this gamestate
	//Primarily to take care of minor but annoying things like properly
	//setting the view
	virtual void onSwitch();
};

