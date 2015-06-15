#include "xviii/Headers/stdafx.h"
#include "xviii/Terrain/Water.h"


Water::Water(World& _world, TextureManager& tm, sf::Vector2f _pos) :
TerrainTile(_world, tm, TextureManager::Terrain::WATER, TerrainType::WATER, _pos)
{
}
