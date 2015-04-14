#pragma once

#include "Cavalry.h"

class PitsisKatsebi : public Cavalry
{
public:
	PitsisKatsebi(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir);

	virtual int getMaxHp() const;
	virtual int getMaxMov() const;
	virtual int getMaxRange() const;

	virtual std::string rangedAttack(UnitTile* unit, int distance);

	virtual float getFlankModifier(UnitFamily _family, Modifier _flank) const;

private:
	static const int maxhp{14};
	static const int maxMov{12};
	static const int maxRange{5};
};

