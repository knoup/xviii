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
GameState{game}
{
    std::vector<std::string> quotes;

    quotes.push_back("\"Cavalry is useful before, during, and after the battle.\" - Napoleon");
    quotes.push_back("\"Don't forget your great guns, which are the most respectable arguments of the rights of kings.\" - Frederick II");
    quotes.push_back("\"Do not fire until you see the white of their eyes!\" - Joseph Warren");
    quotes.push_back("\"Soldiers usually win the battles and generals get the credit for them.\" - Napoleon");
    quotes.push_back("\"War is not merely a political act but a real political instrument, a continuation of political\n intercourse, a carrying out of the same by other means.\" - Carl von Clausewitz");
    quotes.push_back("\"Discipline is the soul of an army. It makes small numbers formidable;\nprocures success to the weak, and esteem to all.\" - George Washington");
    quotes.push_back("\"The backbone of surprise is fusing speed with secrecy.\" - Carl von Clausewitz");
    quotes.push_back("\"It is even better to act quickly and err than to hesitate until the time of action is past.\" - Carl von Clausewitz");
    quotes.push_back("\"Men are always more inclined to pitch their estimate of the enemy's strength\n too high than too low, such is human nature.\" - Carl von Clausewitz");
    quotes.push_back("\"Everything in war is simple, but the simplest thing is difficult.\" - Carl von Clausewitz");
    quotes.push_back("\"There are times when the utmost daring is the height of wisdom.\" - Carl von Clausewitz");

	titleText.setCharacterSize(275);
	titleText.setFont(game->mManager.fontManager->getFont(FontManager::Eighteen));
	titleText.setString("X V I I I");

    //menuSelectView.reset(sf::FloatRect({}, {},xResolution, yResolution));
    menuSelectView.setCenter({680,0});
    menuSelectView.setSize(game->mWindow.getSize().x, game->mWindow.getSize().y);

    backgroundView.reset(sf::FloatRect({}, {},xResolution, yResolution));

	//Randomise title text colour, for the heck of it:
	boost::random::uniform_int_distribution<int> distribution(0, 255);
	int randColourR{distribution(game->mManager.randomEngine)};
	int randColourG{distribution(game->mManager.randomEngine)};
	int randColourB{distribution(game->mManager.randomEngine)};
	titleText.setFillColor(sf::Color(randColourR, randColourG, randColourB));

	titleText.setOrigin(titleText.getLocalBounds().width / 2, titleText.getLocalBounds().height / 2);
	titleText.setPosition(xResolution / 2, -(yResolution / 2.f));

    //Select a random quote:
	boost::random::uniform_int_distribution<int> quoteDistribution(0, quotes.size() - 1);
	int randQuote{quoteDistribution(game->mManager.randomEngine)};

    quoteText.setCharacterSize(20);
	quoteText.setFont(game->mManager.fontManager->getFont(FontManager::Arial));
    quoteText.setStyle(2);
	quoteText.setString(quotes.at(randQuote));

    quoteText.setOrigin(quoteText.getLocalBounds().width / 2, quoteText.getLocalBounds().height / 2);
	quoteText.setPosition(xResolution / 2, -(yResolution / 7.5f));

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

    //This will probably be required for the save menu
	//menuSelectView.setCenter(menuSelectView.getCenter().x, menuIterator->text.getPosition().y);
}

void GameState_MenuState::draw(){
	game->mWindow.clear(sf::Color::Black);
	game->mWindow.setView(backgroundView);
	game->mWindow.draw(backgroundSprite);

	game->mWindow.setView(menuSelectView);
	game->mWindow.draw(titleText);
	game->mWindow.draw(quoteText);

	for (auto& item : menuList){
		game->mWindow.draw(item.text);
	}
}

void GameState_MenuState::onSwitch(){
    menuSelectView.setCenter({680,0});
    menuSelectView.setSize(game->mWindow.getSize().x, game->mWindow.getSize().y);
}

void GameState_MenuState::lineUpObjects(){

	for (size_t i{0}; i < menuList.size(); ++i){
		menuList[i].text.setFont(game->mManager.fontManager->getFont(FontManager::Arial));
		menuList[i].text.setOrigin(menuList[i].text.getLocalBounds().width / 2, menuList[i].text.getLocalBounds().height / 2);
		menuList[i].text.setFillColor(sf::Color::White);
		menuList[i].text.setStyle(sf::Text::Bold);

		int textXPos = xResolution / 2;
		int textYPos = (i * 50);

		menuList[i].text.setPosition(textXPos, textYPos);
	}

	menuIterator = menuList.begin();
	menuSelectView.setCenter(menuSelectView.getCenter().x, menuIterator->text.getPosition().y);
}
