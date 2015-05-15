#include "stdafx.h"
#include "Kapikulu.h"

#include "Player.h"

Kapikulu::Kapikulu(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir) :
Lancer(_world, _mt19937, _belongsToPlayer, tm, fm, _dir, TextureManager::Unit::ARMLAN, UnitType::KAP)
{
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

	calculateEffectiveMov();
	mov = maxMov;
	hasRotated = false;
	hasMeleeAttacked = false;
	hasRangedAttacked = false;
	updateStats();
}