#pragma once

#include "Ant.h"

class RiverAnt : public Ant
{
public:
	RiverAnt(World* _world, int _lifetime);
	virtual void crawl();
protected:
	//Rivers keep track of their own direction, as they are more likely to 
	//continue going on the last direction
	int lastDirection;
};

