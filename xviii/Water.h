#pragma once

#include "TerrainTile.h"

class Water : public TerrainTile
{
public:
	Water(TextureManager& tm, sf::Vector2f _pos);
};

