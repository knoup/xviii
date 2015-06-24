#pragma once

#include "boost/filesystem.hpp"
#include "boost/filesystem/fstream.hpp"

#include "xviii/Units/UnitTile.h"
#include "xviii/Core/TextureManager.h"
#include "xviii/Core/Player.h"

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

		std::vector<World::Era> eras;
		//Elements must be inserted in order of furthest to shortest distances; the first
		//element's upper threshold should represent the furthest a unit can shoot
		std::vector<UnitTile::RangedAttackRange> rangedAttackDistValues;
		std::vector<UnitTile::RangedAttackRange> bridgeAttackDistValues;
		std::vector<UnitTile::HealingRange> healingRangeValues;

		std::vector<UnitTile::FlankModifiers> flankModifierValues;
		std::vector<UnitTile::BonusVSMainType> bonusesVsMainTypes;
		std::vector<UnitTile::BonusVSFamilyType> bonusesVsFamilyTypes;
		std::vector<UnitTile::BonusVSName> bonusesVsNames;

		//////////////////
		bool hasSquareFormationAbility{false};
		bool hasLimberAbility{false};
		bool hasLancerAbility{false};
		/////////////////

		bool waterCrosser{false};

		float squareFormationModifier{0};

		bool melee;
		bool skirmish;
		bool frightening;
		bool halfRangedDamage;

		float maxHp;
		int maxMov;
		int cost;
		int limit{0};
	};

	UnitLoader(TextureManager& _tm);
	void load();

	std::map<std::string, UnitClassData> customClasses;

private:
	void parse(boost::filesystem::path path);

	TextureManager& tm;
};

