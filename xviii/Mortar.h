#pragma once

#include "UnitTile.h"

class Mortar : public UnitTile
{
public:
	Mortar(UnitLoader& _unitLoader, World& _world, std::mt19937&, Player* _belongsToPlayer, TextureManager& _tm, FontManager& _fm, TextureManager::Unit _texture, std::string _name, UnitType _type, UnitFamily _familyType, Direction _dir);

	//Overloaded for artillery and mortar due to the differing rules in what constitutes an obscured LoS; art/mor don't care if there are units 
	//(both friendly and enemy) in the way. Simply calls UnitTile's function with canShootOverUnits being set to true
	virtual sf::Vector2i distanceFrom(TerrainTile* _terrain, bool& _validMovDirection, bool& _validAttackDirection, bool& _obstructionPresent, bool& _inMovementRange, bool& _inRangedAttackRange, bool canShootOverUnits = false, int coneWidth = 1);

	virtual std::string rotate(Direction _dir);

	inline virtual int getMaxHp() const{ return maxhp; };
	inline virtual int getMaxMov() const{ return maxMov; };

	inline virtual int getCost() const{ return 2; };
	inline virtual int getLimit() const{ return 5; };

	virtual std::string meleeAttack(UnitTile* _unit);

private:
	static const int maxhp{2};
	static const int maxMov{0};
};

