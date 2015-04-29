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
//Setting these to nullptr, they are properly initialised in the constructor body
currentPlayer{nullptr},
currentView{nullptr},
uiView{sf::FloatRect(0, -174, xResolution, 154)},
uiSprite{mTextureManager.getSprite(TextureManager::UI::RECTANGLE)},
mousePos{},
elapsedTurns{1},
saveCreator{this}
{
	uiView.setViewport(sf::FloatRect(0, 0.8f, 1, 0.2f));
	uiSprite.setPosition(0, -174);

	//FPS independent logic is not that crucial in a game without physics, but I should probably get around to it eventually anyway
	mWindow.setFramerateLimit(120);
	
	MenuState = new GameState_Menu(this);
	SelectNationsState = new GameState_SelectNations(this);
	SetupState = new GameState_Setup(this);
	PlayState = new GameState_Play(this);

	state = MenuState;

	gameLoop();

}


void Game::gameLoop(){
	FrameTime lastFT{0.f};
	FrameTime currentSlice{0.f};

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

		FrameTime ft{boost::chrono::duration_cast<boost::chrono::duration<float, boost::milli>>(elapsedTime).count()};
		lastFT = ft;
	}

	delete SetupState;
	delete PlayState;

	return;
}

void Game::getInput(){
	state->getInput();
}

void Game::update(FrameTime mFT){
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
	SetupState = nullptr;
	delete SetupState;
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
