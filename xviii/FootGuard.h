#pragma once

#include "UnitTile.h"

class FootGuard : public UnitTile
{
public:
	FootGuard(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir, TextureManager::Unit texType = TextureManager::Unit::HINF, UnitType uType = UnitType::FOOT);


	//FootGuard's reset() is overloaded due to the additional hasHealed variable that needs to be reset; giving it to all other UnitTiles would
	//be redundant since only General can even heal
	virtual void reset();
	//Footguard's moveTo is overloaded because of the rule: INF can either MOVE, PARTIALLY ROTATE, or FULLY ROTATE in addition to attacking.
	std::string moveTo(TerrainTile* terrainTile);
	//Footguard's interactWithFriendly() is overloaded for his healing ability
	virtual std::string interactWithFriendly(UnitTile* _unit);

	virtual std::string rotate(Direction _dir);

	inline virtual int getMaxHp() const{ return maxhp; };
	inline virtual int getMaxMov() const{ return maxMov; };
	inline virtual int getMaxRange() const{ return maxRange; };

	virtual std::string meleeAttack(UnitTile* _unit);

	virtual std::string meleeAttack(Infantry* inf);
	virtual std::string meleeAttack(FootGuard* foot);
	virtual std::string meleeAttack(Cavalry* cav);
	virtual std::string meleeAttack(Artillery* art);
	virtual std::string meleeAttack(Mortar* mor);

	virtual std::string rangedAttack(UnitTile* unit, int distance);

	virtual float getFlankModifier(UnitFamily _family, Modifier _flank) const;

	virtual bool getHasHealed() const;
	virtual void setHasHealed(bool _hasHealed);

private:
	bool hasHealed{false};

	static const int maxhp{22};
	static const int maxMov{6};
	static const int maxRange{6};
};

