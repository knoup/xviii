#include "stdafx.h"
#include "GameState_Menu.h"

GameState_Menu::GameState_Menu(Game* game) :
GameState{game},
menuSelectView{sf::FloatRect({}, {},xResolution, yResolution)}
{
	menuList.push_back({{"New Game"}, Action::NEW});
	
	boost::filesystem::directory_iterator end;

	if (boost::filesystem::exists("save")){
		for (boost::filesystem::directory_iterator it("save"); it != end; ++it){
			menuList.push_back({it->path(), Action::LOAD});
		}
	}

	for (int i{0}; i < menuList.size(); ++i){
		menuList[i].text.setFont(game->mFontManager.getFont(FontManager::Arial));
		menuList[i].text.setOrigin(menuList[i].text.getLocalBounds().width / 2, menuList[i].text.getLocalBounds().height / 2);
		menuList[i].text.setColor(sf::Color(80, 80, 80));

		int textXPos = xResolution / 2;
		int textYPos = (i * 50);

		menuList[i].text.setPosition(textXPos, textYPos);
	}
	//Set selected to the first item in menuList, which will always be "New Game"
	menuIterator = menuList.begin();
}

void GameState_Menu::getInput(){
	sf::Event event;

	while (game->mWindow.pollEvent(event)){
		switch (event.type){

		case sf::Event::Closed:
			game->mWindow.close();
			break;

		case sf::Event::KeyPressed:
			if (event.key.code == CONFIRM_KEY){
				switch (menuIterator->action){
					case Action::NEW:
						game->setGameStateSelectNations();
						break;

					case Action::LOAD:
						game->saveCreator.parse(menuIterator->path);
						game->setGameStatePlay();
						break;
				}
			}


			//--menuList.end() because menuList.end() would point to a undereferencable reference
			//(after the end of the vector); --menuList.end() rather points to the last element

			else if ((event.key.code == UP_ARROW || event.key.code == DOWN_ARROW) && menuList.size() > 1){

				//Unhighlight current object
				menuIterator->text.setColor((sf::Color(80, 80, 80)));

				if (event.key.code == UP_ARROW){
					if (menuIterator == menuList.begin()){
						menuIterator = --menuList.end();
					}
					else{
						--menuIterator;
					}
				}
				else if (event.key.code == DOWN_ARROW){
					if (menuIterator == --menuList.end()){
						menuIterator = menuList.begin();
					}
					else{
						++menuIterator;
					}
				}
			}

			else if (event.key.code == DELETE_KEY && menuIterator->action != Action::NEW){
				boost::filesystem::remove(menuIterator->path);
				menuList.erase(menuIterator);
				menuIterator = menuList.begin();

				for (int i{0}; i < menuList.size(); ++i){
					int textXPos = xResolution / 2;
					int textYPos = (i * 50);


					menuList[i].text.setPosition(textXPos, textYPos);
				}
			}

		}
	}
}

void GameState_Menu::update(){
	if (menuIterator->text.getColor() != sf::Color::White){
		menuIterator->text.setColor(sf::Color::White);
	}

	menuSelectView.setCenter(menuSelectView.getCenter().x, menuIterator->text.getPosition().y);
}

void GameState_Menu::draw(){
	game->mWindow.clear(sf::Color::Black);

	game->mWindow.setView(menuSelectView);

	for (auto& item : menuList){
		game->mWindow.draw(item.text);
	}
}
