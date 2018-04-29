#include "xviii/Headers/stdafx.h"
#include "xviii/UI/Scrollbar.h"

Scrollbar::Scrollbar(const sf::RenderWindow& _targetWindow, sf::View& _targetView, sf::View& _backgroundView) :
    targetWindow{_targetWindow},
    targetView{_targetView},
    backgroundView{_backgroundView}
{
}

void Scrollbar::init(float _totalMenuHeight, float _initialXPos, float _firstElementPosition_y, float _firstElementHeight, sf::Color _fillColor){
    totalMenuHeight = _totalMenuHeight;

    if(active){
		outerRect.setSize({20, targetView.getSize().y});
		outerRect.setPosition(_initialXPos, targetView.getViewport().top * backgroundView.getSize().y);
		outerRect.setFillColor(sf::Color::Transparent);
		outerRect.setOutlineThickness(2);
		outerRect.setOutlineColor(sf::Color::White);

		innerRect.setPosition(outerRect.getPosition());
		innerRect.setFillColor(_fillColor);

		float outerRect_height = outerRect.getGlobalBounds().height;

		float finalRatio = totalMenuHeight / outerRect_height;


		float innerRect_height{targetView.getCenter().y - _firstElementPosition_y - _firstElementHeight / 2};

		innerRect_height/= finalRatio;
		innerRect_height*= 2;

		innerRect.setSize({float(outerRect.getSize().x), innerRect_height});
	}
	else{
		outerRect.setFillColor(sf::Color::Transparent);
		outerRect.setOutlineColor(sf::Color::Transparent);
		outerRect.setFillColor(sf::Color::Transparent);
		outerRect.setOutlineColor(sf::Color::Transparent);
	}
}

void Scrollbar::draw(sf::RenderTarget &target, sf::RenderStates states) const{
	target.draw(outerRect, states);
	target.draw(innerRect, states);
}

void Scrollbar::scroll(bool _down){
    float step{float(outerRect.getGlobalBounds().height * 0.07)};

	float distanceFromTop{innerRect.getPosition().y - outerRect.getPosition().y};

	float distanceFromBottom
	{
		(outerRect.getPosition().y + outerRect.getGlobalBounds().height - outerRect.getOutlineThickness() * 2)
		-
		(innerRect.getPosition().y + innerRect.getGlobalBounds().height)
	};

	if(!_down){
		if(distanceFromTop > 0){
			if(step > distanceFromTop){
				step = distanceFromTop;
			}
			innerRect.setPosition(innerRect.getPosition().x, innerRect.getPosition().y - step);
		}
	}
	else{
		if(distanceFromBottom > 0){
			if(step > distanceFromBottom){
				step = distanceFromBottom;
			}
			innerRect.setPosition(innerRect.getPosition().x, innerRect.getPosition().y + step);
		}
	}
}

void Scrollbar::update(sf::Vector2i _mousePos){
    if(!active){
        return;
    }

    float outerRect_top = outerRect.getPosition().y;
    float outerRect_bottom = outerRect_top + outerRect.getGlobalBounds().height - (outerRect.getOutlineThickness() * 2);

    float innerRect_center_y{innerRect.getPosition().y + innerRect.getGlobalBounds().height / 2};

    float innerRect_distanceFromTop{innerRect_center_y - outerRect_top};

    float outerRect_height = outerRect_bottom - outerRect_top;

    float finalRatio = totalMenuHeight / outerRect_height;

    float finalY = (finalRatio * (innerRect_distanceFromTop));

    targetView.setCenter(targetView.getCenter().x, finalY);

    if(dragging){
        sf::Vector2f mousePos{targetWindow.mapPixelToCoords(_mousePos, backgroundView)};

        float newYPos{mousePos.y - innerRect.getGlobalBounds().height / 2};

        float newTop{newYPos};
        float newBottom{mousePos.y + innerRect.getGlobalBounds().height / 2};

        if(newTop <  outerRect_top){
            newYPos = outerRect_top;
        }

        else if(newBottom > outerRect_bottom){
            newYPos = outerRect_bottom - innerRect.getGlobalBounds().height;
        }

        innerRect.setPosition(innerRect.getPosition().x, newYPos);

    }
}
