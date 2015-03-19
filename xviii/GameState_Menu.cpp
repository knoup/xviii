#include "stdafx.h"
#include "GameState_Menu.h"

void GameState_Menu::clearHighlighting(){
	//Reset all the others to grey
	for (auto& object : menuList){
		object.text.setColor(sf::Color(80, 80, 80));
	}
}

GameState_Menu::GameState_Menu(Game* game) :
GameState{game}
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

		int textXPos = game->mWindow.getSize().x / 2;
		int textYPos = (i * 50) + 200;


		menuList[i].text.setPosition(textXPos, textYPos);
	}

	//Set selected to the first item in menuList, which will always be "New Game"
	menuIterator.first = menuList.begin();
	menuIterator.second = true;
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
				switch (menuIterator.first->action){
					case Action::NEW:
						game->setGameStateSetup();
						break;

					case Action::LOAD:
						game->saveCreator.parse(menuIterator.first->path);
						game->setGameStatePlay();
						break;
				}
			}


			//--menuList.end() because menuList.end() would point to a undereferencable reference
			//(after the end of the vector); --menuList.end() rather points to the last element

			else if ((event.key.code == UP_ARROW || event.key.code == DOWN_ARROW) && menuList.size() > 1){
				if (event.key.code == UP_ARROW){
					if (menuIterator.first == menuList.begin()){
						clearHighlighting();
						menuIterator.first = --menuList.end();
					}
					else{
						menuIterator.second = false;
						iterate();
					}
				}
				else if (event.key.code == DOWN_ARROW){
					if (menuIterator.first == --menuList.end()){
						clearHighlighting();
						menuIterator.first = menuList.begin();
					}
					else{
						menuIterator.second = true;
						iterate();
					}
				}
			}

		}
	}
}

void GameState_Menu::update(){
	if (menuIterator.first->text.getColor() != sf::Color::White){
		menuIterator.first->text.setColor(sf::Color::White);
	}
}

void GameState_Menu::draw(){
	game->mWindow.clear(sf::Color::Black);

	for (auto& item : menuList){
		game->mWindow.draw(item.text);
	}
}

void GameState_Menu::iterate(){
	clearHighlighting();

	if (menuIterator.second == true){
		++menuIterator.first;
	}
	else if (menuIterator.second == false){
		--menuIterator.first;
	}
}