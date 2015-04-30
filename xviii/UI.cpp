#include "stdafx.h"
#include "UI.h"

#include "GameState.h"

UI::UI(GameState* _gameState, TextureManager& _tm, FontManager& _fm) :
gameState(_gameState),
tm(_tm),
fm(_fm),
uiView{sf::FloatRect(0, -174, xResolution, 154)},
uiSprite{tm.getSprite(TextureManager::UI::RECTANGLE)}
{
	uiView.setViewport(sf::FloatRect(0, 0.8f, 1, 0.2f));
	uiSprite.setPosition(0, -174);

	currentPlayerText.setFont(fm.getFont(FontManager::Type::Lucon));
	currentPlayerText.setColor(sf::Color::White);
	currentPlayerText.setPosition(970, -170);

	button.sprite = tm.getSprite(TextureManager::UI::BUTTON);
	button.sprite.setOrigin(button.sprite.getLocalBounds().width / 2, button.sprite.getLocalBounds().height / 2);
	button.sprite.setPosition(1235, -80);
	button.text.setFont(fm.getFont(FontManager::Type::Lucon));
	//button.text origin
	//button.text position
	//These are handled in their respective UI children classes to ensure proper centering
	button.rekt.setSize({button.sprite.getLocalBounds().width, button.sprite.getLocalBounds().height});
	button.rekt.setOrigin(button.rekt.getLocalBounds().width / 2, button.rekt.getLocalBounds().height / 2);
	button.rekt.setPosition(button.sprite.getPosition().x + button.rekt.getOutlineThickness()
		, button.sprite.getPosition().y + button.rekt.getOutlineThickness());

	button.text.setColor(sf::Color::White);
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