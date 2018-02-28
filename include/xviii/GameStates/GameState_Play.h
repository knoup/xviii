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
		    text{},
		    sprite{},
		    rekt{},
			highlighted{false}
		{
			text.setString("NEXT TURN");
			text.setCharacterSize(25);
			text.setFillColor(sf::Color::Black);
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
    //The copy constructor and = operator for this class have been disabled
	//Copy constructor
	GameState_Play(const GameState_Play&) = delete;
	//Operator=
	GameState_Play & operator=(const GameState_Play&) = delete;

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
	bool middleButtonHeld;

	sf::Text tileDistanceText;

	PlayUI playUI;
	bool drawUI;
	sf::Clock animationClock;

	bool moveAnimationPlaying{false};

	//These are all required for the smooth zoom/interpolation of the camera
	sf::Vector2f smoothZoom_currentCenter{};
	sf::Vector2f smoothZoom_targetCenter{};
	float smoothZoom_targetZoom = 0.0f;
	float smoothZoom_currentZoom = 0.0f;
	float smoothZoom_previousZoom = 0.0f;
	bool smoothZoom_zooming = false;
	float smoothZoom_lerpFactor = 0.0085f;
	////////////////////////////////////////////////////////////////////////

};

