#include "stdafx.h"
#include "GameState_Setup.h"


GameState_Setup::GameState_Setup(Game* _game) :
GameState{_game},
setupUI(this, game->mTextureManager, game->mFontManager),
selectedSpawnableUnit{nullptr}
{
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

					std::vector<Player::SpawnableUnit> current{game->currentPlayer->getSpawnableUnits()};

					for (int i{0}; i < current.size(); ++i){
						if (uiCoords.x > current[i].left() && uiCoords.x < current[i].right()
							&&
							uiCoords.y > current[i].top() && uiCoords.y < current[i].bottom()){

							selectedSpawnableUnit = std::move(std::unique_ptr<Player::SpawnableUnit>(new Player::SpawnableUnit(current[i])));
							break;

						}
					}


					if (uiCoords.x >= setupUI.getButton().left() && uiCoords.x <= setupUI.getButton().right()
						&&
						uiCoords.y >= setupUI.getButton().top() && uiCoords.y <= setupUI.getButton().bottom()){
						
						//As long as the player has at least one non-general unit
						if (game->currentPlayer->getDeploymentPoints() <= 29){
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

						game->currentPlayer->spawnUnit(selectedSpawnableUnit->type, worldCoords);

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

					game->currentPlayer->removeUnit(worldCoords);

					break;
				}

			}

			break;

		case sf::Event::Closed:
			game->mWindow.close();
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

		case sf::Event::MouseButtonReleased:
			if (event.mouseButton.button == sf::Mouse::Middle){
				middleButtonHeld = false;
			}

			break;

		default: break;
		}

	}

}

void GameState_Setup::update(FrameTime mFT){
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
			game->setGameStatePlay();
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

