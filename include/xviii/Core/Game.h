#pragma once

#include "xviii/Core/MasterManager.h"

#include "xviii/Core/World.h"
#include "xviii/Core/Player.h"
#include "xviii/Core/SaveGame.h"

#include "xviii/GameStates/GameState_Play.h"
#include "xviii/GameStates/GameState_SelectNations.h"
#include "xviii/GameStates/GameState_Setup.h"
#include "xviii/GameStates/GameState_MainMenu.h"
#include "xviii/GameStates/GameState_CustomBattleMenu.h"
#include "xviii/GameStates/GameState_CustomBattleLoadMenu.h"
#include "xviii/GameStates/GameState_CustomBattleSelectEraMenu.h"
#include "xviii/GameStates/GameState_CreditMenu.h"
#include "xviii/GameStates/GameState_CombatPauseMenu.h"
#include "xviii/GameStates/GameState_SetupPauseMenu.h"

class UnitTile;

class Game : public sf::NonCopyable
{
public:
	Game();

	void gameLoop();

	void getInput();
	void update(float mFT);
	void draw();

    void setGameState(GameState* _state);

	//Cycles to the next player; sets currentPlayer, currentView, and inactivePlayer, and resets the ready status
	void nextPlayer();

	MasterManager mManager;
	sf::RenderWindow mWindow;

	GameState* state;

	std::unique_ptr<GameState_MainMenu> MainMenuState;
	std::unique_ptr<GameState_CustomBattleMenu> CustomBattleMenuState;
	std::unique_ptr<GameState_CustomBattleLoadMenu> CustomBattleLoadMenuState;
	std::unique_ptr<GameState_CustomBattleSelectEraMenu> CustomBattleSelectEraMenuState;
	std::unique_ptr<GameState_CreditMenu> CreditMenuState;
	std::unique_ptr<GameState_CombatPauseMenu> CombatPauseMenuState;
	std::unique_ptr<GameState_SetupPauseMenu> SetupPauseMenuState;

	std::unique_ptr<GameState_SelectNations> SelectNationsState;
	std::unique_ptr<GameState_Setup> SetupState;
	std::unique_ptr<GameState_Play> PlayState;

	World mWorld;

	Player* Player1;
	Player* Player2;

	Player* currentPlayer;
	sf::View* currentView;

	Player* inactivePlayer;

	std::vector<Player*> mPlayers;

	sf::Vector2i mousePos;

	SaveGame saveCreator;
};

