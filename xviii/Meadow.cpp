#include "stdafx.h"
#include "Meadow.h"

//TODO

Meadow::Meadow(TextureManager& tm, sf::Vector2f _pos) :
TerrainTile{tm, TerrainType::MEADOW, _pos}
{
}


Meadow::~Meadow()
{
}
