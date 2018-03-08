#include "xviii/Headers/stdafx.h"
#include "xviii/GameStates/GameState_CustomBattlePauseMenu.h"

#include "xviii/Core/Game.h"

GameState_CustomBattlePauseMenu::GameState_CustomBattlePauseMenu(Game* game) :
GameState_MenuState{game}
{

}

void GameState_CustomBattlePauseMenu::init(){
    menuList.push_back({std::string("Back to Main Menu"), true, game->MainMenuState.get(), Action::NONE});
	menuList.push_back({std::string("Save"), true, game->PlayState.get(), Action::SAVE});
	menuList.push_back({std::string("Resume"), true, game->PlayState.get(), Action::NONE});
	menuList.push_back({std::string(""), false, nullptr, Action::NONE});
	menuList.push_back({std::string("Exit"), true, nullptr, Action::EXIT});

	lineUpObjects();
}

void GameState_CustomBattlePauseMenu::draw(){
    game->mWindow.setView(*game->currentView);
	game->mWorld->draw(game->mWindow);

	for (auto& player : game->mPlayers){
		player->drawUnits(game->mWindow);
	}

	game->mWindow.setView(menuSelectView);

	for (auto& item : menuList){
		game->mWindow.draw(item.text);
	}
}
