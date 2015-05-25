#pragma once

#include "Cuirassier.h"

class PitsisKatsebi : public Cuirassier
{
public:
	PitsisKatsebi(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir);

	inline virtual int getMaxHp() const{ return maxhp; };
	inline virtual int getMaxMov() const{ return maxMov; };

	//Override Cuirassier's preMeleeAttack() with blank function
	virtual void preMeleeAttack(UnitTile* unit, bool attacking){};

private:
	static const int maxhp{14};
	static const int maxMov{12};
};

