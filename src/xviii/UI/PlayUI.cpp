#include "xviii/Headers/stdafx.h"
#include "xviii/UI/PlayUI.h"

#include "xviii/Core/GameState_Play.h"
#include "xviii/Core/Game.h"

PlayUI::PlayUI(GameState_Play* _gameState, TextureManager& _tm, FontManager& _fm) :
gameState{_gameState},
UI(_tm, _fm)
{
	button.text.setCharacterSize(20);
	button.setString("NEXT TURN");
	button.text.setOrigin(button.text.getLocalBounds().width / 2, button.text.getGlobalBounds().height / 2);
	button.text.setPosition(button.sprite.getPosition().x, button.sprite.getPosition().y - 10);

	elapsedTurnsText.setFont(fm.getFont(FontManager::Type::Lucon));
	elapsedTurnsText.setColor(sf::Color::Yellow);
	elapsedTurnsText.setPosition(20, -130);

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

	squareFormationText.setFont(fm.getFont(FontManager::Type::Lucon));
	limberText.setColor(sf::Color::White);
	squareFormationText.setPosition(970, -170);

	limberText.setFont(fm.getFont(FontManager::Type::Lucon));
	limberText.setColor(sf::Color::White);
	limberText.setPosition(970, -130);

	lancerBonusReadyText.setFont(fm.getFont(FontManager::Type::Lucon));
	lancerBonusReadyText.setColor(sf::Color::White);
	lancerBonusReadyText.setPosition(970, -80);
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

void PlayUI::update(){
	if (gameState->game->currentPlayer->isReady()){
		clearCurrentMessageText();
		setSaveStatus(false);
	}

	drawLimberText = false;
	drawSquareFormationText = false;
	drawLancerBonusReadyText = false;

	if (gameState->selected != nullptr){

		if (gameState->selected->hasLimberAbility()){
			drawLimberText = true;

			if (gameState->selected->getLimber()){
				limberText.setString("Limber ON");
			}
			else{
				limberText.setString("Limber OFF");
			}
		}

		if (gameState->selected->hasSquareFormationAbility()){
			drawSquareFormationText = true;

			if (gameState->selected->getSquareFormationActive()){
				squareFormationText.setString("S.F. ON");
			}
			else{
				squareFormationText.setString("S.F. OFF");
			}
		}

		if (gameState->selected->hasLancerAbility()){
			drawLancerBonusReadyText = true;

			if (gameState->selected->getLancerBonusReady()){
				lancerBonusReadyText.setString("Lncr bns RDY");
			}
			else{
				lancerBonusReadyText.setString("Lncr bns NT RDY");
			}
		}
	}


	setCurrentPlayerText(gameState->game->currentPlayer->getName());
	setElapsedTurnsText(gameState->game->mWorld.getElapsedTurns());

	//For the highlighting of the next turn button:
	sf::Vector2f uiCoords{gameState->game->mWindow.mapPixelToCoords(gameState->game->mousePos, uiView)};

	if (uiCoords.x >= button.left() && uiCoords.x <= button.right()
		&&
		uiCoords.y >= button.top() && uiCoords.y <= button.bottom()){

		setButtonHighlighted(true);
	}
	else{
		setButtonHighlighted(false);
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

	if (drawLimberText){
		target.draw(limberText);
	}
	if (drawSquareFormationText){
		target.draw(squareFormationText);
	}
	if (drawLancerBonusReadyText){
		target.draw(lancerBonusReadyText);
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
