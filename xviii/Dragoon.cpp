#include "stdafx.h"
#include "Dragoon.h"

#include "Player.h"

static const float infFrontFlankModifier = 0.5;
static const float infSideFlankModifier = 0.5;
static const float infRearFlankModifier = 1;

static const float cavFrontFlankModifier = 1;
static const float cavSideFlankModifier = 2;
static const float cavRearFlankModifier = 2;


Dragoon::Dragoon(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir):
UnitTile(_world, _mt19937, _belongsToPlayer, tm, fm, TextureManager::Unit::DRAG, UnitType::DRAG, _dir)
{
	deploymentCost = 3;
	limit = 5;

	mov = maxMov;
	hp = maxhp;
	waterCrosser = true;
}

std::string Dragoon::rotate(UnitTile::Direction _dir){
	if (hasRotated){
		return "Cannot rotate any more";
	}
	else if (dir == _dir){
		return "Already facing " + UnitTile::dirToString(dir);
	}
	//If it was a full rotation
	if (_dir == opposite(dir)){
		hasAttacked = true;
		mov = 0;
	}

	hasRotated = true;
	dir = _dir;
	updateStats();

	return "Successfully rotated to " + UnitTile::dirToString(dir);
}

std::string Dragoon::interactWithFriendly(UnitTile* _unit){
	return{};
}

int Dragoon::getMaxHp() const{
	return maxhp;
}

int Dragoon::getMaxMov() const{
	return maxMov;
}

int Dragoon::getMaxRange() const{
	return maxRange;
}

std::string Dragoon::attack(UnitTile* _unit, int distance, UnitTile::Modifier flank){
	return _unit->attack(this, distance, flank);
}

std::string Dragoon::attack(Infantry* inf, int distance, UnitTile::Modifier flank){

	if (distance != 1){
		return rangedAttack(inf, distance);
	}

	std::uniform_int_distribution<int> distribution(1, 6);

	int thisRoll_int{distribution(mt19937)};
	int enemyRoll_int{distribution(mt19937)};

	float thisRoll = thisRoll_int;
	float enemyRoll = enemyRoll_int;

	float damageDealt{0};
	float damageReceived{0};


	float flankModifier;
	Modifier flankType;

	switch (flank){
	case Modifier::FRONT_FLANK:
		flankType = Modifier::FRONT_FLANK;
		flankModifier = infFrontFlankModifier;
		break;

	case Modifier::SIDE_FLANK:
		flankType = Modifier::SIDE_FLANK;
		flankModifier = infSideFlankModifier;
		break;

	case Modifier::REAR_FLANK:
		flankType = Modifier::REAR_FLANK;
		flankModifier = infRearFlankModifier;
	}

	modVector.emplace_back(flankType, flankModifier);

	multRollByModifiers(thisRoll);
	inf->multRollByModifiers(enemyRoll);

	if (abs(thisRoll - enemyRoll) < 0.01){
		damageDealt = 0.5;
		damageReceived = 1;

		inf->takeDamage(damageDealt);
		this->takeDamage(damageReceived);
	}
	else if (thisRoll > enemyRoll){
		damageDealt = 4;

		inf->takeDamage(damageDealt);

	}
	else if (enemyRoll > thisRoll){
		damageDealt = 1;
		damageReceived = 2;

		inf->takeDamage(damageDealt);
		this->takeDamage(damageReceived);

	}

	mov = 0;
	this->updateStats();
	inf->updateStats();
	hasAttacked = true;

	return attackReport(distance, this, inf, thisRoll_int, enemyRoll_int, damageDealt, damageReceived, modVector, inf->modVector);

}

std::string Dragoon::attack(Cavalry* cav, int distance, UnitTile::Modifier flank){
	if (distance != 1){
		return rangedAttack(cav, distance);
	}

	std::uniform_int_distribution<int> distribution(1, 6);

	int thisRoll_int{distribution(mt19937)};
	int enemyRoll_int{distribution(mt19937)};

	float thisRoll = thisRoll_int;
	float enemyRoll = enemyRoll_int;

	float damageDealt{0};
	float damageReceived{0};

	float flankModifier;
	Modifier flankType;

	switch (flank){
	case Modifier::FRONT_FLANK:
		flankType = Modifier::FRONT_FLANK;
		flankModifier = cavFrontFlankModifier;
		break;

	case Modifier::SIDE_FLANK:
		flankType = Modifier::SIDE_FLANK;
		flankModifier = cavSideFlankModifier;
		break;

	case Modifier::REAR_FLANK:
		flankType = Modifier::REAR_FLANK;
		flankModifier = cavRearFlankModifier;
	}

	modVector.emplace_back(flankType, flankModifier);

	multRollByModifiers(thisRoll);
	cav->multRollByModifiers(enemyRoll);

	if (abs(thisRoll - enemyRoll) < 0.01){
		damageDealt = 1;
		damageReceived = 1;

		this->takeDamage(damageReceived);
		cav->takeDamage(damageDealt);
	}
	else{
		//If the difference between rolls is less than 3
		if (abs(thisRoll - enemyRoll) < 3){
			//Player with the highest roll inflicts 1 DMG on the other
			if (thisRoll > enemyRoll){
				damageDealt = 1;
				cav->takeDamage(damageDealt);
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
				cav->takeDamage(damageDealt);
			}
			else if (enemyRoll > thisRoll){
				damageReceived = 2;
				this->takeDamage(damageReceived);
			}
		}
	}

	mov = 0;
	this->updateStats();
	cav->updateStats();
	hasAttacked = true;

	return attackReport(distance, this, cav, thisRoll_int, enemyRoll_int, damageDealt, damageReceived, modVector, cav->modVector);
}

std::string Dragoon::attack(Cuirassier* cuir, int distance, UnitTile::Modifier flank){
	if (distance != 1){
		return rangedAttack(cuir, distance);
	}

	std::uniform_int_distribution<int> distribution(1, 6);

	int thisRoll_int{distribution(mt19937)};
	int enemyRoll_int{distribution(mt19937)};

	float thisRoll = thisRoll_int;
	float enemyRoll = enemyRoll_int;

	float damageDealt{0};
	float damageReceived{0};

	float flankModifier;
	Modifier flankType;

	switch (flank){
	case Modifier::FRONT_FLANK:
		flankType = Modifier::FRONT_FLANK;
		flankModifier = cavFrontFlankModifier;
		break;

	case Modifier::SIDE_FLANK:
		flankType = Modifier::SIDE_FLANK;
		flankModifier = cavSideFlankModifier;
		break;

	case Modifier::REAR_FLANK:
		flankType = Modifier::REAR_FLANK;
		flankModifier = cavRearFlankModifier;
	}

	modVector.emplace_back(flankType, flankModifier);

	//Cuirassier's +1 vs cav
	cuir->modVector.emplace_back(UnitTile::Modifier::CUIRASSIER, 1);

	multRollByModifiers(thisRoll);
	cuir->multRollByModifiers(enemyRoll);

	if (abs(thisRoll - enemyRoll) < 0.01){
		damageDealt = 1;
		damageReceived = 1;

		this->takeDamage(damageReceived);
		cuir->takeDamage(damageDealt);
	}
	else{
		//If the difference between rolls is less than 3
		if (abs(thisRoll - enemyRoll) < 3){
			//Player with the highest roll inflicts 1 DMG on the other
			if (thisRoll > enemyRoll){
				damageDealt = 1;
				cuir->takeDamage(damageDealt);
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
				cuir->takeDamage(damageDealt);
			}
			else if (enemyRoll > thisRoll){
				damageReceived = 2;
				this->takeDamage(damageReceived);
			}
		}
	}

	mov = 0;
	this->updateStats();
	cuir->updateStats();
	hasAttacked = true;

	return attackReport(distance, this, cuir, thisRoll_int, enemyRoll_int, damageDealt, damageReceived, modVector, cuir->modVector);
}

std::string Dragoon::attack(Dragoon* drag, int distance, UnitTile::Modifier flank){
	if (distance != 1){
		return rangedAttack(drag, distance);
	}

	std::uniform_int_distribution<int> distribution(1, 6);

	int thisRoll_int{distribution(mt19937)};
	int enemyRoll_int{distribution(mt19937)};

	float thisRoll = thisRoll_int;
	float enemyRoll = enemyRoll_int;

	float damageDealt{0};
	float damageReceived{0};

	float flankModifier;
	Modifier flankType;

	switch (flank){
	case Modifier::FRONT_FLANK:
		flankType = Modifier::FRONT_FLANK;
		flankModifier = cavFrontFlankModifier;
		break;

	case Modifier::SIDE_FLANK:
		flankType = Modifier::SIDE_FLANK;
		flankModifier = cavSideFlankModifier;
		break;

	case Modifier::REAR_FLANK:
		flankType = Modifier::REAR_FLANK;
		flankModifier = cavRearFlankModifier;
	}

	modVector.emplace_back(flankType, flankModifier);

	multRollByModifiers(thisRoll);
	drag->multRollByModifiers(enemyRoll);

	if (abs(thisRoll - enemyRoll) < 0.01){
		damageDealt = 1;
		damageReceived = 1;

		this->takeDamage(damageReceived);
		drag->takeDamage(damageDealt);
	}
	else{
		//If the difference between rolls is less than 3
		if (abs(thisRoll - enemyRoll) < 3){
			//Player with the highest roll inflicts 1 DMG on the other
			if (thisRoll > enemyRoll){
				damageDealt = 1;
				drag->takeDamage(damageDealt);
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
				drag->takeDamage(damageDealt);
			}
			else if (enemyRoll > thisRoll){
				damageReceived = 2;
				this->takeDamage(damageReceived);
			}
		}
	}

	mov = 0;
	this->updateStats();
	drag->updateStats();
	hasAttacked = true;

	return attackReport(distance, this, drag, thisRoll_int, enemyRoll_int, damageDealt, damageReceived, modVector, drag->modVector);
}

std::string Dragoon::attack(LightCav* lcav, int distance, UnitTile::Modifier flank){
	if (distance != 1){
		return rangedAttack(lcav, distance);
	}

	std::uniform_int_distribution<int> distribution(1, 6);

	int thisRoll_int{distribution(mt19937)};
	int enemyRoll_int{distribution(mt19937)};

	float thisRoll = thisRoll_int;
	float enemyRoll = enemyRoll_int;

	float damageDealt{0};
	float damageReceived{0};

	float flankModifier;
	Modifier flankType;

	switch (flank){
	case Modifier::FRONT_FLANK:
		flankType = Modifier::FRONT_FLANK;
		flankModifier = cavFrontFlankModifier;
		break;

	case Modifier::SIDE_FLANK:
		flankType = Modifier::SIDE_FLANK;
		flankModifier = cavSideFlankModifier;
		break;

	case Modifier::REAR_FLANK:
		flankType = Modifier::REAR_FLANK;
		flankModifier = cavRearFlankModifier;
	}

	modVector.emplace_back(flankType, flankModifier);

	multRollByModifiers(thisRoll);
	lcav->multRollByModifiers(enemyRoll);

	if (abs(thisRoll - enemyRoll) < 0.01){
		damageDealt = 1;
		damageReceived = 1;

		this->takeDamage(damageReceived);
		lcav->takeDamage(damageDealt);
	}
	else{
		//If the difference between rolls is less than 3
		if (abs(thisRoll - enemyRoll) < 3){
			//Player with the highest roll inflicts 1 DMG on the other
			if (thisRoll > enemyRoll){
				damageDealt = 1;
				lcav->takeDamage(damageDealt);
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
				lcav->takeDamage(damageDealt);
			}
			else if (enemyRoll > thisRoll){
				damageReceived = 2;
				this->takeDamage(damageReceived);
			}
		}
	}

	mov = 0;
	this->updateStats();
	lcav->updateStats();
	hasAttacked = true;

	return attackReport(distance, this, lcav, thisRoll_int, enemyRoll_int, damageDealt, damageReceived, modVector, lcav->modVector);
}

std::string Dragoon::attack(Artillery* art, int distance, UnitTile::Modifier flank){
	if (distance != 1){
		return rangedAttack(art, distance);
	}

	float damageDealt{0};
	float damageReceived{0};

	std::uniform_int_distribution<int> distribution(1, 6);

	int thisRoll_int{distribution(mt19937)};

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
	hasAttacked = true;

	return attackReport(distance, this, art, thisRoll_int, 0, damageDealt, damageReceived, modVector, art->modVector);
}

std::string Dragoon::attack(Mortar* mor, int distance, UnitTile::Modifier flank){
	if (distance != 1){
		return rangedAttack(mor, distance);
	}

	float damageDealt{0};
	float damageReceived{0};

	std::uniform_int_distribution<int> distribution(1, 6);

	int thisRoll_int{distribution(mt19937)};

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
	hasAttacked = true;

	return attackReport(distance, this, mor, thisRoll_int, 0, damageDealt, damageReceived, modVector, mor->modVector);
}

std::string Dragoon::attack(General* gen, int distance, UnitTile::Modifier flank){
	if (distance != 1){
		return rangedAttack(gen, distance);
	}

	std::uniform_int_distribution<int> distribution(1, 6);

	int thisRoll_int{distribution(mt19937)};
	int enemyRoll_int{distribution(mt19937)};

	float thisRoll = thisRoll_int;
	float enemyRoll = enemyRoll_int;

	float damageDealt{0};
	float damageReceived{0};

	float flankModifier;
	Modifier flankType;

	switch (flank){
	case Modifier::FRONT_FLANK:
		flankType = Modifier::FRONT_FLANK;
		flankModifier = cavFrontFlankModifier;
		break;

	case Modifier::SIDE_FLANK:
		flankType = Modifier::SIDE_FLANK;
		flankModifier = cavSideFlankModifier;
		break;

	case Modifier::REAR_FLANK:
		flankType = Modifier::REAR_FLANK;
		flankModifier = cavRearFlankModifier;
	}

	modVector.emplace_back(flankType, flankModifier);

	multRollByModifiers(thisRoll);
	gen->multRollByModifiers(enemyRoll);

	if (abs(thisRoll - enemyRoll) < 0.01){
		damageDealt = 1;
		damageReceived = 1;

		this->takeDamage(damageReceived);
		gen->takeDamage(damageDealt);
	}
	else{
		//If the difference between rolls is less than 3
		if (abs(thisRoll - enemyRoll) < 3){
			//Player with the highest roll inflicts 1 DMG on the other
			if (thisRoll > enemyRoll){
				damageDealt = 1;
				gen->takeDamage(damageDealt);
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
				gen->takeDamage(damageDealt);
			}
			else if (enemyRoll > thisRoll){
				damageReceived = 2;
				this->takeDamage(damageReceived);
			}
		}
	}

	mov = 0;
	this->updateStats();
	gen->updateStats();
	hasAttacked = true;

	return attackReport(distance, this, gen, thisRoll_int, enemyRoll_int, damageDealt, damageReceived, modVector, gen->modVector);


}

std::string Dragoon::rangedAttack(UnitTile* unit, int distance){
	std::uniform_int_distribution<int> distribution(1, 6);

	int thisRoll_int{distribution(mt19937)};

	float thisRoll = thisRoll_int;

	float damageDealt{0};

	if (distance > maxRange){
		return outOfRange();
	}

	float distanceModifier;

	if (distance >= 5 && distance <= 9){
		distanceModifier = 0.5;
	}
	else if (distance >= 2 && distance <= 4){
		distanceModifier = 1;
	}
	else if (distance == 1){
		distanceModifier = 1.5;
	}

	modVector.emplace_back(Modifier::DISTANCE, distanceModifier);

	multRollByModifiers(thisRoll);
	damageDealt = thisRoll;
	unit->takeDamage(damageDealt);

	mov = 0;
	this->updateStats();
	unit->updateStats();
	hasAttacked = true;

	return attackReport(distance, this, unit, thisRoll_int, 0, damageDealt, 0, modVector, unit->modVector);
}