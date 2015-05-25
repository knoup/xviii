#pragma once

#include "Cavalry.h"

//At the moment, essentially a clone of the Timarioti

class Courtin : public Cavalry
{
public:
	Courtin(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir);

	inline virtual int getMaxHp() const{ return maxhp; };
	inline virtual int getMaxMov() const{ return maxMov; };

private:
	static const int maxhp{9};
	static const int maxMov{14};
};
