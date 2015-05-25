#pragma once

#include "Grenadier.h"

class Janissary : public Grenadier
{
public:
	Janissary(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir);

	inline virtual int getMaxHp() const{ return maxhp; };
	inline virtual int getMaxMov() const{ return maxMov; };

private:
	static const int maxhp{20};
	static const int maxMov{6};
};

