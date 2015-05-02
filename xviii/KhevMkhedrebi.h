#pragma once

#include "Cuirassier.h"

class KhevMkhedrebi : public Cuirassier
{
public:
	KhevMkhedrebi(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir);

	inline virtual int getMaxHp() const{ return maxhp; };
	inline virtual int getMaxMov() const{ return maxMov; };
	inline virtual int getMaxRange() const{ return maxRange; };

	//Inherits preMeleeAttack() from Cuirassier

private:
	static const int maxhp{12};
	static const int maxMov{12};
	static const int maxRange{0};
};

