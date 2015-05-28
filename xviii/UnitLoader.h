#pragma once

#include "boost/filesystem.hpp"
#include "boost/filesystem/fstream.hpp"

#include "UnitTile.h"
//#include "Player.h"

class UnitLoader
{
public:
	struct UnitClassData{
		//This struct contains all the data needed to "create" classes from read
		//txt files
		UnitClassData(std::string _name, boost::filesystem::path _path) : 
			name{_name},
			mPath{_path}
		{
		}

		std::string name;
		boost::filesystem::path mPath;

		//std::vector<Player::Nation> nations;
		std::string unitName;
		UnitTile::UnitType unitType;
		UnitTile::UnitFamily unitFamilyType;

		std::vector<UnitTile::RangedAttackRange> rangedAttackDistValues;
		std::vector<UnitTile::HealingRange> healingRangeValues;

		bool melee;
		bool skirmish;
		bool frightening;
		bool lancer;

		float maxHp;
		int maxMov;
		int cost;
	};

	UnitLoader();
	void load();

	std::map<std::string, UnitClassData> customClasses;

private:
	void parse(boost::filesystem::path path);
};

