#pragma once
#include "GameState.h"
#include "global.h"

class GameState_Play : public GameState
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
			text.setString("NEXT TURN");
			text.setCharacterSize(25);
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

	GameState_Play(Game* _game);

	//Due to the way gamestate changing works, the PlayState is created before the player decides
	//whether to load a save or not. When the player loads the save, there are some essential values
	//that need to be updated (turn, current player text, etc). only once;
	//rather than having them constantly be updated in update(), I made this function instead, although it
	//feels "hacky"...
	void oneTimeUpdate();

	virtual void getInput();
	virtual void update();
	virtual void draw();
private:
	//Sets saveText to either say that the user has saved or not
	void saveTextString(bool _value);

	UnitTile* selected;

	//UI stuff

	Button nextTurnButton;
	sf::Text currentPlayerText;
	sf::Text elapsedTurnsText;

	sf::Text tileDistanceText;
	//Purely aesthetic
	sf::Text messageLogText;

	sf::Text currentMessageText;

	sf::Text saveText;

	std::string currentMessage;
};

