#pragma once

#include "Cuirassier.h"

class Curci : public Cuirassier
{
public:
	Curci(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir);

	inline virtual int getMaxHp() const{ return maxhp; };
	inline virtual int getMaxMov() const{ return maxMov; };
	inline virtual int getMaxRange() const{ return maxRange; };

	//Overrides Cuirassier's preAttack() with blank entry
	inline virtual void preMeleeAttack(UnitTile* unit, bool attacking){};

private:
	static const int maxhp{13};
	static const int maxMov{9};
	static const int maxRange{8};
};

