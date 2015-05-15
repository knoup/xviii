#pragma once

#include "Lancer.h"

class Gul : public Lancer
{
public:
	Gul(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir);

	//Frightening
	inline virtual bool frightening(){ return true; };

	inline virtual int getMaxHp() const{ return maxhp; };
	inline virtual int getMaxMov() const{ return maxMov; };
	inline virtual int getMaxRange() const{ return maxRange; };

private:
	static const int maxhp{10};
	static const int maxMov{12};
	static const int maxRange{0};
};

