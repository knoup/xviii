#pragma once

#include "xviii/Units/UnitTile.h"

class Artillery : public UnitTile
{
public:
	Artillery(UnitLoader& _unitLoader, World& _world, boost::random::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& _tm, FontManager& _fm, TextureManager::Unit _texture, std::string _name, UnitType _type, UnitFamily _familyType, Direction _dir);

    inline virtual bool canAttackTerrain(){return true;};
    inline virtual bool attacksTerrainWithUnits(){return true;};

	//Overloaded for artillery and mortar due to the differing rules in what constitutes an obscured LoS; art/mor don't care if there are units
	//(both friendly and enemy) in the way. Simply calls UnitTile's function with canShootOverUnits being set to true
	virtual sf::Vector2i distanceFrom(TerrainTile* _terrain, bool& _validMovDirection, bool& _validAttackDirection, bool& _obstructionPresent, bool& _inMovementRange, bool& _inRangedAttackRange, bool mudCrosser=true, bool canShootOverUnits = false, int coneWidth = 1);

    virtual std::string terrainAttack(TerrainTile* terrain, int distance);

	virtual std::string rotate(Direction _dir);

	virtual std::string meleeAttack(UnitTile* _unit);
};

