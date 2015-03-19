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
	
	/*menuIterator is a pair containining an iterator and a boolean;
		The iterator will serve as a pointer to the currently selected option, that can
		 be incremented and decremented to move around the vector

		 The boolean will serve as an indicator of what direction to iterate in. True
		 means that menuIterator is to be incremented (i.e. moving forward in menuList),
		 and false indicates menuIterator is to be decremented (i.e. moving backwards in menuList)
		*/
	std::pair<std::vector<saveObject>::iterator, bool > menuIterator;

	void clearHighlighting();
	void iterate();
};

