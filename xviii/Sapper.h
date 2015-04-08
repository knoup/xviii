#pragma once

#include "Infantry.h"

class Sapper : public Infantry
{
public:
	Sapper(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir);

	virtual int getMaxHp() const;
	virtual int getMaxMov() const;
	virtual int getMaxRange() const;

	virtual std::string rangedAttack(UnitTile* unit, int distance);

private:
	static const int maxhp{10};
	static const int maxMov{4};
	static const int maxRange{4};
};

