#pragma once

#include "World.h"
#include "Player.h"
#include "TextureManager.h"
#include "FontManager.h"
#include "SaveGame.h"
#include "UnitLoader.h"

#include <random>
#include <boost/chrono.hpp>

#include "GameState_Play.h"
#include "GameState_SelectNations.h"
#include "GameState_Setup.h"
#include "GameState_Menu.h"

class UnitTile;

class Game : public sf::NonCopyable
{
public:
	Game();

	void gameLoop();

	void getInput();
	void update(float mFT);
	void draw();

	void setGameStateSelectNations();
	void setGameStateSetup();
	void setGameStatePlay();

	//Cycles to the next player; sets currentPlayer and currentView, and resets the ready status
	void nextPlayer();

	std::random_device randevice;
	std::mt19937 mtengine;

	sf::RenderWindow mWindow;

	GameState* state;

	std::unique_ptr<GameState_Menu> MenuState;
	std::unique_ptr<GameState_SelectNations> SelectNationsState;
	std::unique_ptr<GameState_Setup> SetupState;
	std::unique_ptr<GameState_Play> PlayState;

	TextureManager mTextureManager;
	FontManager mFontManager;

	World mWorld;
	
	Player* Player1;
	Player* Player2;

	Player* currentPlayer;
	sf::View* currentView;

	std::vector<Player*> mPlayers;

	sf::Vector2i mousePos;

	SaveGame saveCreator;
	UnitLoader mUnitLoader;
};

