#include "xviii/Headers/stdafx.h"
#include "xviii/Terrain/Urban.h"

#include "xviii/Units/UnitTile.h"

Urban::Urban(TerrainLoader& _terrainLoader, World& _world, TextureManager& tm, sf::Vector2f _pos) :
TerrainTile(_terrainLoader, _world, tm, TextureManager::Terrain::URBAN, TerrainType::URBAN, _pos)
{
}
