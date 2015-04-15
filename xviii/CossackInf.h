#pragma once

#include "Infantry.h"

class CossackInf : public Infantry
{
public:
	CossackInf(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir);

	virtual int getMaxHp() const;
	virtual int getMaxMov() const;
	virtual int getMaxRange() const;

	virtual void preAttack(UnitTile* unit, bool attacking);

private:
	static const int maxhp{17};
	static const int maxMov{7};
	static const int maxRange{6};
};

