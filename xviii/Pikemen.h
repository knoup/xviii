#pragma once

#include "Infantry.h"

class Pikemen : public Infantry
{
public:
	Pikemen(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir, TextureManager::Unit texType = TextureManager::Unit::PIKE, UnitType uType = UnitType::PIKE);

	inline virtual int getMaxHp() const{ return maxhp; };
	inline virtual int getMaxMov() const{ return maxMov; };
	inline virtual int getMaxRange() const{ return maxRange; };

	virtual void preMeleeAttack(UnitTile* unit, bool attacking);

private:
	static const int maxhp{12};
	static const int maxMov{4};
	static const int maxRange{0};	
};

