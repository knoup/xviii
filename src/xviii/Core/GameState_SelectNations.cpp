#include "xviii/Headers/stdafx.h"
#include "xviii/Core/GameState_SelectNations.h"

#include "xviii/Core/Game.h"
#include "xviii/Core/FactionLoader.h"

void GameState_SelectNations::updateNationName(){
	currentNationName.setString(flagIterator->displayName);

	sf::FloatRect textRect = currentNationName.getLocalBounds();
	currentNationName.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	currentNationName.setPosition(xResolution / 2, yResolution / 1.5);
}

GameState_SelectNations::GameState_SelectNations(Game* _game) :
GameState{_game},
flagView{sf::FloatRect({}, {}, xResolution, yResolution)},
uiView{sf::FloatRect({}, {}, xResolution, yResolution)}
{

	for(auto& faction : game->mManager.factionLoader->customFactions){
        flagMenuItems.emplace_back(faction.second.factionID, faction.second.displayName, game->mManager.textureManager->getFlagSprite(faction.second.textureID));
	}

	for (size_t i{0}; i < flagMenuItems.size(); ++i){
		int spriteXPos = (i * 75);
		int spriteYPos = yResolution / 2;

		flagMenuItems[i].sprite.setPosition(spriteXPos, spriteYPos);
		flagMenuItems[i].rekt.setPosition(spriteXPos, spriteYPos);
	}


    flagIterator = flagMenuItems.begin() + flagMenuItems.size() / 2;
    flagIterator->highlighted = true;


	currentPlayerText.setFont(game->mManager.fontManager->getFont(FontManager::Arial));
	currentPlayerText.setString("Player 1");
	currentPlayerText.setColor(sf::Color::White);
	currentPlayerText.setCharacterSize(55);;
	currentPlayerText.setOrigin(currentPlayerText.getLocalBounds().width / 2, currentPlayerText.getLocalBounds().height / 2);
	currentPlayerText.setPosition(xResolution / 2, yResolution / 4);

	currentNationName.setFont(game->mManager.fontManager->getFont(FontManager::Arial));
	currentNationName.setColor(sf::Color::Black);
	currentNationName.setCharacterSize(50);

	updateNationName();
}

void GameState_SelectNations::getInput(){
	sf::Event event;

	while (game->mWindow.pollEvent(event)){
		switch (event.type){
		case sf::Event::KeyPressed:
			if (event.key.code == Key::CONFIRM_KEY){

				if (game->Player1 == nullptr){
					game->Player1 = new Player({game->mManager, game->mWorld, flagIterator->factionID, true});
					game->mPlayers.emplace_back(game->Player1);
					//Once player 1's made their selection, delete the country he chose
					flagMenuItems.erase(flagIterator);
					flagIterator = flagMenuItems.begin() + flagMenuItems.size() / 2;

					//And fix the positions of the rest
					for (size_t i{0}; i < flagMenuItems.size(); ++i){
						int spriteXPos = (i * 75);
						int spriteYPos = yResolution / 2;

						flagMenuItems[i].sprite.setPosition(spriteXPos, spriteYPos);
						flagMenuItems[i].rekt.setPosition(spriteXPos, spriteYPos);
					}

					updateNationName();
					currentPlayerText.setString("Player 2");
				}
				else{
					game->Player2 = new Player({game->mManager, game->mWorld, flagIterator->factionID, false});
					game->mPlayers.emplace_back(game->Player2);
					game->currentPlayer = game->Player1;
					game->currentView = &game->currentPlayer->view;
					game->setGameStateSetup();
				}

			}
			else if (event.key.code == Key::RIGHT_ARROW || event.key.code == Key::LEFT_ARROW || event.key.code == Key::LEFT_KEY || event.key.code == Key::RIGHT_KEY){
				flagIterator->highlighted = false;

				if (event.key.code == Key::LEFT_ARROW || event.key.code == Key::LEFT_KEY){
					if (flagIterator == flagMenuItems.begin()){
						flagIterator = --flagMenuItems.end();
					}
					else{
						--flagIterator;
					}
				}
				else if (event.key.code == Key::RIGHT_ARROW || event.key.code == Key::RIGHT_KEY){
					if (flagIterator == --flagMenuItems.end()){
						flagIterator = flagMenuItems.begin();
					}
					else{
						++flagIterator;
					}
				}

				updateNationName();

			}

			else if (event.key.code == Key::RANDOMNATION_KEY){
				boost::random::uniform_int_distribution<int> distribution(0, flagMenuItems.size() - 1);
				int randNum{distribution(game->mManager.randomEngine)};

				flagIterator->highlighted = false;
				flagIterator = flagMenuItems.begin();
				flagIterator += randNum;
				flagIterator->highlighted = true;
				updateNationName();
			}

			break;

		case sf::Event::Closed:
			game->mWindow.close();
			break;

		case sf::Event::Resized:
			uiView.setSize(event.size.width, event.size.height);
			flagView.setSize(event.size.width, event.size.height);
			break;

		default: break;
		}
	}
}

void GameState_SelectNations::update(float mFT){
	flagView.setCenter(flagIterator->sprite.getPosition().x, flagView.getCenter().y);

	if (!flagIterator->highlighted){
		flagIterator->highlighted = true;
	}
}

void GameState_SelectNations::draw(){
	game->mWindow.clear(sf::Color(120,120,120));

	game->mWindow.setView(uiView);
	game->mWindow.draw(currentPlayerText);
	game->mWindow.draw(currentNationName);


	game->mWindow.setView(flagView);
	for (auto& flag : flagMenuItems){
		flag.draw(game->mWindow);
	}
}
