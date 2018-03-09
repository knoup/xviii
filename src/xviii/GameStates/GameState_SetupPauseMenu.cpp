#include "xviii/Headers/stdafx.h"
#include "xviii/GameStates/GameState_SetupPauseMenu.h"

#include "xviii/Core/Game.h"

GameState_SetupPauseMenu::GameState_SetupPauseMenu(Game* game) :
GameState_MenuState{game}
{

}

void GameState_SetupPauseMenu::init(){
    menuList.push_back({std::string("Back to Main Menu"), true, game->MainMenuState.get(), Action::NONE});
	menuList.push_back({std::string("Save"), true, game->SetupState.get(), Action::SAVE});
	menuList.push_back({std::string("Resume"), true, game->SetupState.get(), Action::NONE});
	menuList.push_back({std::string(""), false, nullptr, Action::NONE});
	menuList.push_back({std::string("Exit"), true, nullptr, Action::EXIT});

	lineUpObjects();
}

void GameState_SetupPauseMenu::draw(){
    game->mWindow.setView(*game->currentView);
	game->mWorld->draw(game->mWindow);

    game->currentPlayer->drawUnits(game->mWindow);

	game->mWindow.setView(menuSelectView);

	for (auto& item : menuList){
		game->mWindow.draw(item.text);
	}
}
