#pragma once

#include "GameState.h"

#include "SetupUI.h"
#include "global.h"

class GameState_Setup : public GameState
{
public:
	GameState_Setup(Game* game);
	virtual void getInput();
	virtual void update(FrameTime mFT);
	virtual void draw();

private:
	sf::Vector2f cameraVelocity;
	SetupUI setupUI;
	bool drawUI{true};

	std::unique_ptr<Player::SpawnableUnit> selectedSpawnableUnit;

};

