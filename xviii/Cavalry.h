#pragma once

#include "UnitTile.h"

class Cavalry : public UnitTile
{
public:
	Cavalry(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir, TextureManager::Unit texType = TextureManager::Unit::CAV, UnitType uType = UnitType::CAV);

	virtual std::string rotate(Direction _dir);
	virtual std::string interactWithFriendly(UnitTile* _unit);

	virtual int getMaxHp() const;
	virtual int getMaxMov() const;
	virtual int getMaxRange() const;

	virtual std::string meleeAttack(UnitTile* _unit);

	virtual std::string meleeAttack(Infantry* inf);
	virtual std::string meleeAttack(FootGuard* foot);
	virtual std::string meleeAttack(Cavalry* cav);
	virtual std::string meleeAttack(Artillery* art);
	virtual std::string meleeAttack(Mortar* mor);

	virtual std::string rangedAttack(UnitTile* unit, int distance);

	virtual float getFlankModifier(UnitFamily _family, Modifier _flank) const;

private:
	static const int maxhp{12};
	static const int maxMov{12};
	static const int maxRange{0};
};

