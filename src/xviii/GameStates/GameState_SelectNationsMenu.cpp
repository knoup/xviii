#include "xviii/Headers/stdafx.h"
#include "xviii/GameStates/GameState_SelectNationsMenu.h"

#include "xviii/Core/Game.h"
#include "xviii/Core/FactionLoader.h"

void GameState_SelectNationsMenu::updateNationName(){
    //player1NationText.setString(" - " + flagIterator1->displayName);
    //player1NationText.setPosition(flagIterator1->sprite.getPosition().x + 25, flagIterator1->sprite.getPosition().y - 20);
    //player1Text.setPosition(flagIterator1->sprite.getPosition().x - 150, flagIterator1->sprite.getPosition().y - 20);

    //player2NationText.setString(flagIterator2->displayName + " - ");
    //player2NationText.setOrigin(player2NationText.getLocalBounds().width, 0);
    //player2NationText.setPosition(flagIterator2->sprite.getPosition().x - 25, flagIterator2->sprite.getPosition().y - 20);
    //player2Text.setPosition(flagIterator2->sprite.getPosition().x + 150, flagIterator2->sprite.getPosition().y - 20);
}

GameState_SelectNationsMenu::GameState_SelectNationsMenu(Game* _game) :
GameState_MenuState{_game},
flagMenuItems1{},
flagMenuItems2{},
flagIterator1{},
flagIterator2{},
flagView1{sf::FloatRect({}, {}, game->mWindow.getSize().x, game->mWindow.getSize().y)},
flagView2{sf::FloatRect({}, {}, game->mWindow.getSize().x, game->mWindow.getSize().y)},
player1Text{},
player2Text{},
player1NationText{},
player2NationText{}
{
    backgroundSprite = game->mManager.textureManager->getRandomBackground();

	for(auto& faction : game->mManager.factionLoader->customFactions){
		flagMenuItems1.emplace_back(faction.second.factionID, faction.second.displayName, game->mManager.textureManager->getFlagSprite(faction.second.textureID), game->mManager.fontManager->getFont(FontManager::Type::TCMT));
		flagMenuItems2.emplace_back(faction.second.factionID, faction.second.displayName, game->mManager.textureManager->getFlagSprite(faction.second.textureID), game->mManager.fontManager->getFont(FontManager::Type::TCMT));
	}

    //flagIterator1 = flagMenuItems1.begin() + flagMenuItems1.size() / 2;
    flagIterator1 = flagMenuItems1.begin();
    flagIterator1->highlighted = true;

    //flagIterator2 = flagMenuItems2.begin() + flagMenuItems2.size() / 2;
    flagIterator2 = flagMenuItems2.begin();
    flagIterator2->highlighted = true;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    player1Text.setFont(game->mManager.fontManager->getFont(FontManager::Type::TCMT));
	player1Text.setString("Player 1");
	player1Text.setFillColor(sf::Color::Yellow);
	player1Text.setCharacterSize(30);;

	player2Text.setFont(game->mManager.fontManager->getFont(FontManager::Type::TCMT));
	player2Text.setString("Player 2");
	player2Text.setFillColor(sf::Color::Yellow);
	player2Text.setCharacterSize(30);;

	player1NationText.setFont(game->mManager.fontManager->getFont(FontManager::Type::TCMT));
	player1NationText.setFillColor(sf::Color::White);
	player1NationText.setCharacterSize(30);

	player2NationText.setFont(game->mManager.fontManager->getFont(FontManager::Type::TCMT));
	player2NationText.setFillColor(sf::Color::White);
	player2NationText.setCharacterSize(30);;

	updateNationName();

	////////////
	menuList.push_back({std::string("Start (All Eras)"), true, nullptr, Action::NEW, World::Era::ALL});
	menuList.push_back({std::string("Start (Late Era)"), true, nullptr, Action::NEW, World::Era::LATE});
	menuList.push_back({std::string("Start (Mid Era)"), true, nullptr, Action::NEW, World::Era::MID});
	menuList.push_back({std::string("Start (Early Era)"), true, nullptr, Action::NEW, World::Era::EARLY});
	menuList.push_back({std::string("Advanced Settings"), true, nullptr, Action::NONE});
	menuList.push_back({std::string(""), false, nullptr, Action::NONE});
	menuList.push_back({std::string("Back"), true, game->CustomBattleMenuState.get(), Action::NONE});
	////////////

	handleResize();
}

void GameState_SelectNationsMenu::getInput(){

    //GameState_MenuState::getInput();

    bool confirm{false};
	sf::Event event;

	while (game->mWindow.pollEvent(event)){
		switch (event.type){

        case sf::Event::Closed:
            game->exitGame(false);
            break;

		case sf::Event::MouseWheelMoved:
		    {

		    std::vector<FlagMenuItem>* flagMenuItems{nullptr};
            std::vector<FlagMenuItem>::iterator* flagIterator{nullptr};

            if(event.mouseWheel.x < xResolution / 3){
                flagMenuItems = &flagMenuItems1;
                flagIterator = &flagIterator1;
            }
            else if(event.mouseWheel.x > 0.66 * xResolution){
                flagMenuItems = &flagMenuItems2;
                flagIterator = &flagIterator2;
            }
            else{
                break;
            }

            if(event.mouseWheel.delta > 0){

                (*flagIterator)->highlighted = false;

                if((*flagIterator) == (*flagMenuItems).begin()){
                    (*flagIterator) = (*flagMenuItems).end() - 1;
                }
                else{
                    (*flagIterator)--;
                }

                (*flagIterator)->highlighted = true;

            }

            else if(event.mouseWheel.delta < 0){

                (*flagIterator)->highlighted = false;

                if((*flagIterator) == (*flagMenuItems).end() - 1){
                    (*flagIterator) = (*flagMenuItems).begin();
                }
                else{
                    (*flagIterator)++;
                }

                (*flagIterator)->highlighted = true;

            }

            updateNationName();

			break;

		    }


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

					    if(flagIterator1->factionID == flagIterator2->factionID){
                            break;
					    }

					    game->mWorld = new World(game->mManager, sf::Vector2i(69, 100));
						game->mWorld->generateRandomWorld(menuIterator->era);

                        game->Player1 = new Player{game->mManager, game->mWorld, flagIterator1->factionID, true};
                        game->mPlayers.emplace_back(game->Player1);

                        game->Player2 = new Player{game->mManager, game->mWorld, flagIterator2->factionID, false};
                        game->mPlayers.emplace_back(game->Player2);

                        game->currentPlayer = game->Player1;
                        game->currentView = &game->currentPlayer->view;
						game->setGameState(game->SetupState.get());
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

                        //Unhighlight current object
                        menuIterator->text.setFillColor((sf::Color::White));

                        menuIterator = menuList.begin();
                        menuIterator += i;

                        menuIterator->text.setFillColor((sf::Color::Yellow));
                    }
                }

            break;
            }

            case sf::Event::Resized:
                handleResize();
                break;


		default: break;

		}

	}


}

void GameState_SelectNationsMenu::update(float mFT){

    GameState_MenuState::update(mFT);
}

void GameState_SelectNationsMenu::draw(){
	game->mWindow.clear(sf::Color(120,120,120));

	game->mWindow.setView(backgroundView);
	game->mWindow.draw(backgroundSprite);

    game->mWindow.draw(titleText);

	game->mWindow.setView(menuSelectView);

	for (auto& item : menuList){
		game->mWindow.draw(item.text);
	}


	game->mWindow.setView(flagView1);
	for (auto& flag : flagMenuItems1){
		flag.draw(game->mWindow);
		//game->mWindow.draw(player1Text);
		//game->mWindow.draw(player1NationText);
	}

	game->mWindow.setView(flagView2);
	for (auto& flag : flagMenuItems2){
		flag.draw(game->mWindow);
		//game->mWindow.draw(player2Text);
		//game->mWindow.draw(player2NationText);
	}
}

void GameState_SelectNationsMenu::handleResize(){
	//flagView1.setViewport(sf::FloatRect(0, 0, 1, 1));
    //flagView2.setViewport(sf::FloatRect(0.5f, 0, 1, 1));

    flagView1.setCenter({float(game->mWindow.getSize().x * 0.125), float(game->mWindow.getSize().y / 4) - 30});
    flagView1.setSize(game->mWindow.getSize().x / 3, game->mWindow.getSize().y / 2);
    flagView1.setViewport({0, 0.45, 0.33, 0.5});

    flagView2.setCenter({float(game->mWindow.getSize().x * 0.125), float(game->mWindow.getSize().y / 4) - 30});
    flagView2.setSize(game->mWindow.getSize().x / 3, game->mWindow.getSize().y / 2);
    flagView2.setViewport({0.66, 0.45, 0.33, 0.5});


	GameState_MenuState::handleResize();
	lineUpObjects();
}

void GameState_SelectNationsMenu::lineUpObjects(){

	int previousFlagYPos{0};

	//The following algorithm appropriately places the menu items and,
	//if neccessary, splits them into as many lines as needed.

	//For two lined entries, it attempts to intelligently
	//split only following following a space character.
	//If this is not possible, or for entries that span more
	//than two lines, it splits the string into equal parts.

	for (size_t i{0}; i < flagMenuItems1.size(); ++i){
        int textYPos{previousFlagYPos};
        float textXPos{flagMenuItems1[i].sprite.getPosition().x + (flagMenuItems1[i].sprite.getGlobalBounds().width) + flagMenuItems1[i].rekt.getOutlineThickness() * 2};


		flagMenuItems1[i].displayNameText.setPosition(textXPos, textYPos);

		int spriteYPos = (previousFlagYPos);
		int spriteXPos{0};

		flagMenuItems1[i].sprite.setPosition(spriteXPos, spriteYPos);
		flagMenuItems1[i].rekt.setPosition(spriteXPos, spriteYPos);

		float height{0};

		if(flagMenuItems1[i].displayNameText.getGlobalBounds().height > flagMenuItems1[i].sprite.getGlobalBounds().height){
			height = flagMenuItems1[i].displayNameText.getGlobalBounds().height;
		}
		else{
			height = flagMenuItems1[i].sprite.getGlobalBounds().height;
		}

		previousFlagYPos += height * 1.1;

		previousFlagYPos += height * 0.1;
	}

	for (size_t i{0}; i < flagMenuItems2.size(); ++i){
		int spriteYPos = (i * 45);
		int spriteXPos{0};

		flagMenuItems2[i].sprite.setPosition(spriteXPos, spriteYPos);
		flagMenuItems2[i].rekt.setPosition(spriteXPos, spriteYPos);
	}

	//player1Text.setOrigin(player1Text.getLocalBounds().width / 2, player1Text.getLocalBounds().height / 2);
	//player1Text.setPosition(xResolution / 8, -350);

	//player2Text.setOrigin(player2Text.getLocalBounds().width, 0);
	//player2Text.setPosition((xResolution / 8) * 3, -350);

	//player2NationText.setOrigin(player2NationText.getLocalBounds().width, 0);

	GameState_MenuState::lineUpObjects();
}
