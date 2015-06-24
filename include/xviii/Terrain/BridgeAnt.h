#pragma once

#include "xviii/Terrain/Ant.h"

class BridgeAnt : public Ant
{
public:
	BridgeAnt(TerrainLoader& _terrainLoader, World& _world, int _lifetime);
	virtual void crawl();
protected:
};

