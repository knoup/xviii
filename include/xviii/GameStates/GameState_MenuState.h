#pragma once

#include "xviii/GameStates/GameState.h"

#include "boost/filesystem/fstream.hpp"

#include "xviii/Headers/global.h"
#include "xviii/Headers/keybinds.h"

class GameState_MenuState : public GameState
{
public:
	GameState_MenuState(Game* game);
	virtual void getInput();
	virtual void update(float mFT);
	virtual void draw();
protected:
	enum class Action{NEW, LOAD, EXIT, NONE};

	//If the action is not NONE, the game will perform that action upon choosing the object.
	//If the state is not null, the game will switch to that gamestate upon choosing the object.

	struct menuObject{
		menuObject(boost::filesystem::path _path, GameState* _state, Action _action, World::Era _era = World::Era::ALL) :
			path{_path}, state{_state}, action{_action}, era{_era}
		{
			text.setString(_path.filename().string());
		}

		boost::filesystem::path path;
		sf::Text text;
		GameState* state;
		Action action;
		//This will only matter if the action is NEW; for loading games, this will be
		//loaded from the save file
		World::Era era;
	};

	std::vector<menuObject> menuList;

	//menuIterator will serve as an easy way to access the pointer to
	// the currently selected option that can be incremented and
	//decremented to move around the vector

	std::vector<menuObject>::iterator menuIterator;

	sf::View menuSelectView;
	sf::View backgroundView;

	sf::Text titleText;
	//Due to the massive amount of available backgrounds, and the fact that only one will be ever used,
	//this is the only place in the code where I won't handle a texture with TextureManager.
	std::unique_ptr<sf::Texture> backgroundTexture;
	sf::Sprite backgroundSprite;

	void lineUpObjects();
};

