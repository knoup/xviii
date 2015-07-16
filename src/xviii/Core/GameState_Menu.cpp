#include "xviii/Headers/stdafx.h"
#include "xviii/Core/GameState_Menu.h"

#include "xviii/Core/Game.h"

GameState_Menu::GameState_Menu(Game* game) :
GameState{game},
menuSelectView{sf::FloatRect({}, {},xResolution, yResolution)},
backgroundView{sf::FloatRect({}, {}, xResolution, yResolution)}
{
	titleText.setString("X V I I I");
	titleText.setCharacterSize(275);
	titleText.setFont(game->mFontManager.getFont(FontManager::Eighteen));

	//Randomise title text colour, for the heck of it:
	boost::random::uniform_int_distribution<int> distribution(0, 255);
	int randColourR{distribution(game->mtengine)};
	int randColourG{distribution(game->mtengine)};
	int randColourB{distribution(game->mtengine)};
	titleText.setColor(sf::Color(randColourR, randColourG, randColourB));

	titleText.setOrigin(titleText.getLocalBounds().width / 2, titleText.getLocalBounds().height / 2);
	titleText.setPosition(xResolution / 2, -(yResolution / 2.5f));

	std::vector<boost::filesystem::path> paths;
	boost::filesystem::directory_iterator end;

	if (boost::filesystem::exists("assets/gfx/backgrounds")){
		for (boost::filesystem::directory_iterator it("assets/gfx/backgrounds"); it != end; ++it){
			paths.push_back(it->path());
		}
	}

	if (!paths.empty()){
		boost::random::uniform_int_distribution<int> dist(0, paths.size() - 1);
		int randomIndex{dist(game->mtengine)};
		std::string randomPath{paths[randomIndex].string()};

		backgroundTexture = std::move(std::unique_ptr<sf::Texture>(new sf::Texture()));
		backgroundTexture->loadFromFile(randomPath);
		backgroundSprite.setTexture(*backgroundTexture);
	}

	////////////////////////////////////////////////////////////////////////

	menuList.push_back({{"New Game (All Eras)"}, Action::NEW, World::Era::ALL});
	menuList.push_back({{"New Game (Early Era)"}, Action::NEW, World::Era::EARLY});
	menuList.push_back({{"New Game (Mid Era)"}, Action::NEW, World::Era::MID});
	menuList.push_back({{"New Game (Late Era)"}, Action::NEW, World::Era::LATE});

	if (boost::filesystem::exists("save")){
		for (boost::filesystem::directory_iterator it("save"); it != end; ++it){
			menuList.push_back({it->path(), Action::LOAD, World::Era::ALL});
		}
	}

	menuList.push_back({{"Exit"}, Action::EXIT, World::Era::ALL});

	for (size_t i{0}; i < menuList.size(); ++i){
		menuList[i].text.setFont(game->mFontManager.getFont(FontManager::Arial));
		menuList[i].text.setOrigin(menuList[i].text.getLocalBounds().width / 2, menuList[i].text.getLocalBounds().height / 2);
		menuList[i].text.setColor(sf::Color::White);
		menuList[i].text.setStyle(sf::Text::Bold);

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
			if (event.key.code == Key::CONFIRM_KEY){
				switch (menuIterator->action){
					case Action::NEW:
						game->mWorld.generateRandomWorld(menuIterator->era);
						game->setGameStateSelectNations();
						break;

					case Action::LOAD:
						game->saveCreator.parse(menuIterator->path);
						game->setGameStatePlay();
						break;

					case Action::EXIT:
						game->mWindow.close();
						break;
				}
			}


			//--menuList.end() because menuList.end() would point to a undereferencable reference
			//(after the end of the vector); --menuList.end() rather points to the last element

			else if ((event.key.code == Key::UP_ARROW || event.key.code == Key::DOWN_ARROW || event.key.code == Key::UP_KEY || event.key.code == Key::DOWN_KEY) && menuList.size() > 1){

				//Unhighlight current object
				menuIterator->text.setColor((sf::Color::White));

				if (event.key.code == Key::UP_ARROW || event.key.code == Key::UP_KEY){
					if (menuIterator == menuList.begin()){
						menuIterator = --menuList.end();
					}
					else{
						--menuIterator;
					}
				}
				else if (event.key.code == Key::DOWN_ARROW || event.key.code == Key::DOWN_KEY){
					if (menuIterator == --menuList.end()){
						menuIterator = menuList.begin();
					}
					else{
						++menuIterator;
					}
				}
			}

			else if (event.key.code == Key::DELETE_KEY && menuIterator->action != Action::NEW){
				if (menuIterator->action == Action::EXIT){
					for (size_t i{0}; i < menuList.size(); ++i){
						menuList[i].text.setFont(game->mFontManager.getFont(FontManager::Arial));

						menuList[i].text.setString("THERE IS NO ESCAPE");
						menuList[i].text.setOrigin(menuList[i].text.getLocalBounds().width / 2, menuList[i].text.getLocalBounds().height / 2);
					}

					titleText.setCharacterSize(170);
					titleText.setString("THERE IS NO ESCAPE");
					titleText.setOrigin(titleText.getLocalBounds().width / 2, titleText.getLocalBounds().height / 2);
				}

				boost::filesystem::remove(menuIterator->path);
				menuList.erase(menuIterator);
				menuIterator = menuList.begin();

				for (size_t i{0}; i < menuList.size(); ++i){
					int textXPos = xResolution / 2;
					int textYPos = (i * 50);


					menuList[i].text.setPosition(textXPos, textYPos);
				}
			}

			break;

		case sf::Event::Resized:
			menuSelectView.setSize(event.size.width, event.size.height);
			break;

		default: break;

		}
	}
}

void GameState_Menu::update(float mFT){
	if (menuIterator->text.getColor() != sf::Color::Yellow){
		menuIterator->text.setColor(sf::Color::Yellow);
	}

	menuSelectView.setCenter(menuSelectView.getCenter().x, menuIterator->text.getPosition().y);
}

void GameState_Menu::draw(){
	game->mWindow.clear(sf::Color::Black);
	game->mWindow.setView(backgroundView);
	game->mWindow.draw(backgroundSprite);

	game->mWindow.setView(menuSelectView);
	game->mWindow.draw(titleText);

	for (auto& item : menuList){
		game->mWindow.draw(item.text);
	}
}
