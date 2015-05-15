#pragma once

#include "Infantry.h"

class ArtGuard : public Infantry
{
public:
	ArtGuard(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir, TextureManager::Unit texType = TextureManager::Unit::ARTGUARD, UnitType uType = UnitType::ARTGUARD);

	inline virtual int getMaxHp() const{ return maxhp; };
	inline virtual int getMaxMov() const{ return maxMov; };
	inline virtual int getMaxRange() const{ return maxRange; };

private:
	static const int maxhp{4};
	static const int maxMov{3};
	static const int maxRange{4};
};

