#pragma once

#include "TerrainTile.h"

//TODO

class Meadow : public TerrainTile
{
public:
	Meadow(TextureManager& tm, sf::Vector2f _pos);
	~Meadow();
};

