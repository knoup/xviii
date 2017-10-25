#pragma once

#include "boost/filesystem.hpp"
#include "boost/filesystem/fstream.hpp"

#include "xviii/Core/TextureManager.h"
#include "xviii/Core/Player.h"

class UnitLoader
{
public:
	struct UnitClassData{
		//This struct contains all the data needed to "create" classes from read
		//txt files; the name acts as a unique ID
		UnitClassData(std::string _unitID, boost::filesystem::path _path) :
			unitID{_unitID},
			displayName{},
			shortDisplayName{},
			textureID{},
			mPath{_path},
			unitName{},
			unitType{},
			unitFamilyType{},
            availableFactions{},
            availableCultures{},
            eras{},
            rangedAttackDistValues{},
            bridgeAttackDistValues{},
            healingRangeValues{},
            flankModifierValues{},
            bonusesVsMainTypes{},
            bonusesVsFamilyTypes{},
            bonusesVsUnitIDs{}
		{
		}

        std::string unitID;
		std::string displayName;
		std::string shortDisplayName;
		std::string textureID;

		boost::filesystem::path mPath;

		std::string unitName;
		UnitTile::UnitType unitType;
		UnitTile::UnitFamily unitFamilyType;

        std::vector<std::string> availableFactions;
        std::vector<std::string> availableCultures;

		std::vector<World::Era> eras;
		//Elements must be inserted in order of furthest to shortest distances; the first
		//element's upper threshold should represent the furthest a unit can shoot
		std::vector<UnitTile::RangedAttackRange> rangedAttackDistValues;
		std::vector<UnitTile::RangedAttackRange> bridgeAttackDistValues;
		std::vector<UnitTile::HealingRange> healingRangeValues;

		std::vector<UnitTile::FlankModifiers> flankModifierValues;
		std::vector<UnitTile::BonusVSMainType> bonusesVsMainTypes;
		std::vector<UnitTile::BonusVSFamilyType> bonusesVsFamilyTypes;
		std::vector<UnitTile::BonusVsUnitID> bonusesVsUnitIDs;

		//////////////////
		bool hasSquareFormationAbility{false};
		bool hasLimberAbility{false};
		bool hasLancerAbility{false};
		/////////////////

		bool waterCrosser{false};

		float squareFormationModifier{0};

		bool melee{true};
		bool skirmish{false};
		bool frightening{false};
		bool halfRangedDamage{false};
		bool canShootOverUnits{false};

		int shotsPerTurn{1};
		int chargesPerTurn{1};

		float maxHp{10};
		int maxMov{10};
		int coneWidth{1};
		int cost{1};
		int limit{0};
		int unitViewDistance{5};
		int flagViewDistance{7};
	};

	UnitLoader(TextureManager& _tm);
	void load();

	std::map<std::string, UnitClassData> customClasses;

private:
	void parse(boost::filesystem::path path);

	TextureManager& tm;
};

