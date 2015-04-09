#include "stdafx.h"
#include "Road.h"


Road::Road(TextureManager& tm, sf::Vector2f _pos) :
TerrainTile(tm, TextureManager::Terrain::ROAD, TerrainType::ROAD, _pos)
{
}
