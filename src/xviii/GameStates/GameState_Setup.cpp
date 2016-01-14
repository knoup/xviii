#include "xviii/Headers/stdafx.h"
#include "xviii/GameStates/GameState_Setup.h"

#include "xviii/Core/Game.h"

GameState_Setup::GameState_Setup(Game* _game) :
GameState{_game},
setupUI(game->mManager, this),
selectedSpawnableUnit{nullptr}
{
}

void GameState_Setup::oneTimeUpdate(){

    int points1{0};
    for(auto& unit : game->Player1->getUnits()){
        points1 += unit.get()->getCost();
    }
    game->Player1->setDeploymentPoints(game->Player1->getMaxDeploymentPoints() - points1);



    int points2{0};
    for(auto& unit : game->Player2->getUnits()){
        points2 += unit.get()->getCost();
    }
    game->Player2->setDeploymentPoints(game->Player2->getMaxDeploymentPoints() - points2);

}

void GameState_Setup::getInput(){
	sf::Event event;

	while (game->mWindow.pollEvent(event)){

		switch (event.type){

		case sf::Event::MouseMoved:
			game->mousePos.x = event.mouseMove.x;
			game->mousePos.y = event.mouseMove.y;
			break;

		case sf::Event::Resized:
			game->Player1->view.setSize(event.size.width, event.size.height);
			game->Player2->view.setSize(event.size.width, event.size.height);

			break;

		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Middle){
				middleButtonHeld = true;
				middleButtonCoords = {event.mouseButton.x, event.mouseButton.y};
			}

			else if (event.mouseButton.button == sf::Mouse::Left && drawUI){

				//If no menu item was selectedSpawnableUnit, select it

				if (selectedSpawnableUnit == nullptr){
					sf::Vector2f worldCoords{game->mWindow.mapPixelToCoords(game->mousePos, *game->currentView)};
					sf::Vector2f uiCoords{game->mWindow.mapPixelToCoords(game->mousePos, setupUI.uiView)};

					std::vector<SpawnableUnit> current{game->currentPlayer->getSpawnableUnits()};

					for (size_t i{0}; i < current.size(); ++i){
						if (uiCoords.x > current[i].left() && uiCoords.x < current[i].right()
							&&
							uiCoords.y > current[i].top() && uiCoords.y < current[i].bottom()){

							selectedSpawnableUnit = std::move(std::unique_ptr<SpawnableUnit>(new SpawnableUnit(current[i])));
							break;

						}
					}


					if (uiCoords.x >= setupUI.getButton().left() && uiCoords.x <= setupUI.getButton().right()
						&&
						uiCoords.y >= setupUI.getButton().top() && uiCoords.y <= setupUI.getButton().bottom()){

						//As long as the player has at least one non-general unit
						if (game->currentPlayer->getDeploymentPoints() <= game->currentPlayer->getMaxDeploymentPoints() - 1){
							game->currentPlayer->setReady(true);
						}

					}
				}

				//Spawn a unit on the tile:

				else{
					sf::Vector2i mouseCoords{event.mouseButton.x, event.mouseButton.y};
					sf::Vector2i worldCoords{game->mWindow.mapPixelToCoords(mouseCoords, *game->currentView)};

					if ((worldCoords.x <= game->mWorld.getDimensionsInPixels().x &&
						worldCoords.x >= 0) &&
						(worldCoords.y <= game->mWorld.getDimensionsInPixels().y &&
						worldCoords.y >= 0)){

						game->currentPlayer->spawnUnit(selectedSpawnableUnit->unitID, worldCoords);

					}

					selectedSpawnableUnit = nullptr;
					break;
				}
			}


			else if (event.mouseButton.button == sf::Mouse::Right && drawUI){

				//Deselect the currently selectedSpawnableUnit icon:

				if (selectedSpawnableUnit != nullptr){
					selectedSpawnableUnit = nullptr;
					break;
				}

				//Delete a unit from a tile:

				else{
					sf::Vector2i mouseCoords{event.mouseButton.x, event.mouseButton.y};
					sf::Vector2i worldCoords{game->mWindow.mapPixelToCoords(mouseCoords, *game->currentView)};

					auto removed = game->currentPlayer->removeUnit(worldCoords);

					if(removed != nullptr){
                        game->currentPlayer->setDeploymentPoints(game->currentPlayer->getDeploymentPoints() + removed.get()->getCost());
					}

					break;
				}

			}

			break;

		case sf::Event::Closed:
			game->mWindow.close();
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

            case Key::TOGGLE_SAVE:
				game->saveCreator.create();
				break;

			case Key::HIDE_UI_KEY:
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

		case sf::Event::MouseButtonReleased:
			if (event.mouseButton.button == sf::Mouse::Middle){
				middleButtonHeld = false;
			}

			break;

		default: break;
		}

	}

}

void GameState_Setup::update(float mFT){
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
		sf::Vector2f resultantVector = (sf::Vector2f{middleButtonCoords} -sf::Vector2f{game->mousePos});
		resultantVector.x *= 0.0055;
		resultantVector.y *= 0.0055;
		game->currentView->move(resultantVector * mFT);
	}

	setupUI.update();

	if (game->currentPlayer->isReady()){
		if (game->currentPlayer == game->Player1){
			game->nextPlayer();
		}
		else if (game->currentPlayer == game->Player2){
			game->nextPlayer();
			game->setGameState(game->PlayState.get());
		}
	}


	sf::Vector2f worldCoords{game->mWindow.mapPixelToCoords(game->mousePos, *game->currentView)};

    if(selectedSpawnableUnit != nullptr){
            selectedSpawnableUnit->unitSprite.setPosition(worldCoords);
	}
}

void GameState_Setup::draw(){
	game->mWindow.setView(*game->currentView);
	game->mWorld.draw(game->mWindow);


    //We won't be drawing the enemy player's units. It's only fair that both players be able to
    //get an overview of the map before spawning their units, without seeing each other's positions.

    game->currentPlayer->drawUnits(game->mWindow);

	//
	if (drawUI){
		game->mWindow.setView(setupUI.uiView);
		setupUI.draw(game->mWindow);
	}
	//

	game->mWindow.setView(*game->currentView);
	if (selectedSpawnableUnit != nullptr){
		game->mWindow.draw(selectedSpawnableUnit->unitSprite);
	}
}

