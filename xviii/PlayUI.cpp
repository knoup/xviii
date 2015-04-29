#include "stdafx.h"
#include "PlayUI.h"


PlayUI::PlayUI(TextureManager& _tm, FontManager& _fm) : 
UI(_tm, _fm)
{
	button.text.setCharacterSize(20);
	button.setString("NEXT TURN");
	button.text.setOrigin(button.text.getLocalBounds().width / 2, button.text.getGlobalBounds().height / 2);
	button.text.setPosition(button.sprite.getPosition().x, button.sprite.getPosition().y - 10);

	elapsedTurnsText.setFont(fm.getFont(FontManager::Type::Lucon));
	elapsedTurnsText.setColor(sf::Color::Yellow);
	elapsedTurnsText.setPosition(20, -170);

	messageLogText.setFont(fm.getFont(FontManager::Type::Lucon));
	messageLogText.setColor(sf::Color::White);
	messageLogText.setCharacterSize(15);
	messageLogText.setPosition(580, -170);
	messageLogText.setString("Messages");

	currentMessageText.setFont(fm.getFont(FontManager::Type::Lucon));
	currentMessageText.setColor(sf::Color::Cyan);
	currentMessageText.setCharacterSize(22);
	currentMessageText.setPosition(220, -150);

	saveText.setFont(fm.getFont(FontManager::Type::Arial));
	saveText.setCharacterSize(20);
	saveText.setPosition(20, -80);
	setSaveStatus(false);
}

PlayUI::~PlayUI(){

}

void PlayUI::setElapsedTurnsText(int _num){
	elapsedTurnsText.setString("Turn " + std::to_string(_num));
}

void PlayUI::setCurrentMessageText(std::string _str){
	currentMessageText.setString(_str);
}

void PlayUI::clearCurrentMessageText(){
	currentMessageText.setString("");
}

void PlayUI::setSaveStatus(bool val){
	if (val){
		saveText.setString("Saved!");
	}
	else{
		saveText.setString("Not saved");
	}
}

void PlayUI::draw(sf::RenderTarget &target, sf::RenderStates states) const{
	//Don't forget to set the view first

	target.draw(uiSprite);
	target.draw(currentPlayerText);
	target.draw(elapsedTurnsText);
	target.draw(saveText);


	if (!currentMessageText.getString().isEmpty()){
		target.draw(currentMessageText);
	}

	target.draw(messageLogText);

	//ready button
	target.draw(button.sprite);
	target.draw(button.text);

	if (button.highlighted){
		target.draw(button.rekt);
	}
	//
}