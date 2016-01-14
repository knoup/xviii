#include "xviii/Headers/stdafx.h"
#include "xviii/GameStates/GameState_MainMenu.h"

#include "xviii/Core/Game.h"

GameState_MainMenu::GameState_MainMenu(Game* game) :
GameState_MenuState{game}
{

}

void GameState_MainMenu::init(){
    menuList.push_back({{"[New Campaign]"}, nullptr, Action::NONE});
	menuList.push_back({{"[Load Campaign]"}, nullptr, Action::NONE});
	menuList.push_back({{"Custom Battle"}, game->CustomBattleMenuState.get(), Action::NONE});
	menuList.push_back({{"[Options]"}, nullptr, Action::NONE});
	menuList.push_back({{"Credits"}, game->CreditMenuState.get(), Action::NONE});
	menuList.push_back({{"Exit"}, nullptr, Action::EXIT});

	lineUpObjects();
}
