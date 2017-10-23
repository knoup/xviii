#include "xviii/Headers/stdafx.h"
#include "xviii/GameStates/GameState_CustomBattleMenu.h"

#include "xviii/Core/Game.h"

GameState_CustomBattleMenu::GameState_CustomBattleMenu(Game* game) :
GameState_MenuState{game}
{

}

void GameState_CustomBattleMenu::init(){
    menuList.push_back({{"New"}, true, game->SelectNationsState.get(), Action::NONE});
	menuList.push_back({{"Load"}, true, game->CustomBattleLoadMenuState.get(), Action::NONE});
	menuList.push_back({{"Multiplayer"}, true, game->MultiplayerMenuState.get(), Action::NONE});
	menuList.push_back({{""}, false, nullptr, Action::NONE});
	menuList.push_back({{"Back"}, true, game->MainMenuState.get(), Action::NONE});

	lineUpObjects();
}
