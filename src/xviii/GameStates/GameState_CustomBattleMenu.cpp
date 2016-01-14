#include "xviii/Headers/stdafx.h"
#include "xviii/GameStates/GameState_CustomBattleMenu.h"

#include "xviii/Core/Game.h"

GameState_CustomBattleMenu::GameState_CustomBattleMenu(Game* game) :
GameState_MenuState{game}
{

}

void GameState_CustomBattleMenu::init(){
    menuList.push_back({{"New"}, game->CustomBattleSelectEraMenuState.get(), Action::NONE});
	menuList.push_back({{"Load"}, game->CustomBattleLoadMenuState.get(), Action::NONE});
	menuList.push_back({{"Back"}, game->MainMenuState.get(), Action::NONE});

	lineUpObjects();
}
