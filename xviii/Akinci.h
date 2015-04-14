#pragma once

#include "LightCav.h"

class Akinci : public LightCav
{
public:
	Akinci(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir);

	virtual int getMaxHp() const;
	virtual int getMaxMov() const;
	virtual int getMaxRange() const; 

	virtual std::string rangedAttack(UnitTile* unit, int distance);

private:
	static const int maxhp{7};
	static const int maxMov{16};
	static const int maxRange{8};
};

