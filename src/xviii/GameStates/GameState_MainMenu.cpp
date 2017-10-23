#include "xviii/Headers/stdafx.h"
#include "xviii/GameStates/GameState_MainMenu.h"

#include "xviii/Core/Game.h"

GameState_MainMenu::GameState_MainMenu(Game* game) :
GameState_MenuState{game}
{

}

void GameState_MainMenu::init(){
    //menuList.push_back({{"[New Campaign]"}, true, nullptr, Action::NONE});
	//menuList.push_back({{"[Load Campaign]"}, true, nullptr, Action::NONE});
	menuList.push_back({{"Battle Menu"}, true, game->CustomBattleMenuState.get(), Action::NONE});
	menuList.push_back({{"Options"}, true, nullptr, Action::NONE});
	menuList.push_back({{"Credits"}, true, game->CreditMenuState.get(), Action::NONE});
	menuList.push_back({{""}, false, nullptr, Action::NONE});
	menuList.push_back({{"Exit"}, true, nullptr, Action::EXIT});

	lineUpObjects();
}
