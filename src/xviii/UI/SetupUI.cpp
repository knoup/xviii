#include "xviii/Headers/stdafx.h"
#include "xviii/UI/SetupUI.h"

#include "xviii/GameStates/GameState_Setup.h"
#include "xviii/Core/Game.h"

SetupUI::SetupUI(MasterManager& _masterManager, GameState_Setup* _gameState) :
UI(_masterManager),
gameState{_gameState}
{
	button.setString("READY");
	button.text.setOrigin(button.text.getLocalBounds().width / 2, button.text.getGlobalBounds().height / 2);
	button.text.setPosition(button.sprite.getPosition().x, button.sprite.getPosition().y - 10);

	numbRemaining.setFont(masterManager.fontManager->getFont(FontManager::Type::Lucon));
	numbRemaining.setCharacterSize(70);
	numbRemaining.setColor(sf::Color::Green);
	numbRemaining.setPosition(50, 34);

	deploymentPointsTextRemaining.setFont(masterManager.fontManager->getFont(FontManager::Type::Lucon));
	deploymentPointsTextRemaining.setCharacterSize(19);
	deploymentPointsTextRemaining.setColor(sf::Color::White);
	deploymentPointsTextRemaining.setPosition(10, 114);

	deploymentPointsTextRemaining.setString("deployment points");
}

SetupUI::~SetupUI(){

}

void SetupUI::setNumbRemaining(int _num){
	numbRemaining.setString(std::to_string(_num));
}

void SetupUI::setNumbRemainingColour(sf::Color col){
	numbRemaining.setColor(col);
}

void SetupUI::update(){
	setCurrentPlayerText(gameState->game->currentPlayer->getShortDisplayName());
	setNumbRemaining(gameState->game->currentPlayer->getDeploymentPoints());


	//Changes the color of the number depending on how many points you have
	if (gameState->game->currentPlayer->getDeploymentPoints() > 20){
		setNumbRemainingColour(sf::Color::Green);
	}
	else if (gameState->game->currentPlayer->getDeploymentPoints() > 10){
		setNumbRemainingColour(sf::Color::Yellow);
	}
	else{
		setNumbRemainingColour(sf::Color::Red);
	}


	//For the highlighting of the ready button:
	sf::Vector2f uiCoords{gameState->game->mWindow.mapPixelToCoords(gameState->game->mousePos,uiView)};

	if (uiCoords.x >= button.left() && uiCoords.x <= button.right()
		&&
		uiCoords.y >= button.top() && uiCoords.y <= button.bottom()){

		setButtonHighlighted(true);
	}
	else{
		setButtonHighlighted(false);
	}
}

void SetupUI::draw(sf::RenderTarget &target, sf::RenderStates states) const{
	//Don't forget to set the view first

	target.draw(uiSprite);
	target.draw(currentPlayerText);
	target.draw(numbRemaining);
	target.draw(deploymentPointsTextRemaining);

	//selectable units
	for (auto& item : gameState->game->currentPlayer->getSpawnableUnits()){
		gameState->game->mWindow.draw(item.unitSprite);
		gameState->game->mWindow.draw(item.unitName);
	}

	//ready button
	target.draw(button.sprite);
	target.draw(button.text);

	if (button.highlighted){
		target.draw(button.rekt);
	}
	//
}
