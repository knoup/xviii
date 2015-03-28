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
selected{nullptr}
{
	nextTurnButton.sprite = game->mTextureManager.getSprite(TextureManager::UI::BUTTON);
	nextTurnButton.sprite.setOrigin(nextTurnButton.sprite.getLocalBounds().width / 2, nextTurnButton.sprite.getLocalBounds().height / 2);
	nextTurnButton.sprite.setPosition(1235, -80);
	nextTurnButton.text.setFont(game->mFontManager.getFont(FontManager::Type::Lucon));
	nextTurnButton.text.setOrigin(nextTurnButton.text.getLocalBounds().width / 2, nextTurnButton.text.getGlobalBounds().height / 2);
	nextTurnButton.text.setPosition(nextTurnButton.sprite.getPosition().x, nextTurnButton.sprite.getPosition().y - 10);
	nextTurnButton.rekt.setSize({nextTurnButton.sprite.getLocalBounds().width, nextTurnButton.sprite.getLocalBounds().height});
	nextTurnButton.rekt.setOrigin(nextTurnButton.rekt.getLocalBounds().width / 2, nextTurnButton.rekt.getLocalBounds().height / 2);
	nextTurnButton.rekt.setPosition(nextTurnButton.sprite.getPosition().x + nextTurnButton.rekt.getOutlineThickness()
		, nextTurnButton.sprite.getPosition().y + nextTurnButton.rekt.getOutlineThickness());

	nextTurnButton.text.setColor(sf::Color::White);

	currentPlayerText.setFont(game->mFontManager.getFont(FontManager::Type::Lucon));
	currentPlayerText.setColor(sf::Color::Yellow);
	currentPlayerText.setPosition(970, -170);

	elapsedTurnsText.setFont(game->mFontManager.getFont(FontManager::Type::Lucon));
	elapsedTurnsText.setColor(sf::Color::Yellow);
	elapsedTurnsText.setPosition(20, -170);

	tileDistanceText.setFont(game->mFontManager.getFont(FontManager::Type::Lucon));
	tileDistanceText.setString("");
	tileDistanceText.setCharacterSize(20);

	messageLogText.setFont(game->mFontManager.getFont(FontManager::Type::Lucon));
	messageLogText.setColor(sf::Color::White);
	messageLogText.setCharacterSize(15);
	messageLogText.setPosition(580, -170);
	messageLogText.setString("Messages");

	currentMessageText.setFont(game->mFontManager.getFont(FontManager::Type::Lucon));
	currentMessageText.setColor(sf::Color::Cyan);
	currentMessageText.setCharacterSize(22);
	currentMessageText.setPosition(310, -150);


	elapsedTurnsText.setString("Turn " + std::to_string(game->elapsedTurns));

	saveText.setFont(game->mFontManager.getFont(FontManager::Type::Arial));
	saveText.setCharacterSize(20);
	saveText.setPosition(20, -80);
	saveTextString(false);
}

void GameState_Play::oneTimeUpdate(){
	currentPlayerText.setString(game->currentPlayer->getName());
	currentPlayerText.setColor(game->currentPlayer->getColour());
	elapsedTurnsText.setString("Turn " + std::to_string(game->elapsedTurns));
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
				game->currentView->move(0, -50);
				break;

			case RIGHT_KEY:
				game->currentView->move(50, 0);
				break;

			case DOWN_KEY:
				game->currentView->move(0, 50);
				break;

			case LEFT_KEY:
				game->currentView->move(-50, 0);
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
					currentMessage = selected->rotate(UnitTile::Direction::N);
					saveTextString(false);
				}
				break;

			case EAST_KEY:
				if (selected != nullptr){
					currentMessage = selected->rotate(UnitTile::Direction::E);
					saveTextString(false);
				}
				break;

			case SOUTH_KEY:
				if (selected != nullptr){
					currentMessage = selected->rotate(UnitTile::Direction::S);
					saveTextString(false);
				}
				break;

			case WEST_KEY:
				if (selected != nullptr){
					currentMessage = selected->rotate(UnitTile::Direction::W);
					saveTextString(false);
				}
				break;

			case TOGGLE_SAVE:
				if (game->saveCreator.create()){
					saveTextString(true);
				}
				break;

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
			if (event.mouseButton.button == sf::Mouse::Left){
				sf::Vector2i mouseCoords{event.mouseButton.x, event.mouseButton.y};
				sf::Vector2i worldCoords{game->mWindow.mapPixelToCoords(mouseCoords, *game->currentView)};
				sf::Vector2f uiCoords{game->mWindow.mapPixelToCoords(game->mousePos, game->uiView)};

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

						for (auto& unitInLayer : game->mWorld.getCombatLayer()){
							if (unitInLayer->getTilePos() == terrain){
								occupied = true;
							}
						}

						//If vacant, move to the tile
						if (!occupied){
							currentMessage = selected->moveTo(terrain);
							saveTextString(false);
						}

						//If the tile is occupied by an enemy unit, attack
						if (occupied && !friendly){
							currentMessage = selected->attack(unit);
							saveTextString(false);

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
							currentMessage = selected->interactWithFriendly(unit);
							saveTextString(false);
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

					if (uiCoords.x >= nextTurnButton.left() && uiCoords.x <= nextTurnButton.right()
						&&
						uiCoords.y >= nextTurnButton.top() && uiCoords.y <= nextTurnButton.bottom()){

						game->currentPlayer->setReady(true);

					}
				}
			}
			else if (event.mouseButton.button == sf::Mouse::Right){
				
				if (selected != nullptr){
					selected->setHighlighted(false);
					selected = nullptr;
				}
				
				currentMessage.clear();
			}

			break;
		}
	}
}

void GameState_Play::saveTextString(bool _value){
	if (_value){
		saveText.setString("Saved!");
	}
	else{
		saveText.setString("Not saved");
	}
}

void GameState_Play::update(){

	currentMessageText.setString(currentMessage);

	if (game->currentPlayer->isReady()){
		//Blank the current message
		currentMessage.clear();

		for (auto& unit : game->mWorld.getCombatLayer()){
			unit->reset();
		}

		game->nextPlayer();
		game->elapsedTurns += 1;

		saveTextString(false);
		currentPlayerText.setString(game->currentPlayer->getName());
		currentPlayerText.setColor(game->currentPlayer->getColour());
		elapsedTurnsText.setString("Turn " + std::to_string(game->elapsedTurns));
	}

	//For the highlighting of the next turn button:
	sf::Vector2f uiCoords{game->mWindow.mapPixelToCoords(game->mousePos, game->uiView)};

	if (uiCoords.x >= nextTurnButton.left() && uiCoords.x <= nextTurnButton.right()
		&&
		uiCoords.y >= nextTurnButton.top() && uiCoords.y <= nextTurnButton.bottom()){

		nextTurnButton.highlighted = true;
	}
	else{
		nextTurnButton.highlighted = false;
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

				if (!validAttackDirection || obstructionPresent || (dist > 1 && !inRangedAttackRange) || selected->getHasAttacked()){
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

		tileDistanceText.setString(std::to_string(dist) + (selected->dirToString(selected->getDir())));
		tileDistanceText.setPosition({game->mWindow.mapPixelToCoords({game->mousePos.x - 18, game->mousePos.y + 18}, *game->currentView)});
		
	}
}

void GameState_Play::draw(){
	game->mWindow.setView(*game->currentView);
	game->mWorld.draw(game->mWindow);

	if (selected != nullptr){
		game->mWindow.draw(tileDistanceText);
	}

	game->mWindow.setView(game->uiView);
	game->mWindow.draw(game->uiSprite);
	game->mWindow.draw(currentPlayerText);
	game->mWindow.draw(elapsedTurnsText);
	game->mWindow.draw(saveText);

	if (!currentMessage.empty()){
		game->mWindow.draw(currentMessageText);
	}

	game->mWindow.draw(messageLogText);
	nextTurnButton.draw(game->mWindow);
}