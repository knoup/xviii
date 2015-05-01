#pragma once

#include "World.h"
#include "Player.h"
#include "TextureManager.h"
#include "FontManager.h"
#include "SaveGame.h"

#include <random>
#include <boost/chrono.hpp>

class GameState;
class GameState_Setup;
class GameState_SelectNations;
class GameState_Play;
class GameState_Menu;
class UnitTile;

class Game : public sf::NonCopyable
{
public:
	Game();

	void gameLoop();

	void getInput();
	void update(FrameTime mFT);
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
	GameState_SelectNations* SelectNationsState;
	GameState_Menu* MenuState;
	GameState_Setup* SetupState;
	GameState_Play* PlayState;

	TextureManager mTextureManager;
	FontManager mFontManager;

	World mWorld;
	
	Player* Player1;
	Player* Player2;

	Player* currentPlayer;
	sf::View* currentView;

	std::vector<Player*> mPlayers;

	sf::Vector2i mousePos;

	int elapsedTurns;

	SaveGame saveCreator;
};

