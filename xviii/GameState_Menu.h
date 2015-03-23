#pragma once

#include "GameState.h"

#include "boost/filesystem/fstream.hpp"

#include "keybinds.h"

class GameState_Menu : public GameState
{
public:
	GameState_Menu(Game* game);
	virtual void getInput();
	virtual void update();
	virtual void draw();
private:
	enum class Action{ NEW, LOAD };

	struct saveObject{
		saveObject(boost::filesystem::path _path, Action _action) :
			path{_path},action{_action}
		{
			text.setString(_path.filename().string());
		}

		boost::filesystem::path path;
		sf::Text text;
		Action action;
	};

	std::vector<saveObject> menuList;
	
	
	//menuIterator will serve as an easy way to access the pointer to
	// the currently selected option that can be incremented and
	//decremented to move around the vector

	std::vector<saveObject>::iterator menuIterator;

	void clearHighlighting();

	sf::View menuSelectView;
};

