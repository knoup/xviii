#pragma once

#include "xviii/GameStates/GameState_MenuState.h"
#include "xviii/Headers/global.h"
#include "xviii/Headers/keybinds.h"

class GameState_SelectNationsMenu : public GameState_MenuState
{
public:
	GameState_SelectNationsMenu(Game* game);
	virtual void getInput();
	virtual void update(float mFT);
	virtual void draw();

private:
	void updateNationName();

	struct FlagMenuItem{
		FlagMenuItem(std::string _factionID, std::string _displayName, sf::Sprite _sprite) :
			factionID{_factionID},
			displayName{_displayName},
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

        std::string factionID;
        std::string displayName;
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

	std::vector<FlagMenuItem> flagMenuItems1;
	std::vector<FlagMenuItem> flagMenuItems2;
	std::vector<FlagMenuItem>::iterator flagIterator1;
	std::vector<FlagMenuItem>::iterator flagIterator2;
	sf::View flagView1;
	sf::View flagView2;

	sf::Text player1Text;
	sf::Text player2Text;

	sf::Text player1NationText;
	sf::Text player2NationText;

	sf::Sprite backgroundSprite;;
	sf::View backgroundView;
};

