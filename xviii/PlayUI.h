#pragma once

#include "UI.h"

class PlayUI : public UI
{
public:
	PlayUI(TextureManager& _tm, FontManager& _fm);
	virtual ~PlayUI();
	void setElapsedTurnsText(int _num);
	void setCurrentMessageText(std::string _str);
	void clearCurrentMessageText();
	void setSaveStatus(bool val);
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states = sf::RenderStates::Default) const;
private:
	sf::Text elapsedTurnsText;
	sf::Text messageLogText;
	sf::Text currentMessageText;
	sf::Text saveText;
};

