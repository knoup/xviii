#include "xviii/Headers/stdafx.h"
#include "xviii/GameStates/GameState_MenuState.h"

#include "xviii/Core/Game.h"

sf::View GameState_MenuState::menuSelectView;
sf::View GameState_MenuState::backgroundView;

sf::Clock GameState_MenuState::fadeAnimationClock;
bool GameState_MenuState::fadingOut{true};

sf::Text GameState_MenuState::titleText;
sf::Text GameState_MenuState::quoteText;

std::unique_ptr<sf::Texture> GameState_MenuState::backgroundTexture;
sf::Sprite GameState_MenuState::backgroundSprite;

GameState_MenuState::GameState_MenuState(Game* game) :
GameState{game},
menuList{},
menuIterator{},
scrollbar{game->mWindow, menuSelectView, backgroundView}
{
    handleResize();
}

void GameState_MenuState::getInput(){
	sf::Event event;
	bool confirm{false};

	while (game->mWindow.pollEvent(event)){
		switch (event.type){

		case sf::Event::Closed:
			game->exitGame(false);
			break;

		case sf::Event::MouseButtonReleased:

			if(event.mouseButton.button == sf::Mouse::Left){
				scrollbar.setDragging(false);
			}
			break;

        case sf::Event::MouseButtonPressed:

            if(event.mouseButton.button == sf::Mouse::Left){
            	sf::FloatRect scrollBarOuterRectBounds = scrollbar.getOuterGlobalBounds();
            	sf::Vector2i coords{game->mousePos};
                sf::Vector2f mousePos{game->mWindow.mapPixelToCoords(coords, backgroundView)};

            	if(scrollbar.getActive() && scrollBarOuterRectBounds.intersects({mousePos.x, mousePos.y, 1.f, 1.f})){
					scrollbar.setDragging(true);;
            	}
            	else{
					confirm = true;
            	}
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
            	game->mousePos = {event.mouseMove.x, event.mouseMove.y};

                sf::Vector2i coords{game->mousePos};

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
			{
				if(scrollbar.getActive()){
					if(event.mouseWheel.delta > 0){
						scrollbar.scroll(0);
					}
					else if(event.mouseWheel.delta < 0){
						scrollbar.scroll(1);
					}
				}
			}

			break;

		case sf::Event::Resized:
            handleResize();
			break;

		default: break;

		}
	}
}

void GameState_MenuState::update(float /*mFT*/){
	if (!menuIterator->highlighted && menuIterator->highlightable){
		menuIterator->highlighted = true;
	}

	if(menuIterator->highlighted){
        auto transparency = menuIterator->text.getFillColor().a;

        int modifier;
        if(fadingOut){
            modifier = -1;
        }
        else{
            modifier = 1;
        }

        if(fadeAnimationClock.getElapsedTime().asMicroseconds() > 10){
            transparency += modifier;
            fadeAnimationClock.restart();
        }

        if(transparency <= 50){
            fadingOut = false;
        }
        else if(transparency == 255){
            fadingOut = true;
        }

        menuIterator->text.setFillColor(sf::Color(255,255,0,transparency));
	}

	scrollbar.update({game->mousePos});
}

void GameState_MenuState::draw(){
	game->mWindow.clear(sf::Color::Black);
	game->mWindow.setView(backgroundView);
	game->mWindow.draw(backgroundSprite);

	game->mWindow.draw(titleText);
	game->mWindow.draw(quoteText);

	game->mWindow.draw(scrollbar);

	game->mWindow.setView(menuSelectView);

	for (auto& item : menuList){
		game->mWindow.draw(item.text);
	}
}

void GameState_MenuState::onSwitch(){
    handleResize();
}

void GameState_MenuState::handleResize(){
	menuSelectView.setCenter({float(game->mWindow.getSize().x / 2), float(game->mWindow.getSize().y / 4) - 10});
    menuSelectView.setSize(game->mWindow.getSize().x / 2, game->mWindow.getSize().y / 2);
    menuSelectView.setViewport({0.25, 0.45, 0.5, 0.5});

    backgroundView.reset(sf::FloatRect({}, {},game->mWindow.getSize().x, game->mWindow.getSize().y));
    backgroundSprite.setOrigin(backgroundSprite.getGlobalBounds().width / 2, backgroundSprite.getGlobalBounds().height / 2);
    backgroundSprite.setPosition(backgroundView.getCenter());

    lineUpObjects();
}

void GameState_MenuState::lineUpObjects(){
	menuObject* widestObject = nullptr;


	if(!menuList.empty()){
		if(menuList.back().text.getPosition().y - menuList.front().text.getPosition().y > menuSelectView.getSize().y){
            scrollbar.setActive(true);
		}
		else{
			scrollbar.setActive(false);
		}
			widestObject = &menuList.front();
	}
	else{
        scrollbar.setActive(false);
	}

	titleText.setPosition(backgroundView.getSize().x / 2, 0);
	quoteText.setPosition(backgroundView.getSize().x / 2, titleText.getPosition().y + titleText.getGlobalBounds().height * 2);

	for (size_t i{0}; i < menuList.size(); ++i){
		int characterSize{35};

		menuList[i].text.setFont(game->mManager.fontManager->getFont(FontManager::Type::TCMT));
		menuList[i].text.setCharacterSize(characterSize);

        float textWidth{menuList[i].text.getGlobalBounds().width};
        float viewWidth{menuSelectView.getSize().x};

        while(textWidth > viewWidth && characterSize > 2){
			characterSize -= 2;
			menuList[i].text.setCharacterSize(characterSize);
			textWidth = menuList[i].text.getGlobalBounds().width;
			viewWidth = menuSelectView.getSize().x;
        }

        if(widestObject->text.getGlobalBounds().width < textWidth){
			widestObject = &menuList[i];
        }

		menuList[i].text.setOrigin(menuList[i].text.getGlobalBounds().width / 2, menuList[i].text.getGlobalBounds().height / 2);
		menuList[i].text.setFillColor(sf::Color::White);
		menuList[i].text.setStyle(sf::Text::Bold);

		int textXPos = menuSelectView.getCenter().x;
		int textYPos = (i * 50);

		menuList[i].text.setPosition(textXPos, textYPos);
	}


	if(scrollbar.getActive()){
        float totalMenuHeight = (menuList.back().text.getPosition().y + menuList.back().text.getGlobalBounds().height / 2)

                                - (menuList.front().text.getPosition().y - menuList.front().text.getGlobalBounds().height / 2);

        float initialXPos = widestObject->text.getPosition().x + (widestObject->text.getGlobalBounds().width / 2) * 1.2;
        float firstElementPosition_y = menuList.front().text.getPosition().y;
        float firstElementHeight = menuList.front().text.getGlobalBounds().height;

        scrollbar.init(totalMenuHeight, initialXPos, firstElementPosition_y, firstElementHeight, titleText.getColor());
	}

	menuIterator = menuList.begin();
}
