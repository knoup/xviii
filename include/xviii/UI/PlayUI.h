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

	void setDrawGeneralRangeIndicator(bool _v){drawGeneralRangeIndicator = _v;};
	bool getDrawGeneralRangeIndicator(){return drawGeneralRangeIndicator;};

	void turnlyUpdate();

	virtual void update();
    //playUI.draw() automatically changes views in order to draw what it needs to.
    //Keep this in mind, and always reset the view after calling it.
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states = sf::RenderStates::Default) const;

    //This function purposely doesn't alter the arrow's alpha value
    inline void setArrowColor(sf::Color _color){
        arrow[0].color.r  = _color.r;
        arrow[0].color.g  = _color.g;
        arrow[0].color.b  = _color.b;

        arrow[1].color.r  = _color.r;
        arrow[1].color.g  = _color.g;
        arrow[1].color.b  = _color.b;

        arrowTip1[0].color.r  = _color.r;
        arrowTip1[0].color.g  = _color.g;
        arrowTip1[0].color.b  = _color.b;

        arrowTip1[1].color.r  = _color.r;
        arrowTip1[1].color.g  = _color.g;
        arrowTip1[1].color.b  = _color.b;

        arrowTip2[0].color.r  = _color.r;
        arrowTip2[0].color.g  = _color.g;
        arrowTip2[0].color.b  = _color.b;

        arrowTip2[1].color.r  = _color.r;
        arrowTip2[1].color.g  = _color.g;
        arrowTip2[1].color.b  = _color.b;
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
	bool drawGeneralRangeIndicator{false};

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

	//Note that these are also used to animate the arrow.
	static sf::Clock outlineAnimationClock;
	static bool outlineFadingOut;

	sf::RectangleShape pseudoOutline;
};

