#pragma once

#include "Cuirassier.h"

class KhevMkhedrebi : public Cuirassier
{
public:
	KhevMkhedrebi(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir);

	virtual int getMaxHp() const;
	virtual int getMaxMov() const;
	virtual int getMaxRange() const;

private:
	static const int maxhp{12};
	static const int maxMov{12};
	static const int maxRange{0};
};
