#include "xviii/Headers/stdafx.h"
#include "xviii/Terrain/Urban.h"


Urban::Urban(World& _world, TextureManager& tm, sf::Vector2f _pos) :
TerrainTile(_world, tm, TextureManager::Terrain::URBAN, TerrainType::URBAN, _pos)
{
}
