#include "xviii/Headers/stdafx.h"
#include "xviii/Units/General.h"

#include "xviii/Core/Player.h"

General::General(UnitLoader& _unitLoader, World& _world, boost::random::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& _tm, FontManager& _fm, TextureManager::Unit _texture, std::string _name, UnitType _type, UnitFamily _familyType, Direction _dir) :
Cavalry(_unitLoader, _world, _mt19937, _belongsToPlayer, _tm, _fm, _texture, _name, _type, _familyType, _dir)
{
}

void General::reset(){
	mov = getMaxMov();

	if (!limber && hasLimberAbility()){
		mov = 0;
	}

	if (hasLancerAbility()){
		if (!hasMeleeAttacked){
			lancerBonusReady = true;
		}
		else{
			lancerBonusReady = false;
		}
	}

	hasHealed = false;
	hasMoved = false;
	hasPartialRotated = false;
	hasFullRotated = false;
	hasMeleeAttacked = false;
	hasRangedAttacked = false;
	updateStats();
}

void General::takeDamage(UnitTile* attacker, float& _dmg, int distance){
	if (hp - _dmg < 0.4){
		for (auto& unit : player->getUnits()){
			if (unit.get() != this){
				//It is neither ranged nor melee, really, hence the 0
				float boilerplate{2};
				unit->takeDamage(attacker, boilerplate, 0);
			}
		}
	}

	UnitTile::takeDamage(attacker, _dmg, distance);
}
