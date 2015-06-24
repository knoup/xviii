#pragma once

#include "xviii/Units/Cavalry.h"

class General : public Cavalry
{
public:
	General(UnitLoader& _unitLoader, World& _world, boost::random::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& _tm, FontManager& _fm, TextureManager::Unit _texture, std::string _name, UnitType _type, UnitFamily _familyType, Direction _dir);

    inline virtual bool canAttackTerrain(){return false;};
    inline virtual bool attacksTerrainWithUnits(){return false;};

	//General's reset() is overloaded because calculateEffectiveMov() shouldn't be called for him
	virtual void reset();
	//General's takeDamage() is overloaded due to the rule that all other friendlies lose 2 hp on his death
	virtual void takeDamage(UnitTile* attacker, float& _dmg, int distance);

};

