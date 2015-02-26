#include "stdafx.h"
#include "GameState_Menu.h"


GameState_Menu::GameState_Menu(Game* game) :
GameState{game}
{
	menuText.setFont(game->mFontManager.getFont(FontManager::Arial));
	menuText.setCharacterSize(30);

	std::string str = "N - start a new game\n"
					  "L - load an existing save ";

	std::ifstream save("save.dat");
	//If save.dat exists
	if (save){
		str += "(1 found)";
	}
	//Otherwise
	else{
		str += "(none found)";
	}

	menuText.setString(str);

	menuText.setOrigin(menuText.getLocalBounds().width / 2, menuText.getLocalBounds().height / 2);
	menuText.setPosition(game->mWindow.getSize().x / 2, game->mWindow.getSize().y / 2);
}

void GameState_Menu::getInput(){
	sf::Event event;

	while (game->mWindow.pollEvent(event)){
		switch (event.type){

		case sf::Event::Closed:
			game->mWindow.close();
			break;

		case sf::Event::KeyPressed:

			switch (event.key.code){

			case NEW_GAME:
				game->setGameStateSetup();
				break;

			case LOAD_GAME:
				std::ifstream save("save.dat");
				//If save.dat exists, load from it
				if (save){
					game->saveCreator.parse();
					game->setGameStatePlay();
				}
				//Otherwise, just start a new game
				else{
					game->setGameStateSetup();
				}
				break;

			}

		}
	}
}

void GameState_Menu::update(){

}

void GameState_Menu::draw(){
	game->mWindow.clear(sf::Color::Black);
	game->mWindow.draw(menuText);
}