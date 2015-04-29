#pragma once

#include "UI.h"

class SetupUI : public UI
{
public:
	SetupUI(TextureManager& _tm, FontManager& _fm);
	virtual ~SetupUI();
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states = sf::RenderStates::Default) const;
	void setNumbRemaining(int _num);
	void setNumbRemainingColour(sf::Color col);
private:
	sf::Text numbRemaining;
	sf::Text deploymentPointsTextRemaining;
};

