#include "stdafx.h"
#include "FootGuard.h"


#include "stdafx.h"
#include "Infantry.h"

#include "Player.h"

static const float infFrontFlankModifier = 0.5;
static const float infSideFlankModifier = 1;
static const float infRearFlankModifier = 2;

static const float cavFrontFlankModifier = 1;
static const float cavSideFlankModifier = 1.5;
static const float cavRearFlankModifier = 2;

float FootGuard::getFlankModifier(UnitFamily _family, Modifier _flank) const{
	if (_family == UnitFamily::INF_FAMILY || _family == UnitFamily::HINF_FAMILY){
		switch (_flank){
		case Modifier::FRONT_FLANK:
			return infFrontFlankModifier;
			break;

		case Modifier::SIDE_FLANK:
			return infSideFlankModifier;
			break;

		case Modifier::REAR_FLANK:
			return infRearFlankModifier;
			break;
		}
	}

	else if (_family == UnitFamily::CAV_FAMILY){
		switch (_flank){
		case Modifier::FRONT_FLANK:
			return cavFrontFlankModifier;
			break;

		case Modifier::SIDE_FLANK:
			return cavSideFlankModifier;
			break;

		case Modifier::REAR_FLANK:
			return cavRearFlankModifier;
			break;
		}
	}

	//If unit is neither in INF or CAV family, return 0. Modifiers of 0 will be ignored.
	else{
		return 0;
	}
}

void FootGuard::reset(){
	mov = maxMov;
	hasRotated = false;
	hasMeleeAttacked = false;
	hasRangedAttacked = false;
	hasHealed = false;
	updateStats();
}

std::string FootGuard::interactWithFriendly(UnitTile* _unit){
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

		if (diff >= 1){
			return _unit->heal(1);
		}
		else{
			return _unit->heal(diff);
		}
	}

	return{};
}

bool FootGuard::getHasHealed() const{
	return hasHealed;
}

void FootGuard::setHasHealed(bool _hasHealed){
	hasHealed = _hasHealed;
}

FootGuard::FootGuard(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir, TextureManager::Unit texType, UnitType uType) :
UnitTile(_world, _mt19937, _belongsToPlayer, tm, fm, texType, uType, UnitFamily::HINF_FAMILY, _dir)
{
	deploymentCost = 1;
	limit = 0;

	waterCrosser = false;
	mov = maxMov;
	hp = maxhp;
}

std::string FootGuard::moveTo(TerrainTile* terrainTile){

	bool validMovDirection{false};
	bool validAttackDirection{false};
	bool obstructionPresent{false};
	bool inMovementRange{false};
	bool inRangedAttackRange{false};
	int movExpended{0};

	//Get the coordinates of the current tile the unit is at
	sf::Vector2i currentCoords{world.cartesianCoordsAtIndex(world.indexAtTile(*terrain))};

	//Get the coordinates of the tile to be moved to
	sf::Vector2i toMoveToCoords{world.cartesianCoordsAtIndex(world.indexAtTile(*terrainTile))};

	movExpended = distanceFrom(terrainTile, validMovDirection, validAttackDirection, obstructionPresent, inMovementRange, inRangedAttackRange);

	if (obstructionPresent){
		return OBSTRUCTION_PRESENT_MOV;
	}

	else if (validMovDirection && inMovementRange){
		hasMoved = true;
		terrain->resetUnit();
		terrain = terrainTile;
		terrainTile->setUnit(this);
		mov -= movExpended;
		sprite.setPosition(terrainTile->getPos());
		unitFlag.setPosition(terrainTile->getPos());
		yellowOutline.setPosition(terrainTile->getPos());
		redOutline.setPosition(terrainTile->getPos());
		updateStats();
		return MOV_SUCCESS + std::to_string(toMoveToCoords.x + 1) + ", " + std::to_string(toMoveToCoords.y + 1);
	}

	else if (validMovDirection && !inMovementRange){
		return{NO_MOV};
	}

	else if (!validMovDirection){
		return{INVALID_DIR_MOV};
	}

}


std::string FootGuard::rotate(UnitTile::Direction _dir){
	if (hasMeleeAttacked || hasRangedAttacked){
		return "Can't rotate after attacking";
	}
	if (hasRotated){
		return ALREADY_ROTATED;
	}
	else if (hasMoved){
		return "Can't rotate after moving";
	}
	else if (dir == _dir){
		return ALREADY_FACING + UnitTile::dirToString();
	}

	hasRotated = true;
	mov = 0;
	dir = _dir;
	updateStats();

	return SUCCESSFUL_ROTATION + UnitTile::dirToString();
}

std::string FootGuard::meleeAttack(UnitTile* _unit){
	return _unit->meleeAttack(this);
}

std::string FootGuard::meleeAttack(Infantry* inf){

	std::uniform_int_distribution<int> distribution(1, 6);

	int thisRoll_int{distribution(mt19937)};
	int enemyRoll_int{distribution(mt19937)};

	float thisRoll = thisRoll_int;
	float enemyRoll = enemyRoll_int;

	float damageDealt{0};
	float damageReceived{0};

	multRollByModifiers(thisRoll);
	inf->multRollByModifiers(enemyRoll);

	if (abs(thisRoll - enemyRoll) < 0.01){
		damageDealt = 1;
		damageReceived = 1;

		this->takeDamage(damageReceived);
		inf->takeDamage(damageDealt);
	}
	else{
		//If the difference between rolls is less than 3
		if (abs(thisRoll - enemyRoll) < 3){
			if (thisRoll > enemyRoll){
				damageDealt = 1;

				inf->takeDamage(damageDealt);
			}
			else if (enemyRoll > thisRoll){
				damageReceived = 1;

				this->takeDamage(damageReceived);
			}
		}
		//If the difference is greater or equal to 3,
		else{
			if (thisRoll > enemyRoll){
				damageDealt = 2;
				inf->takeDamage(damageDealt);
			}
			else if (enemyRoll > thisRoll){
				damageReceived = 2;
				this->takeDamage(damageReceived);
			}
		}
	}

	mov = 0;
	this->updateStats();
	inf->updateStats();
	hasMeleeAttacked = true;

	return attackReport(1, this, inf, thisRoll_int, enemyRoll_int, damageDealt, damageReceived);
}

std::string FootGuard::meleeAttack(FootGuard* foot){

	std::uniform_int_distribution<int> distribution(1, 6);

	int thisRoll_int{distribution(mt19937)};
	int enemyRoll_int{distribution(mt19937)};

	float thisRoll = thisRoll_int;
	float enemyRoll = enemyRoll_int;

	float damageDealt{0};
	float damageReceived{0};

	multRollByModifiers(thisRoll);
	foot->multRollByModifiers(enemyRoll);

	if (abs(thisRoll - enemyRoll) < 0.01){
		damageDealt = 1;
		damageReceived = 1;

		this->takeDamage(damageReceived);
		foot->takeDamage(damageDealt);
	}
	else{
		//If the difference between rolls is less than 3
		if (abs(thisRoll - enemyRoll) < 3){
			if (thisRoll > enemyRoll){
				damageDealt = 1;

				foot->takeDamage(damageDealt);
			}
			else if (enemyRoll > thisRoll){
				damageReceived = 1;

				this->takeDamage(damageReceived);
			}
		}
		//If the difference is greater or equal to 3,
		else{
			if (thisRoll > enemyRoll){
				damageDealt = 2;
				foot->takeDamage(damageDealt);
			}
			else if (enemyRoll > thisRoll){
				damageReceived = 2;
				this->takeDamage(damageReceived);
			}
		}
	}

	mov = 0;
	this->updateStats();
	foot->updateStats();
	hasMeleeAttacked = true;

	return attackReport(1, this, foot, thisRoll_int, enemyRoll_int, damageDealt, damageReceived);

}

std::string FootGuard::meleeAttack(Cavalry* cav){

	std::uniform_int_distribution<int> distribution(1, 6);

	int thisRoll_int{distribution(mt19937)};
	int enemyRoll_int{distribution(mt19937)};

	float thisRoll = thisRoll_int;
	float enemyRoll = enemyRoll_int;

	float damageDealt{0};
	float damageReceived{0};

	multRollByModifiers(thisRoll);
	cav->multRollByModifiers(enemyRoll);

	if (abs(thisRoll - enemyRoll) < 0.01){
		damageDealt = 1;
		damageReceived = 0.5;

		cav->takeDamage(damageDealt);
		this->takeDamage(damageReceived);
	}
	else if (thisRoll > enemyRoll){
		damageDealt = 2;
		damageReceived = 1;

		cav->takeDamage(damageDealt);
		this->takeDamage(damageReceived);

	}
	else if (enemyRoll > thisRoll){
		damageReceived = 4;

		this->takeDamage(damageReceived);

	}

	mov = 0;
	this->updateStats();
	cav->updateStats();
	hasMeleeAttacked = true;

	return attackReport(1, this, cav, thisRoll_int, enemyRoll_int, damageDealt, damageReceived);

}

std::string FootGuard::meleeAttack(Artillery* art){

	std::uniform_int_distribution<int> distribution(1, 6);

	int thisRoll_int{distribution(mt19937)};

	float damageDealt{0};
	float damageReceived{0};


	float thisRoll = thisRoll_int;


	multRollByModifiers(thisRoll);

	if (thisRoll > 3 || abs(thisRoll - 3) < 0.01){
		damageDealt = 3;

		art->takeDamage(damageDealt);

	}
	else if (thisRoll < 3){
		damageDealt = 3;
		damageReceived = 3;

		art->takeDamage(damageDealt);
		this->takeDamage(damageReceived);
	}

	mov = 0;
	this->updateStats();
	art->updateStats();
	hasMeleeAttacked = true;

	return attackReport(1, this, art, thisRoll_int, 0, damageDealt, damageReceived);

}

std::string FootGuard::meleeAttack(Mortar* mor){

	std::uniform_int_distribution<int> distribution(1, 6);

	int thisRoll_int{distribution(mt19937)};

	float damageDealt{0};
	float damageReceived{0};

	float thisRoll = thisRoll_int;

	multRollByModifiers(thisRoll);

	if (thisRoll > 3 || abs(thisRoll - 3) < 0.01){
		damageDealt = 2;

		mor->takeDamage(damageDealt);

	}
	else if (thisRoll < 3){
		damageDealt = 2;
		damageReceived = 0.5;

		mor->takeDamage(damageDealt);
		this->takeDamage(damageReceived);
	}


	mov = 0;
	this->updateStats();
	mor->updateStats();
	hasMeleeAttacked = true;

	return attackReport(1, this, mor, thisRoll_int, 0, damageDealt, damageReceived);

}

std::string FootGuard::rangedAttack(UnitTile* unit, int distance){

	std::uniform_int_distribution<int> distribution(1, 6);

	int thisRoll_int{distribution(mt19937)};

	float thisRoll = thisRoll_int;

	float damageDealt{0};

	float distanceModifier{1};

	if (distance == 6){
		distanceModifier = 0.5;
	}
	else if (distance >= 3 && distance <= 5){
		distanceModifier = 1;
	}
	else if (distance == 2 || distance == 1){
		distanceModifier = 2;
	}

	modVector.emplace_back(Modifier::DISTANCE, distanceModifier);

	multRollByModifiers(thisRoll);
	damageDealt = thisRoll;
	unit->takeDamage(damageDealt);

	mov = 0;
	this->updateStats();
	unit->updateStats();
	hasRangedAttacked = true;

	return attackReport(distance, this, unit, thisRoll_int, 0, damageDealt, 0);
}