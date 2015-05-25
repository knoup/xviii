#pragma once

#include "Infantry.h"

//Essentially clones of regular infantry

class Dorunaby : public Infantry
{
public:
	Dorunaby(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir, TextureManager::Unit texType = TextureManager::Unit::GRE, UnitType uType = UnitType::GRE);

	inline virtual int getMaxHp() const{ return maxhp; };
	inline virtual int getMaxMov() const{ return maxMov; };

private:
	static const int maxhp{18};
	static const int maxMov{6};
};

