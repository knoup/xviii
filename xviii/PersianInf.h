#pragma once

#include "Infantry.h"

class PersianInf : public Infantry
{
public:
	PersianInf(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir);

	inline virtual int getMaxHp() const{ return maxhp; };
	inline virtual int getMaxMov() const{ return maxMov; };

	virtual void preMeleeAttack(UnitTile* unit, bool attacking);

private:
	static const int maxhp{15};
	static const int maxMov{8};
};

