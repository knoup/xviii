#include "xviii/Headers/stdafx.h"
#include "xviii/Core/Tile.h"

#include "xviii/Core/World.h"

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

sf::Vector2i Tile::getCartesianPos() const{
	//N.B.
	//In the interest of keeping this function const, I used this
	return world.cartesianPosAtIndex(world.indexAtPixelPos(sf::Vector2i{left(), top()}));
	//Instead of this:
	//Tile* ptr = this;
	//return world.cartesianPosAtIndex(world.indexAtPixelPos(world.indexAtTile(this)));
}

sf::Vector2f Tile::getPixelPos() const{
	return sprite.getPosition();
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

