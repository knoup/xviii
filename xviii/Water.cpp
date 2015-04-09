#include "stdafx.h"
#include "Water.h"


Water::Water(TextureManager& tm, sf::Vector2f _pos) : 
TerrainTile(tm, TextureManager::Terrain::WATER, TerrainType::WATER, _pos)
{
}