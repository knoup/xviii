#pragma once

#include "xviii/Core/World.h"

/*
This is the "generic ant" - it generates random clusters of certain tiles, and for
this reason is best suited for MUD, URBAN, WOODS, and MEADOW. It can be used for
WATER to generate small lakes as well.
*/

class TerrainLoader;

class Ant
{
public:
	Ant(World* _world, TerrainTile::TerrainType _type, int _lifetime);
    //The copy constructor and = operator for this class have been disabled
	//Copy constructor
	Ant(const Ant&) = delete;
	//Operator=
	Ant & operator=(const Ant&) = delete;
	virtual ~Ant();
	virtual void crawl();
protected:
	virtual void increment(int dir, sf::Vector2i& cartesianCoords);

	World* world;
	TerrainTile::TerrainType type;
	int lifetime;
	int currentIndex;
};

