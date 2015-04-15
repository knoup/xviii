#pragma once

#include "Cuirassier.h"

class PitsisKatsebi : public Cuirassier
{
public:
	PitsisKatsebi(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir);

	virtual int getMaxHp() const;
	virtual int getMaxMov() const;
	virtual int getMaxRange() const;

	virtual std::string rangedAttack(UnitTile* unit, int distance);

	//Override Cuirassier's bonuses by providing empty body
	virtual void preAttack(UnitTile* unit, bool attacking){};

private:
	static const int maxhp{14};
	static const int maxMov{12};
	static const int maxRange{5};
};

