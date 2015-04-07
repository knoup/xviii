#pragma once

#include "UnitTile.h"



class General : public UnitTile
{
public:
	General(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir);

	//General's reset is overloaded due to the additional hasHealed variable that needs to be reset; giving it to all other UnitTiles would
	//be redundant since only General can even heal
	virtual void reset();
	//General's takeDamage() is overloaded due to the rule that all other friendlies lose 2 hp on his death
	virtual void takeDamage(float _dmg);

	virtual std::string rotate(Direction _dir);
	virtual std::string interactWithFriendly(UnitTile* _unit);

	virtual std::string attack(UnitTile* _unit, int distance);

	virtual int getMaxHp() const;
	virtual int getMaxMov() const;
	virtual int getMaxRange() const;

	virtual std::string attack(Infantry* inf, int distance);
	virtual std::string attack(Cavalry* cav, int distance);
	virtual std::string attack(Cuirassier* cuir, int distance);
	virtual std::string attack(Dragoon* drag, int distance);
	virtual std::string attack(LightCav* lcav, int distance);
	virtual std::string attack(Artillery* art, int distance);
	virtual std::string attack(Mortar* mor, int distance);
	virtual std::string attack(General* gen, int distance);
	virtual std::string attack(Akinci* aki, int distance);

	virtual std::string rangedAttack(UnitTile* unit, int distance);

	virtual float getFlankModifier(UnitFamily _family, Modifier _flank);

	virtual bool getHasHealed() const;
	virtual void setHasHealed(bool _hasHealed);
	
private:
	bool hasHealed{false};

	static const int maxhp{5};
	static const int maxMov{6};
	static const int maxRange{2};
};

