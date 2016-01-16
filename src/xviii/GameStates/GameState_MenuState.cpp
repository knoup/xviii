#include "xviii/Headers/stdafx.h"
#include "xviii/GameStates/GameState_MenuState.h"

#include "xviii/Core/Game.h"

sf::Text GameState_MenuState::titleText;
std::unique_ptr<sf::Texture> GameState_MenuState::backgroundTexture;
sf::Sprite GameState_MenuState::backgroundSprite;

GameState_MenuState::GameState_MenuState(Game* game) :
GameState{game},
menuSelectView{sf::FloatRect({}, {},xResolution, yResolution)},
backgroundView{sf::FloatRect({}, {}, xResolution, yResolution)}
{
	titleText.setCharacterSize(275);
	titleText.setFont(game->mManager.fontManager->getFont(FontManager::Eighteen));
	titleText.setString("X V I I I");

	//Randomise title text colour, for the heck of it:
	boost::random::uniform_int_distribution<int> distribution(0, 255);
	int randColourR{distribution(game->mManager.randomEngine)};
	int randColourG{distribution(game->mManager.randomEngine)};
	int randColourB{distribution(game->mManager.randomEngine)};
	titleText.setColor(sf::Color(randColourR, randColourG, randColourB));

	titleText.setOrigin(titleText.getLocalBounds().width / 2, titleText.getLocalBounds().height / 2);
	titleText.setPosition(xResolution / 2, -(yResolution / 2.5f));

    backgroundSprite = game->mManager.textureManager->getRandomBackground();
}

void GameState_MenuState::getInput(){
	sf::Event event;

	bool confirm{false};

	while (game->mWindow.pollEvent(event)){
		switch (event.type){

		case sf::Event::Closed:
			game->exitGame(false);
			break;


        case sf::Event::MouseButtonPressed:

            if(event.mouseButton.button == sf::Mouse::Left){
                confirm = true;
            }

        case sf::Event::KeyPressed:

            if (event.key.code == Key::CONFIRM_KEY){
                confirm = true;
            }

			if (confirm){
				switch (menuIterator->action){
					case Action::NEW:
                        game->mWorld = new World(game->mManager, sf::Vector2i(69, 100));
						game->mWorld->generateRandomWorld(menuIterator->era);
						game->setGameState(game->SelectNationsState.get());
						break;

					case Action::LOAD:
						game->saveCreator.parse(menuIterator->path);
						break;

					case Action::EXIT:
						game->exitGame(false);
						break;

                    case Action::SAVE:
                        if (game->saveCreator.create()){
                            game->PlayState->setSaveStatus(true);
                        }
				}

				if(menuIterator->state != nullptr){
                    game->setGameState(menuIterator->state);
				}
			}


			//--menuList.end() because menuList.end() would point to a undereferencable reference
			//(after the end of the vector); --menuList.end() rather points to the last element

			else if ((event.key.code == Key::UP_ARROW || event.key.code == Key::DOWN_ARROW || event.key.code == Key::UP_KEY || event.key.code == Key::DOWN_KEY) && menuList.size() > 1){

				//Unhighlight current object
				menuIterator->text.setColor((sf::Color::White));

				if (event.key.code == Key::UP_ARROW || event.key.code == Key::UP_KEY){
					if (menuIterator == menuList.begin()){
                        auto it = --menuList.end();

                        if(it->highlightable){
                            menuIterator = --menuList.end();
                        }
					}
					else{
                        auto it = menuIterator - 1;

                        if(it->highlightable){
                            --menuIterator;
						}
					}
				}

				//There's something wrong here; holding down the arrow key if it's at the bottom
				//won't flip it back to the top. Investigate later.

				else if (event.key.code == Key::DOWN_ARROW || event.key.code == Key::DOWN_KEY){
					if (menuIterator == --menuList.end()){
                        auto it = --menuList.begin();

                        if(it->highlightable){
                            menuIterator = menuList.begin();
                        }
					}
					else{
                        auto it = menuIterator + 1;

                        if(it->highlightable){
                            ++menuIterator;
                        }
					}
				}
			}

			break;


            case sf::Event::MouseMoved:{

                sf::Vector2i coords{event.mouseMove.x, event.mouseMove.y};

                sf::Vector2f mousePos{game->mWindow.mapPixelToCoords(coords, menuSelectView)};

                for(size_t i{0}; i < menuList.size(); ++i){
                    if(menuList[i].text.getGlobalBounds().contains(mousePos)){

                        //Unhighlight current object
                        menuIterator->text.setColor((sf::Color::White));

                        menuIterator = menuList.begin();
                        menuIterator += i;
                    }
                }

            break;
            }


		case sf::Event::Resized:
			menuSelectView.setSize(event.size.width, event.size.height);
			break;

		default: break;

		}
	}
}

void GameState_MenuState::update(float mFT){
	if (menuIterator->text.getColor() != sf::Color::Yellow && menuIterator->highlightable){
		menuIterator->text.setColor(sf::Color::Yellow);
	}

	//menuSelectView.setCenter(menuSelectView.getCenter().x, menuIterator->text.getPosition().y);
}

void GameState_MenuState::draw(){
	game->mWindow.clear(sf::Color::Black);
	game->mWindow.setView(backgroundView);
	game->mWindow.draw(backgroundSprite);

	game->mWindow.setView(menuSelectView);
	game->mWindow.draw(titleText);

	for (auto& item : menuList){
		game->mWindow.draw(item.text);
	}
}

void GameState_MenuState::lineUpObjects(){

	for (size_t i{0}; i < menuList.size(); ++i){
		menuList[i].text.setFont(game->mManager.fontManager->getFont(FontManager::Arial));
		menuList[i].text.setOrigin(menuList[i].text.getLocalBounds().width / 2, menuList[i].text.getLocalBounds().height / 2);
		menuList[i].text.setColor(sf::Color::White);
		menuList[i].text.setStyle(sf::Text::Bold);

		int textXPos = xResolution / 2;
		int textYPos = (i * 50);

		menuList[i].text.setPosition(textXPos, textYPos);
	}

	menuIterator = menuList.begin();
	menuSelectView.setCenter(menuSelectView.getCenter().x, menuIterator->text.getPosition().y);
}
