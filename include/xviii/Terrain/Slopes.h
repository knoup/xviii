#pragma once

#include "xviii/Terrain/TerrainTile.h"

class Slopes : public TerrainTile
{
public:
	Slopes(World& _world, TextureManager& tm, sf::Vector2f _pos);
};

