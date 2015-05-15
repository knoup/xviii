#pragma once

#include "Infantry.h"

class Azaps : public Infantry
{
public:
	Azaps(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir, TextureManager::Unit texType = TextureManager::Unit::IRR, UnitType uType = UnitType::AZAP);

	inline virtual int getMaxHp() const{ return maxhp; };
	inline virtual int getMaxMov() const{ return maxMov; };
	inline virtual int getMaxRange() const{ return maxRange; };

	//Override LightInf's preMeleeAttack that gives -2 in melee combat with a blank declaration
	virtual void preMeleeAttack(UnitTile* unit, bool attacking){};

private:
	static const int maxhp{6};
	static const int maxMov{9};
	static const int maxRange{6};
};

