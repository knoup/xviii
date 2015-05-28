#include "stdafx.h"
#include "General.h"

#include "Player.h"

General::General(UnitLoader& _unitLoader, World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir) :
Cavalry(_unitLoader, _world, _mt19937, _belongsToPlayer, tm, fm, _dir, TextureManager::Unit::GEN, UnitType::GEN)
{
	mov = maxMov;
	hp = maxhp;
	/*
	rangedAttackDistValues.clear();
	rangedAttackDistValues.emplace_back(2, getMaxRange(), 0.5);

	healingRangeValues.clear();
	healingRangeValues.emplace_back(0, 0, 2);*/
}

void General::reset(){
	mov = maxMov;
	hasPartialRotated = false;
	hasFullRotated = false;
	hasMeleeAttacked = false;
	hasRangedAttacked = false;
	hasHealed = false;
	updateStats();
}

void General::takeDamage(UnitTile* attacker, float& _dmg, int distance){
	if (hp - _dmg < 0.4){
		for (auto& unit : player->getUnits()){
			if (unit.get() != this){
				//It is neither ranged nor melee, really, hence the 0
				float boilerplate{2};
				unit->takeDamage(attacker, boilerplate, 0);
			}
		}
	}

	UnitTile::takeDamage(attacker, _dmg, distance);
}