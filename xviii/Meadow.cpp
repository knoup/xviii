#include "stdafx.h"
#include "Meadow.h"


Meadow::Meadow(World* _world, TextureManager& tm, sf::Vector2f _pos) :
TerrainTile(_world, tm, TextureManager::Terrain::MEADOW, TerrainType::MEADOW, _pos)
{
}
