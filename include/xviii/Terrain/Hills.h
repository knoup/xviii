#pragma once

#include "xviii/Terrain/TerrainTile.h"

class Hills : public TerrainTile
{
public:
	Hills(World& _world, TextureManager& tm, sf::Vector2f _pos);
};

