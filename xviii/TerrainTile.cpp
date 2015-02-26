#include "stdafx.h"
#include "TerrainTile.h"


//Terain tiles don't really need a textured sprite, but we still need the sprite
//for locational information. I'll initialise the sprites as terrain anyway, but
//we won't be drawing them directly (but rather using vertex arrays; see world.cpp)

TerrainTile::TerrainTile(TextureManager& tm, TerrainType type, sf::Vector2f _pos) :
Tile{tm, TextureManager::Terrain::MEADOW},
terrainType{type}
{
	sprite.setPosition(_pos);
}

void TerrainTile::setPos(sf::Vector2f _pos){
	sprite.setPosition(_pos);
}


sf::Vector2f TerrainTile::getPos() const{
	return sprite.getPosition();
}

void TerrainTile::draw(sf::RenderTarget &target, sf::RenderStates states) const{
	target.draw(sprite, states);
}

TerrainTile::~TerrainTile(){
}
