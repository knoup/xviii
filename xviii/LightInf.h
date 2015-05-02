#pragma once

#include "Infantry.h"

class LightInf : public Infantry
{
public:
	LightInf(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir, TextureManager::Unit texType = TextureManager::Unit::LINF, UnitType uType = UnitType::LINF);

	inline virtual int getMaxHp() const{ return maxhp; };
	inline virtual int getMaxMov() const{ return maxMov; };
	inline virtual int getMaxRange() const{ return maxRange; };
	
	//Overloaded for the cone width of 3
	virtual int distanceFrom(TerrainTile* _terrain, bool& _validMovDirection, bool& _validAttackDirection, bool& _obstructionPresent, bool& _inMovementRange, bool& _inRangedAttackRange, bool canShootOverUnits = false, int coneWidth = 1);
	//Overloaded for Light Infantry's taking half damage on all ranged attacks
	virtual void takeDamage(float& _dmg, int distance);

	virtual std::string rangedAttack(UnitTile* unit, int distance);

	virtual void preMeleeAttack(UnitTile* unit, bool attacking);

private:
	static const int maxhp{9};
	static const int maxMov{9};
	static const int maxRange{8};
};

