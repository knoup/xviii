#include "stdafx.h"
#include "GameState_Play.h"

std::string boolToString(bool _value){
	if (_value){
		return "YES";
	}
	else if (!_value){
		return "NO";
	}
}

GameState_Play::GameState_Play(Game* _game) : 
GameState{_game},
playUI(this, game->mTextureManager, game->mFontManager),
selected{nullptr}
{
	

	tileDistanceText.setFont(game->mFontManager.getFont(FontManager::Type::Lucon));
	tileDistanceText.setString("");
	tileDistanceText.setCharacterSize(20);


	//elapsedTurnsText.setString("Turn " + std::to_string(game->elapsedTurns));

}

void GameState_Play::oneTimeUpdate(){
	playUI.setCurrentPlayerText(game->currentPlayer->getName());
	playUI.setElapsedTurnsText(game->elapsedTurns);
}

void GameState_Play::getInput(){
	sf::Event event;

	while (game->mWindow.pollEvent(event)){
		switch (event.type){

		case sf::Event::Resized:
			game->Player1->view.setSize(event.size.width, event.size.height);
			game->Player2->view.setSize(event.size.width, event.size.height);

			break;

		case sf::Event::Closed:
			game->mWindow.close();
			break;

		case sf::Event::MouseMoved:
			game->mousePos.x = event.mouseMove.x;
			game->mousePos.y = event.mouseMove.y;
			break;

		case sf::Event::KeyPressed:

			switch (event.key.code){

			case UP_KEY:
				cameraVelocity = {0.f, -2.f};
				break;

			case RIGHT_KEY:
				cameraVelocity = {2.f, 0.f};
				break;

			case DOWN_KEY:
				cameraVelocity = {0.f, 2.f};
				break;

			case LEFT_KEY:
				cameraVelocity = {-2.f, 0.f};
				break;

			case RESETZOOM_KEY:
				game->currentView->setSize(xResolution, yResolution);
				break;

			case ZOOMIN_KEY:
				game->currentView->setSize(game->currentView->getSize().x - xResolution / 10, game->currentView->getSize().y - yResolution / 10);
				break;

			case ZOOMOUT_KEY:
				game->currentView->setSize(game->currentView->getSize().x + xResolution / 10, game->currentView->getSize().y + yResolution / 10);
				break;

			case NORTH_KEY:
				if (selected != nullptr){
					playUI.setCurrentMessageText(selected->rotate(UnitTile::Direction::N));
					playUI.setSaveStatus(false);
				}
				break;

			case EAST_KEY:
				if (selected != nullptr){
					playUI.setCurrentMessageText(selected->rotate(UnitTile::Direction::E));
					playUI.setSaveStatus(false);
				}
				break;

			case SOUTH_KEY:
				if (selected != nullptr){
					playUI.setCurrentMessageText(selected->rotate(UnitTile::Direction::S));
					playUI.setSaveStatus(false);
				}
				break;

			case WEST_KEY:
				if (selected != nullptr){
					playUI.setCurrentMessageText(selected->rotate(UnitTile::Direction::W));
					playUI.setSaveStatus(false);
				}
				break;

			case TOGGLE_SAVE:
				if (game->saveCreator.create()){
					playUI.setSaveStatus(true);
				}
				break;

			case HIDE_UI_KEY:
				if (drawUI){
					drawUI = false;
				}
				else if (!drawUI){
					drawUI = true;
				}
				break;

			default: break;

			}

			break;

		case sf::Event::MouseWheelMoved:
			if (event.mouseWheel.delta > 0){
				game->currentView->setSize(game->currentView->getSize().x - xResolution / 12, game->currentView->getSize().y - yResolution / 12);
			}
			else if (event.mouseWheel.delta < 0){
				game->currentView->setSize(game->currentView->getSize().x + xResolution / 12, game->currentView->getSize().y + yResolution / 12);
			}

			break;

		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Middle){
				middleButtonHeld = true;
				middleButtonCoords = {event.mouseButton.x, event.mouseButton.y};
			}

			else if (event.mouseButton.button == sf::Mouse::Left && drawUI){
				sf::Vector2i mouseCoords{event.mouseButton.x, event.mouseButton.y};
				sf::Vector2i worldCoords{game->mWindow.mapPixelToCoords(mouseCoords, *game->currentView)};
				sf::Vector2f uiCoords{game->mWindow.mapPixelToCoords(game->mousePos, playUI.uiView)};

				if (uiCoords.x >= playUI.getButton().left() && uiCoords.x <= playUI.getButton().right()
					&&
					uiCoords.y >= playUI.getButton().top() && uiCoords.y <= playUI.getButton().bottom()){

					game->currentPlayer->setReady(true);

				}

				if (worldCoords.x >= game->mWorld.getDimensionsInPixels().x || worldCoords.y >= game->mWorld.getDimensionsInPixels().y ||
					worldCoords.x <= 0 || worldCoords.y <= 0){
					return;
				}

				auto unit = game->mWorld.unitAtMouseCoords(worldCoords);
				auto terrain = game->mWorld.terrainAtMouseCoords(worldCoords);
				bool friendly{true};

				//Cache the unit's allignment
				if (unit != nullptr){
					if (unit->getPlayer() != game->currentPlayer){
						friendly = false;
					}	
				}

				//If you previously had a selected unit, unhighlight it
				if (selected != nullptr){
					selected->setHighlighted(false);

					//If a unit is selected and you click on a terrain tile,
					//move the unit there if it is unnocupied
					if (terrain != nullptr){
						bool occupied{false};

						for (auto& player : game->mPlayers){
							for (auto& unit : player->getUnits()){
								if (unit->getTerrain() == terrain){
									occupied = true;
								}
							}
						}

						//If vacant, move to the tile
						if (!occupied){
							playUI.setCurrentMessageText(selected->moveTo(terrain));
							playUI.setSaveStatus(false);
						}

						//If the tile is occupied by an enemy unit, attack
						if (occupied && !friendly){
							playUI.setCurrentMessageText(selected->attack(unit));
							playUI.setSaveStatus(false);

							selected->modVector.clear();
							unit->modVector.clear();

							//Remove the unit if it's dead; if it isn't, update stats
							for (auto& unit : game->mWorld.getDamagedUnits()){
								if (!unit->removeIfDead()){
									unit->updateStats();
								}
							}

							game->mWorld.clearDamagedUnits();

						}
						else if (occupied && friendly){
							playUI.setCurrentMessageText(selected->interactWithFriendly(unit));
							playUI.setSaveStatus(false);
							//specially for the general's heal ability
						}
					}
					
					//Finally, unselect the tile
					selected = nullptr;
				}

				else if (selected == nullptr){
					//If you click a unit
					if (unit != nullptr && friendly){
						selected = unit;
						selected->setHighlighted(true);
					}

				}
			}

			else if (event.mouseButton.button == sf::Mouse::Right && drawUI){
				
				if (selected != nullptr){
					selected->setHighlighted(false);
					selected = nullptr;
				}
				
				playUI.clearCurrentMessageText();
			}

			break;

			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Middle){
					middleButtonHeld = false;
				}

				break;

			default: break;
		}
	}
}

void GameState_Play::update(FrameTime mFT){
	if (cameraVelocity.x >= -0.1 && cameraVelocity.x <= 0.1 && cameraVelocity.x != 0){
		cameraVelocity = {0, 0};
	}
	else if (cameraVelocity.x > 0){
		cameraVelocity.x -= 0.01f;
	}
	else if (cameraVelocity.x < 0){
		cameraVelocity.x += 0.01f;
	}

	if (cameraVelocity.y >= -0.5 && cameraVelocity.y <= 0.5 && cameraVelocity.y != 0){
		cameraVelocity = {0, 0};
	}
	else if (cameraVelocity.y > 0){
		cameraVelocity.y -= 0.01f;
	}
	else if (cameraVelocity.y < 0){
		cameraVelocity.y += 0.01f;
	}

	game->currentView->move(cameraVelocity * mFT);

	if (middleButtonHeld){
		sf::Vector2f resultantVector = (sf::Vector2f{middleButtonCoords} - sf::Vector2f{game->mousePos});
		resultantVector.x *= 0.0055;
		resultantVector.y *= 0.0055;
		game->currentView->move(resultantVector * mFT);
	}

	playUI.update();

	if (game->currentPlayer->isReady()){
		for (auto& unit : game->currentPlayer->getUnits()){
				unit->reset();
		}

		game->nextPlayer();
		game->elapsedTurns += 1;
	}

	//Code for the mouse indicator of distance:

	sf::Vector2i mouseLocation{game->mWindow.mapPixelToCoords(game->mousePos, *game->currentView)};

	if (selected != nullptr && (mouseLocation.x < game->mWorld.getDimensionsInPixels().x && mouseLocation.y < game->mWorld.getDimensionsInPixels().y
		&&
		mouseLocation.x > 0 && mouseLocation.y > 0)){
		//Just a little type conversion because of some quirks
		sf::Vector2f fworldCoords = game->mWindow.mapPixelToCoords(game->mousePos, *game->currentView);
		sf::Vector2i iworldCoords{int(fworldCoords.x), int(fworldCoords.y)};\

		auto terrain = game->mWorld.terrainAtMouseCoords(iworldCoords);
		auto unit = game->mWorld.unitAtMouseCoords(iworldCoords);

		bool validMovDirection{false};
		bool validAttackDirection{false};
		bool obstructionPresent{false};
		bool inMovementRange{false};
		bool inRangedAttackRange{false};

		int dist = selected->distanceFrom(terrain, validMovDirection, validAttackDirection, obstructionPresent, inMovementRange, inRangedAttackRange);

		//If you aren't mousing over an enemy unit
		if (unit == nullptr && terrain != nullptr){

			if (inMovementRange && !obstructionPresent){
				tileDistanceText.setColor(sf::Color::Black);
			}
			else if (!inMovementRange && inRangedAttackRange){
				tileDistanceText.setColor(sf::Color::Magenta);
			}
			else if (obstructionPresent || !validMovDirection || !inMovementRange){
				tileDistanceText.setColor(sf::Color::Red);
			}

		}
		//If you are mousing over a unit
		else if (unit != nullptr){

			//Check if it is an enemy unit
			bool friendly = (unit->getPlayer() == game->currentPlayer);

				if (!validAttackDirection || obstructionPresent || (dist > 1 && !inRangedAttackRange) || selected->getHasMeleeAttacked() || selected->getHasMeleeAttacked()){
					tileDistanceText.setColor(sf::Color::Red); 
				}
				else{
					if (friendly){
						tileDistanceText.setColor(sf::Color::Magenta);
					}
					else{
						tileDistanceText.setColor(sf::Color::Blue);
					}
				}

		}

		tileDistanceText.setString(std::to_string(dist) + (selected->dirToString()));
		tileDistanceText.setPosition({game->mWindow.mapPixelToCoords({game->mousePos.x - 18, game->mousePos.y + 18}, *game->currentView)});
		
	}
}

void GameState_Play::draw(){
	game->mWindow.setView(*game->currentView);
	game->mWorld.draw(game->mWindow);

	for (auto& player : game->mPlayers){
		player->drawUnits(game->mWindow);
	}

	if (selected != nullptr){
		game->mWindow.draw(tileDistanceText);
	}

	//
	if (drawUI){
		game->mWindow.setView(playUI.uiView);
		playUI.draw(game->mWindow);
	}
	//
}