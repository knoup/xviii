#include "xviii/Headers/stdafx.h"
#include "xviii/Core/GameState_Play.h"

#include "xviii/Core/Game.h"

std::string boolToString(bool _value){
	if (_value){
		return "YES";
	}
	else if (!_value){
		return "NO";
	}

	return "???";
}

GameState_Play::GameState_Play(Game* _game) :
GameState{_game},
selected{nullptr},
playUI(game->mManager, this)
{


	tileDistanceText.setFont(game->mManager.fontManager->getFont(FontManager::Type::Lucon));
	tileDistanceText.setString("");
	tileDistanceText.setCharacterSize(20);
}

void GameState_Play::oneTimeUpdate(){

	playUI.turnlyUpdate();

	for (auto& unit : game->inactivePlayer->getUnits()){
            unit->drawUnit = false;
            unit->drawFlag = false;
            unit->updateStats();
		}

		for (auto& unit : game->currentPlayer->getUnits()){
            unit->drawUnit = true;
            unit->drawFlag = true;
            game->mWorld.calculateViewDistance(unit.get());
            unit->updateStats();
		}
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

			case Key::UP_KEY:
				cameraVelocity = {0.f, -2.f};
				break;

			case Key::RIGHT_KEY:
				cameraVelocity = {2.f, 0.f};
				break;

			case Key::DOWN_KEY:
				cameraVelocity = {0.f, 2.f};
				break;

			case Key::LEFT_KEY:
				cameraVelocity = {-2.f, 0.f};
				break;

			case Key::RESETZOOM_KEY:
				game->currentView->setSize(xResolution, yResolution);
				break;

			case Key::ZOOMIN_KEY:
				game->currentView->setSize(game->currentView->getSize().x - xResolution / 10, game->currentView->getSize().y - yResolution / 10);
				break;

			case Key::ZOOMOUT_KEY:
				game->currentView->setSize(game->currentView->getSize().x + xResolution / 10, game->currentView->getSize().y + yResolution / 10);
				break;

			case Key::NORTH_KEY:
				if (selected != nullptr){
					playUI.setCurrentMessageText(selected->rotate(UnitTile::Direction::N));
					playUI.setSaveStatus(false);
				}
				break;

			case Key::EAST_KEY:
				if (selected != nullptr){
					playUI.setCurrentMessageText(selected->rotate(UnitTile::Direction::E));
					playUI.setSaveStatus(false);
				}
				break;

			case Key::SOUTH_KEY:
				if (selected != nullptr){
					playUI.setCurrentMessageText(selected->rotate(UnitTile::Direction::S));
					playUI.setSaveStatus(false);
				}
				break;

			case Key::WEST_KEY:
				if (selected != nullptr){
					playUI.setCurrentMessageText(selected->rotate(UnitTile::Direction::W));
					playUI.setSaveStatus(false);
				}
				break;

			case Key::TOGGLE_SAVE:
				if (game->saveCreator.create()){
					playUI.setSaveStatus(true);
				}
				break;

			case Key::NEXT_TURN:
				game->currentPlayer->setReady(true);
				break;

			case Key::HIDE_UI_KEY:
				if (drawUI){
					drawUI = false;
				}
				else if (!drawUI){
					drawUI = true;
				}
				break;

			case Key::LIMBER_KEY:
			{
				if (selected != nullptr){
					if (selected->hasLimberAbility()){
						playUI.setCurrentMessageText(selected->toggleLimber());
					}
				}
				break;
			}

			case Key::SQUARE_FORMATION_KEY:
			{
				if (selected != nullptr){
					if (selected->hasSquareFormationAbility()){
						playUI.setCurrentMessageText(selected->toggleSquareFormationActive());
					}
				}
				break;
			}

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

			else if (event.mouseButton.button == sf::Mouse::Left){
				sf::Vector2i mouseCoords{event.mouseButton.x, event.mouseButton.y};
				sf::Vector2i worldCoords{game->mWindow.mapPixelToCoords(mouseCoords, *game->currentView)};
				sf::Vector2f uiCoords{game->mWindow.mapPixelToCoords(game->mousePos, playUI.uiView)};

				if (uiCoords.x >= playUI.getButton().left() && uiCoords.x <= playUI.getButton().right()
					&&
					uiCoords.y >= playUI.getButton().top() && uiCoords.y <= playUI.getButton().bottom()
                    &&
                    drawUI){

					game->currentPlayer->setReady(true);

				}

				if (worldCoords.x >= game->mWorld.getDimensionsInPixels().x || worldCoords.y >= game->mWorld.getDimensionsInPixels().y ||
					worldCoords.x <= 0 || worldCoords.y <= 0){
					return;
				}

				auto unit = game->mWorld.unitAtPixelPos(worldCoords);
				auto terrain = game->mWorld.terrainAtPixelPos(worldCoords);
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

						if (terrain->getUnit() != nullptr){
                            occupied = true;
						}

						if (!occupied){
                            if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)){
                                playUI.setCurrentMessageText(selected->attack(terrain));
                            }
                            else{
                                playUI.setCurrentMessageText(selected->moveTo(terrain));
                            }

                            playUI.setSaveStatus(false);
						}

						//If the tile is occupied by an enemy unit, attack
						if (occupied && !friendly){
							playUI.setCurrentMessageText(selected->attack(terrain));
							playUI.setSaveStatus(false);

							selected->modVector.clear();
							unit->modVector.clear();

							game->mWorld.clearDamagedUnits();
						}
						else if (occupied && friendly){
							playUI.setCurrentMessageText(selected->heal(unit));
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

			else if (event.mouseButton.button == sf::Mouse::Right){

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

void GameState_Play::update(float mFT){
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

    //////////////////////////////////////////////////////////////////////////////
	//TURNLY UPDATES
	//////////////////////////////////////////////////////////////////////////////

	if (game->currentPlayer->isReady()){

		game->nextPlayer();

        game->mWorld.turnlyUpdate();
        playUI.turnlyUpdate();

		for (auto& unit : game->inactivePlayer->getUnits()){
            unit->drawUnit = false;
            unit->drawFlag = false;
            unit->reset();
		}

		for (auto& unit : game->currentPlayer->getUnits()){
            unit->drawUnit = true;
            unit->drawFlag = true;
            game->mWorld.calculateViewDistance(unit.get());
            unit->updateStats();
		}

	}

	//////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////

	//Code for the mouse indicator of distance:

	sf::Vector2i mouseLocation{game->mWindow.mapPixelToCoords(game->mousePos, *game->currentView)};
	sf::Vector2i worldDimensions{game->mWorld.getDimensionsInPixels()};

	if (selected != nullptr && (mouseLocation.x < worldDimensions.x && mouseLocation.y < worldDimensions.y
		&&
		mouseLocation.x > 0 && mouseLocation.y > 0)){

		TerrainTile* terrain = game->mWorld.terrainAtPixelPos(mouseLocation);
		UnitTile* unit = terrain->getUnit();

		UnitTile::Direction dir = selected->getDir();

		bool validMovDirection{false};
		bool validAttackDirection{false};
		bool rangedObstructionPresent{false};
		bool meleeObstructionPresent{false};
		bool inMovementRange{false};
		bool inRangedAttackRange{false};

		//Store the distance between the selected tile and currently moused over tile in vectorDist
		sf::Vector2i vectorDist = selected->distanceFrom(terrain, validMovDirection, validAttackDirection, rangedObstructionPresent, meleeObstructionPresent, inMovementRange, inRangedAttackRange);


		int primaryAxisDistance{0};
		if (dir == UnitTile::Direction::N || dir == UnitTile::Direction::S){
			primaryAxisDistance = abs(vectorDist.y);
		}
		else{
			primaryAxisDistance = abs(vectorDist.x);
		}

		//For the direction string:
		std::string dir_string_X;
		std::string dir_string_Y;

		//N or S
		if (vectorDist.y < 0){
			dir_string_Y = "N";
		}
		else if (vectorDist.y > 0){
			dir_string_Y = "S";
		}

		//E or W
		if (vectorDist.x > 0){
			dir_string_X += "E";
		}
		else if (vectorDist.x < 0){
			dir_string_X += "W";
		}

		//If you aren't mousing over a (visible) enemy unit
		if ((unit == nullptr && terrain != nullptr) || (unit != nullptr && !unit->drawUnit || !unit->drawFlag)){

			if (inMovementRange && !rangedObstructionPresent && !meleeObstructionPresent){
				tileDistanceText.setColor(sf::Color::Black);
			}
			else if (!inMovementRange && inRangedAttackRange){
				tileDistanceText.setColor(sf::Color::Magenta);
			}

			//Commenting disabling red cursor on obstruction for now; this allows "cheating" by being able to see
			//if there are units in the way, despite them being invisible. However, in the block of code below this
			//(unit != nullptr), in 99% of the cases, the cursor will remain red when behind visible enemy units,
			//so for the most part, things work as intended. The side effect of this is that when able to attack a
			//unit, the cursor will remain blue even behind it.

			//else if (rangedObstructionPresent || meleeObstructionPresent|| !validMovDirection || !inMovementRange){
			else if (!validMovDirection || !inMovementRange){
				tileDistanceText.setColor(sf::Color::Red);
			}

		}
		//If you are mousing over a visible unit
		else if (unit != nullptr){

			//Check if it is an enemy unit
			bool friendly = (unit->getPlayer() == game->currentPlayer);

			if (((!validAttackDirection && (!selected->canHeal())) || meleeObstructionPresent || rangedObstructionPresent || (primaryAxisDistance > 1 && !inRangedAttackRange) || selected->getHasMeleeAttacked() || selected->getHasMeleeAttacked())){
					tileDistanceText.setColor(sf::Color::Red);
				}
				else{
					if (friendly && !selected->canHeal()){
						tileDistanceText.setColor(sf::Color::Magenta);
					}
					else{
						tileDistanceText.setColor(sf::Color::Blue);
					}
				}

		}

		std::string finalString;

		bool yDistanceOverZero{abs(vectorDist.y) > 0};
		bool xDistanceOverZero{abs(vectorDist.x) > 0};

		if (yDistanceOverZero){
			finalString += std::to_string(abs(vectorDist.y)) + dir_string_Y;
		}
		if (xDistanceOverZero){
			if (yDistanceOverZero){
				finalString += ",";
			}
			finalString += std::to_string(abs(vectorDist.x)) + dir_string_X;
		}

		tileDistanceText.setString(finalString);

		mouseLocation.x -= 18;
		mouseLocation.y += 18;

		tileDistanceText.setPosition({mouseLocation.x, mouseLocation.y});

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
