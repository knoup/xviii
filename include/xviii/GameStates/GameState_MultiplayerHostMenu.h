#pragma once

#include "xviii/GameStates/GameState_MenuState.h"

#include "boost/filesystem/fstream.hpp"

#include "xviii/Headers/global.h"
#include "xviii/Headers/keybinds.h"

#include "SFML/Network.hpp"

class GameState_MultiplayerHostMenu : public GameState_MenuState
{
public:
	GameState_MultiplayerHostMenu(Game* game);

	void init();

	virtual void update(float mFT);
	virtual void draw();

private:
    sf::TcpListener tcpListener;
    sf::Text waitText;

    virtual void lineUpObjects();
};

