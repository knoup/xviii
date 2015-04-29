#include "stdafx.h"
#include "GameState_Setup.h"


GameState_Setup::GameState_Setup(Game* _game) :
GameState{_game},
selectedSpawnableUnit{nullptr}
{
	numbRemaining.setFont(game->mFontManager.getFont(FontManager::Type::Lucon));
	numbRemaining.setCharacterSize(70);
	numbRemaining.setColor(sf::Color::Green);
	numbRemaining.setPosition(145,-170);

	currentPlayerText.setFont(game->mFontManager.getFont(FontManager::Type::Lucon));
	currentPlayerText.setColor(sf::Color::Yellow);
	currentPlayerText.setPosition(970, -170);

	deploymentPointsRemaining.setFont(game->mFontManager.getFont(FontManager::Type::Lucon));
	deploymentPointsRemaining.setCharacterSize(19);
	deploymentPointsRemaining.setColor(sf::Color::White);
	deploymentPointsRemaining.setPosition(60, -80);

	deploymentPointsRemaining.setString("deployment points remain");

	readyButton.sprite = game->mTextureManager.getSprite(TextureManager::UI::BUTTON);
	readyButton.sprite.setOrigin(readyButton.sprite.getLocalBounds().width / 2, readyButton.sprite.getLocalBounds().height / 2);
	readyButton.sprite.setPosition(1235, -80);
	readyButton.text.setFont(game->mFontManager.getFont(FontManager::Type::Lucon));
	readyButton.text.setOrigin(readyButton.text.getLocalBounds().width / 2, readyButton.text.getGlobalBounds().height / 2);
	readyButton.text.setPosition(readyButton.sprite.getPosition().x, readyButton.sprite.getPosition().y - 10);
	readyButton.rekt.setSize({readyButton.sprite.getLocalBounds().width, readyButton.sprite.getLocalBounds().height});
	readyButton.rekt.setOrigin(readyButton.rekt.getLocalBounds().width / 2, readyButton.rekt.getLocalBounds().height / 2);
	readyButton.rekt.setPosition(readyButton.sprite.getPosition().x + readyButton.rekt.getOutlineThickness()
		, readyButton.sprite.getPosition().y + readyButton.rekt.getOutlineThickness());

	readyButton.text.setColor(sf::Color::White);
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
			if (event.mouseButton.button == sf::Mouse::Left){

				//If no menu item was selectedSpawnableUnit, select it

				if (selectedSpawnableUnit == nullptr){
					sf::Vector2f worldCoords{game->mWindow.mapPixelToCoords(game->mousePos, *game->currentView)};
					sf::Vector2f uiCoords{game->mWindow.mapPixelToCoords(game->mousePos, game->uiView)};

					std::vector<Player::SpawnableUnit> current{game->currentPlayer->getSpawnableUnits()};

					for (int i{0}; i < current.size(); ++i){
						if (uiCoords.x > current[i].left() && uiCoords.x < current[i].right()
							&&
							uiCoords.y > current[i].top() && uiCoords.y < current[i].bottom()){

							selectedSpawnableUnit = std::move(std::unique_ptr<Player::SpawnableUnit>(new Player::SpawnableUnit(current[i])));
							break;

						}
					}


					if (uiCoords.x >= readyButton.left() && uiCoords.x <= readyButton.right()
						&&
						uiCoords.y >= readyButton.top() && uiCoords.y <= readyButton.bottom()){
						
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


			else if (event.mouseButton.button == sf::Mouse::Right){

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

			default:
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

	currentPlayerText.setString(game->currentPlayer->getName());
	currentPlayerText.setColor(game->currentPlayer->getColour());

	numbRemaining.setString(std::to_string(game->currentPlayer->getDeploymentPoints()));

	if (game->currentPlayer->isReady()){
		if (game->currentPlayer == game->Player1){
			game->nextPlayer();
		}
		else if (game->currentPlayer == game->Player2){
			game->nextPlayer();
			game->setGameStatePlay();
		}

		currentPlayerText.setString(game->currentPlayer->getName());

	}

	//Changes the color of the number depending on how many points you have
	if (game->currentPlayer->getDeploymentPoints() > 20){
		numbRemaining.setColor(sf::Color::Green);
	}
	else if (game->currentPlayer->getDeploymentPoints() > 10){
		numbRemaining.setColor(sf::Color::Yellow);
	}
	else{
		numbRemaining.setColor(sf::Color::Red);
	}

	sf::Vector2f worldCoords{game->mWindow.mapPixelToCoords(game->mousePos, *game->currentView)};

    if(selectedSpawnableUnit != nullptr){
            selectedSpawnableUnit->unitSprite.setPosition(worldCoords);
	}

	//For the highlighting of the ready button:
	sf::Vector2f uiCoords{game->mWindow.mapPixelToCoords(game->mousePos, game->uiView)};

	if (uiCoords.x >= readyButton.left() && uiCoords.x <= readyButton.right()
		&&
		uiCoords.y >= readyButton.top() && uiCoords.y <= readyButton.bottom()){

		readyButton.highlighted = true;
	}
	else{
		readyButton.highlighted = false;
	}
}

void GameState_Setup::draw(){
	game->mWindow.setView(*game->currentView);
	game->mWorld.draw(game->mWindow);

	//
	game->mWindow.setView(game->uiView);

	game->mWindow.draw(game->uiSprite);
	game->mWindow.draw(numbRemaining);
	game->mWindow.draw(currentPlayerText);
	game->mWindow.draw(deploymentPointsRemaining);

	readyButton.draw(game->mWindow);

	for (auto& item : game->currentPlayer->getSpawnableUnits()){
		game->mWindow.draw(item.unitSprite);
		game->mWindow.draw(item.unitName);
	}

	game->mWindow.setView(*game->currentView);
	if (selectedSpawnableUnit != nullptr){
		game->mWindow.draw(selectedSpawnableUnit->unitSprite);
	}

}

