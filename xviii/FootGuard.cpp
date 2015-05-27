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

void FootGuard::preMeleeAttack(UnitTile* unit, bool attacking){
	//+1 in melee rolls
	this->modVector.emplace_back(Modifier::ADDITIONAL, 1);
}

void FootGuard::reset(){
	hasHealed = false;
	UnitTile::reset();
}

FootGuard::FootGuard(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir, TextureManager::Unit texType, UnitType uType) :
Infantry(_world, _mt19937, _belongsToPlayer, tm, fm, _dir, texType, uType)
{
	mov = maxMov;
	hp = maxhp;

	healingRangeValues.clear();
	healingRangeValues.emplace_back(1, 10, 1);
}

