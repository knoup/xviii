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
	virtual void lineUpObjects();
	virtual void handleResize();

	void updateNationName();

	struct FlagMenuItem{
		FlagMenuItem(std::string _factionID, std::string _displayName, sf::Sprite _sprite, const sf::Font& _font) :
			factionID{_factionID},
			displayName{_displayName},
			sprite{_sprite},
			displayNameText{},
			highlighted{false},
			rekt{}
		{
			displayNameText.setFont(_font);
			displayNameText.setString(displayName);
			displayNameText.setFillColor(sf::Color::Black);
			displayNameText.setCharacterSize(25);

			while(displayNameText.getGlobalBounds().width > 300){
				displayNameText.setCharacterSize(displayNameText.getCharacterSize() - 2);
			}

			rekt.setSize({sprite.getLocalBounds().width + float(1.2 * displayNameText.getGlobalBounds().width), sprite.getLocalBounds().height});
			rekt.setFillColor(sf::Color(255,255,255, 190));
			rekt.setOutlineColor(sf::Color::Black);
			rekt.setOutlineThickness(1);
		};

        //We're going to want to sort the nations alphabetically, so we define
        //the < operator for that purpose here.
        bool operator < (const FlagMenuItem& _other){
            return (displayNameText.getString() < _other.displayNameText.getString());
        };

        std::string factionID;
        std::string displayName;
		sf::Sprite sprite;
		sf::Text displayNameText;

		bool highlighted;
		sf::RectangleShape rekt;

		void draw(sf::RenderTarget& _window){
			_window.draw(rekt);
			_window.draw(sprite);
			_window.draw(displayNameText);
		}

		void setPosition(sf::Vector2f _pos){
			rekt.setPosition(_pos);
			sprite.setPosition({_pos.x + 3, _pos.y});
			float heightDifference{sprite.getGlobalBounds().height - displayNameText.getGlobalBounds().height};
			displayNameText.setPosition({sprite.getPosition().x + sprite.getGlobalBounds().width + 3, sprite.getPosition().y + heightDifference});
		}

		void highlight(bool _v){
            highlighted = _v;

            if(!highlighted){
                rekt.setFillColor(sf::Color(255,255,255, 190));
            }
            else{
                rekt.setFillColor(sf::Color(255,255,0, 190));
            }
		}
	};

	std::vector<FlagMenuItem> flagMenuItems1;
	std::vector<FlagMenuItem> flagMenuItems2;
	std::vector<FlagMenuItem>::iterator flagIterator1;
	std::vector<FlagMenuItem>::iterator flagIterator2;
	//std::vector<sf::VertexArray> lineVector1;
	//std::vector<sf::VertexArray> lineVector2;
	sf::View flagView1;
	sf::View flagView2;

	sf::Text player1Text;
	sf::Text player2Text;

	sf::Text player1NationText;
	sf::Text player2NationText;

private:
    Scrollbar scrollbar_player1;
    Scrollbar scrollbar_player2;

    void detectMousedOverNations();
};

