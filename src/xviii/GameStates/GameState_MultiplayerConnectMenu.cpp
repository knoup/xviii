#include "xviii/Headers/stdafx.h"
#include "xviii/GameStates/GameState_MultiplayerConnectMenu.h"

#include "xviii/Core/Game.h"

GameState_MultiplayerConnectMenu::GameState_MultiplayerConnectMenu(Game* game) :
GameState_MenuState{game}
{

}

void GameState_MultiplayerConnectMenu::init(){
	menuList.push_back({{"Back"}, true, game->MultiplayerMenuState.get(), Action::NONE});
	lineUpObjects();
}
