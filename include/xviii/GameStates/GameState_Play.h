#pragma once
#include "xviii/GameStates/GameState.h"
#include "xviii/Headers/global.h"
#include "xviii/Headers/keybinds.h"

#include "xviii/UI/PlayUI.h"

class GameState_Play : public GameState
{
	friend class PlayUI;

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
	virtual void update(float mFT);
	virtual void draw();
	virtual void onSwitch();

    //A little wrapper, since we need to access this from the combat pause menu and playUI is private...
	inline void setSaveStatus(bool val){playUI.setSaveStatus(val);};
private:
    void handleWeather();

	UnitTile* selected;

	sf::Vector2f cameraVelocity;
	sf::Vector2i middleButtonCoords;
	bool middleButtonHeld{false};

	sf::Text tileDistanceText;

	PlayUI playUI;
	bool drawUI{true};
	sf::Clock animationClock;

};

