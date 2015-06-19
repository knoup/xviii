#include "xviii/Headers/stdafx.h"
#include "xviii/Terrain/Hills.h"


Hills::Hills(TerrainLoader& _terrainLoader, World& _world, TextureManager& tm, sf::Vector2f _pos) :
TerrainTile(_terrainLoader, _world, tm, TextureManager::Terrain::HILLS, TerrainType::HILLS, _pos)
{
}
