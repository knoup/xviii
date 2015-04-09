#include "stdafx.h"
#include "Slopes.h"


Slopes::Slopes(TextureManager& tm, sf::Vector2f _pos):
TerrainTile(tm, TextureManager::Terrain::SLOPES, TerrainType::SLOPES, _pos)
{
}
