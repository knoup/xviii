#include "stdafx.h"
#include "Infantry.h"

#include "Player.h"

static const float infFrontFlankModifier = 0.5;
static const float infSideFlankModifier = 1;
static const float infRearFlankModifier = 2;

static const float cavFrontFlankModifier = 1;
static const float cavSideFlankModifier = 1.5;
static const float cavRearFlankModifier = 2;

float Infantry::getFlankModifier(UnitFamily _family, Modifier _flank) const{
	if (_family == UnitFamily::INF_FAMILY || _family == UnitFamily::HINF_FAMILY || _family == UnitFamily::LINF_FAMILY){
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


Infantry::Infantry(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir, TextureManager::Unit texType, UnitType uType) :
UnitTile(_world, _mt19937, _belongsToPlayer, tm, fm, texType, uType, UnitFamily::INF_FAMILY, _dir)
{
	mov = maxMov;
	hp = maxhp;
	rangedAttackDistValues.clear();
	rangedAttackDistValues.emplace_back(6, 6, 0.5);
	rangedAttackDistValues.emplace_back(3, 5, 1);
	rangedAttackDistValues.emplace_back(2, 2, 2);
}

std::string Infantry::moveTo(TerrainTile* terrainTile){

	bool validMovDirection{false};
	bool validAttackDirection{false};
	bool obstructionPresent{false};
	bool inMovementRange{false};
	bool inRangedAttackRange{false};
	int movExpended{0};

	//Get the coordinates of the current tile the unit is at
	sf::Vector2i currentCoords{world.cartesianPosAtIndex(world.indexAtTile(*terrain))};

	//Get the coordinates of the tile to be moved to
	sf::Vector2i toMoveToCoords{world.cartesianPosAtIndex(world.indexAtTile(*terrainTile))};

	sf::Vector2i vectorDist = distanceFrom(terrainTile, validMovDirection, validAttackDirection, obstructionPresent, inMovementRange, inRangedAttackRange);

	if (dir == Direction::N || dir == Direction::S){
		movExpended = abs(vectorDist.y);
	}
	else{
		movExpended = abs(vectorDist.x);
	}

	if (obstructionPresent){
		return OBSTRUCTION_PRESENT_MOV;
	}

	else if (validMovDirection && inMovementRange){
		hasMoved = true;
		terrain->resetUnit();
		terrain = terrainTile;
		terrainTile->setUnit(this);
		mov -= movExpended;
		sprite.setPosition(terrainTile->getPixelPos());
		unitFlag.setPosition(terrainTile->getPixelPos());
		yellowOutline.setPosition(terrainTile->getPixelPos());
		redOutline.setPosition(terrainTile->getPixelPos());
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


std::string Infantry::rotate(UnitTile::Direction _dir){
	bool skirmish = {canSkirmish()};
	bool oppositeRotation{_dir == opposite(dir)};

	if (hasMeleeAttacked || (!skirmish && hasRangedAttacked) || (skirmish && !oppositeRotation)){
		return NO_ROTATE_AFTER_ATK;
	}
	if (hasRotated){
		return ALREADY_ROTATED;
	}
	else if (hasMoved && !skirmish){
		return NO_ROTATE_AFTER_MOV;
	}
	else if (dir == _dir){
		return ALREADY_FACING + UnitTile::dirToString();
	}

	hasRotated = true;

	if (skirmish && hasRangedAttacked){
		mov = 2;
	}
	else{
		mov = 0;
	}

	dir = _dir;
	updateStats();

	return SUCCESSFUL_ROTATION + UnitTile::dirToString();
}

std::string Infantry::interactWithFriendly(UnitTile* _unit){
	return{};
}

std::string Infantry::meleeAttack(UnitTile* _unit){
	return _unit->meleeAttack(this);
}

std::string Infantry::meleeAttack(Infantry* inf){

	std::uniform_int_distribution<int> distribution(1, 6);

	int thisRoll_int{distribution(mt19937)};
	int enemyRoll_int{distribution(mt19937)};

	float thisRoll = thisRoll_int;
	float enemyRoll = enemyRoll_int;

	float damageDealt{0};
	float damageReceived{0};

	multRollByModifiers(thisRoll);
	inf->multRollByModifiers(enemyRoll);

	
	//BREAKTHROUGH ABILITY
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool retreat{false};
	bool frontal{false};

	float retreatDamageDealt{0};

	//Checks if the attack is frontal or not

	for (int i{0}; i < modVector.size(); ++i){
		if (modVector[i].modType == Modifier::FRONT_FLANK){
			frontal = true;
			break;
		}
		break;
	}

	//For frontal attacks,
	if (frontal){
		//if the attacker's ORIGINAL roll is >= 6 AND the defender's ORIGINAL roll is <6
		//OR
		//if the attacker's FINAL roll is > than the defender's FINAL roll
		if ((thisRoll_int == 6 && enemyRoll_int < 6) || (thisRoll > enemyRoll)){
			std::cout << inf->getCartesianPos().x << ", " << inf->getCartesianPos().y << std::endl;
			sf::Vector2i enemyPos{inf->getCartesianPos()};
			sf::Vector2i enemyRetreatPos{enemyPos};

			switch (this->getDir()){
			case Direction::N:
				enemyRetreatPos.y -= 2;
				break;
			case Direction::E:
				enemyRetreatPos.x += 2;
				break;
			case Direction::S:
				enemyRetreatPos.y += 2;
				break;
			case Direction::W:
				enemyRetreatPos.x -= 2;
				break;
			}

			//Now check if the tile to retreat to is not occupied:
			if (world.canBePlacedAtCartesianPos(enemyRetreatPos)){
				retreat = true;
				//Here, we use the spawn function since it is essentially an instant teleport
				inf->spawn(world.terrainAtCartesianPos(enemyRetreatPos));
				inf->setDir(opposite(inf->getDir()));
				//The pushed back unit is immobilised for the next turn, and takes 2 damage
				retreatDamageDealt += 2;
				inf->setHasMeleeAttacked(true);
				inf->setHasRangedAttacked(true);
				inf->setHasMoved(true);
				inf->setMov(0);
			}
			else{
				//If the unit is unable to retreat, they suffer 6 damage
				retreatDamageDealt += 6;
			}

		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	if (abs(thisRoll - enemyRoll) < 0.01){
		damageDealt += 1;
		damageReceived += 1;

		this->takeDamage(inf, damageReceived, 1);
		inf->takeDamage(this, damageDealt, 1);
	}
	else{
		//If the difference between rolls is less than 3
		if (abs(thisRoll - enemyRoll) < 3){
			if (thisRoll > enemyRoll){
				damageDealt += 1;

				inf->takeDamage(this, damageDealt, 1);
			}
			else if (enemyRoll > thisRoll){
				damageReceived += 1;

				this->takeDamage(inf, damageReceived, 1);
			}
		}
		//If the difference is greater or equal to 3,
		else{
			if (thisRoll > enemyRoll){
				damageDealt += 2;
				inf->takeDamage(this, damageDealt, 1);
			}
			else if (enemyRoll > thisRoll){
				damageReceived += 2;
				this->takeDamage(inf, damageReceived, 1);
			}
		}
	}

	//After all else has been determined, take the retreat damage, if there was any
	if (retreatDamageDealt > 0){
		damageDealt += retreatDamageDealt;
		inf->takeDamage(this, retreatDamageDealt, 1);
	}

	mov = 0;
	this->updateStats();
	inf->updateStats();
	hasMeleeAttacked = true;

	return attackReport(1, this, inf, thisRoll_int, enemyRoll_int, damageDealt, damageReceived, retreat);

}

std::string Infantry::meleeAttack(Cavalry* cav){

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
		damageDealt += 1;
		damageReceived += 0.5;

		cav->takeDamage(this, damageDealt, 1);
		this->takeDamage(cav, damageReceived, 1);
	}
	else if (thisRoll > enemyRoll){
		damageDealt += 2;
		damageReceived += 1;

		cav->takeDamage(this, damageDealt, 1);
		this->takeDamage(cav, damageReceived, 1);

	}
	else if (enemyRoll > thisRoll){
		damageReceived += 4;

		this->takeDamage(cav, damageReceived, 1);

	}

	mov = 0;
	this->updateStats();
	cav->updateStats();
	hasMeleeAttacked = true;

	return attackReport(1, this, cav, thisRoll_int, enemyRoll_int, damageDealt, damageReceived);
	
}

std::string Infantry::meleeAttack(Artillery* art){

	std::uniform_int_distribution<int> distribution(1, 6);

	int thisRoll_int{distribution(mt19937)};

	float damageDealt{0};
	float damageReceived{0};


	float thisRoll = thisRoll_int;

	
	multRollByModifiers(thisRoll);

	if (thisRoll > 3 || abs(thisRoll - 3) < 0.01){
		damageDealt += 3;

		art->takeDamage(this, damageDealt, 1);

	}
	else if (thisRoll < 3){
		damageDealt += 3;
		damageReceived += 3;

		art->takeDamage(this, damageDealt, 1);
		this->takeDamage(art, damageReceived, 1);
	}

	mov = 0;
	this->updateStats();
	art->updateStats();
	hasMeleeAttacked = true;

	return attackReport(1, this, art, thisRoll_int, 0, damageDealt, damageReceived);

}

std::string Infantry::meleeAttack(Mortar* mor){

	std::uniform_int_distribution<int> distribution(1, 6);

	int thisRoll_int{distribution(mt19937)};

	float damageDealt{0};
	float damageReceived{0};

	float thisRoll = thisRoll_int;

	multRollByModifiers(thisRoll);

	if (thisRoll > 3 || abs(thisRoll - 3) < 0.01){
		damageDealt += 2;

		mor->takeDamage(this, damageDealt, 1);

	}
	else if (thisRoll < 3){
		damageDealt += 2;
		damageReceived += 0.5;

		mor->takeDamage(this, damageDealt, 1);
		this->takeDamage(mor, damageReceived, 1);
	}


	mov = 0;
	this->updateStats();
	mor->updateStats();
	hasMeleeAttacked = true;

	return attackReport(1, this, mor, thisRoll_int, 0, damageDealt, damageReceived);

}