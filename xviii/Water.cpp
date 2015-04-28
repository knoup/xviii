#include "stdafx.h"
#include "Water.h"


Water::Water(World* _world, TextureManager& tm, sf::Vector2f _pos) :
TerrainTile(_world, tm, TextureManager::Terrain::WATER, TerrainType::WATER, _pos)
{
}