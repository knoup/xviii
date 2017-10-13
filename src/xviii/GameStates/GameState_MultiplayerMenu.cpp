#include "xviii/Headers/stdafx.h"
#include "xviii/GameStates/GameState_MultiplayerMenu.h"

#include "xviii/Core/Game.h"

GameState_MultiplayerMenu::GameState_MultiplayerMenu(Game* game) :
GameState_MenuState{game}
{

}

void GameState_MultiplayerMenu::init(){
    menuList.push_back({{"Host"}, true, game->MultiplayerHostMenuState.get(), Action::NONE});
	menuList.push_back({{"Connect to host"}, true, game->MultiplayerConnectMenuState.get(), Action::NONE});
	menuList.push_back({{"Multiplayer options"}, true, nullptr, Action::NONE});
	menuList.push_back({{"Back"}, true, game->CustomBattleMenuState.get(), Action::NONE});

	lineUpObjects();
}
