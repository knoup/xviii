#pragma once

#include "World.h"

/*
This is the "generic ant" - it generates random clusters of certain tiles, and for
this reason is best suited for MUD, URBAN, WOODS, and MEADOW. It can be used for 
WATER to generate small lakes as well.
*/

class Ant 
{
public:
	Ant(World* _world, TerrainTile::TerrainType _type, int _lifetime);
	virtual void crawl();
protected:
	virtual void increment(int dir, sf::Vector2i& cartesianCoords);

	World* world;
	TerrainTile::TerrainType type;
	int lifetime;
	int currentIndex;
};

