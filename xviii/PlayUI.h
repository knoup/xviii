#pragma once

#include "UI.h"

class GameState_Play;

class PlayUI : public UI
{
public:
	PlayUI(GameState_Play* _gameState, TextureManager& _tm, FontManager& _fm);
	virtual ~PlayUI();
	void setElapsedTurnsText(int _num);
	void setCurrentMessageText(std::string _str);
	void clearCurrentMessageText();
	void setSaveStatus(bool val);
	virtual void update();
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states = sf::RenderStates::Default) const;
private:
	GameState_Play* gameState;

	sf::Text elapsedTurnsText;
	sf::Text messageLogText;
	sf::Text currentMessageText;
	sf::Text saveText;
	sf::Text squareFormationText;
	sf::Text limberText;

	bool drawSquareFormationText{false};
	bool drawLimberText{false};
};

