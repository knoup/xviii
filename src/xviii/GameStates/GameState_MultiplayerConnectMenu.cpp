#include "xviii/Headers/stdafx.h"
#include "xviii/GameStates/GameState_MultiplayerConnectMenu.h"

#include "xviii/Core/Game.h"

GameState_MultiplayerConnectMenu::GameState_MultiplayerConnectMenu(Game* game) :
GameState_MenuState{game}
{

}

void GameState_MultiplayerConnectMenu::init(){
    menuList.push_back({{"Establish connection"}, true, nullptr, Action::NONE});
    menuList.push_back({{""}, false, nullptr, Action::NONE});
	menuList.push_back({{"Back"}, true, game->MultiplayerMenuState.get(), Action::NONE});
	lineUpObjects();

    instructionalText.setCharacterSize(40);
	instructionalText.setFont(game->mManager.fontManager->getFont(FontManager::Lucon));
	instructionalText.setString("Enter the host's IP:");
	instructionalText.setFillColor(sf::Color::Red);
	instructionalText.setOrigin(instructionalText.getLocalBounds().width / 2, instructionalText.getLocalBounds().height / 2);
	instructionalText.setPosition(xResolution / 2, -(yResolution / 3.5f));

    IPText.setCharacterSize(30);
	IPText.setFont(game->mManager.fontManager->getFont(FontManager::Arial));
	IPText.setOrigin(IPText.getLocalBounds().width / 2, IPText.getLocalBounds().height / 2);
	IPText.setPosition(xResolution / 2, -(yResolution / 5.f));
}

void GameState_MultiplayerConnectMenu::getInput(){
	sf::Event event;
	bool confirm{false};

	while (game->mWindow.pollEvent(event)){

        if (event.type == sf::Event::TextEntered){

            if (IPString.size() < 15 && (event.text.unicode == 46 || (event.text.unicode >= 48 && event.text.unicode <= 57))){
                IPString += static_cast<char>(event.text.unicode);
            }
            else if(event.text.unicode == 8 && !IPString.empty()){
                IPString.erase(IPString.size()-1);
            }

            IPText.setString(IPString);
            IPText.setOrigin(IPText.getLocalBounds().width / 2, IPText.getLocalBounds().height / 2);
            IPText.setPosition(xResolution / 2, -(yResolution / 5.f));

        }

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
                        break;

                    case Action::NONE:
                        break;
				}

				if(menuIterator->state != nullptr){
                    game->setGameState(menuIterator->state);
				}
			}


			//--menuList.end() because menuList.end() would point to a undereferencable reference
			//(after the end of the vector); --menuList.end() rather points to the last element

			else if ((event.key.code == Key::UP_ARROW || event.key.code == Key::DOWN_ARROW || event.key.code == Key::UP_KEY || event.key.code == Key::DOWN_KEY) && menuList.size() > 1){

				//Unhighlight current object
				menuIterator->text.setFillColor((sf::Color::White));

				if (event.key.code == Key::UP_ARROW || event.key.code == Key::UP_KEY){
					if (menuIterator == menuList.begin()){
						menuIterator = --menuList.end();
					}
					else{
						--menuIterator;
					}
				}


				else if (event.key.code == Key::DOWN_ARROW || event.key.code == Key::DOWN_KEY){
					if (menuIterator == --menuList.end()){
						menuIterator = menuList.begin();
					}
					else{
						++menuIterator;
					}
				}
			}

			break;


            case sf::Event::MouseMoved:{

                sf::Vector2i coords{event.mouseMove.x, event.mouseMove.y};

                sf::Vector2f mousePos{game->mWindow.mapPixelToCoords(coords, menuSelectView)};

                for(size_t i{0}; i < menuList.size(); ++i){
                    if(menuList[i].text.getGlobalBounds().contains(mousePos)){

                        //Ensure that the next highlighted menu will start at
                        //maximum opaqueness and start fading out
                        fadingOut = true;
                        //Unhighlight current object
                        menuIterator->highlighted = false;
                        menuIterator->text.setFillColor(sf::Color::White);

                        menuIterator = menuList.begin();
                        menuIterator += i;
                    }
                }

            break;
            }

            case sf::Event::MouseWheelMoved:

            if(scroll){
                if (event.mouseWheel.delta > 0){
                    if(abs(menuList[0].text.getPosition().y - menuSelectView.getCenter().y) > 20){
                        menuSelectView.setCenter(menuSelectView.getCenter().x, menuSelectView.getCenter().y - 30);
                    }
                }
                else if (event.mouseWheel.delta < 0){
                    if(abs(menuList[menuList.size() - 1].text.getPosition().y - menuSelectView.getCenter().y) > 300){
                        menuSelectView.setCenter(menuSelectView.getCenter().x, menuSelectView.getCenter().y + 30);
                    }
                }
            }

			break;


		case sf::Event::Resized:
			menuSelectView.setSize(event.size.width, event.size.height);
			break;

		default: break;

		}
	}
}


void GameState_MultiplayerConnectMenu::update(float mFT){
    GameState_MenuState::update(mFT);

}

void GameState_MultiplayerConnectMenu::draw(){
    game->mWindow.clear(sf::Color::Black);
	game->mWindow.setView(backgroundView);
	game->mWindow.draw(backgroundSprite);

	game->mWindow.setView(menuSelectView);
	game->mWindow.draw(IPText);
	game->mWindow.draw(instructionalText);

	for (auto& item : menuList){
		game->mWindow.draw(item.text);
	}
}
