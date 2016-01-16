#pragma once

#include "xviii/Terrain/Ant.h"

class BridgeAnt : public Ant
{
public:
	BridgeAnt(World* _world, int _lifetime);
	virtual void crawl();
protected:
};

