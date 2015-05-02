#include "stdafx.h"
#include "Tile.h"

#include "World.h"

Tile::Tile(World& _world, TextureManager& tm, TextureManager::Terrain type) :
world(_world),
sprite{tm.getSprite(type)},
highlighted{false}
{
}

Tile::Tile(World& _world, TextureManager& tm, TextureManager::Unit type) :
world(_world),
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

