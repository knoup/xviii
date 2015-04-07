#pragma once

#include "Cavalry.h"

class LightCav : public Cavalry
{
public:
	LightCav(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir);

	virtual int getMaxHp() const;
	virtual int getMaxMov() const;
	virtual int getMaxRange() const;

	virtual float getFlankModifier(UnitFamily _family, Modifier _flank) const;

private:
	static const int maxhp{9};
	static const int maxMov{15};
	static const int maxRange{0};
};

