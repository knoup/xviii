#pragma once

#include "LightInf.h"

class Vitae : public LightInf
{
public:
	Vitae(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir);

	inline virtual int getMaxHp() const{ return maxhp; };
	inline virtual int getMaxMov() const{ return maxMov; };
	inline virtual int getMaxRange() const{ return maxRange; };

private:
	static const int maxhp{9};
	static const int maxMov{8};
	static const int maxRange{8};
};

