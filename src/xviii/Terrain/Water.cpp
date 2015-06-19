#include "xviii/Headers/stdafx.h"
#include "xviii/Terrain/Water.h"


Water::Water(TerrainLoader& _terrainLoader, World& _world, TextureManager& tm, sf::Vector2f _pos) :
TerrainTile(_terrainLoader, _world, tm, TextureManager::Terrain::WATER, TerrainType::WATER, _pos)
{
}
