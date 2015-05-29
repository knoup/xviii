#pragma once

#include "boost/filesystem.hpp"
#include "boost/filesystem/fstream.hpp"

#include "UnitTile.h"
#include "TextureManager.h"
#include "Player.h"

class UnitLoader
{
public:
	struct UnitClassData{
		//This struct contains all the data needed to "create" classes from read
		//txt files; the name acts as a unique ID
		UnitClassData(std::string _name, boost::filesystem::path _path) : 
			name{_name},
			mPath{_path}
		{
		}

		std::string name;
		boost::filesystem::path mPath;

		std::vector<Player::Nation> nations;
		std::string unitName;
		UnitTile::UnitType unitType;
		UnitTile::UnitFamily unitFamilyType;
		TextureManager::Unit texture;

		//Elements must be inserted in order of furthest to shortest distances; the first 
		//element's upper threshold should represent the furthest a unit can shoot
		std::vector<UnitTile::RangedAttackRange> rangedAttackDistValues;
		std::vector<UnitTile::HealingRange> healingRangeValues;

		std::vector<UnitTile::FlankModifiers> flankModifierValues;

		bool melee;
		bool skirmish;
		bool frightening;
		bool halfRangedDamage;
		bool lancer;

		float maxHp;
		int maxMov;
		int cost;
		int limit;
	};

	UnitLoader(TextureManager& _tm);
	void load();

	std::map<std::string, UnitClassData> customClasses;

private:
	void parse(boost::filesystem::path path);

	TextureManager& tm;
};

