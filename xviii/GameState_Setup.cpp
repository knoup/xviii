#include "stdafx.h"
#include "GameState_Setup.h"


GameState_Setup::GameState_Setup(Game* _game) :
GameState{_game},
selected{nullptr}

{
	numbRemaining.setFont(game->mFontManager.getFont(FontManager::Type::Lucon));
	numbRemaining.setCharacterSize(70);
	numbRemaining.setColor(sf::Color::Green);
	numbRemaining.setPosition(100,-140);

	numbRemaining.setString(std::to_string(game->currentPlayer->getDeploymentPoints()));

	currentPlayerText.setFont(game->mFontManager.getFont(FontManager::Type::Lucon));
	currentPlayerText.setColor(sf::Color::Yellow);
	currentPlayerText.setPosition(1160, -170);

	Menu INF(UnitTile::UnitType::INF);
	INF.unitName.setFont(game->mFontManager.getFont(FontManager::Type::Lucon));
	INF.unitName.setColor(sf::Color::White);
	INF.unitName.setString("INFANTRY");
	INF.unitName.setCharacterSize(12);
	INF.unitName.setOrigin(INF.unitName.getLocalBounds().width / 2, INF.unitName.getLocalBounds().height / 2);

	INF.unitSprite = game->mTextureManager.getSprite(TextureManager::Unit::INF);
	INF.unitSprite.setOrigin(INF.unitSprite.getGlobalBounds().width / 2, INF.unitSprite.getGlobalBounds().height / 2);

	INF.unitSprite.setPosition({430, -130});
	INF.unitName.setPosition({INF.unitSprite.getPosition().x, INF.unitSprite.getPosition().y - 30});

	Menu CAV(UnitTile::UnitType::CAV);
	CAV.unitName.setFont(game->mFontManager.getFont(FontManager::Type::Lucon));
	CAV.unitName.setColor(sf::Color::White);
	CAV.unitName.setString("CAVALRY(5)");
	CAV.unitName.setCharacterSize(12);
	CAV.unitName.setOrigin(CAV.unitName.getLocalBounds().width / 2, CAV.unitName.getLocalBounds().height / 2);

	CAV.unitSprite = game->mTextureManager.getSprite(TextureManager::Unit::CAV);
	CAV.unitSprite.setOrigin(CAV.unitSprite.getGlobalBounds().width / 2, CAV.unitSprite.getGlobalBounds().height / 2);

	CAV.unitSprite.setPosition({530, -130});
	CAV.unitName.setPosition({CAV.unitSprite.getPosition().x, CAV.unitSprite.getPosition().y - 30});

	Menu CUIR(UnitTile::UnitType::CUIR);
	CUIR.unitName.setFont(game->mFontManager.getFont(FontManager::Type::Lucon));
	CUIR.unitName.setColor(sf::Color::White);
	CUIR.unitName.setString("CUIRASSIER(5)");
	CUIR.unitName.setCharacterSize(12);
	CUIR.unitName.setOrigin(CUIR.unitName.getLocalBounds().width / 2, CUIR.unitName.getLocalBounds().height / 2);

	CUIR.unitSprite = game->mTextureManager.getSprite(TextureManager::Unit::CUIR);
	CUIR.unitSprite.setOrigin(CUIR.unitSprite.getGlobalBounds().width / 2, CUIR.unitSprite.getGlobalBounds().height / 2);

	CUIR.unitSprite.setPosition({730, -130});
	CUIR.unitName.setPosition({CUIR.unitSprite.getPosition().x, CUIR.unitSprite.getPosition().y - 30});

	Menu LCAV(UnitTile::UnitType::LCAV);
	LCAV.unitName.setFont(game->mFontManager.getFont(FontManager::Type::Lucon));
	LCAV.unitName.setColor(sf::Color::White);
	LCAV.unitName.setString("LCAV(3)");
	LCAV.unitName.setCharacterSize(12);
	LCAV.unitName.setOrigin(LCAV.unitName.getLocalBounds().width / 2, LCAV.unitName.getLocalBounds().height / 2);

	LCAV.unitSprite = game->mTextureManager.getSprite(TextureManager::Unit::LCAV);
	LCAV.unitSprite.setOrigin(LCAV.unitSprite.getGlobalBounds().width / 2, LCAV.unitSprite.getGlobalBounds().height / 2);

	LCAV.unitSprite.setPosition({630, -60});
	LCAV.unitName.setPosition({LCAV.unitSprite.getPosition().x, LCAV.unitSprite.getPosition().y - 30});

	Menu ART(UnitTile::UnitType::ART);
	ART.unitName.setFont(game->mFontManager.getFont(FontManager::Type::Lucon));
	ART.unitName.setColor(sf::Color::White);
	ART.unitName.setString("ARTILLERY(5)");
	ART.unitName.setCharacterSize(12);
	ART.unitName.setOrigin(ART.unitName.getLocalBounds().width / 2, ART.unitName.getLocalBounds().height / 2);


	ART.unitSprite = game->mTextureManager.getSprite(TextureManager::Unit::ART);
	ART.unitSprite.setOrigin(ART.unitSprite.getGlobalBounds().width / 2, ART.unitSprite.getGlobalBounds().height / 2);

	ART.unitSprite.setPosition({430, -60});
	ART.unitName.setPosition({ART.unitSprite.getPosition().x, ART.unitSprite.getPosition().y - 30});

	Menu MOR(UnitTile::UnitType::MOR);
	MOR.unitName.setFont(game->mFontManager.getFont(FontManager::Type::Lucon));
	MOR.unitName.setColor(sf::Color::White);
	MOR.unitName.setString("MORTAR(5)");
	MOR.unitName.setCharacterSize(12);
	MOR.unitName.setOrigin(MOR.unitName.getLocalBounds().width / 2, MOR.unitName.getLocalBounds().height / 2);

	MOR.unitSprite = game->mTextureManager.getSprite(TextureManager::Unit::MOR);
	MOR.unitSprite.setOrigin(MOR.unitSprite.getGlobalBounds().width / 2, MOR.unitSprite.getGlobalBounds().height / 2);

	MOR.unitSprite.setPosition({530, -60});
	MOR.unitName.setPosition({MOR.unitSprite.getPosition().x, MOR.unitSprite.getPosition().y - 30});

	Menu GEN(UnitTile::UnitType::GEN);
	GEN.unitName.setFont(game->mFontManager.getFont(FontManager::Type::Lucon));
	GEN.unitName.setColor(sf::Color::White);
	GEN.unitName.setString("GENERAL(1)");
	GEN.unitName.setCharacterSize(12);
	GEN.unitName.setOrigin(GEN.unitName.getLocalBounds().width / 2, GEN.unitName.getLocalBounds().height / 2);

	GEN.unitSprite = game->mTextureManager.getSprite(TextureManager::Unit::GEN);
	GEN.unitSprite.setOrigin(GEN.unitSprite.getGlobalBounds().width / 2, GEN.unitSprite.getGlobalBounds().height / 2);

	GEN.unitSprite.setPosition({630, -130});
	GEN.unitName.setPosition({GEN.unitSprite.getPosition().x, GEN.unitSprite.getPosition().y - 30});

	MenuItems.emplace_back(INF);
	MenuItems.emplace_back(CAV);
	MenuItems.emplace_back(CUIR);
	MenuItems.emplace_back(LCAV);
	MenuItems.emplace_back(ART);
	MenuItems.emplace_back(MOR);
	MenuItems.emplace_back(GEN);

	sf::Text shortcuts;

	sf::Text infShortcut;
	sf::Text cavShortcut;
	sf::Text artShortcut;
	sf::Text morShortcut;
	sf::Text genShortcut;

	/*
	You will notice I set the origins for the following sf::Text objects to

	(GEN.unitName.getLocalBounds().width / 2, GEN.unitName.getLocalBounds().height / 2)

	This was a mistake at first, but I noticed changing it causes the text to become blurry somehow,
	so I kept it. I know it doesn't make much sense, but still...
	*/


	shortcuts.setFont(game->mFontManager.getFont(FontManager::Type::Lucon));
	shortcuts.setColor(sf::Color::White);
	shortcuts.setString("Spawning Shortcuts:");
	shortcuts.setCharacterSize(12);
	shortcuts.setOrigin(shortcuts.getLocalBounds().width / 2, shortcuts.getLocalBounds().height / 2);
	shortcuts.setPosition(300, -160);

	infShortcut.setFont(game->mFontManager.getFont(FontManager::Type::Lucon));
	infShortcut.setColor(sf::Color::White);
	infShortcut.setString("T - INF");
	infShortcut.setCharacterSize(12);
	infShortcut.setOrigin(GEN.unitName.getLocalBounds().width / 2, GEN.unitName.getLocalBounds().height / 2);
	infShortcut.setPosition(330, -130);

	cavShortcut.setFont(game->mFontManager.getFont(FontManager::Type::Lucon));
	cavShortcut.setColor(sf::Color::White);
	cavShortcut.setString("Y - CAV");
	cavShortcut.setCharacterSize(12);
	cavShortcut.setOrigin(GEN.unitName.getLocalBounds().width / 2, GEN.unitName.getLocalBounds().height / 2);
	cavShortcut.setPosition(330, -115);

	genShortcut.setFont(game->mFontManager.getFont(FontManager::Type::Lucon));
	genShortcut.setColor(sf::Color::White);
	genShortcut.setString("U - GEN");
	genShortcut.setCharacterSize(12);
	genShortcut.setOrigin(GEN.unitName.getLocalBounds().width / 2, GEN.unitName.getLocalBounds().height / 2);
	genShortcut.setPosition(330, -100);

	artShortcut.setFont(game->mFontManager.getFont(FontManager::Type::Lucon));
	artShortcut.setColor(sf::Color::White);
	artShortcut.setString("F - ART");
	artShortcut.setCharacterSize(12);
	artShortcut.setOrigin(GEN.unitName.getLocalBounds().width / 2, GEN.unitName.getLocalBounds().height / 2);
	artShortcut.setPosition(330, -85);

	morShortcut.setFont(game->mFontManager.getFont(FontManager::Type::Lucon));
	morShortcut.setColor(sf::Color::White);
	morShortcut.setString("G - MOR");
	morShortcut.setCharacterSize(12);
	morShortcut.setOrigin(GEN.unitName.getLocalBounds().width / 2, GEN.unitName.getLocalBounds().height / 2);
	morShortcut.setPosition(330, -70);


	keyShortcuts.emplace_back(shortcuts);
	keyShortcuts.emplace_back(infShortcut);
	keyShortcuts.emplace_back(cavShortcut);
	keyShortcuts.emplace_back(artShortcut);
	keyShortcuts.emplace_back(morShortcut);
	keyShortcuts.emplace_back(genShortcut);

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

		case sf::Event::Resized:
			game->Player1.view.setSize(event.size.width, event.size.height);
			game->Player2.view.setSize(event.size.width, event.size.height);

			break;

		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left){

				//If no menu item was selected, select it

				if (selected == nullptr){
					sf::Vector2f worldCoords{game->mWindow.mapPixelToCoords(game->mousePos, *game->currentView)};
					sf::Vector2f uiCoords{game->mWindow.mapPixelToCoords(game->mousePos, game->uiView)};

					for (int i{0}; i < MenuItems.size(); ++i){
						if (uiCoords.x > MenuItems[i].left() && uiCoords.x < MenuItems[i].right()
							&&
							uiCoords.y > MenuItems[i].top() && uiCoords.y < MenuItems[i].bottom()){

							selected = new Menu(MenuItems[i]);
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

						game->currentPlayer->spawnUnit(selected->type, worldCoords);

					}

					selected = nullptr;
					delete selected;
					break;
				}
			}


			else if (event.mouseButton.button == sf::Mouse::Right){

				//Deselect the currently selected icon:

				if (selected != nullptr){
					
					selected = nullptr;
					delete selected;
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


		case sf::Event::MouseMoved:
			game->mousePos.x = event.mouseMove.x;
			game->mousePos.y = event.mouseMove.y;
			break;

		case sf::Event::Closed:
			game->mWindow.close();
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
				game->currentView->setSize(game->mWindow.getSize().x, game->mWindow.getSize().y);
				break;

            case ZOOMIN_KEY:
				game->currentView->setSize(game->currentView->getSize().x - game->mWindow.getSize().x / 10, game->currentView->getSize().y - game->mWindow.getSize().y / 10);
                break;

            case ZOOMOUT_KEY:
				game->currentView->setSize(game->currentView->getSize().x + game->mWindow.getSize().x / 10, game->currentView->getSize().y + game->mWindow.getSize().y / 10);
                break;

            case SPAWNINF_KEY:
				selected = nullptr;
				delete selected;
                selected = new Menu(MenuItems[0]);
                break;

            case SPAWNCAV_KEY:
				selected = nullptr;
				delete selected;
                selected = new Menu(MenuItems[1]);
                break;

            case SPAWNART_KEY:
				selected = nullptr;
				delete selected;
                selected = new Menu(MenuItems[2]);
                break;

            case SPAWNMOR_KEY:
				selected = nullptr;
				delete selected;
                selected = new Menu(MenuItems[3]);
                break;

            case SPAWNGEN_KEY:
				selected = nullptr;
				delete selected;
                selected = new Menu(MenuItems[4]);
                break;

			default:
				break;
			}

			break;

		case sf::Event::MouseWheelMoved:
			if (event.mouseWheel.delta > 0){
				game->currentView->setSize(game->currentView->getSize().x - game->mWindow.getSize().x / 12, game->currentView->getSize().y - game->mWindow.getSize().y / 12);
			}
			else if (event.mouseWheel.delta < 0){
				game->currentView->setSize(game->currentView->getSize().x + game->mWindow.getSize().x / 12, game->currentView->getSize().y + game->mWindow.getSize().y / 12);
			}

			break;
		}

	}

}

void GameState_Setup::update(){

	numbRemaining.setString(std::to_string(game->currentPlayer->getDeploymentPoints()));

	//
	currentPlayerText.setString(game->currentPlayer->getName());

	//
	if (game->currentPlayer->isReady()){
		if (game->currentPlayer == &game->Player1){
			game->nextPlayer();
		}
		else if (game->currentPlayer == &game->Player2){
			game->nextPlayer();
			game->setGameStatePlay();
		}
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

    if(selected != nullptr){
            selected->unitSprite.setPosition(worldCoords);
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

	

/*
        std::cout << worldCoords.x;
        std::cout << ", " << worldCoords.y;
        std::cout << std::endl;
*/

}

void GameState_Setup::draw(){
	game->mWindow.setView(*game->currentView);
	game->mWorld.draw(game->mWindow);

	//
	game->mWindow.setView(game->uiView);

	game->mWindow.draw(game->uiSprite);
	game->mWindow.draw(numbRemaining);
	game->mWindow.draw(currentPlayerText);

	readyButton.draw(game->mWindow);

	for (auto& menu : MenuItems){
		menu.draw(game->mWindow);
	}

	//for (auto& shortcut : keyShortcuts){
	//	game->mWindow.draw(shortcut);
	//}

	//
	game->mWindow.setView(*game->currentView);
	if (selected != nullptr){
		game->mWindow.draw(selected->unitSprite);
	}

}

