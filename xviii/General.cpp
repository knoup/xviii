#include "stdafx.h"
#include "General.h"

#include "Player.h"

General::General(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir) :
Cavalry(_world, _mt19937, _belongsToPlayer, tm, fm, _dir, TextureManager::Unit::GEN, UnitType::GEN)
{
	mov = maxMov;
	hp = maxhp;

	rangedAttackDistValues.clear();
	rangedAttackDistValues.emplace_back(2, getMaxRange(), 0.5);
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

std::string General::interactWithFriendly(UnitTile* _unit){
	if (_unit == this){
		return CANNOT_HEAL_SELF;
	}
	else if (hasHealed){
		return ALREADY_HEALED;
	}
	else if (_unit->gethp() == _unit->getMaxHp()){
		return AT_MAX_HP;
	}
	else {
		float hp = _unit->gethp();
		float max = _unit->getMaxHp();
		float diff = max - hp;

		hasHealed = true;

		if (diff >= 2){
			return _unit->beHealed(2);
		}
		else{
			return _unit->beHealed(diff);
		}
	}

	return{};
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

bool General::getUniqueVariable() const{
	return hasHealed;
}

void General::setUniqueVariable(bool _hasHealed){
	hasHealed = _hasHealed;
}