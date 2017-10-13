#include "xviii/Headers/stdafx.h"
#include "xviii/GameStates/GameState_MultiplayerHostMenu.h"

#include "xviii/Core/Game.h"

GameState_MultiplayerHostMenu::GameState_MultiplayerHostMenu(Game* game) :
GameState_MenuState{game}
{

}

void GameState_MultiplayerHostMenu::init(){
	menuList.push_back({{"Back"}, true, game->MultiplayerMenuState.get(), Action::NONE});
	lineUpObjects();
}
