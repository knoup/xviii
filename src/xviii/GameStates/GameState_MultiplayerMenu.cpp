#include "xviii/Headers/stdafx.h"
#include "xviii/GameStates/GameState_MultiplayerMenu.h"

#include "xviii/Core/Game.h"

GameState_MultiplayerMenu::GameState_MultiplayerMenu(Game* game) :
GameState_MenuState{game}
{

}

void GameState_MultiplayerMenu::init(){
    menuList.push_back({std::string("Host"), true, game->MultiplayerHostMenuState.get(), Action::NONE});
	menuList.push_back({std::string("Connect to host"), true, game->MultiplayerConnectMenuState.get(), Action::NONE});
	menuList.push_back({std::string("Multiplayer options"), true, nullptr, Action::NONE});
	menuList.push_back({std::string(""), false, nullptr, Action::NONE});
	menuList.push_back({std::string("Back"), true, game->CustomBattleMenuState.get(), Action::NONE});

	lineUpObjects();
}
