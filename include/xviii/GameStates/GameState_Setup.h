#pragma once

#include "xviii/GameStates/GameState.h"

#include "xviii/UI/SetupUI.h"
#include "xviii/Headers/global.h"
#include "xviii/Headers/keybinds.h"

class GameState_Setup : public GameState
{
public:
	GameState_Setup(Game* game);
	virtual void getInput();
	virtual void update(float mFT);
	virtual void draw();
	virtual void onSwitch();

	void oneTimeUpdate();

private:
	virtual void handleResize();

	sf::Vector2f cameraVelocity;
	sf::Vector2i middleButtonCoords;
	bool middleButtonHeld;

	SetupUI setupUI;
	bool drawUI;

	std::unique_ptr<SpawnableUnit> selectedSpawnableUnit;

	//These are all required for the smooth zoom/interpolation of the camera
	sf::Vector2f smoothZoom_currentCenter{};
	sf::Vector2f smoothZoom_targetCenter{};
	float smoothZoom_targetZoom = 0.0f;
	float smoothZoom_currentZoom = 0.0f;
	float smoothZoom_previousZoom = 0.0f;
	bool smoothZoom_zooming = false;
	float smoothZoom_lerpFactor = 0.0085f;
	////////////////////////////////////////////////////////////////////////
};

