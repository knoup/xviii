#include "xviii/Headers/stdafx.h"
#include "xviii/UI/UI.h"

#include "xviii/GameStates/GameState.h"

UI::UI(MasterManager& _masterManager) :
masterManager(_masterManager),
uiSprite{masterManager.textureManager->getSprite(TextureManager::UI::RECTANGLE)},
currentPlayerText{},
button{},
uiView{sf::FloatRect(0, 0, barWidth, barHeight)}
{
	uiView.setViewport(sf::FloatRect(0, 0.8f, 1, 0.2f));
	uiSprite.setPosition(0, 0);

	currentPlayerText.setFont(masterManager.fontManager->getFont(FontManager::Type::TCMT));
	currentPlayerText.setFillColor(sf::Color::Green);
	currentPlayerText.setPosition(20, 4);

	button.sprite = masterManager.textureManager->getSprite(TextureManager::UI::BUTTON);
	button.sprite.setOrigin(button.sprite.getLocalBounds().width / 2, button.sprite.getLocalBounds().height / 2);
	button.sprite.setPosition(1235, 79);
	button.text.setFont(masterManager.fontManager->getFont(FontManager::Type::TCMT));
	//button.text origin
	//button.text position
	//These are handled in their respective UI children classes to ensure proper centering
	button.rekt.setSize({button.sprite.getLocalBounds().width, button.sprite.getLocalBounds().height});
	button.rekt.setOrigin(button.rekt.getLocalBounds().width / 2, button.rekt.getLocalBounds().height / 2);
	button.rekt.setPosition(button.sprite.getPosition().x + button.rekt.getOutlineThickness()
		, button.sprite.getPosition().y + button.rekt.getOutlineThickness());

	button.text.setFillColor(sf::Color::White);
}

UI::~UI(){
}

void UI::setCurrentPlayerText(std::string str){
	currentPlayerText.setString(str);
}

void UI::setButtonHighlighted(bool val){
	button.highlighted = val;
}

const UI::Button& UI::getButton() const{
	return button;
}
