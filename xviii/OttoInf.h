#pragma once

#include "Infantry.h"

class OttoInf : public Infantry
{
public:
	OttoInf(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir);

	virtual int getMaxHp() const;
	virtual int getMaxMov() const;
	virtual int getMaxRange() const;

	virtual void preAttack(UnitTile* unit, bool attacking);

private:
	static const int maxhp{15};
	static const int maxMov{8};
	static const int maxRange{6};
};

