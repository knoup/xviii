#include "stdafx.h"
#include "Woods.h"


Woods::Woods(World* _world, TextureManager& tm, sf::Vector2f _pos) :
TerrainTile(_world, tm, TextureManager::Terrain::WOODS, TerrainType::WOODS, _pos)
{
}