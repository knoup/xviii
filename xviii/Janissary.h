#pragma once

#include "Infantry.h"

//Same as Grenadier, for the moment

class Janissary : public Infantry
{
public:
	Janissary(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir);

	virtual int getMaxHp() const;
	virtual int getMaxMov() const;
	virtual int getMaxRange() const;

private:
	static const int maxhp{20};
	static const int maxMov{6};
	static const int maxRange{6};
};

