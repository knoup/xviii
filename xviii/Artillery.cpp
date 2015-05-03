#include "stdafx.h"
#include "Artillery.h"

#include "World.h"

Artillery::Artillery(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir) :
UnitTile(_world, _mt19937, _belongsToPlayer, tm, fm, TextureManager::Unit::ART, UnitType::ART, UnitFamily::ART_FAMILY, _dir)
{
	mov = maxMov;
	hp = maxhp;
}

std::string Artillery::rotate(UnitTile::Direction _dir){
	if (hasRangedAttacked){
		return NO_ROTATE_AFTER_ATTACK;
	}
	else if (hasRotated){
		return ALREADY_ROTATED;
	}
	else if (dir == _dir){
		return ALREADY_FACING + UnitTile::dirToString();
	}

	hasRotated = true;
	dir = _dir;
	updateStats();

	return SUCCESSFUL_ROTATION + UnitTile::dirToString();
}

std::string Artillery::interactWithFriendly(UnitTile* _unit){
	return{};
}

sf::Vector2i Artillery::distanceFrom(TerrainTile* _terrain, bool& _validMovDirection, bool& _validAttackDirection, bool& _obstructionPresent, bool& _inMovementRange, bool& _inRangedAttackRange, bool canShootOverUnits, int coneWidth){
	return UnitTile::distanceFrom(_terrain, _validMovDirection, _validAttackDirection, _obstructionPresent, _inMovementRange, _inRangedAttackRange, true, 5);
}

std::string Artillery::meleeAttack(UnitTile* _unit){
	//This is used for double dispatch calls. However, we can also place the code for artillery's guard protection
	//here, since this will always be called when a unit meleeAttacks()'s artillery.

	bool protectedByGuard{false};
	sf::Vector2i currentPos = getCartesianPos();

	//Check all adjacent tiles for a friendly artillery guard
	for (int x{-1}; x <= 1 && !protectedByGuard; ++x){
		for (int y{-1}; y <= 1 && !protectedByGuard; ++y){

			sf::Vector2i adjacentPos{currentPos.x + x, currentPos.y + y};
			auto unit = world.unitAtTerrain(world.terrainAtCartesianPos(adjacentPos));

			if (unit != nullptr){

				if (unit->getPlayer() == getPlayer() && unit->getUnitType() == UnitType::ARTGUARD){
					protectedByGuard = true;
				}
			}
		}

	}

	if (!protectedByGuard){
		return _unit->meleeAttack(this);
	}

	return "Artillery Guard must be killed first";
}

std::string Artillery::rangedAttack(UnitTile* unit, int distance){

	std::uniform_int_distribution<int> distribution(1, 6);

	int thisRoll_int{distribution(mt19937)};

	float thisRoll = thisRoll_int;

	float damageDealt{0};

	if (thisRoll_int >= 4 && thisRoll_int <= 6){
		if (distance >= 20 && distance <= 24){
			damageDealt += 1;
		}
		else if (distance <= 19 && distance >= 10){
			damageDealt += 2;
		}
		else if (distance <= 9){
			damageDealt += 4;
		}

		unit->takeDamage(damageDealt, distance);
	}

	mov = 0;
	this->updateStats();
	unit->updateStats();
	hasRangedAttacked = true;

	return attackReport(distance, this, unit, thisRoll_int, 0, damageDealt, 0);
}