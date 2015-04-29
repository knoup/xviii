#include "stdafx.h"
#include "SetupUI.h"


SetupUI::SetupUI(TextureManager& _tm, FontManager& _fm) :
UI(_tm, _fm)
{
	button.setString("READY");
	button.text.setOrigin(button.text.getLocalBounds().width / 2, button.text.getGlobalBounds().height / 2);
	button.text.setPosition(button.sprite.getPosition().x, button.sprite.getPosition().y - 10);

	numbRemaining.setFont(fm.getFont(FontManager::Type::Lucon));
	numbRemaining.setCharacterSize(70);
	numbRemaining.setColor(sf::Color::Green);
	numbRemaining.setPosition(145, -170);

	deploymentPointsTextRemaining.setFont(fm.getFont(FontManager::Type::Lucon));
	deploymentPointsTextRemaining.setCharacterSize(19);
	deploymentPointsTextRemaining.setColor(sf::Color::White);
	deploymentPointsTextRemaining.setPosition(60, -80);

	deploymentPointsTextRemaining.setString("deployment points remain");
}

SetupUI::~SetupUI(){

}

void SetupUI::setNumbRemaining(int _num){
	numbRemaining.setString(std::to_string(_num));
}

void SetupUI::setNumbRemainingColour(sf::Color col){
	numbRemaining.setColor(col);
}


void SetupUI::draw(sf::RenderTarget &target, sf::RenderStates states) const{
	//Don't forget to set the view first 

	target.draw(uiSprite);
	target.draw(currentPlayerText);
	target.draw(numbRemaining);
	target.draw(deploymentPointsTextRemaining);
	
	//ready button
	target.draw(button.sprite);
	target.draw(button.text);

	if (button.highlighted){
		target.draw(button.rekt);
	}
	//
}