#pragma once

#include "TerrainTile.h"

class Urban : public TerrainTile
{
public:
	Urban(World* _world, TextureManager& tm, sf::Vector2f _pos);
};

