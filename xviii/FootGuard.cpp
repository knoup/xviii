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
	mov = maxMov;
	hasRotated = false;
	hasMeleeAttacked = false;
	hasRangedAttacked = false;
	hasHealed = false;
	updateStats();
}

std::string FootGuard::interactWithFriendly(UnitTile* _unit){
	if (_unit == this){
		return CANNOT_HEAL_SELF;
	}
	else if (hasHealed){
		return ALREADY_HEALED;
	}
	else if (_unit->gethp() == _unit->getMaxHp()){
		return AT_MAX_HP;
	}
	else {
		float hp = _unit->gethp();
		float max = _unit->getMaxHp();
		float diff = max - hp;

		hasHealed = true;

		if (diff >= 1){
			return _unit->heal(1);
		}
		else{
			return _unit->heal(diff);
		}
	}

	return{};
}

bool FootGuard::getHasHealed() const{
	return hasHealed;
}

void FootGuard::setHasHealed(bool _hasHealed){
	hasHealed = _hasHealed;
}

FootGuard::FootGuard(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir, TextureManager::Unit texType, UnitType uType) :
Infantry(_world, _mt19937, _belongsToPlayer, tm, fm, _dir, texType, uType)
{
	mov = maxMov;
	hp = maxhp;
}

