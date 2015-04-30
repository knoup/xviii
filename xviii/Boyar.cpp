#include "stdafx.h"
#include "Boyar.h"

#include "Player.h"

Boyar::Boyar(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir) :
Cavalry(_world, _mt19937, _belongsToPlayer, tm, fm, _dir, TextureManager::Unit::CUIR, UnitType::BOY)
{
	mov = maxMov;
	hp = maxhp;
}

std::string Boyar::meleeAttack(Infantry* inf){

	std::uniform_int_distribution<int> distribution(1, 6);

	int thisRoll_int{distribution(mt19937)};
	int enemyRoll_int{distribution(mt19937)};

	float thisRoll = thisRoll_int;
	float enemyRoll = enemyRoll_int;

	float damageDealt{0};
	float damageReceived{0};

	multRollByModifiers(thisRoll);
	inf->multRollByModifiers(enemyRoll);

	//If FINAL roll is 8 or above and attack bonus is ready...
	if (thisRoll >= 8 && attackBonusReady){
		damageDealt = 4;
		inf->takeDamage(damageDealt, 1);
	}

	if (abs(thisRoll - enemyRoll) < 0.01){
		damageDealt = 0.5;
		damageReceived = 1;

		inf->takeDamage(damageDealt, 1);
		this->takeDamage(damageReceived, 1);
	}
	else if (thisRoll > enemyRoll){
		damageDealt = 4;

		inf->takeDamage(damageDealt, 1);

	}
	else if (enemyRoll > thisRoll){
		damageDealt = 1;
		damageReceived = 2;

		inf->takeDamage(damageDealt, 1);
		this->takeDamage(damageReceived, 1);

	}
	

	mov = 0;
	this->updateStats();
	inf->updateStats();
	hasMeleeAttacked = true;

	return attackReport(1, this, inf, thisRoll_int, enemyRoll_int, damageDealt, damageReceived);
}

std::string Boyar::meleeAttack(FootGuard* foot){

	std::uniform_int_distribution<int> distribution(1, 6);

	int thisRoll_int{distribution(mt19937)};
	int enemyRoll_int{distribution(mt19937)};

	float thisRoll = thisRoll_int;
	float enemyRoll = enemyRoll_int;

	float damageDealt{0};
	float damageReceived{0};

	multRollByModifiers(thisRoll);
	foot->multRollByModifiers(enemyRoll);

	//If FINAL roll is 8 or above and attack bonus is ready...
	if (thisRoll >= 8 && attackBonusReady){
		damageDealt = 4;
		foot->takeDamage(damageDealt, 1);
	}

	if (abs(thisRoll - enemyRoll) < 0.01){
		damageDealt = 0.5;
		damageReceived = 1;

		foot->takeDamage(damageDealt, 1);
		this->takeDamage(damageReceived, 1);
	}
	else if (thisRoll > enemyRoll){
		damageDealt = 4;

		foot->takeDamage(damageDealt, 1);

	}
	else if (enemyRoll > thisRoll){
		damageDealt = 1;
		damageReceived = 2;

		foot->takeDamage(damageDealt, 1);
		this->takeDamage(damageReceived, 1);

	}
	

	mov = 0;
	this->updateStats();
	foot->updateStats();
	hasMeleeAttacked = true;

	return attackReport(1, this, foot, thisRoll_int, enemyRoll_int, damageDealt, damageReceived);
}

std::string Boyar::meleeAttack(Cavalry* cav){

	std::uniform_int_distribution<int> distribution(1, 6);

	int thisRoll_int{distribution(mt19937)};
	int enemyRoll_int{distribution(mt19937)};

	float thisRoll = thisRoll_int;
	float enemyRoll = enemyRoll_int;

	float damageDealt{0};
	float damageReceived{0};

	
	multRollByModifiers(thisRoll);
	cav->multRollByModifiers(enemyRoll);

	//If FINAL roll is 8 or above and attack bonus is ready...
	if (thisRoll >= 8 && attackBonusReady){
		damageDealt = 3;
		cav->takeDamage(damageDealt, 1);
	}

	if (abs(thisRoll - enemyRoll) < 0.01){
		damageDealt = 1;
		damageReceived = 1;

		this->takeDamage(damageReceived, 1);
		cav->takeDamage(damageDealt, 1);
	}
	else{
		//If the difference between rolls is less than 3
		if (abs(thisRoll - enemyRoll) < 3){
			//Player with the highest roll inflicts 1 DMG on the other
			if (thisRoll > enemyRoll){
				damageDealt = 1;
				cav->takeDamage(damageDealt, 1);
			}
			else if (enemyRoll > thisRoll){
				damageReceived = 1;
				this->takeDamage(damageReceived, 1);
			}
		}
		//If the difference is greater or equal to 3,
		else{
			if (thisRoll > enemyRoll){
				damageDealt = 2;
				cav->takeDamage(damageDealt, 1);
			}
			else if (enemyRoll > thisRoll){
				damageReceived = 2;
				this->takeDamage(damageReceived, 1);
			}
		}
	}
	

	mov = 0;
	this->updateStats();
	cav->updateStats();
	hasMeleeAttacked = true;

	return attackReport(1, this, cav, thisRoll_int, enemyRoll_int, damageDealt, damageReceived);
}

void Boyar::reset(){
	//Before resetting the hasMeleeAttacked variable, set attackBonusReady. This way, we can check if
	//the unit has attacked this turn and if it hasn't, we can set the bonus ready for the next turn
	if (!hasMeleeAttacked){
		attackBonusReady = true;
	}
	else{
		attackBonusReady = false;
	}

	mov = maxMov;
	hasRotated = false;
	hasMeleeAttacked = false;
	hasRangedAttacked = false;
	updateStats();
}
