#include "stdafx.h"
#include "Tile.h"


Tile::Tile(TextureManager& tm, TextureManager::Terrain type) :
sprite{tm.getSprite(type)},
highlighted{false}
{
}

Tile::Tile(TextureManager& tm, TextureManager::Unit type) :
sprite{tm.getSprite(type)},
highlighted{false}
{
}

Tile::~Tile(){
}

void Tile::setHighlighted(bool _value){
	highlighted = _value;
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

