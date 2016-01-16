#pragma once

#include "xviii/Terrain/Ant.h"

class RiverAnt : public Ant
{
public:
	RiverAnt(World* _world, int _lifetime);
	virtual void crawl();
protected:
	//Rivers keep track of their initial direction; they are more likely to
	//continue going on the in their starting direction
	int initialDirection;
};

