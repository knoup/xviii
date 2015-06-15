#include "xviii/Headers/stdafx.h"
#include "xviii/Terrain/Slopes.h"


Slopes::Slopes(World& _world, TextureManager& tm, sf::Vector2f _pos) :
TerrainTile(_world, tm, TextureManager::Terrain::SLOPES, TerrainType::SLOPES, _pos)
{
}
