#include "stdafx.h"
#include "General.h"

#include "World.h"

General::General(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir) :
Cavalry(_world, _mt19937, _belongsToPlayer, tm, fm, _dir, TextureManager::Unit::GEN, UnitType::GEN)
{
	mov = maxMov;
	hp = maxhp;
}

void General::reset(){
	mov = maxMov;
	hasRotated = false;
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
			return _unit->heal(2);
		}
		else{
			return _unit->heal(diff);
		}
	}

	return{};
}

void General::takeDamage(float& _dmg, int distance){
	if (hp - _dmg < 0.4){
		for (auto& unit : world.getUnitLayer()){
			if (unit->getPlayer() == this->getPlayer() && unit.get() != this){
				//It is neither ranged nor melee, really, hence the 0
				float boilerplate{2};
				unit->takeDamage(boilerplate, 0);
			}
		}
	}

	UnitTile::takeDamage(_dmg, distance);
}

std::string General::rangedAttack(UnitTile* unit, int distance){

	std::uniform_int_distribution<int> distribution(1, 6);

	int thisRoll_int{distribution(mt19937)};

	float thisRoll = thisRoll_int;

	float damageDealt{0};

	float distanceModifier{0.5};

	modVector.emplace_back(Modifier::DISTANCE, distanceModifier);

	multRollByModifiers(thisRoll);

	damageDealt = thisRoll;
	unit->takeDamage(damageDealt, distance);

	mov = 0;
	this->updateStats();
	unit->updateStats();
	hasRangedAttacked = true;

	return attackReport(distance, this, unit, thisRoll_int, 0, damageDealt, 0);
}

bool General::getHasHealed() const{
	return hasHealed;
}

void General::setHasHealed(bool _hasHealed){
	hasHealed = _hasHealed;
}