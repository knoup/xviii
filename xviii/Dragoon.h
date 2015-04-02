#pragma once

#include "UnitTile.h"


class Dragoon : public UnitTile
{
public:
	Dragoon(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir);

	virtual std::string rotate(Direction _dir);
	virtual std::string interactWithFriendly(UnitTile* _unit);

	virtual int getMaxHp() const;
	virtual int getMaxMov() const;
	virtual int getMaxRange() const;

	virtual std::string attack(UnitTile* _unit, int distance, UnitTile::Modifier flank);

	virtual std::string attack(Infantry* inf, int distance, UnitTile::Modifier flank);
	virtual std::string attack(Cavalry* cav, int distance, UnitTile::Modifier flank);
	virtual std::string attack(Cuirassier* cuir, int distance, UnitTile::Modifier flank);
	virtual std::string attack(Dragoon* drag, int distance, UnitTile::Modifier flank);
	virtual std::string attack(LightCav* lcav, int distance, UnitTile::Modifier flank);
	virtual std::string attack(Artillery* art, int distance, UnitTile::Modifier flank);
	virtual std::string attack(Mortar* mor, int distance, UnitTile::Modifier flank);
	virtual std::string attack(General* gen, int distance, UnitTile::Modifier flank);
	virtual std::string attack(Akinci* aki, int distance, UnitTile::Modifier flank);

	virtual std::string rangedAttack(UnitTile* unit, int distance);


private:

	static const int maxhp{10};
	static const int maxMov{12};
	static const int maxRange{9};
};



