#pragma once

#include "xviii/Core/Player.h"

#include "xviii/Core/UnitLoader.h"

class Scrollbar : public sf::Drawable
{
public:
    Scrollbar(const sf::RenderWindow& _targetWindow, sf::View& _targetView, sf::View& _backgroundView);
    //The copy constructor and = operator for this class have been disabled
	//Copy constructor
	Scrollbar(const Scrollbar&) = delete;
	//Operator=
	Scrollbar & operator=(const Scrollbar&) = delete;

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;

	//N.B.
	//The reason that the init function isn't integrated into the constructor is that,
	//in classes that use the scrollbar, totalMenuHeight won't always be known right away.
	//Additionally, several events (such as resizing the window) will require plenty
	//of parameters to be reset.

	void init(float _totalMenuHeight, float _initialXPos, float _firstElementPosition_y, float _firstElementHeight);

	inline void setActive(bool _v){active = _v;};
	inline void setDragging(bool _v){dragging = _v;};
	//inline void setTotalMenuHeight(float _f){totalMenuHeight = _f;};
	inline bool getActive() const{return active;};
	inline bool getDragging() const{return dragging;};
	//inline float getTotalMenuHeight() const{return totalMenuHeight;};

    inline sf::FloatRect getInnerGlobalBounds(){return innerRect.getGlobalBounds();};
    inline sf::FloatRect getOuterGlobalBounds(){return outerRect.getGlobalBounds();};

    void scroll(bool _down);
    void update(sf::Vector2i _mousePos);

private:
    float totalMenuHeight{0};

    const sf::RenderWindow& targetWindow;
    sf::View& targetView;
    sf::View& backgroundView;

    bool active{true};
    bool dragging{false};

    sf::RectangleShape innerRect{};
    sf::RectangleShape outerRect{};
};

