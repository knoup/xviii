#include "stdafx.h"
#include "Cuirassier.h"

static const float infFrontFlankModifier = 0.5;
static const float infSideFlankModifier = 1;
static const float infRearFlankModifier = 2;

static const float cavFrontFlankModifier = 1;
static const float cavSideFlankModifier = 2;
static const float cavRearFlankModifier = 2;

float Cuirassier::getFlankModifier(UnitFamily _family, Modifier _flank) const{
	if (_family == UnitFamily::INF_FAMILY || _family == UnitFamily::HINF_FAMILY){
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


Cuirassier::Cuirassier(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir, TextureManager::Unit texType, UnitType uType) :
Cavalry(_world, _mt19937, _belongsToPlayer, tm, fm, _dir, texType, uType)
{
	mov = maxMov;
	hp = maxhp;
}

void Cuirassier::preAttack(UnitTile* unit, bool attacking){
	if (unit->getUnitFamilyType() == UnitFamily::CAV_FAMILY){
		this->modVector.emplace_back(Modifier::ADDITIONAL, 1);
	}
}