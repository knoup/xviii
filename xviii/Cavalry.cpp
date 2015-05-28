#include "stdafx.h"
#include "Cavalry.h"

#include "Player.h"

static const float infFrontFlankModifier = 0.5;
static const float infSideFlankModifier = 1;
static const float infRearFlankModifier = 2;

static const float cavFrontFlankModifier = 1;
static const float cavSideFlankModifier = 2;
static const float cavRearFlankModifier = 2;

bool Cavalry::lancerBonus(UnitTile* defender, float finalAttackerRoll, bool attackBonusReady, float& damageDealt){
	//If FINAL roll is 8 or above and attack bonus is ready...
	if (finalAttackerRoll >= 8 && attackBonusReady){
		if (defender->getUnitFamilyType() == UnitFamily::INF_FAMILY
			|| defender->getUnitFamilyType() == UnitFamily::HINF_FAMILY
			|| defender->getUnitFamilyType() == UnitFamily::LINF_FAMILY){
			damageDealt += 4;
		}
		else if (defender->getUnitFamilyType() == UnitFamily::CAV_FAMILY){
			damageDealt += 3;
		}

		defender->takeDamage(this, damageDealt, 1);
		return true;
	}

	return false;
}

float Cavalry::getFlankModifier(UnitFamily _family, Modifier _flank) const{
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

Cavalry::Cavalry(UnitLoader& _unitLoader, World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir, TextureManager::Unit texType, UnitType uType) :
UnitTile(_unitLoader, _world, _mt19937, _belongsToPlayer, tm, fm, texType, uType, UnitFamily::CAV_FAMILY, _dir)
{
	mov = maxMov;
	hp = maxhp;
}


std::string Cavalry::rotate(UnitTile::Direction _dir){
	bool oppositeRotation{_dir == opposite(dir)};

	if (hasMeleeAttacked || (!getSkirmish() && hasRangedAttacked) || ((getSkirmish() && !oppositeRotation) && getHasAnyAttacked())){
		return NO_ROTATE_AFTER_ATTACK;
	}
	else if ((!getSkirmish() && getHasAnyRotated()) || (getSkirmish() && getHasAnyRotated() && !hasRangedAttacked)){
		return ALREADY_ROTATED;
	}
	else if (dir == _dir){
		return ALREADY_FACING + UnitTile::dirToString();
	}

	//If it was a full rotation
	if (oppositeRotation){
		if (getSkirmish() && oppositeRotation && hasRangedAttacked){
			mov = 2;
		}
		else{
			mov = 0;
		}

		hasFullRotated = true;

		//Due to the rule that cav cannot attack after full rotation, and to simplify matters, I set the
		//hasAttacked variables to true here
		hasMeleeAttacked = true;
		hasRangedAttacked = true;
	}
	else{
		hasPartialRotated = true;
	}

	dir = _dir;
	updateStats();

	return SUCCESSFUL_ROTATION + UnitTile::dirToString();
}
	
std::string Cavalry::meleeAttack(UnitTile* _unit){
	return _unit->meleeAttack(this);
}

std::string Cavalry::meleeAttack(Infantry* inf){

	std::uniform_int_distribution<int> distribution(1, 6);

	int thisRoll_int{distribution(mt19937)};
	int enemyRoll_int{distribution(mt19937)};

	float thisRoll = thisRoll_int;
	float enemyRoll = enemyRoll_int;

	float damageDealt{0};
	float damageReceived{0};

	multRollByModifiers(thisRoll);
	inf->multRollByModifiers(enemyRoll);

	if (getLancer()){
		if (lancerBonus(inf, thisRoll, getUniqueVariable(), damageDealt)){
			mov = 0;
			this->updateStats();
			inf->updateStats();
			hasMeleeAttacked = true;

			return attackReport(1, this, inf, thisRoll_int, enemyRoll_int, damageDealt, damageReceived);
		}
	}

	if (abs(thisRoll - enemyRoll) < 0.01){
		damageDealt += 0.5;
		damageReceived += 1;

		inf->takeDamage(this, damageDealt, 1);
		this->takeDamage(inf, damageReceived, 1);
	}
	else if (thisRoll > enemyRoll){
		damageDealt += 4;

		inf->takeDamage(this, damageDealt, 1);

	}
	else if (enemyRoll > thisRoll){
		damageDealt += 1;
		damageReceived += 2;

		inf->takeDamage(this, damageDealt, 1);
		this->takeDamage(inf, damageReceived, 1);

	}

	mov = 0;
	this->updateStats();
	inf->updateStats();
	hasMeleeAttacked = true;
	
	return attackReport(1, this, inf, thisRoll_int, enemyRoll_int, damageDealt, damageReceived);
}

std::string Cavalry::meleeAttack(Cavalry* cav){

	std::uniform_int_distribution<int> distribution(1, 6);

	int thisRoll_int{distribution(mt19937)};
	int enemyRoll_int{distribution(mt19937)};

	float thisRoll = thisRoll_int;
	float enemyRoll = enemyRoll_int;

	float damageDealt{0};
	float damageReceived{0};

	multRollByModifiers(thisRoll);
	cav->multRollByModifiers(enemyRoll);

	if (getLancer()){
		if (lancerBonus(cav, thisRoll, getUniqueVariable(), damageDealt)){
			mov = 0;
			this->updateStats();
			cav->updateStats();
			hasMeleeAttacked = true;

			return attackReport(1, this, cav, thisRoll_int, enemyRoll_int, damageDealt, damageReceived);
		}
	}

	if (abs(thisRoll - enemyRoll) < 0.01){
		damageDealt += 1;
		damageReceived += 1;

		this->takeDamage(cav, damageReceived, 1);
		cav->takeDamage(this, damageDealt, 1);
	}
	else{
		//If the difference between rolls is less than 3
		if (abs(thisRoll - enemyRoll) < 3){
			//Player with the highest roll inflicts 1 DMG on the other
			if (thisRoll > enemyRoll){
				damageDealt += 1;
				cav->takeDamage(this, damageDealt, 1);
			}
			else if (enemyRoll > thisRoll){
				damageReceived += 1;
				this->takeDamage(cav, damageReceived, 1);
			}
		}
		//If the difference is greater or equal to 3,
		else{
			if (thisRoll > enemyRoll){
				damageDealt += 2;
				cav->takeDamage(this, damageDealt, 1);
			}
			else if (enemyRoll > thisRoll){
				damageReceived += 2;
				this->takeDamage(cav, damageReceived, 1);
			}
		}
	}

	mov = 0;
	this->updateStats();
	cav->updateStats();
	hasMeleeAttacked = true;

	return attackReport(1, this, cav, thisRoll_int, enemyRoll_int, damageDealt, damageReceived);
	
}

std::string Cavalry::meleeAttack(Artillery* art){

	float damageDealt{0};
	float damageReceived{0};

	std::uniform_int_distribution<int> distribution(1, 6);

	int thisRoll_int{distribution(mt19937)};
	
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

std::string Cavalry::meleeAttack(Mortar* mor){

	float damageDealt{0};
	float damageReceived{0};

	std::uniform_int_distribution<int> distribution(1, 6);

	int thisRoll_int{distribution(mt19937)};

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