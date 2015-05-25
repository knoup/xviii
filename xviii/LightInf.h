#pragma once

#include "Infantry.h"

class LightInf : public Infantry
{
public:
	LightInf(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir, TextureManager::Unit texType = TextureManager::Unit::LINF, UnitType uType = UnitType::LINF);

	//Determines whether the unit can skirmish or not (skirmishing gives the ability to fully rotate after firing, and have 2 movement points left over)
	inline virtual bool canSkirmish(){ return true; };

	inline virtual int getMaxHp() const{ return maxhp; };
	inline virtual int getMaxMov() const{ return maxMov; };
	
	//Overloaded for the cone width of 3
	virtual sf::Vector2i distanceFrom(TerrainTile* _terrain, bool& _validMovDirection, bool& _validAttackDirection, bool& _obstructionPresent, bool& _inMovementRange, bool& _inRangedAttackRange, bool canShootOverUnits = false, int coneWidth = 1);
	//Overloaded for Light Infantry's taking half damage on all ranged attacks
	virtual void takeDamage(UnitTile* attacker, float& _dmg, int distance);

	virtual void preMeleeAttack(UnitTile* unit, bool attacking);

private:
	static const int maxhp{9};
	static const int maxMov{9};
};

