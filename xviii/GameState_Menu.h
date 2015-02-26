#pragma once

#include "GameState.h"

#include "keybinds.h"

class GameState_Menu : public GameState
{
public:
	GameState_Menu(Game* game);
	virtual void getInput();
	virtual void update();
	virtual void draw();
private:
	sf::Text menuText;
};

