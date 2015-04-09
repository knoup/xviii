#include "stdafx.h"
#include "Meadow.h"


Meadow::Meadow(TextureManager& tm, sf::Vector2f _pos) : 
TerrainTile(tm, TextureManager::Terrain::MEADOW, TerrainType::MEADOW, _pos)
{
}
