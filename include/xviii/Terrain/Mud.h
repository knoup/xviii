#pragma once

#include "xviii/Terrain/TerrainTile.h"

class Mud : public TerrainTile
{
public:
	Mud(TerrainLoader& _terrainLoader, World& _world, TextureManager& tm, sf::Vector2f _pos);
};

