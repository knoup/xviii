#pragma once

#include "Game.h"

class GameState
{
public:
	Game* game;
	GameState(Game* _game);
	virtual void getInput() = 0;
	virtual void update(FrameTime mFT) = 0;
	virtual void draw() = 0;
};

