#include "xviii/Headers/stdafx.h"
#include "xviii/UI/PlayUI.h"

#include "xviii/GameStates/GameState_Play.h"
#include "xviii/Core/Game.h"

PlayUI::PlayUI(MasterManager& _masterManager, GameState_Play* _gameState) :
UI(_masterManager),
gameState{_gameState},
elapsedTurnsText{},
messageLogText{},
currentMessageText{},
currentWeatherText{},
currentTimeText{},
saveText{},
squareFormationText{},
limberText{},
lancerBonusReadyText{},
generalRangeIndicator1{},
generalRangeIndicator2{}
{
	button.text.setCharacterSize(20);
	button.setString("NEXT TURN");
	button.text.setOrigin(button.text.getLocalBounds().width / 2, button.text.getLocalBounds().height / 2);
	button.text.setPosition(button.sprite.getPosition().x, button.sprite.getPosition().y - 10);

	elapsedTurnsText.setFont(masterManager.fontManager->getFont(FontManager::Type::Lucon));
	elapsedTurnsText.setFillColor(sf::Color::Yellow);
	elapsedTurnsText.setPosition(20, 44);

	messageLogText.setFont(masterManager.fontManager->getFont(FontManager::Type::Lucon));
	messageLogText.setFillColor(sf::Color::White);
	messageLogText.setCharacterSize(15);
	messageLogText.setPosition(580, 4);
	messageLogText.setString("Messages");

	currentMessageText.setFont(masterManager.fontManager->getFont(FontManager::Type::Lucon));
	currentMessageText.setFillColor(sf::Color::Cyan);
	currentMessageText.setCharacterSize(19);
	currentMessageText.setPosition(340, 24);

	currentWeatherText.setFont(masterManager.fontManager->getFont(FontManager::Type::Eighteen));
	currentWeatherText.setFillColor(sf::Color::White);
	currentWeatherText.setCharacterSize(30);
	currentWeatherText.setPosition(205, 4);

	currentTimeText.setFont(masterManager.fontManager->getFont(FontManager::Type::Eighteen));
	currentTimeText.setFillColor(sf::Color::Cyan);
	currentTimeText.setCharacterSize(40);
	currentTimeText.setPosition(135, 94);


	saveText.setFont(masterManager.fontManager->getFont(FontManager::Type::Arial));
	saveText.setCharacterSize(20);
	saveText.setPosition(20, 94);
	setSaveStatus(false);

	squareFormationText.setFont(masterManager.fontManager->getFont(FontManager::Type::Lucon));
	limberText.setFillColor(sf::Color::White);
	squareFormationText.setPosition(970, 4);

	limberText.setFont(masterManager.fontManager->getFont(FontManager::Type::Lucon));
	limberText.setFillColor(sf::Color::White);
	limberText.setPosition(970, 44);

	lancerBonusReadyText.setFont(masterManager.fontManager->getFont(FontManager::Type::Lucon));
	lancerBonusReadyText.setFillColor(sf::Color::White);
	lancerBonusReadyText.setPosition(970, 94);

	float thickness{5};


	generalRangeIndicator1.setFillColor(sf::Color::Transparent);
    generalRangeIndicator1.setOutlineThickness(thickness);
	generalRangeIndicator1.setOutlineColor(sf::Color(0,0,0,250));
    generalRangeIndicator1.setSize({(masterManager.textureManager->getSize().x * 21), (masterManager.textureManager->getSize().y * 21)});

    generalRangeIndicator1.setCornersRadius(20);
    generalRangeIndicator1.setCornerPointCount(20);

    generalRangeIndicator1.setOrigin((generalRangeIndicator1.getLocalBounds().width / 2) - thickness, (generalRangeIndicator1.getLocalBounds().height / 2) - thickness);

    generalRangeIndicator2.setFillColor(sf::Color::Transparent);
    generalRangeIndicator2.setOutlineThickness(thickness);
	generalRangeIndicator2.setOutlineColor(sf::Color(255,0,0,250));
    generalRangeIndicator2.setSize({(masterManager.textureManager->getSize().x * 31), (masterManager.textureManager->getSize().y * 31)});

    generalRangeIndicator2.setCornersRadius(20);
    generalRangeIndicator2.setCornerPointCount(20);

    generalRangeIndicator2.setOrigin((generalRangeIndicator2.getLocalBounds().width / 2) - thickness, (generalRangeIndicator2.getLocalBounds().height / 2) - thickness);


}

PlayUI::~PlayUI(){
}

void PlayUI::setElapsedTurnsText(int _num){
	elapsedTurnsText.setString("Turn " + std::to_string(_num));
}

void PlayUI::setCurrentWeatherText(){
    auto weatherEffects = gameState->game->mWorld->getWeatherEffects();

    std::string tempStr{};

    if(weatherEffects.empty()){
        tempStr = "clear";
    }

    for(auto& effect : weatherEffects){
        #define X(_str, _weather, _u, _f)\
            if(effect.first == _weather){\
                tempStr += _str;\
                tempStr += "\n";\
            }
            WEATHERPROPERTIES
            #undef X
    }


    currentWeatherText.setString(tempStr);
}

void PlayUI::setCurrentTimeText(std::pair<int,int> _time){
    std::string minutesStr;

    if(_time.second < 10){
        minutesStr = "0" + std::to_string(_time.second);
    }
    else{
        minutesStr = std::to_string(_time.second);
    }
	currentTimeText.setString(std::to_string(_time.first) + ":" + minutesStr);

	if(gameState->game->mWorld->getIsNighttime()){
        currentTimeText.setFillColor(sf::Color::Cyan);
	}
	else{
        currentTimeText.setFillColor(sf::Color::Yellow);
	}

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

		if(gameState->selected == gameState->game->currentPlayer->getGeneral()){
            UnitTile* general = gameState->game->currentPlayer->getGeneral();
            generalRangeIndicator1.setPosition(general->getTerrain()->getPixelPosCenter());
            generalRangeIndicator2.setPosition(general->getTerrain()->getPixelPosCenter());
		}
	}

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

void PlayUI::turnlyUpdate(){
    setCurrentPlayerText(gameState->game->currentPlayer->getShortDisplayName());
    setElapsedTurnsText(gameState->game->mWorld->getElapsedTurns());
    setCurrentTimeText(gameState->game->mWorld->getCurrentTime().getTime());
    setCurrentWeatherText();
}

void PlayUI::draw(sf::RenderTarget &target, sf::RenderStates /*states*/) const{
    //Normally, the world view should be already set when this function is called
    if(gameState->selected != nullptr){
        if(gameState->selected == gameState->game->currentPlayer->getGeneral()){
            target.draw(generalRangeIndicator2);
            target.draw(generalRangeIndicator1);
        }
    }

	//After drawing the general range indicators, we move on to the UI view
	gameState->game->mWindow.setView(uiView);

	target.draw(uiSprite);
	target.draw(currentPlayerText);
	target.draw(currentWeatherText);
	target.draw(currentTimeText);
	target.draw(elapsedTurnsText);
	target.draw(saveText);
    target.draw(currentMessageText);

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
