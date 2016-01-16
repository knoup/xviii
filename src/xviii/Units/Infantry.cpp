#include "xviii/Headers/stdafx.h"
#include "xviii/Units/Infantry.h"

#include "xviii/Core/Player.h"

Infantry::Infantry(World* _world, Player* _belongsToPlayer, std::string _unitID, UnitType _type, UnitFamily _familyType, Direction _dir) :
UnitTile(_world, _belongsToPlayer, _unitID, _type, _familyType, _dir)
{
}

std::string Infantry::moveTo(TerrainTile* terrainTile){

	if (getSquareFormationActive() && hasSquareFormationAbility()){
		return SF_ACTIVE;
	}

	bool validMovDirection{false};
	bool validAttackDirection{false};
	bool rangedObstructionPresent{false};
	bool meleeObstructionPresent{false};
	bool inMovementRange{false};
	bool inRangedAttackRange{false};
	int movExpended{0};

	//Get the coordinates of the current tile the unit is at
	sf::Vector2i currentCoords{world->cartesianPosAtIndex(world->indexAtTile(*terrain))};

	//Get the coordinates of the tile to be moved to
	sf::Vector2i toMoveToCoords{world->cartesianPosAtIndex(world->indexAtTile(*terrainTile))};

	sf::Vector2i vectorDist = distanceFrom(terrainTile, validMovDirection, validAttackDirection, rangedObstructionPresent, meleeObstructionPresent, inMovementRange, inRangedAttackRange);

	if (meleeObstructionPresent){
		return OBSTRUCTION_PRESENT_MOV;
	}

	else if (validMovDirection && inMovementRange){

            int PRIMARYAXIS_CURRENT;
            int PRIMARYAXIS_DESTINATION;
            int SECONDARYAXIS_CURRENT;
            int SECONDARYAXIS_DESTINATION;

            int PRIMARYAXIS_MOVEMENT;

            switch (dir){
            case UnitTile::Direction::N:
                PRIMARYAXIS_CURRENT = currentCoords.y;
                PRIMARYAXIS_DESTINATION = toMoveToCoords.y;
                SECONDARYAXIS_CURRENT = currentCoords.x;
                SECONDARYAXIS_DESTINATION = toMoveToCoords.x;

                PRIMARYAXIS_MOVEMENT = -1;
                break;

            case UnitTile::Direction::E:
                PRIMARYAXIS_CURRENT = currentCoords.x;
                PRIMARYAXIS_DESTINATION = toMoveToCoords.x;
                SECONDARYAXIS_CURRENT = currentCoords.y;
                SECONDARYAXIS_DESTINATION = toMoveToCoords.y;

                PRIMARYAXIS_MOVEMENT = 1;
                break;

            case UnitTile::Direction::S:
                PRIMARYAXIS_CURRENT = currentCoords.y;
                PRIMARYAXIS_DESTINATION = toMoveToCoords.y;
                SECONDARYAXIS_CURRENT = currentCoords.x;
                SECONDARYAXIS_DESTINATION = toMoveToCoords.x;

                PRIMARYAXIS_MOVEMENT = 1;
                break;


            case UnitTile::Direction::W:
                PRIMARYAXIS_CURRENT = currentCoords.x;
                PRIMARYAXIS_DESTINATION = toMoveToCoords.x;
                SECONDARYAXIS_CURRENT = currentCoords.y;
                SECONDARYAXIS_DESTINATION = toMoveToCoords.y;
                PRIMARYAXIS_MOVEMENT = -1;

                break;
        }

        sf::Vector2i finalCoords{toMoveToCoords};

        bool exitLoop{false};

        //Begin at the tile that comes after the current tile, and loop to the destination (inclusive)
        for (int i{PRIMARYAXIS_CURRENT + PRIMARYAXIS_MOVEMENT}; i != PRIMARYAXIS_DESTINATION && !exitLoop; i += PRIMARYAXIS_MOVEMENT){

            TerrainTile* terrainInTheWay;
            int indexToCheck = i;

            if (dir == Direction::N || dir == Direction::S){
                terrainInTheWay = world->terrainAtCartesianPos({SECONDARYAXIS_CURRENT, indexToCheck});
            }
            else{
                terrainInTheWay = world->terrainAtCartesianPos({indexToCheck, SECONDARYAXIS_CURRENT});
            }

            if(world->calculateViewDistance(this, terrainInTheWay, false)){

                if (dir == Direction::N || dir == Direction::S){
                    finalCoords.x = SECONDARYAXIS_CURRENT;
                    finalCoords.y = i;
                }

                else{
                    finalCoords.x = i;
                    finalCoords.y = SECONDARYAXIS_CURRENT;
                }

                exitLoop = true;
            }
        }


        if (dir == Direction::N || dir == Direction::S){
            movExpended = abs(finalCoords.y - currentCoords.y);
        }
        else{
            movExpended = abs(finalCoords.x - currentCoords.x);
        }

        TerrainTile* destination = world->terrainAtCartesianPos(finalCoords);

        //If we call wearDownBridges now, and the terrain tile we were standing on was
        //a bridge with 1 hp left, it will be deleted and terrain will be a dangling
        //pointer.

        TerrainTile* oldTerrain = terrain;

		setTerrain(destination);
		mov -= movExpended;
		hasMoved = true;

		//If we only move one tile, the view distance won't be recalculated in the loop,
		//so just do it again here anyway

        world->calculateViewDistance(this, false);
        world->highlightVisibleTiles();
		updateStats();

		world->wearDownTempBridges(oldTerrain, destination);

		if(finalCoords == toMoveToCoords){
            return MOV_SUCCESS + std::to_string(finalCoords.x + 1) + ", " + std::to_string(finalCoords.y + 1);
        }

        else{
            return "Movement disrupted!";
        }

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

	if (getHasMeleeAttacked() || (!getSkirmish() && getHasRangedAttacked()) || ((getSkirmish() && !oppositeRotation) && getHasAnyAttacked())){
		return NO_ROTATE_AFTER_ATK;
	}
	else if ((!getSkirmish() && getHasAnyRotated()) || (getSkirmish() && getHasAnyRotated() && !getHasRangedAttacked())){
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

	if (getSkirmish() && oppositeRotation && getHasRangedAttacked()){
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

	int thisRoll_int{distribution(world->masterManager.randomEngine)};
	int enemyRoll_int{distribution(world->masterManager.randomEngine)};

	float thisRoll = thisRoll_int;
	float enemyRoll = enemyRoll_int;

	float damageDealt{0};
	float damageReceived{0};

	multRollByModifiers(thisRoll);
	inf->multRollByModifiers(enemyRoll);


	//BREAKTHROUGH ABILITY
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//The retreat bool does not specify whether the retreat was successful (in that the unit was actually able to retreat),
	//but rather that the breakthrough bonus was procced. Its only purpose is to give information to attackReport()
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

            retreat = true;

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

            TerrainTile* retreatTile = world->terrainAtCartesianPos(enemyRetreatPos);

            bool validRetreatTile{false};
            bool retreatTileIsWater{false};

            //In the case of the retreat tile being water, there will be a 50% chance that the
            //unit will actually retreat into it, thus killing it instantly, or get the regular
            //extra damage that is dealt when units cannot retreat

            if(retreatTile != nullptr){

                if(retreatTile->getTerrainType() == TerrainTile::TerrainType::WATER){
                    retreatTileIsWater = true;
                }
                else if (retreatTile->getUnit() == nullptr){
                    validRetreatTile = true;
                }
            }

            bool willRetreat{0};

            if(retreatTileIsWater){
                boost::random::uniform_int_distribution<int> randomChance(0, 1);
                willRetreat = randomChance(world->masterManager.randomEngine);
            }

			//Now check if the tile to retreat to is not occupied:
			if (validRetreatTile || (retreatTileIsWater && willRetreat)){
				//Here, we use the spawn function since it is essentially an instant teleport
				inf->spawn(world->terrainAtCartesianPos(enemyRetreatPos));
				inf->setDir(opposite(inf->getDir()));
				//The pushed back unit is immobilised for the next turn, and takes 2 damage
				retreatDamageDealt += 2;
				inf->stun();
			}
			else if (!validRetreatTile || (retreatTileIsWater && !willRetreat)){
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
	meleeAttacks++;

	return attackReport(1, this, inf, thisRoll_int, enemyRoll_int, damageDealt, damageReceived, retreat);

}

std::string Infantry::meleeAttack(Cavalry* cav){

	boost::random::uniform_int_distribution<int> distribution(1, 6);

	int thisRoll_int{distribution(world->masterManager.randomEngine)};
	int enemyRoll_int{distribution(world->masterManager.randomEngine)};

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
	meleeAttacks++;

	return attackReport(1, this, cav, thisRoll_int, enemyRoll_int, damageDealt, damageReceived);

}

std::string Infantry::meleeAttack(Artillery* art){

	boost::random::uniform_int_distribution<int> distribution(1, 6);

	int thisRoll_int{distribution(world->masterManager.randomEngine)};

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
	meleeAttacks++;

	return attackReport(1, this, art, thisRoll_int, 0, damageDealt, damageReceived);

}

std::string Infantry::meleeAttack(Mortar* mor){

	boost::random::uniform_int_distribution<int> distribution(1, 6);

	int thisRoll_int{distribution(world->masterManager.randomEngine)};

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
	meleeAttacks++;

	return attackReport(1, this, mor, thisRoll_int, 0, damageDealt, damageReceived);

}
