#pragma once

#include "TerrainTile.h"

class Road : public TerrainTile
{
public:
	Road(TextureManager& tm, sf::Vector2f _pos);
};
