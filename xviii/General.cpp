#include "stdafx.h"
#include "General.h"

#include "World.h"

General::General(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir) :
Cavalry(_world, _mt19937, _belongsToPlayer, tm, fm, _dir, TextureManager::Unit::GEN, UnitType::GEN)
{
	deploymentCost = 0;
	limit = 1;

	waterCrosser = false;
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
		return "Cannot heal self";
	}
	if (_unit->gethp() != _unit->getMaxHp() && !hasHealed){
		hasHealed = true;
		return _unit->heal();
	}
	else if (hasHealed){
		return "Already healed";
	}
	else if (_unit->gethp() == _unit->getMaxHp()){
		return "Unit is at max HP";
	}

	return{};
}

void General::takeDamage(float _dmg){
	if (hp - _dmg < 0.4){
		for (auto& unit : world.getCombatLayer()){
			if (unit->getPlayer() == this->getPlayer() && unit.get() != this){
				unit->takeDamage(2);
			}
		}
	}

	UnitTile::takeDamage(_dmg);
}

int General::getMaxHp() const{
	return maxhp;
}

int General::getMaxMov() const{
	return maxMov;
}

int General::getMaxRange() const{
	return maxRange;
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
	unit->takeDamage(damageDealt);

	mov = 0;
	this->updateStats();
	unit->updateStats();
	hasRangedAttacked = true;

	return attackReport(distance, this, unit, thisRoll_int, 0, damageDealt, 0, modVector, unit->modVector);
}

bool General::getHasHealed() const{
	return hasHealed;
}

void General::setHasHealed(bool _hasHealed){
	hasHealed = _hasHealed;
}