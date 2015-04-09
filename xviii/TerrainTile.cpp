#include "stdafx.h"
#include "TerrainTile.h"


TerrainTile::TerrainTile(TextureManager& tm, TextureManager::Terrain textType, TerrainType terrainType, sf::Vector2f _pos) :
Tile{tm, textType},
terrainType{terrainType}
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
