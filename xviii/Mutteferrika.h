#pragma once

#include "Dragoon.h"

class Mutteferrika : public Dragoon
{
public:
	Mutteferrika(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir);

	inline virtual int getMaxHp() const{ return maxhp; };
	inline virtual int getMaxMov() const{ return maxMov; };

private:
	static const int maxhp{12};
	static const int maxMov{14};
};

