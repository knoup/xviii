#pragma once

#include "TerrainTile.h"

class Water : public TerrainTile
{
public:
	Water(World* _world, TextureManager& tm, sf::Vector2f _pos);
};

