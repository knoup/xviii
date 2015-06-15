#pragma once

#include "xviii/Terrain/TerrainTile.h"

class Road : public TerrainTile
{
public:
	Road(World& _world, TextureManager& tm, sf::Vector2f _pos);
};

