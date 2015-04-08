#pragma once

#include "Infantry.h"

class LightInfantry : public Infantry
{
public:
	LightInfantry(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir);

	virtual int getMaxHp() const;
	virtual int getMaxMov() const;
	virtual int getMaxRange() const;

	virtual std::string rangedAttack(UnitTile* unit, int distance);

private:
	static const int maxhp{9};
	static const int maxMov{9};
	static const int maxRange{8};
};

