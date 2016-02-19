#include "xviii/Headers/stdafx.h"
#include "xviii/GameStates/GameState_SelectNations.h"

#include "xviii/Core/Game.h"
#include "xviii/Core/FactionLoader.h"

void GameState_SelectNations::updateNationName(){
    player1NationText.setString(" - " + flagIterator1->displayName);
    player1NationText.setPosition(flagIterator1->sprite.getPosition().x + 25, flagIterator1->sprite.getPosition().y - 20);
    player1Text.setPosition(flagIterator1->sprite.getPosition().x - 150, flagIterator1->sprite.getPosition().y - 20);

    player2NationText.setString(flagIterator2->displayName + " - ");
    player2NationText.setOrigin(player2NationText.getLocalBounds().width, 0);
    player2NationText.setPosition(flagIterator2->sprite.getPosition().x - 25, flagIterator2->sprite.getPosition().y - 20);
    player2Text.setPosition(flagIterator2->sprite.getPosition().x + 150, flagIterator2->sprite.getPosition().y - 20);
}

GameState_SelectNations::GameState_SelectNations(Game* _game) :
GameState_MenuState{_game},
flagView1{sf::FloatRect({}, {}, xResolution, yResolution)},
flagView2{sf::FloatRect({}, {}, xResolution, yResolution)},
backgroundView{sf::FloatRect({}, {}, xResolution, yResolution)}
{
    backgroundSprite = game->mManager.textureManager->getRandomBackground();

    flagView1.setViewport(sf::FloatRect(0, 0, 1, 1));
    flagView2.setViewport(sf::FloatRect(0.5f, 0, 1, 1));


    flagView1.setCenter(flagView1.getCenter().x, 0);
    flagView2.setCenter(flagView2.getCenter().x, 0);

	for(auto& faction : game->mManager.factionLoader->customFactions){
        flagMenuItems1.emplace_back(faction.second.factionID, faction.second.displayName, game->mManager.textureManager->getFlagSprite(faction.second.textureID));
	}

	for (size_t i{0}; i < flagMenuItems1.size(); ++i){
		int spriteYPos = (i * 45) - 130;
		int spriteXPos = xResolution / 8;

		flagMenuItems1[i].sprite.setPosition(spriteXPos, spriteYPos);
		flagMenuItems1[i].rekt.setPosition(spriteXPos, spriteYPos);
	}

    flagIterator1 = flagMenuItems1.begin() + flagMenuItems1.size() / 2;
    //flagIterator1 = flagMenuItems1.begin();
    flagIterator1->highlighted = true;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    for(auto& faction : game->mManager.factionLoader->customFactions){
        flagMenuItems2.emplace_back(faction.second.factionID, faction.second.displayName, game->mManager.textureManager->getFlagSprite(faction.second.textureID));
	}

	for (size_t i{0}; i < flagMenuItems2.size(); ++i){
		int spriteYPos = (i * 45) - 130;
		int spriteXPos = (xResolution / 8) * 3;

		flagMenuItems2[i].sprite.setPosition(spriteXPos, spriteYPos);
		flagMenuItems2[i].rekt.setPosition(spriteXPos, spriteYPos);
	}

    flagIterator2 = flagMenuItems2.begin() + flagMenuItems2.size() / 2;
    //flagIterator2 = flagMenuItems2.begin();
    flagIterator2->highlighted = true;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    player1Text.setFont(game->mManager.fontManager->getFont(FontManager::Arial));
	player1Text.setString("Player 1");
	player1Text.setColor(sf::Color::Yellow);
	player1Text.setCharacterSize(30);;
	//player1Text.setOrigin(player1Text.getLocalBounds().width / 2, player1Text.getLocalBounds().height / 2);
	//player1Text.setPosition(xResolution / 8, -350);

	player2Text.setFont(game->mManager.fontManager->getFont(FontManager::Arial));
	player2Text.setString("Player 2");
	player2Text.setColor(sf::Color::Yellow);
	player2Text.setCharacterSize(30);;
	player2Text.setOrigin(player2Text.getLocalBounds().width, 0);
	//player2Text.setPosition((xResolution / 8) * 3, -350);

	player1NationText.setFont(game->mManager.fontManager->getFont(FontManager::Arial));
	player1NationText.setColor(sf::Color::White);
	player1NationText.setCharacterSize(30);

	player2NationText.setFont(game->mManager.fontManager->getFont(FontManager::Arial));
	player2NationText.setColor(sf::Color::White);
	player2NationText.setCharacterSize(30);;
	player2NationText.setOrigin(player2NationText.getLocalBounds().width, 0);

	updateNationName();

	////////////
	menuList.push_back({{"Back"}, true, game->CustomBattleSelectEraMenuState.get(), Action::NONE});
	menuList.push_back({{"Start"}, true, nullptr, Action::NEW});
	////////////

	lineUpObjects();
}

void GameState_SelectNations::getInput(){

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

                        game->Player1 = new Player({game->mManager, game->mWorld, flagIterator1->factionID, true});
                        game->mPlayers.emplace_back(game->Player1);

                        game->Player2 = new Player({game->mManager, game->mWorld, flagIterator2->factionID, false});
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
                        menuIterator->text.setColor((sf::Color::White));

                        menuIterator = menuList.begin();
                        menuIterator += i;

                        menuIterator->text.setColor((sf::Color::Yellow));
                    }
                }

            break;
            }


		default: break;

		}

	}


}

void GameState_SelectNations::update(float mFT){

    GameState_MenuState::update(mFT);

	flagView1.setCenter(flagView1.getCenter().x, flagIterator1->sprite.getPosition().y);
	flagView2.setCenter(flagView2.getCenter().x, flagIterator2->sprite.getPosition().y);

	//if (!flagIterator->highlighted){
	//	flagIterator->highlighted = true;
	//}
}

void GameState_SelectNations::draw(){
	game->mWindow.clear(sf::Color(120,120,120));

	game->mWindow.setView(backgroundView);
	game->mWindow.draw(backgroundSprite);

	game->mWindow.setView(menuSelectView);
	game->mWindow.draw(titleText);

	for (auto& item : menuList){
		game->mWindow.draw(item.text);
	}


	game->mWindow.setView(flagView1);
	for (auto& flag : flagMenuItems1){
		flag.draw(game->mWindow);
		game->mWindow.draw(player1Text);
		game->mWindow.draw(player1NationText);
	}

	game->mWindow.setView(flagView2);
	for (auto& flag : flagMenuItems2){
		flag.draw(game->mWindow);
		game->mWindow.draw(player2Text);
		game->mWindow.draw(player2NationText);
	}
}
