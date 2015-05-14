#pragma once

#include "Cavalry.h"

class Timarioti : public Cavalry
{
public:
	Timarioti(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir);

	//Skirmisher
	virtual bool canSkirmish(){ return true; };

	inline virtual int getMaxHp() const{ return maxhp; };
	inline virtual int getMaxMov() const{ return maxMov; };
	inline virtual int getMaxRange() const{ return maxRange; };

	virtual std::string rangedAttack(UnitTile* unit, int distance);

private:
	static const int maxhp{11};
	static const int maxMov{14};
	static const int maxRange{8};
};
