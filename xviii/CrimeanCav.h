#pragma once

#include "LightCav.h"

class CrimeanCav : public LightCav
{
public:
	CrimeanCav(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir);

	//Skirmisher
	inline virtual bool canSkirmish(){ return true; };

	inline virtual int getMaxHp() const{ return maxhp; };
	inline virtual int getMaxMov() const{ return maxMov; };

private:
	static const int maxhp{6};
	static const int maxMov{17};
};

