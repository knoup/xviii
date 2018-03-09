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

bool GameState_MenuState::scrollbarActive{false};
sf::RectangleShape GameState_MenuState::scrollBarOuterRect;
sf::RectangleShape GameState_MenuState::scrollBarInnerRect;

GameState_MenuState::GameState_MenuState(Game* game) :
GameState{game},
menuList{},
menuIterator{}
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
			{
				/*
				if (event.mouseWheel.delta > 0){
					if(menuSelectView.getCenter().y > menuSelectView.getSize().y / 2){
						menuSelectView.setCenter(menuSelectView.getCenter().x, menuSelectView.getCenter().y - 30);
					}
				}
				else if (event.mouseWheel.delta < 0){
					if(abs((menuList[menuList.size() - 1].text.getPosition().y + menuList[menuList.size() - 1].text.getGlobalBounds().height) - menuSelectView.getCenter().y) > menuSelectView.getSize().y / 2){
						menuSelectView.setCenter(menuSelectView.getCenter().x, menuSelectView.getCenter().y + 30);
					}
				}
				*/

				if(scrollbarActive){
					if(event.mouseWheel.delta > 0){
						scrollBar(0);
					}
					else if(event.mouseWheel.delta < 0){
						scrollBar(1);
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


	//Scrollbar logic
	///////////////////////////////////////////////////////////
	//This still needs some minor tweaking. Namely, the -30 and +30.
	//They need to be dynamic values. I'm trying to find the exact
	//relationship they have with the ratio and menuSelectView...
	///////////////////////////////////////////////////////////
	if(scrollbarActive){
		float scrollBarOuter_top{scrollBarOuterRect.getPosition().y - 30};
		float scrollBarInner_centerX{scrollBarInnerRect.getPosition().x + scrollBarInnerRect.getGlobalBounds().width / 2};
		float scrollBarInner_centerY{scrollBarInnerRect.getPosition().y + scrollBarInnerRect.getGlobalBounds().height / 2};
		float scrollBarOuter_bottom{scrollBarOuter_top + scrollBarOuterRect.getGlobalBounds().height};

		float scrollBarInner_distanceFromTop{scrollBarInner_centerY - scrollBarOuter_top};
		float menuList_distanceFromTop{menuSelectView.getCenter().y - menuList.front().text.getPosition().y};

		float totalMenuListHeight = menuList.back().text.getPosition().y;
		float totalScrollBarOuter_Height = scrollBarOuterRect.getGlobalBounds().height + 30;

		float finalRatio = totalMenuListHeight / totalScrollBarOuter_Height;

		float finalY = (finalRatio * (scrollBarInner_distanceFromTop));

		menuSelectView.setCenter(menuSelectView.getCenter().x, finalY);
	}
	///////////////////////////////////////////////////////////
}

void GameState_MenuState::draw(){
	game->mWindow.clear(sf::Color::Black);
	game->mWindow.setView(backgroundView);
	game->mWindow.draw(backgroundSprite);

	game->mWindow.draw(titleText);
	game->mWindow.draw(quoteText);

	if(scrollbarActive){
		game->mWindow.draw(scrollBarOuterRect);
		game->mWindow.draw(scrollBarInnerRect);
	}

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

    lineUpObjects();
}

void GameState_MenuState::lineUpObjects(){
	menuObject* widestObject = nullptr;


	if(!menuList.empty()){
		if(menuList.back().text.getPosition().y - menuList.front().text.getPosition().y > menuSelectView.getSize().y){
				scrollbarActive = true;
		}
		else{
			scrollbarActive = false;
		}
			widestObject = &menuList.front();
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

	if(scrollbarActive){
		float scrollbarXPos = widestObject->text.getPosition().x + (widestObject->text.getGlobalBounds().width / 2) * 1.2;
		scrollBarOuterRect.setSize({10, menuSelectView.getSize().y});
		scrollBarOuterRect.setPosition(scrollbarXPos, menuSelectView.getViewport().top * backgroundView.getSize().y);
		scrollBarOuterRect.setFillColor(sf::Color::Transparent);
		scrollBarOuterRect.setOutlineThickness(2);
		scrollBarOuterRect.setOutlineColor(sf::Color::White);

		scrollBarInnerRect.setPosition(scrollBarOuterRect.getPosition());
		scrollBarInnerRect.setSize({float(scrollBarOuterRect.getSize().x), float(scrollBarOuterRect.getSize().y * 0.1)});
		scrollBarInnerRect.setFillColor(titleText.getColor());
	}
	else{
		scrollBarOuterRect.setFillColor(sf::Color::Transparent);
		scrollBarOuterRect.setOutlineColor(sf::Color::Transparent);
		scrollBarInnerRect.setFillColor(sf::Color::Transparent);
		scrollBarInnerRect.setOutlineColor(sf::Color::Transparent);
	}

	menuIterator = menuList.begin();
}


void GameState_MenuState::scrollBar(bool _down){
	float step{float(scrollBarOuterRect.getGlobalBounds().height * 0.07)};

	float distanceFromTop{scrollBarInnerRect.getPosition().y - scrollBarOuterRect.getPosition().y};

	float distanceFromBottom
	{
		(scrollBarOuterRect.getPosition().y + scrollBarOuterRect.getGlobalBounds().height - scrollBarOuterRect.getOutlineThickness() * 2)
		-
		(scrollBarInnerRect.getPosition().y + scrollBarInnerRect.getGlobalBounds().height)
	};

	if(!_down){
		if(distanceFromTop > 0){
			if(step > distanceFromTop){
				step = distanceFromTop;
			}
			scrollBarInnerRect.setPosition(scrollBarInnerRect.getPosition().x, scrollBarInnerRect.getPosition().y - step);
		}
	}
	else{
		if(distanceFromBottom > 0){
			if(step > distanceFromBottom){
				step = distanceFromBottom;
			}
			scrollBarInnerRect.setPosition(scrollBarInnerRect.getPosition().x, scrollBarInnerRect.getPosition().y + step);
		}
	}
}
