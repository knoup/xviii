#include "stdafx.h"
#include "Hills.h"


Hills::Hills(World* _world, TextureManager& tm, sf::Vector2f _pos) :
TerrainTile(_world, tm, TextureManager::Terrain::HILLS, TerrainType::HILLS, _pos)
{
}