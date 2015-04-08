#pragma once

#include "UnitTile.h"

class Infantry : public UnitTile
{
public:
	Infantry(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir, TextureManager::Unit texType = TextureManager::Unit::INF, UnitType uType = UnitType::INF);
	
	//Infantry's moveTo is overloaded because of the rule: INF can either MOVE, PARTIALLY ROTATE, or FULLY ROTATE in addition to attacking.
	std::string moveTo(TerrainTile* terrainTile);
	
	virtual std::string rotate(Direction _dir);
	virtual std::string interactWithFriendly(UnitTile* _unit);

	virtual int getMaxHp() const;
	virtual int getMaxMov() const;
	virtual int getMaxRange() const;

	virtual std::string meleeAttack(UnitTile* _unit);

	virtual std::string meleeAttack(Infantry* inf);
	virtual std::string meleeAttack(Cavalry* cav);
	virtual std::string meleeAttack(Artillery* art);
	virtual std::string meleeAttack(Mortar* mor);
	
	virtual std::string rangedAttack(UnitTile* unit, int distance);

	virtual float getFlankModifier(UnitFamily _family, Modifier _flank) const;

private:
	static const int maxhp{18};
	static const int maxMov{6};
	static const int maxRange{6};
};

