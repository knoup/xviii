#pragma once

#include "LightCav.h"

class DonCossack : public LightCav
{
public:
	DonCossack(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir);

	virtual int getMaxHp() const;
	virtual int getMaxMov() const;
	virtual int getMaxRange() const;

private:
	static const int maxhp{9};
	static const int maxMov{17};
	static const int maxRange{0};
};

