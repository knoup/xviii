#pragma once

#include "Infantry.h"

class Grenadier : public Infantry
{
public:
	Grenadier(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir, TextureManager::Unit texType = TextureManager::Unit::GRE, UnitType uType = UnitType::GRE);

	inline virtual int getMaxHp() const{ return maxhp; };
	inline virtual int getMaxMov() const{ return maxMov; };
	inline virtual int getMaxRange() const{ return maxRange; };

private:
	static const int maxhp{20};
	static const int maxMov{6};
	static const int maxRange{6};	
};

