#pragma once

#include "Infantry.h"

class FootGuard : public Infantry
{
public:
	FootGuard(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir, TextureManager::Unit texType = TextureManager::Unit::HINF, UnitType uType = UnitType::FOOT);


	//FootGuard's reset() is overloaded due to the additional hasHealed variable that needs to be reset; giving it to all other UnitTiles would
	//be redundant since only General can even heal
	virtual void reset();
	//Footguard's interactWithFriendly() is overloaded for his healing ability
	virtual std::string interactWithFriendly(UnitTile* _unit);

	inline virtual int getMaxHp() const{ return maxhp; };
	inline virtual int getMaxMov() const{ return maxMov; };

	inline virtual int getCost() const{ return 1; };
	inline virtual int getLimit() const{ return 0; };

	virtual void preMeleeAttack(UnitTile* unit, bool attacking);

	virtual bool getUniqueVariable() const;
	virtual void setUniqueVariable(bool _hasHealed);

private:
	bool hasHealed{false};

	static const int maxhp{22};
	static const int maxMov{6};
	static const int maxHealingRange{10};
};

