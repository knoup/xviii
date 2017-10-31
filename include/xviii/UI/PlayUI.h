#pragma once

#include "xviii/UI/UI.h"

#include "xviii/Misc/RoundedRectangleShape.h"

class GameState_Play;

class PlayUI : public UI
{
public:
	PlayUI(MasterManager& _masterManager, GameState_Play* _gameState);
    //The copy constructor and = operator for this class have been disabled
	//Copy constructor
	PlayUI(const PlayUI&) = delete;
	//Operator=
	PlayUI & operator=(const PlayUI&) = delete;
	virtual ~PlayUI();
	void setElapsedTurnsText(int _num);
	void setCurrentMessageText(std::string _str);
	void setCurrentWeatherText();
	void setCurrentTimeText(std::pair<int,int> _time);
	void clearCurrentMessageText();
	void setSaveStatus(bool val);

	void turnlyUpdate();

	virtual void update();
    //playUI.draw() automatically changes views in order to draw what it needs to.
    //Keep this in mind, and always reset the view after calling it.
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states = sf::RenderStates::Default) const;

    inline void setArrowColor(sf::Color _color){
        arrow[0].color  = _color;
        arrow[1].color = _color;

        arrowTip1[0].color  = _color;
        arrowTip1[1].color = _color;

        arrowTip2[0].color  = _color;
        arrowTip2[1].color = _color;
	}

	inline void setArrowColor(sf::Color _color1, sf::Color _color2){
        arrow[0].color  = _color1;
        arrow[1].color = _color2;

        arrowTip1[0].color  = _color2;
        arrowTip1[1].color = _color2;

        arrowTip2[0].color  = _color2;
        arrowTip2[1].color = _color2;
	}

private:
	GameState_Play* gameState;

	sf::Text elapsedTurnsText;
	sf::Text messageLogText;
	sf::Text currentMessageText;
	sf::Text currentWeatherText;
	sf::Text currentTimeText;
	sf::Text saveText;
	sf::Text squareFormationText;
	sf::Text limberText;
	sf::Text lancerBonusReadyText;

	sf::RoundedRectangleShape generalRangeIndicator1;
	sf::RoundedRectangleShape generalRangeIndicator2;

	bool drawSquareFormationText{false};
	bool drawLimberText{false};
	bool drawLancerBonusReadyText{false};

    //generalRangeAnimationClock is responsible for the timing of the general range indicator's fading animation
	//generalRangeFadingOut is a toggle responsible for keeping track of whether it's currently fading in or out
	static sf::Clock generalRangeAnimationClock;
	static bool generalRangeFadingOut;

	sf::VertexArray arrow;
	sf::VertexArray arrowTip1;
	sf::VertexArray arrowTip2;

	//Due to the fact that terrain tiles are not drawn individually, but rather a vertex array is used for them,
	//we can't simply highlight the terrain tile. I've come up with a workaround to this by using a transparent
	//rectangle with an outline and setting its position to the mouseover-ed tile instead.

	//outlineAnimationClock and outlineFadingOut work similarly to generalRangeAnimationClock and generalRangeFadingOut
	static sf::Clock outlineAnimationClock;
	static bool outlineFadingOut;

	sf::RectangleShape pseudoOutline;
};

