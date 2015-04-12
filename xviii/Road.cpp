#include "stdafx.h"
#include "Road.h"


Road::Road(World* _world, TextureManager& tm, sf::Vector2f _pos) :
TerrainTile(_world, tm, TextureManager::Terrain::ROAD, TerrainType::ROAD, _pos)
{
}
