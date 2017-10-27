#pragma once

#include "xviii/UI/UI.h"

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

	sf::RectangleShape generalRangeIndicator1;
	sf::RectangleShape generalRangeIndicator2;

	bool drawSquareFormationText{false};
	bool drawLimberText{false};
	bool drawLancerBonusReadyText{false};
};

