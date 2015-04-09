#pragma once

#include "TerrainTile.h"

class Mud : public TerrainTile
{
public:
	Mud(TextureManager& tm, sf::Vector2f _pos);
};

