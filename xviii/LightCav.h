#pragma once

#include "Cavalry.h"

class LightCav : public Cavalry
{
public:
	LightCav(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir, TextureManager::Unit texType = TextureManager::Unit::LCAV, UnitType uType = UnitType::LCAV);

	inline virtual int getMaxHp() const{ return maxhp; };
	inline virtual int getMaxMov() const{ return maxMov; };
	inline virtual int getMaxRange() const{ return maxRange; };

	virtual float getFlankModifier(UnitFamily _family, Modifier _flank) const;

private:
	static const int maxhp{8};
	static const int maxMov{15};
	static const int maxRange{0};
};

