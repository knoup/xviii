#include "stdafx.h"
#include "Woods.h"


Woods::Woods(TextureManager& tm, sf::Vector2f _pos) :
TerrainTile(tm, TextureManager::Terrain::WOODS, TerrainType::WOODS, _pos)
{
}