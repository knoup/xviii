#pragma once

#include "xviii/UI/UI.h"
#include "xviii/UI/SpawnableUnit.h"

class GameState_Setup;

class SetupUI : public UI
{
public:
	SetupUI(MasterManager& _masterManager, GameState_Setup* _gameState);
    //The copy constructor and = operator for this class have been disabled
	//Copy constructor
	SetupUI(const SetupUI&) = delete;
	//Operator=
	SetupUI & operator=(const SetupUI&) = delete;

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

