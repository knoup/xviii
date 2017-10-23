#pragma once

#include "xviii/GameStates/GameState_MenuState.h"

#include "boost/filesystem/fstream.hpp"

#include "xviii/Headers/global.h"
#include "xviii/Headers/keybinds.h"

#include "SFML/Network.hpp"

class GameState_MultiplayerConnectMenu : public GameState_MenuState
{
public:
	GameState_MultiplayerConnectMenu(Game* game);

	void init();

    virtual void getInput();
    virtual void update(float mFT);
	virtual void draw();

private:
    std::string IPString;
    sf::Text IPText;
    sf::Text instructionalText;
};

