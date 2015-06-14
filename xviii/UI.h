#pragma once

#include "TextureManager.h"
#include "FontManager.h"

#include "global.h"

class GameState;

class UI : public sf::Drawable
{
public:
	struct Button{
		sf::Text text;
		sf::Sprite sprite;
		sf::RectangleShape rekt;

		bool highlighted;

		Button() :
			highlighted{false}
		{
			text.setColor(sf::Color::Black);
			rekt.setFillColor(sf::Color::Transparent);
			rekt.setOutlineColor(sf::Color::Yellow);
			rekt.setOutlineThickness(5);
		}

		void setString(std::string str){
			text.setString(str);
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
	};

	UI(TextureManager& _tm, FontManager& _fm);
	//Create a virtual destructor, signifying this is an abstract class
	virtual ~UI() = 0;
	void setCurrentPlayerText(std::string str);
	void setButtonHighlighted(bool val);
	const Button& getButton() const;
	inline virtual void update(){};
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states = sf::RenderStates::Default) const = 0;

protected:
	TextureManager& tm;
	FontManager& fm;

	//
	sf::Sprite uiSprite;
	sf::Text currentPlayerText;
	Button button;

public:
	sf::View uiView;
};

