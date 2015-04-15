#include "stdafx.h"
#include "Kapikulu.h"

#include "Player.h"

Kapikulu::Kapikulu(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir) :
Cuirassier(_world, _mt19937, _belongsToPlayer, tm, fm, _dir, TextureManager::Unit::CUIR, UnitType::KAP)
{
	deploymentCost = 3;
	limit = 5;

	waterCrosser = true;
	mov = maxMov;
	hp = maxhp;
}

void Kapikulu::reset(){
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

std::string Kapikulu::meleeAttack(Infantry* inf){

	std::uniform_int_distribution<int> distribution(1, 6);

	int thisRoll_int{distribution(mt19937)};
	int enemyRoll_int{distribution(mt19937)};

	float thisRoll = thisRoll_int;
	float enemyRoll = enemyRoll_int;

	float damageDealt{0};
	float damageReceived{0};

	//If original roll is 6 and attack bonus is ready...
	if (thisRoll_int == 6 && attackBonusReady){
		damageDealt = 4;
		inf->takeDamage(damageDealt);
	}
	else{
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
	}

	mov = 0;
	this->updateStats();
	inf->updateStats();
	hasMeleeAttacked = true;

	return attackReport(1, this, inf, thisRoll_int, enemyRoll_int, damageDealt, damageReceived);
}

std::string Kapikulu::meleeAttack(FootGuard* foot){

	std::uniform_int_distribution<int> distribution(1, 6);

	int thisRoll_int{distribution(mt19937)};
	int enemyRoll_int{distribution(mt19937)};

	float thisRoll = thisRoll_int;
	float enemyRoll = enemyRoll_int;

	float damageDealt{0};
	float damageReceived{0};

	//If original roll is 6 and attack bonus is ready...
	if (thisRoll_int == 6 && attackBonusReady){
		damageDealt = 4;
		foot->takeDamage(damageDealt);
	}
	else{
		multRollByModifiers(thisRoll);
		foot->multRollByModifiers(enemyRoll);

		if (abs(thisRoll - enemyRoll) < 0.01){
			damageDealt = 0.5;
			damageReceived = 1;

			foot->takeDamage(damageDealt);
			this->takeDamage(damageReceived);
		}
		else if (thisRoll > enemyRoll){
			damageDealt = 4;

			foot->takeDamage(damageDealt);

		}
		else if (enemyRoll > thisRoll){
			damageDealt = 1;
			damageReceived = 2;

			foot->takeDamage(damageDealt);
			this->takeDamage(damageReceived);

		}
	}

	mov = 0;
	this->updateStats();
	foot->updateStats();
	hasMeleeAttacked = true;

	return attackReport(1, this, foot, thisRoll_int, enemyRoll_int, damageDealt, damageReceived);
}

std::string Kapikulu::meleeAttack(Cavalry* cav){

	std::uniform_int_distribution<int> distribution(1, 6);

	int thisRoll_int{distribution(mt19937)};
	int enemyRoll_int{distribution(mt19937)};

	float thisRoll = thisRoll_int;
	float enemyRoll = enemyRoll_int;

	float damageDealt{0};
	float damageReceived{0};

	//If original roll is 6 and attack bonus is ready...
	if (thisRoll_int == 6 && attackBonusReady){
		damageDealt = 3;
		cav->takeDamage(damageDealt);
	}
	else{
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
	}

	mov = 0;
	this->updateStats();
	cav->updateStats();
	hasMeleeAttacked = true;

	return attackReport(1, this, cav, thisRoll_int, enemyRoll_int, damageDealt, damageReceived);
}

bool Kapikulu::getHasHealed() const{
	return attackBonusReady;
}

void Kapikulu::setHasHealed(bool _value){
	attackBonusReady = _value;
}