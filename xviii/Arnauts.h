#pragma once

#include "LightInf.h"

class Arnauts : public LightInf
{
public:
	Arnauts(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir);

	inline virtual int getMaxHp() const{ return maxhp; };
	inline virtual int getMaxMov() const{ return maxMov; };
	inline virtual int getMaxRange() const{ return maxRange; };

private:
	static const int maxhp{8};
	static const int maxMov{8};
	static const int maxRange{8};
};

