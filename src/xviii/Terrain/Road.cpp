#include "xviii/Headers/stdafx.h"
#include "xviii/Terrain/Road.h"


Road::Road(TerrainLoader& _terrainLoader, World& _world, TextureManager& tm, sf::Vector2f _pos) :
TerrainTile(_terrainLoader, _world, tm, TextureManager::Terrain::ROAD, TerrainType::ROAD, _pos)
{
}
