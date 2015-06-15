#pragma once

#include "xviii/Terrain/TerrainTile.h"

class Meadow : public TerrainTile
{
public:
	Meadow(World& _world, TextureManager& tm, sf::Vector2f _pos);
};
