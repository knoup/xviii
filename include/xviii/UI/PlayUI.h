#pragma once

#include "xviii/UI/UI.h"

class GameState_Play;

class PlayUI : public UI
{
public:
	PlayUI(MasterManager& _masterManager, GameState_Play* _gameState);
	virtual ~PlayUI();
	void setElapsedTurnsText(int _num);
	void setCurrentMessageText(std::string _str);
	void setCurrentTimeText(std::pair<int,int> _time);
	void clearCurrentMessageText();
	void setSaveStatus(bool val);

	void turnlyUpdate();

	virtual void update();
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states = sf::RenderStates::Default) const;
private:
	GameState_Play* gameState;

	sf::Text elapsedTurnsText;
	sf::Text messageLogText;
	sf::Text currentMessageText;
	sf::Text currentTimeText;
	sf::Text saveText;
	sf::Text squareFormationText;
	sf::Text limberText;
	sf::Text lancerBonusReadyText;

	bool drawSquareFormationText{false};
	bool drawLimberText{false};
	bool drawLancerBonusReadyText{false};
};

