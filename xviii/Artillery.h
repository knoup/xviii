#pragma once

#include "UnitTile.h"

class Artillery : public UnitTile
{
public:
	Artillery(UnitLoader& _unitLoader, World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir);

	//Overloaded for artillery and mortar due to the differing rules in what constitutes an obscured LoS; art/mor don't care if there are units 
	//(both friendly and enemy) in the way. Simply calls UnitTile's function with canShootOverUnits being set to true
	virtual sf::Vector2i distanceFrom(TerrainTile* _terrain, bool& _validMovDirection, bool& _validAttackDirection, bool& _obstructionPresent, bool& _inMovementRange, bool& _inRangedAttackRange, bool canShootOverUnits = false, int coneWidth = 1);

	//Artillery's reset() is overloaded due to the limber mechanic
	virtual void reset();
	
	virtual std::string rotate(Direction _dir);

	inline virtual int getMaxHp() const{ return maxhp; };
	inline virtual int getMaxMov() const{ return maxMov; };

	inline virtual int getCost() const{ return 3; };
	inline virtual int getLimit() const{ return 5; };

	virtual std::string meleeAttack(UnitTile* _unit);

	virtual std::string rangedAttack(UnitTile* unit, int distance);

	virtual bool getUniqueVariable() const{ return limber; };
	virtual void setUniqueVariable(bool _value){ limber = _value; };
	virtual void toggleLimber();

private:
	//A special artillery ability, limbering
	bool limber{true};

	static const int maxhp{3};
	static const int maxMov{3};
};

