#include "xviii/Headers/stdafx.h"
#include "xviii/GameStates/GameState_CustomBattlePauseMenu.h"

#include "xviii/Core/Game.h"

GameState_CustomBattlePauseMenu::GameState_CustomBattlePauseMenu(Game* game) :
GameState_MenuState{game}
{

}

void GameState_CustomBattlePauseMenu::init(){
    menuList.push_back({{"Back to Main Menu"}, true, nullptr, Action::NONE});
	menuList.push_back({{"Save"}, true, game->PlayState.get(), Action::SAVE});
	menuList.push_back({{"Resume"}, true, game->PlayState.get(), Action::NONE});
	menuList.push_back({{"Exit"}, true, nullptr, Action::EXIT});

	lineUpObjects();
}

void GameState_CustomBattlePauseMenu::draw(){
    game->mWindow.setView(*game->currentView);
	game->mWorld.draw(game->mWindow);

	for (auto& player : game->mPlayers){
		player->drawUnits(game->mWindow);
	}

	game->mWindow.setView(menuSelectView);
	game->mWindow.draw(titleText);

	for (auto& item : menuList){
		game->mWindow.draw(item.text);
	}
}
