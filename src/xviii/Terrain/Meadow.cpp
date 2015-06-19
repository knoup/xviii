#include "xviii/Headers/stdafx.h"
#include "xviii/Terrain/Meadow.h"


Meadow::Meadow(TerrainLoader& _terrainLoader, World& _world, TextureManager& tm, sf::Vector2f _pos) :
TerrainTile(_terrainLoader, _world, tm, TextureManager::Terrain::MEADOW, TerrainType::MEADOW, _pos)
{
}
