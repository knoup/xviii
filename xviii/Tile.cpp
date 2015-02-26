#include "stdafx.h"
#include "Tile.h"

/*
Be sure to initialise selected as false! The draw function is set to
only draw the rectangles if selected is set to true (to give a selected effect);
drawing all the rects induces MASSIVE lag
*/
Tile::Tile(TextureManager& tm, TextureManager::Terrain type) :
sprite{tm.getSprite(type)},
highlighted{false}
{
	rekt.setPosition(sprite.getPosition().x, sprite.getPosition().y);
	rekt.setSize(sf::Vector2f(tm.getSize().x, tm.getSize().y));
	rekt.setOutlineColor(sf::Color::Yellow);
	rekt.setOutlineThickness(-1);
	rekt.setFillColor(sf::Color::Transparent);
}

//Overloaded for both unit and terrain

Tile::Tile(TextureManager& tm, TextureManager::Unit type) :
sprite{tm.getSprite(type)},
highlighted{false}
{
	rekt.setPosition(sprite.getPosition().x, sprite.getPosition().y);
	rekt.setSize(sf::Vector2f(tm.getSize().x, tm.getSize().y));
	rekt.setOutlineColor(sf::Color::Yellow);
	rekt.setOutlineThickness(-1);
	rekt.setFillColor(sf::Color::Transparent);
}

Tile::~Tile(){

}

void Tile::setHighlightColor(sf::Color _color){
	rekt.setOutlineColor(_color);
}

void Tile::setHighlighted(bool _value){
	highlighted = _value;
}

void Tile::resetHighlightedColor(){
	rekt.setOutlineColor(sf::Color::Yellow);
}

int Tile::top() const{
	return sprite.getPosition().y;
}

int Tile::left() const{
	return sprite.getPosition().x;
}

int Tile::bottom() const{
	return sprite.getPosition().y + sprite.getLocalBounds().height;
}

int Tile::right() const {
	return sprite.getPosition().x + sprite.getLocalBounds().width;
}

void Tile::draw(sf::RenderTarget &target, sf::RenderStates states) const{
	target.draw(sprite);
}

