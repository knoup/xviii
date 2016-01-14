#include "xviii/Headers/stdafx.h"
#include "xviii/GameStates/GameState_CustomBattleSelectEraMenu.h"

#include "xviii/Core/Game.h"

GameState_CustomBattleSelectEraMenu::GameState_CustomBattleSelectEraMenu(Game* game) :
GameState_MenuState{game}
{

}

void GameState_CustomBattleSelectEraMenu::init(){
    menuList.push_back({{"All Eras"}, nullptr, Action::NEW});
	menuList.push_back({{"Early Era"}, nullptr, Action::NEW, World::Era::EARLY});
	menuList.push_back({{"Middle Era"}, nullptr, Action::NEW, World::Era::MID});
	menuList.push_back({{"Late Era"}, nullptr, Action::NEW, World::Era::LATE});
	menuList.push_back({{"Back"}, game->CustomBattleMenuState.get(), Action::NONE});

	lineUpObjects();
}
