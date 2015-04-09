#include "stdafx.h"
#include "Hills.h"


Hills::Hills(TextureManager& tm, sf::Vector2f _pos):
TerrainTile(tm, TextureManager::Terrain::HILLS, TerrainType::HILLS, _pos)
{
}