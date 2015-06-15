#pragma once

#include "xviii/Terrain/TerrainTile.h"

class Water : public TerrainTile
{
public:
	Water(World& _world, TextureManager& tm, sf::Vector2f _pos);
};

