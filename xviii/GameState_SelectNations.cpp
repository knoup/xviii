#include "stdafx.h"
#include "GameState_SelectNations.h"


void GameState_SelectNations::clearHighlighting(){
	for (auto& flag : flagSelection){
		flag.highlighted = false;
	}
}

GameState_SelectNations::GameState_SelectNations(Game* _game) :
GameState{_game},
flagView{sf::FloatRect({}, {}, xResolution, yResolution)},
uiView{sf::FloatRect({}, {}, xResolution, yResolution)}
{
	flagSelection.push_back({game->mTextureManager.getSprite(TextureManager::Flag::AUS), Player::Nation::AUS});
	flagSelection.push_back({game->mTextureManager.getSprite(TextureManager::Flag::PRU), Player::Nation::PRU});

	for (int i{0}; i < flagSelection.size(); ++i){
		int spriteXPos = (i * 75);
		int spriteYPos = yResolution / 2;

		flagSelection[i].sprite.setPosition(spriteXPos, spriteYPos);
		flagSelection[i].rekt.setPosition(spriteXPos, spriteYPos);
	}

	flagIterator = flagSelection.begin();
	flagIterator->highlighted = true;

	currentPlayerText.setFont(game->mFontManager.getFont(FontManager::Arial));
	currentPlayerText.setString("Player 1");
	currentPlayerText.setCharacterSize(55);;
	currentPlayerText.setOrigin(currentPlayerText.getLocalBounds().width / 2, currentPlayerText.getLocalBounds().height / 2);
	currentPlayerText.setPosition(xResolution / 2, yResolution / 4);
}

void GameState_SelectNations::getInput(){
	sf::Event event;

	while (game->mWindow.pollEvent(event)){
		switch (event.type){
		case sf::Event::KeyPressed:
			if (event.key.code == CONFIRM_KEY){
			
				if (game->Player1 == nullptr){
					game->Player1 = new Player({game->mWorld, flagIterator->nation, game->mtengine, game->mTextureManager, game->mFontManager, true});
					flagSelection.erase(flagIterator);
					flagIterator = flagSelection.begin();
					currentPlayerText.setString("Player 2");
				}
				else{
					game->Player2 = new Player({game->mWorld, flagIterator->nation, game->mtengine, game->mTextureManager, game->mFontManager, false});
					game->currentPlayer = game->Player1;
					game->currentView = &game->currentPlayer->view;
					game->setGameStateSetup();
				}

			}
			else if (event.key.code == RIGHT_ARROW || event.key.code == LEFT_ARROW){
				clearHighlighting();

				if (event.key.code == LEFT_ARROW){
					if (flagIterator == flagSelection.begin()){
						flagIterator = --flagSelection.end();
					}
					else{
						--flagIterator;
					}
				}
				else if (event.key.code == RIGHT_ARROW){
					if (flagIterator == --flagSelection.end()){
						flagIterator = flagSelection.begin();
					}
					else{
						++flagIterator;
					}
				}
			}

			break;

		case sf::Event::Closed:
			game->mWindow.close();
			break;
		}
	}
}

void GameState_SelectNations::update(){
	flagView.setCenter(flagIterator->sprite.getPosition().x, flagView.getCenter().y);

	if (!flagIterator->highlighted){
		flagIterator->highlighted = true;
	}
}

void GameState_SelectNations::draw(){
	game->mWindow.clear(sf::Color(120,120,120));

	game->mWindow.setView(uiView);
	game->mWindow.draw(currentPlayerText);


	game->mWindow.setView(flagView);
	for (auto& flag : flagSelection){
		flag.draw(game->mWindow);
	}
}