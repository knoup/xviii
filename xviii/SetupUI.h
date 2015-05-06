#pragma once

#include "UI.h"

class GameState_Setup;

class SetupUI : public UI
{
public:
	SetupUI(GameState_Setup* _gameState, TextureManager& _tm, FontManager& _fm);
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

