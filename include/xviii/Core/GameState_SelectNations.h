#pragma once

#include "xviii/Core/GameState.h"
#include "xviii/Headers/global.h"
#include "xviii/Headers/keybinds.h"

class GameState_SelectNations : public GameState
{
public:
	GameState_SelectNations(Game* game);
	virtual void getInput();
	virtual void update(float mFT);
	virtual void draw();

private:
	void updateNationName();

	struct FlagMenuItem{
		FlagMenuItem(std::string _name, sf::Sprite _sprite) :
			name{_name},
			sprite{_sprite},
			highlighted{false}
		{
		    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
			rekt.setSize({sprite.getLocalBounds().width, sprite.getLocalBounds().height});
			rekt.setOrigin(rekt.getLocalBounds().width / 2, rekt.getLocalBounds().height / 2);
			rekt.setFillColor(sf::Color::Transparent);
			rekt.setOutlineColor(sf::Color::Yellow);
			rekt.setOutlineThickness(2);
		};

        std::string name;
		sf::Sprite sprite;

		bool highlighted;
		sf::RectangleShape rekt;

		void draw(sf::RenderTarget& _window){
			_window.draw(sprite);
			if (highlighted){
				_window.draw(rekt);
			}
		}
	};

	std::vector<FlagMenuItem> flagMenuItems;
	std::vector<FlagMenuItem>::iterator flagIterator;

	sf::Text currentPlayerText;
	sf::Text currentNationName;
	sf::View flagView;
	sf::View uiView;
};

