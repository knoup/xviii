#include "stdafx.h"
#include "Game.h"

#include "GameState.h"
#include "GameState_Play.h"
#include "GameState_Setup.h"
#include "GameState_Menu.h"
#include "UnitTile.h"
#include "Player.h"

Game::Game() :
randevice{},
mtengine{randevice()},
mWindow{{1360, 768}, "Dong Bong Military Board Game"},
state{nullptr},
MenuState{nullptr},
SetupState{nullptr},
PlayState{nullptr},
mTextureManager{},
mFontManager{},
mWorld{mTextureManager, sf::Vector2i(69, 100)},
Player1{mWorld, Player::Nation::AUS, sf::Color::Yellow, mtengine, mTextureManager, mFontManager, sf::View{sf::FloatRect(1183, 4800, mWindow.getSize().x, mWindow.getSize().y)}, "Austria"},
//Player2{mWorld, Player::Nation::PRU, sf::Color::White, mtengine, mTextureManager, mFontManager, sf::View{sf::FloatRect(1183, 4800, mWindow.getSize().x, mWindow.getSize().y)}, "Prussia"},
Player2{mWorld, Player::Nation::PRU, sf::Color::White, mtengine, mTextureManager, mFontManager, sf::View{sf::FloatRect(1183, -50, mWindow.getSize().x, mWindow.getSize().y)}, "Prussia"},
//Setting these to nullptr, they are properly initialised in the constructor body
currentPlayer{nullptr},
currentView{nullptr},

uiView{sf::FloatRect(0, -174, mWindow.getSize().x, 154)},
uiSprite{mTextureManager.getSprite(TextureManager::UI::RECTANGLE)},
mousePos{},
elapsedTurns{1},
saveCreator{this}
{
	currentPlayer = &Player1;
	currentView = &Player1.view;

	uiView.setViewport(sf::FloatRect(0, 0.8f, 1, 0.2f));
	uiSprite.setPosition(0, -174);

	mWindow.setFramerateLimit(120);

	
	MenuState = new GameState_Menu(this);
	SetupState = new GameState_Setup(this);
	PlayState = new GameState_Play(this);

	state = MenuState;

	gameLoop();

}


void Game::gameLoop(){
	while (mWindow.isOpen()){
		getInput();
		update();
		draw();
	}

	delete SetupState;
	delete PlayState;

	return;
}

void Game::getInput(){
	state->getInput();
}

void Game::update(){
	state->update();
}

void Game::draw(){
	mWindow.clear(sf::Color(84,84,84));
	state->draw();
	mWindow.display();
}

void Game::setGameStatePlay(){
	PlayState->oneTimeUpdate();
	state = PlayState;
	SetupState = nullptr;
	delete SetupState;
}

void Game::nextPlayer(){
	if (currentPlayer == &Player1){
		currentPlayer = &Player2;
	}
	else if (currentPlayer == &Player2){
		currentPlayer = &Player1;
	}

	currentView = &currentPlayer->view;
	currentPlayer->setReady(false);
}

void Game::setGameStateSetup(){
	state = SetupState;
}