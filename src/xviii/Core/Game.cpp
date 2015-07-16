#include "xviii/Headers/stdafx.h"
#include "xviii/Core/Game.h"

#include "xviii/Headers/global.h"

#include "xviii/Core/Player.h"

#include "xviii/Core/UnitLoader.h"
#include "xviii/Core/TerrainLoader.h"

Game::Game() :
mManager{},
randevice{},
mtengine{randevice()},
mWindow{{xResolution, yResolution}, "Dong Bong Military Board Game"},
state{nullptr},
MenuState{nullptr},
SetupState{nullptr},
PlayState{nullptr},
mWorld{mManager, sf::Vector2i(69, 100), mtengine},
Player1{nullptr},
Player2{nullptr},
currentPlayer{nullptr},
currentView{nullptr},
mousePos{},
saveCreator{this}
{
	mWindow.setFramerateLimit(120);

	mManager.unitLoader->load();
	mManager.terrainLoader->load();

	MenuState = (std::unique_ptr<GameState_Menu>(new GameState_Menu(this)));
	SelectNationsState = (std::unique_ptr<GameState_SelectNations>(new GameState_SelectNations(this)));
	SetupState = (std::unique_ptr<GameState_Setup>(new GameState_Setup(this)));
	PlayState = (std::unique_ptr<GameState_Play>(new GameState_Play(this)));

	state = MenuState.get();

	gameLoop();
}


void Game::gameLoop(){
	constexpr float ftSlice{1.f};
	constexpr float ftStep{1.f};

	float lastFT{0.f};
	float currentSlice{0.f};

	while (mWindow.isOpen()){

		auto timePoint1(std::chrono::high_resolution_clock::now());

		//////////////////////////////////////////////////////////
		getInput();

		currentSlice += lastFT;

		while (currentSlice >= ftSlice){
			currentSlice -= ftSlice;
			update(ftStep);
		}

		draw();
		//////////////////////////////////////////////////////////

		auto timePoint2(std::chrono::high_resolution_clock::now());
		auto elapsedTime(timePoint2 - timePoint1);

		float ft{std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(elapsedTime).count()};
		lastFT = ft;
	}

	delete Player1;
	delete Player2;

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
	state = SelectNationsState.get();
}

void Game::setGameStateSetup(){
	state = SetupState.get();
}

void Game::setGameStatePlay(){
	PlayState->oneTimeUpdate();
	state = PlayState.get();
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
