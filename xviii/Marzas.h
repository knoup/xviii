#pragma once

#include "Cavalry.h"

class Marzas : public Cavalry
{
public:
	Marzas(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir);

	//Skirmisher
	inline virtual bool canSkirmish(){ return true; };

	inline virtual int getMaxHp() const{ return maxhp; };
	inline virtual int getMaxMov() const{ return maxMov; };
	inline virtual int getMaxRange() const{ return maxRange; };

private:
	static const int maxhp{10};
	static const int maxMov{12};
	static const int maxRange{8};
};
