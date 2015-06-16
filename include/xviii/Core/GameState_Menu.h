#pragma once

#include "xviii/Core/GameState.h"

#include "boost/filesystem/fstream.hpp"

#include "xviii/Headers/global.h"
#include "xviii/Headers/keybinds.h"

class GameState_Menu : public GameState
{
public:
	GameState_Menu(Game* game);
	virtual void getInput();
	virtual void update(float mFT);
	virtual void draw();
private:
	enum class Action{ NEW, LOAD, EXIT };

	struct saveObject{
		saveObject(boost::filesystem::path _path, Action _action, World::Era _era) :
			path{_path}, action{_action}, era{_era}
		{
			text.setString(_path.filename().string());
		}

		boost::filesystem::path path;
		sf::Text text;
		Action action;
		//This will only matter if the action is NEW; for loading games, this will be
		//loaded from the save file
		World::Era era;
	};

	std::vector<saveObject> menuList;

	//menuIterator will serve as an easy way to access the pointer to
	// the currently selected option that can be incremented and
	//decremented to move around the vector

	std::vector<saveObject>::iterator menuIterator;

	sf::View menuSelectView;
	sf::View backgroundView;

	sf::Text titleText;
	//Due to the massive amount of available backgrounds, and the fact that only one will be ever used,
	//this is the only place in the code where I won't handle a texture with TextureManager.
	std::unique_ptr<sf::Texture> backgroundTexture;
	sf::Sprite backgroundSprite;

	sf::Text earlyEraText;
	sf::Text midEraText;
	sf::Text lateEraText;
	sf::Text allEraText;
};
