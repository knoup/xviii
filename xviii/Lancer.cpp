#include "stdafx.h"
#include "Lancer.h"


Lancer::Lancer(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir, TextureManager::Unit texType, UnitType uType) :
Cavalry(_world, _mt19937, _belongsToPlayer, tm, fm, _dir, texType, uType)
{
	mov = maxMov;
	hp = maxhp;
}

void Lancer::reset(){
	//Before resetting the hasMeleeAttacked variable, set attackBonusReady. This way, we can check if
	//the unit has attacked this turn and if it hasn't, we can set the bonus ready for the next turn
	if (!hasMeleeAttacked){
		attackBonusReady = true;
	}
	else{
		attackBonusReady = false;
	}

	calculateEffectiveMov();
	hasRotated = false;
	hasMeleeAttacked = false;
	hasRangedAttacked = false;
	updateStats();
}