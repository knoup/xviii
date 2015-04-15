#pragma once

#include "Cuirassier.h"

class Kapikulu : public Cuirassier
{
public:
	Kapikulu(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir);

	inline virtual int getMaxHp() const{ return maxhp; };
	inline virtual int getMaxMov() const{ return maxMov; };
	inline virtual int getMaxRange() const{ return maxRange; };

	//Inherits preAttack() from Cuirassier

private:
	static const int maxhp{16};
	static const int maxMov{9};
	static const int maxRange{0};
};

