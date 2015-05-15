#include "stdafx.h"
#include "LightInf.h"


LightInf::LightInf(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir, TextureManager::Unit texType, UnitType uType) :
Infantry(_world, _mt19937, _belongsToPlayer, tm, fm, _dir, texType, uType)
{
	mov = maxMov;
	hp = maxhp;
	
	//Since Light Inf is somewhat of a special case when it comes to unit families, I will just change its
	//family type in the constructor
	unitFamilyType = UnitFamily::LINF_FAMILY;

	rangedAttackDistValues.clear();
	rangedAttackDistValues.emplace_back(7, 8, 0.5);
	rangedAttackDistValues.emplace_back(3, 6, 1);
	rangedAttackDistValues.emplace_back(2, 2, 1.5);
}

void LightInf::takeDamage(UnitTile* attacker, float& _dmg, int distance){
	if (distance > 1){
		_dmg /= 2.f;
	}

	UnitTile::takeDamage(attacker, _dmg, distance);
}

sf::Vector2i LightInf::distanceFrom(TerrainTile* _terrain, bool& _validMovDirection, bool& _validAttackDirection, bool& _obstructionPresent, bool& _inMovementRange, bool& _inRangedAttackRange, bool canShootOverUnits, int coneWidth){
	return UnitTile::distanceFrom(_terrain, _validMovDirection, _validAttackDirection, _obstructionPresent, _inMovementRange, _inRangedAttackRange, false, 3);
}

void LightInf::preMeleeAttack(UnitTile* unit, bool attacking){
	this->modVector.emplace_back(Modifier::ADDITIONAL, -2);
}