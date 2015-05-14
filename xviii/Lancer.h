#pragma once

#include "Cavalry.h"

class Lancer : public Cavalry

{
public:
	Lancer(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir, TextureManager::Unit texType = TextureManager::Unit::LAN, UnitType uType = UnitType::LAN);

	inline virtual int getMaxHp() const{ return maxhp; };
	inline virtual int getMaxMov() const{ return maxMov; };
	inline virtual int getMaxRange() const{ return maxRange; };

	virtual bool hasLancerBonus(){ return true; };

private:
	static const int maxhp{10};
	static const int maxMov{12};
	static const int maxRange{0};
};

