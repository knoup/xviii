#include "stdafx.h"
#include "Urban.h"


Urban::Urban(TextureManager& tm, sf::Vector2f _pos) :
TerrainTile(tm, TextureManager::Terrain::URBAN, TerrainType::URBAN, _pos)
{
}
