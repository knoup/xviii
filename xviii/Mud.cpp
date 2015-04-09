#include "stdafx.h"
#include "Mud.h"


Mud::Mud(TextureManager& tm, sf::Vector2f _pos):
TerrainTile(tm, TextureManager::Terrain::MUD, TerrainType::MUD, _pos)
{
}