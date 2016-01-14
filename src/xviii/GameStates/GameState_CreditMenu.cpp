#include "xviii/Headers/stdafx.h"
#include "xviii/GameStates/GameState_CreditMenu.h"

#include "xviii/Core/Game.h"

GameState_CreditMenu::GameState_CreditMenu(Game* game) :
GameState_MenuState{game}
{

}

void GameState_CreditMenu::init(){
    menuList.push_back({{"Concept, design, testing - Giuseppe Fazio"}, nullptr, Action::NONE});
	menuList.push_back({{"Programming, design, testing - Ralph Chaanine"}, nullptr, Action::NONE});
	menuList.push_back({{"Back"}, game->MainMenuState.get(), Action::NONE});

	lineUpObjects();
}
