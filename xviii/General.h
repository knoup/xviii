#pragma once

#include "Cavalry.h"

class General : public Cavalry
{
public:
	General(UnitLoader& _unitLoader, World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& _tm, FontManager& _fm, TextureManager::Unit _texture, std::string _name, UnitType _type, UnitFamily _familyType, Direction _dir);

	//General's reset() is overloaded due to the additional hasHealed variable that needs to be reset; giving it to all other UnitTiles would
	//be redundant since only General can even heal
	virtual void reset();
	//General's takeDamage() is overloaded due to the rule that all other friendlies lose 2 hp on his death
	virtual void takeDamage(UnitTile* attacker, float& _dmg, int distance);

	inline virtual int getMaxHp() const{ return maxhp; };
	inline virtual int getMaxMov() const{ return maxMov; };

	inline virtual int getCost() const{ return 0; };
	inline virtual int getLimit() const{ return 1; };
	
private:
	static const int maxhp{5};
	static const int maxMov{6};
};

