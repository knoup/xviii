#include "xviii/Headers/stdafx.h"
#include "xviii/GameStates/GameState_CustomBattleLoadMenu.h"

#include "xviii/Core/Game.h"

GameState_CustomBattleLoadMenu::GameState_CustomBattleLoadMenu(Game* game) :
GameState_MenuState{game}
{

}

void GameState_CustomBattleLoadMenu::init(){

    boost::filesystem::directory_iterator end;

	if (boost::filesystem::exists("save")){
		for (boost::filesystem::directory_iterator it("save"); it != end; ++it){
			menuList.push_back({it->path(), true, nullptr, Action::LOAD});
		}
	}

	menuList.push_back({{"Back"}, true, game->CustomBattleMenuState.get(), Action::NONE});

	lineUpObjects();
}
