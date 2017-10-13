#pragma once

#include "xviii/Core/MasterManager.h"

#include "xviii/Core/World.h"
#include "xviii/Core/Player.h"
#include "xviii/Core/SaveGame.h"

#include "xviii/GameStates/GameState_Play.h"
#include "xviii/GameStates/GameState_SelectNationsMenu.h"
#include "xviii/GameStates/GameState_Setup.h"
#include "xviii/GameStates/GameState_MainMenu.h"
#include "xviii/GameStates/GameState_CustomBattleMenu.h"
#include "xviii/GameStates/GameState_MultiplayerMenu.h"
#include "xviii/GameStates/GameState_MultiplayerHostMenu.h"
#include "xviii/GameStates/GameState_MultiplayerConnectMenu.h"
#include "xviii/GameStates/GameState_CustomBattleLoadMenu.h"
#include "xviii/GameStates/GameState_CreditMenu.h"
#include "xviii/GameStates/GameState_CustomBattlePauseMenu.h"
#include "xviii/GameStates/GameState_SetupPauseMenu.h"

class UnitTile;

class Game : public sf::NonCopyable
{
public:
	Game(sf::RenderWindow& _mWindow);

	bool gameLoop();

	void getInput();
	void update(float mFT);
	void draw();

	void exitGame(bool _restart);

    void setGameState(GameState* _state);

	//Cycles to the next player; sets currentPlayer, currentView, and inactivePlayer, and resets the ready status
	void nextPlayer();

	MasterManager mManager;
	sf::RenderWindow& mWindow;

	GameState* state;

	std::unique_ptr<GameState_MainMenu> MainMenuState;
	std::unique_ptr<GameState_CustomBattleMenu> CustomBattleMenuState;
	std::unique_ptr<GameState_MultiplayerMenu> MultiplayerMenuState;
	std::unique_ptr<GameState_MultiplayerHostMenu> MultiplayerHostMenuState;
	std::unique_ptr<GameState_MultiplayerConnectMenu> MultiplayerConnectMenuState;
	std::unique_ptr<GameState_CustomBattleLoadMenu> CustomBattleLoadMenuState;
	std::unique_ptr<GameState_CreditMenu> CreditMenuState;
	std::unique_ptr<GameState_CustomBattlePauseMenu> CustomBattlePauseMenuState;
	std::unique_ptr<GameState_SetupPauseMenu> SetupPauseMenuState;

	std::unique_ptr<GameState_SelectNationsMenu> SelectNationsState;
	std::unique_ptr<GameState_Setup> SetupState;
	std::unique_ptr<GameState_Play> PlayState;

	World* mWorld;
	Player* Player1;
	Player* Player2;

	Player* currentPlayer;
	sf::View* currentView;

	Player* inactivePlayer;

	std::vector<Player*> mPlayers;

	sf::Vector2i mousePos;

	SaveGame saveCreator;

	bool restart{false};
	bool running{true};

	//This variable is set to true if we make it to the setup or play phase
	bool initialised{false};
};

