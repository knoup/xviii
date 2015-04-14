#pragma once

#include "Dragoon.h"

class AbrMkhedrebi : public Dragoon
{
public:
	AbrMkhedrebi(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir);

	//Overloaded due to Abragi Mkhedrebi's ability to fully rotate after firing, and have 2 movement points left over
	virtual std::string AbrMkhedrebi::rotate(UnitTile::Direction _dir);

	virtual int getMaxHp() const;
	virtual int getMaxMov() const;
	virtual int getMaxRange() const;

private:
	static const int maxhp{8};
	static const int maxMov{12};
	static const int maxRange{5};
};

