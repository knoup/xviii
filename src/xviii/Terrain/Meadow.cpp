#include "xviii/Headers/stdafx.h"
#include "xviii/Terrain/Meadow.h"


Meadow::Meadow(World& _world, TextureManager& tm, sf::Vector2f _pos) :
TerrainTile(_world, tm, TextureManager::Terrain::MEADOW, TerrainType::MEADOW, _pos)
{
}
