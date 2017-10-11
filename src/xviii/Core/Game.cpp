#include "xviii/Headers/stdafx.h"
#include "xviii/Core/Game.h"

#include "xviii/Headers/global.h"

#include "xviii/Core/Player.h"

#include "xviii/Core/UnitLoader.h"
#include "xviii/Core/TerrainLoader.h"

Game::Game(sf::RenderWindow& _mWindow) :
mManager{},
mWindow(_mWindow),
state{nullptr},
MainMenuState{nullptr},
SetupState{nullptr},
PlayState{nullptr},
mWorld{nullptr},
Player1{nullptr},
Player2{nullptr},
currentPlayer{nullptr},
currentView{nullptr},
inactivePlayer{nullptr},
mousePos{},
saveCreator{this}
{
	mWindow.setFramerateLimit(60);

    sf::Image icon;

    if(icon.loadFromFile("xviii.png")){
        mWindow.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }

	mManager.unitLoader->load();
	mManager.terrainLoader->load();

	MainMenuState = (std::unique_ptr<GameState_MainMenu>(new GameState_MainMenu(this)));
	CustomBattleMenuState = (std::unique_ptr<GameState_CustomBattleMenu>(new GameState_CustomBattleMenu(this)));
    CustomBattleLoadMenuState = (std::unique_ptr<GameState_CustomBattleLoadMenu>(new GameState_CustomBattleLoadMenu(this)));
    CreditMenuState = (std::unique_ptr<GameState_CreditMenu>(new GameState_CreditMenu(this)));
	SelectNationsState = (std::unique_ptr<GameState_SelectNationsMenu>(new GameState_SelectNationsMenu(this)));
	SetupState = (std::unique_ptr<GameState_Setup>(new GameState_Setup(this)));
	PlayState = (std::unique_ptr<GameState_Play>(new GameState_Play(this)));
	CustomBattlePauseMenuState = (std::unique_ptr<GameState_CustomBattlePauseMenu>(new GameState_CustomBattlePauseMenu(this)));
    SetupPauseMenuState = (std::unique_ptr<GameState_SetupPauseMenu>(new GameState_SetupPauseMenu(this)));

	MainMenuState->init();
	CustomBattleMenuState->init();
	CustomBattleLoadMenuState->init();
	CreditMenuState->init();
	CustomBattlePauseMenuState->init();
	SetupPauseMenuState->init();

	state = MainMenuState.get();
}

void Game::exitGame(bool _restart){
    restart = _restart;
    running = false;
}


bool Game::gameLoop(){
	constexpr float ftSlice{1.f};
	constexpr float ftStep{1.f};

	float lastFT{0.f};
	float currentSlice{0.f};

	while (running){

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

    delete mWorld;
	delete Player1;
	delete Player2;

	return restart;
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

void Game::setGameState(GameState* _state){
    if(_state == SetupState.get()){
        initialised = true;
        SetupState->oneTimeUpdate();
    }

    else if(_state == PlayState.get()){
        initialised = true;

        //There's no need to call the play state's oneTimeUpdate() if we are paused. This will
        //reset the units' perceived positions and do some other redundant things that aren't needed

        //The state != PlayState.get() part is for ensuring that when toggling resuming and pausing
        //really fast, the game won't be "tricked" into calling oneTimeUpdate().

        if(state != CustomBattlePauseMenuState.get() && state != PlayState.get()){
            PlayState->oneTimeUpdate();
        }
    }

    else if(_state == MainMenuState.get() && initialised){
        exitGame(true);
    }

    state = _state;
    state->onSwitch();
}

void Game::nextPlayer(){
	if (currentPlayer == Player1){
		currentPlayer = Player2;
		inactivePlayer = Player1;
	}
	else if (currentPlayer == Player2){
		currentPlayer = Player1;
		inactivePlayer = Player2;
	}

	currentView = &currentPlayer->view;
	currentPlayer->setReady(false);
	inactivePlayer->setReady(false);
}
