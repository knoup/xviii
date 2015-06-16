#pragma once

#include "xviii/Core/World.h"
#include "xviii/Core/Player.h"
#include "xviii/Core/TextureManager.h"
#include "xviii/Core/FontManager.h"
#include "xviii/Core/SaveGame.h"
#include "xviii/Core/UnitLoader.h"

#include <boost/random.hpp>
#include <boost/random/random_device.hpp>

#include "xviii/Core/GameState_Play.h"
#include "xviii/Core/GameState_SelectNations.h"
#include "xviii/Core/GameState_Setup.h"
#include "xviii/Core/GameState_Menu.h"

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

	boost::random::random_device randevice;
	boost::random::mt19937 mtengine;

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

