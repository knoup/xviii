#pragma once

#include "Cavalry.h"


class Cuirassier : public Cavalry
{
public:
	Cuirassier(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir, TextureManager::Unit texType = TextureManager::Unit::CUIR, UnitType uType = UnitType::CUIR);

	inline virtual int getMaxHp() const{ return maxhp; };
	inline virtual int getMaxMov() const{ return maxMov; };
	inline virtual int getMaxRange() const{ return maxRange; };

	virtual float getFlankModifier(UnitFamily _family, Modifier _flank) const;

	virtual void preMeleeAttack(UnitTile* unit, bool attacking);

private:
	static const int maxhp{15};
	static const int maxMov{9};
	static const int maxRange{0};
};

