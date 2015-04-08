#pragma once

#include "Cavalry.h"

class CrimeanCav : public Cavalry
{
public:
	CrimeanCav(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir);

	//Overloaded due to Crimean Cav's ability to fully rotate after firing, and have 2 movement points left over
	virtual std::string CrimeanCav::rotate(UnitTile::Direction _dir);

	virtual int getMaxHp() const;
	virtual int getMaxMov() const;
	virtual int getMaxRange() const;

	virtual std::string CrimeanCav::rangedAttack(UnitTile* unit, int distance);

	virtual float getFlankModifier(UnitFamily _family, Modifier _flank) const;

private:
	static const int maxhp{7};
	static const int maxMov{17};
	static const int maxRange{8};
};

