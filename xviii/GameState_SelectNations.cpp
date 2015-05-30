#include "stdafx.h"
#include "GameState_SelectNations.h"

#include "Game.h"

void GameState_SelectNations::updateNationName(){
	#define X(nationType, textureType, str)\
		if(flagIterator->nation == nationType){\
			currentNationName.setString(str);\
			}
	NATIONPROPERTIES
	#undef X

	sf::FloatRect textRect = currentNationName.getLocalBounds();
	currentNationName.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	currentNationName.setPosition(xResolution / 2, yResolution / 1.5);
}

GameState_SelectNations::GameState_SelectNations(Game* _game) :
GameState{_game},
flagView{sf::FloatRect({}, {}, xResolution, yResolution)},
uiView{sf::FloatRect({}, {}, xResolution, yResolution)}
{

	flagMenuItems.push_back({game->mTextureManager.getSprite(TextureManager::Flag::AUS), Player::Nation::AUS});
	flagMenuItems.push_back({game->mTextureManager.getSprite(TextureManager::Flag::BAV), Player::Nation::BAV});
	flagMenuItems.push_back({game->mTextureManager.getSprite(TextureManager::Flag::COM), Player::Nation::COM});
	flagMenuItems.push_back({game->mTextureManager.getSprite(TextureManager::Flag::CRI), Player::Nation::CRI});
	flagMenuItems.push_back({game->mTextureManager.getSprite(TextureManager::Flag::FRA), Player::Nation::FRA});
	flagMenuItems.push_back({game->mTextureManager.getSprite(TextureManager::Flag::GBR), Player::Nation::GBR});
	flagMenuItems.push_back({game->mTextureManager.getSprite(TextureManager::Flag::IME), Player::Nation::IME});
	flagMenuItems.push_back({game->mTextureManager.getSprite(TextureManager::Flag::MOL), Player::Nation::MOL});
	flagMenuItems.push_back({game->mTextureManager.getSprite(TextureManager::Flag::OTO), Player::Nation::OTO});
	flagMenuItems.push_back({game->mTextureManager.getSprite(TextureManager::Flag::PER), Player::Nation::PER});
	flagMenuItems.push_back({game->mTextureManager.getSprite(TextureManager::Flag::POR), Player::Nation::POR});
	flagMenuItems.push_back({game->mTextureManager.getSprite(TextureManager::Flag::PRU), Player::Nation::PRU});
	flagMenuItems.push_back({game->mTextureManager.getSprite(TextureManager::Flag::RUS), Player::Nation::RUS});
	flagMenuItems.push_back({game->mTextureManager.getSprite(TextureManager::Flag::SAX), Player::Nation::SAX});
	flagMenuItems.push_back({game->mTextureManager.getSprite(TextureManager::Flag::SPA), Player::Nation::SPA});
	flagMenuItems.push_back({game->mTextureManager.getSprite(TextureManager::Flag::SWE), Player::Nation::SWE});
	flagMenuItems.push_back({game->mTextureManager.getSprite(TextureManager::Flag::VEN), Player::Nation::VEN});
	flagMenuItems.push_back({game->mTextureManager.getSprite(TextureManager::Flag::WAL), Player::Nation::WAL});

	for (int i{0}; i < flagMenuItems.size(); ++i){
		int spriteXPos = (i * 75);
		int spriteYPos = yResolution / 2;

		flagMenuItems[i].sprite.setPosition(spriteXPos, spriteYPos);
		flagMenuItems[i].rekt.setPosition(spriteXPos, spriteYPos);
	}

	flagIterator = flagMenuItems.begin() + flagMenuItems.size() / 2;
	flagIterator->highlighted = true;

	currentPlayerText.setFont(game->mFontManager.getFont(FontManager::Arial));
	currentPlayerText.setString("Player 1");
	currentPlayerText.setColor(sf::Color::White);
	currentPlayerText.setCharacterSize(55);;
	currentPlayerText.setOrigin(currentPlayerText.getLocalBounds().width / 2, currentPlayerText.getLocalBounds().height / 2);
	currentPlayerText.setPosition(xResolution / 2, yResolution / 4);

	currentNationName.setFont(game->mFontManager.getFont(FontManager::Arial));
	currentNationName.setColor(sf::Color::Black);
	currentNationName.setCharacterSize(50);

	updateNationName();
}

void GameState_SelectNations::getInput(){
	sf::Event event;

	while (game->mWindow.pollEvent(event)){
		switch (event.type){
		case sf::Event::KeyPressed:
			if (event.key.code == CONFIRM_KEY){
			
				if (game->Player1 == nullptr){
					game->Player1 = new Player({game->mUnitLoader, game->mWorld, flagIterator->nation, game->mtengine, game->mTextureManager, game->mFontManager, true});
					game->mPlayers.emplace_back(game->Player1);
					//Once player 1's made their selection, delete the country he chose
					flagMenuItems.erase(flagIterator);
					flagIterator = flagMenuItems.begin() + flagMenuItems.size() / 2;

					//And fix the positions of the rest
					for (int i{0}; i < flagMenuItems.size(); ++i){
						int spriteXPos = (i * 75);
						int spriteYPos = yResolution / 2;

						flagMenuItems[i].sprite.setPosition(spriteXPos, spriteYPos);
						flagMenuItems[i].rekt.setPosition(spriteXPos, spriteYPos);
					}

					updateNationName();
					currentPlayerText.setString("Player 2");
				}
				else{
					game->Player2 = new Player({game->mUnitLoader, game->mWorld, flagIterator->nation, game->mtengine, game->mTextureManager, game->mFontManager, false});
					game->mPlayers.emplace_back(game->Player2);
					game->currentPlayer = game->Player1;
					game->currentView = &game->currentPlayer->view;
					game->setGameStateSetup();
				}

			}
			else if (event.key.code == RIGHT_ARROW || event.key.code == LEFT_ARROW || event.key.code == LEFT_KEY || event.key.code == RIGHT_KEY){
				flagIterator->highlighted = false;

				if (event.key.code == LEFT_ARROW || event.key.code == LEFT_KEY){
					if (flagIterator == flagMenuItems.begin()){
						flagIterator = --flagMenuItems.end();
					}
					else{
						--flagIterator;
					}
				}
				else if (event.key.code == RIGHT_ARROW || event.key.code == RIGHT_KEY){
					if (flagIterator == --flagMenuItems.end()){
						flagIterator = flagMenuItems.begin();
					}
					else{
						++flagIterator;
					}
				}

				updateNationName();

			}

			else if (event.key.code == RANDOMNATION_KEY){
				std::uniform_int_distribution<int> distribution(0, flagMenuItems.size() - 1);
				int randNum{distribution(game->mtengine)};

				flagIterator->highlighted = false;
				flagIterator._Ptr = &flagMenuItems.at(randNum);
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