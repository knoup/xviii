#include "xviii/Headers/stdafx.h"
#include "xviii/Units/Infantry.h"

#include "xviii/Core/Player.h"

Infantry::Infantry(UnitLoader& _unitLoader, World& _world, boost::random::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& _tm, FontManager& _fm, TextureManager::Unit _texture, std::string _name, UnitType _type, UnitFamily _familyType, Direction _dir) :
UnitTile(_unitLoader, _world, _mt19937, _belongsToPlayer, _tm, _fm, _texture, _name, _type, _familyType, _dir)
{
}

std::string Infantry::moveTo(TerrainTile* terrainTile){

	if (getSquareFormationActive() && hasSquareFormationAbility()){
		return SF_ACTIVE;
	}

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
		outline.setPosition(terrainTile->getPixelPos());
		updateStats();
		return MOV_SUCCESS + std::to_string(toMoveToCoords.x + 1) + ", " + std::to_string(toMoveToCoords.y + 1);
	}

	else if (validMovDirection && !inMovementRange){
		return{NO_MOV};
	}

	else if (!validMovDirection){
		return{INVALID_DIR_MOV};
	}

    return{"???"};
}


std::string Infantry::rotate(UnitTile::Direction _dir){
	if (getSquareFormationActive() && hasSquareFormationAbility()){
		return SF_ACTIVE;
	}

	bool oppositeRotation{_dir == opposite(dir)};

	if (hasMeleeAttacked || (!getSkirmish() && hasRangedAttacked) || ((getSkirmish() && !oppositeRotation) && getHasAnyAttacked())){
		return NO_ROTATE_AFTER_ATK;
	}
	else if ((!getSkirmish() && getHasAnyRotated()) || (getSkirmish() && getHasAnyRotated() && !hasRangedAttacked)){
		return ALREADY_ROTATED;
	}
	else if (hasMoved && !getSkirmish()){
		return NO_ROTATE_AFTER_MOV;
	}
	else if (dir == _dir){
		return ALREADY_FACING + UnitTile::dirToString();
	}

	if (oppositeRotation){
		hasFullRotated = true;
	}
	else{
		hasPartialRotated = true;
	}

	if (getSkirmish() && oppositeRotation && hasRangedAttacked){
		mov = 2;
	}
	else{
		mov = 0;
	}

	dir = _dir;
	updateStats();

	return SUCCESSFUL_ROTATION + UnitTile::dirToString();
}

std::string Infantry::meleeAttack(UnitTile* _unit){
	return _unit->meleeAttack(this);
}

std::string Infantry::meleeAttack(Infantry* inf){

	boost::random::uniform_int_distribution<int> distribution(1, 6);

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

	for (size_t i{0}; i < modVector.size(); ++i){
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
		//AND
		//The enemy is not in square formation
		if (((thisRoll_int == 6 && enemyRoll_int < 6) || (thisRoll > enemyRoll)) && !inf->getSquareFormationActive()){
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

	boost::random::uniform_int_distribution<int> distribution(1, 6);

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

	boost::random::uniform_int_distribution<int> distribution(1, 6);

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

	boost::random::uniform_int_distribution<int> distribution(1, 6);

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
