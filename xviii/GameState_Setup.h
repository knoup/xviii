#pragma once

#include "GameState.h"

//#include <iostream>
#include "global.h"

class GameState_Setup : public GameState
{
public:
	struct Menu{
		sf::Text unitName;
		sf::Sprite unitSprite;
		UnitTile::UnitType type;

		Menu(UnitTile::UnitType _type) :
			//Just the type used before it is properly loaded
			type{_type}
		{
		}
		
		int top() const{
			return unitSprite.getPosition().y - unitSprite.getLocalBounds().height / 2;
		}
		int left() const{
			return unitSprite.getPosition().x - unitSprite.getGlobalBounds().width / 2;
		}
		int bottom() const{
			return unitSprite.getPosition().y + unitSprite.getGlobalBounds().height / 2;
		}
		int right() const{
			return unitSprite.getPosition().x + unitSprite.getGlobalBounds().width / 2;
		}

		void draw(sf::RenderWindow& target){
			target.draw(unitName);
			target.draw(unitSprite);
		}
	};

	struct Button{
		sf::Text text;
		sf::Sprite sprite;
		sf::RectangleShape rekt;

		bool highlighted;

		Button() : 
			highlighted{false}
		{
			text.setString("READY");
			text.setColor(sf::Color::Black);
			rekt.setFillColor(sf::Color::Transparent);
			rekt.setOutlineColor(sf::Color::Yellow);
			rekt.setOutlineThickness(5);
		}

		int top() const{
			return sprite.getPosition().y - sprite.getLocalBounds().height / 2;
		}
		int left() const{
			return sprite.getPosition().x - sprite.getGlobalBounds().width / 2;
		}
		int bottom() const{
			return sprite.getPosition().y + sprite.getGlobalBounds().height / 2;
		}
		int right() const{
			return sprite.getPosition().x + sprite.getGlobalBounds().width / 2;
		}

		void draw(sf::RenderTarget& target){
			target.draw(sprite);
			target.draw(text);

			if (highlighted){
				target.draw(rekt);
			}
		}
	};

	GameState_Setup(Game* game);
	virtual void getInput();
	virtual void update();
	virtual void draw();

private:
	//UI ELEMENTS
	//TODO: perhaps make a seperate UI class?

	sf::Text numbRemaining;
	sf::Text currentPlayerText;
	sf::Text deploymentPointsRemaining;

	Button readyButton;

	std::vector<sf::Text> keyShortcuts;
	std::vector<Menu> MenuItems;
	Menu* selected;

};

