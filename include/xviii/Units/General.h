#pragma once

#include "xviii/Units/Cavalry.h"

class General : public Cavalry
{
public:
	General(World& _world, Player* _belongsToPlayer, TextureManager::Unit _texture, std::string _name, UnitType _type, UnitFamily _familyType, Direction _dir);

	//General's reset() is overloaded because calculateEffectiveMov() shouldn't be called for him
	virtual void reset();
	//General's takeDamage() is overloaded due to the rule that all other friendlies lose 2 hp on his death
	virtual void takeDamage(UnitTile* attacker, float& _dmg, int distance);

};

