#include "stdafx.h"
#include "Game.h"

#include "global.h"

#include "GameState.h"
#include "GameState_Play.h"
#include "GameState_SelectNations.h"
#include "GameState_Setup.h"
#include "GameState_Menu.h"
#include "UnitTile.h"
#include "Player.h"

Game::Game() :
randevice{},
mtengine{randevice()},
mWindow{{xResolution, yResolution}, "Dong Bong Military Board Game"},
state{nullptr},
MenuState{nullptr},
SetupState{nullptr},
PlayState{nullptr},
mTextureManager{},
mFontManager{},
mWorld{mTextureManager, sf::Vector2i(69, 100), mtengine},
Player1{nullptr},
Player2{nullptr},
currentPlayer{nullptr},
currentView{nullptr},
mousePos{},
elapsedTurns{1},
saveCreator{this},
mUnitLoader{mTextureManager}
{
	mWindow.setFramerateLimit(120);

	mUnitLoader.load();

	MenuState = (new GameState_Menu(this));
	SelectNationsState = (new GameState_SelectNations(this));
	SetupState = (new GameState_Setup(this));
	PlayState = (new GameState_Play(this));

	state = MenuState;

	gameLoop();
}


void Game::gameLoop(){
	constexpr float ftSlice{1.f};
	constexpr float ftStep{1.f};

	float lastFT{0.f};
	float currentSlice{0.f};

	while (mWindow.isOpen()){

		auto timePoint1(boost::chrono::high_resolution_clock::now());

		//////////////////////////////////////////////////////////
		getInput();

		currentSlice += lastFT;

		while (currentSlice >= ftSlice){
			currentSlice -= ftSlice;
			update(ftStep);
		}

		draw();
		//////////////////////////////////////////////////////////

		auto timePoint2(boost::chrono::high_resolution_clock::now());
		auto elapsedTime(timePoint2 - timePoint1);

		float ft{boost::chrono::duration_cast<boost::chrono::duration<float, boost::milli>>(elapsedTime).count()};
		lastFT = ft;
	}

	return;
}

void Game::getInput(){
	state->getInput();
}

void Game::update(float mFT){
	state->update(mFT);
}

void Game::draw(){
	mWindow.clear(sf::Color(84,84,84));
	state->draw();
	mWindow.display();
}

void Game::setGameStateSelectNations(){
	state = SelectNationsState;
}

void Game::setGameStateSetup(){
	state = SetupState;
}

void Game::setGameStatePlay(){
	PlayState->oneTimeUpdate();
	state = PlayState;
}

void Game::nextPlayer(){
	if (currentPlayer == Player1){
		currentPlayer = Player2;
	}
	else if (currentPlayer == Player2){
		currentPlayer = Player1;
	}

	currentView = &currentPlayer->view;
	currentPlayer->setReady(false);
}
