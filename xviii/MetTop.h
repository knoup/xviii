#pragma once

#include "Infantry.h"

class MetTop : public Infantry
{
public:
	MetTop(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir);
	
	virtual int getMaxHp() const;
	virtual int getMaxMov() const;
	virtual int getMaxRange() const;

private:
	static const int maxhp{12};
	static const int maxMov{6};
	static const int maxRange{6};
};

