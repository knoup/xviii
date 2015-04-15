#pragma once

#include "Cuirassier.h"

class Kapikulu : public Cuirassier
{
public:
	Kapikulu(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir);

	virtual int getMaxHp() const;
	virtual int getMaxMov() const;
	virtual int getMaxRange() const;

	//Inherits preAttack() from Cuirassier

private:
	static const int maxhp{16};
	static const int maxMov{9};
	static const int maxRange{0};
};

