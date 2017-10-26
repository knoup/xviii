#include "xviii/Headers/stdafx.h"
#include "xviii/GameStates/GameState_CreditMenu.h"

#include "xviii/Core/Game.h"

GameState_CreditMenu::GameState_CreditMenu(Game* game) :
GameState_MenuState{game}
{

}

void GameState_CreditMenu::init(){
    menuList.push_back({std::string("Concept, design, testing - Giuseppe Fazio"), false, nullptr, Action::NONE});
	menuList.push_back({std::string("Programming, design, testing - Ralph Chaanine"), false, nullptr, Action::NONE});
	menuList.push_back({std::string(""), false, nullptr, Action::NONE});
	menuList.push_back({std::string("Back"), true, game->MainMenuState.get(), Action::NONE});

	lineUpObjects();
}
