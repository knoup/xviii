#include "stdafx.h"
#include "Mud.h"


Mud::Mud(World* _world, TextureManager& tm, sf::Vector2f _pos) :
TerrainTile(_world, tm, TextureManager::Terrain::MUD, TerrainType::MUD, _pos)
{
}