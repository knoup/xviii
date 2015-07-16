#pragma once

#include "xviii/UI/UI.h"
#include "xviii/UI/SpawnableUnit.h"

class GameState_Setup;

class SetupUI : public UI
{
public:
	SetupUI(MasterManager& _masterManager, GameState_Setup* _gameState);
	virtual ~SetupUI();
	virtual void update();
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states = sf::RenderStates::Default) const;
	void setNumbRemaining(int _num);
	void setNumbRemainingColour(sf::Color col);
private:
	GameState_Setup* gameState;

	sf::Text numbRemaining;
	sf::Text deploymentPointsTextRemaining;
};

