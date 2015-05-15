#pragma once

#include "Cavalry.h"

class Dragoon : public Cavalry
{
public:
	Dragoon(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir, TextureManager::Unit texType = TextureManager::Unit::DRAG, UnitType uType = UnitType::DRAG);

	inline virtual int getMaxHp() const{ return maxhp; };
	inline virtual int getMaxMov() const{ return maxMov; };
	inline virtual int getMaxRange() const{ return maxRange; };

	virtual float getFlankModifier(UnitFamily _family, Modifier _flank) const;

private:
	static const int maxhp{10};
	static const int maxMov{12};
	static const int maxRange{5};
};



