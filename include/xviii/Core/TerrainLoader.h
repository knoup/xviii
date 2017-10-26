#pragma once

#include "boost/filesystem.hpp"
#include "boost/filesystem/fstream.hpp"

#include "xviii/Terrain/TerrainTile.h"
#include "xviii/Core/TextureManager.h"

#include <sstream>

class TerrainLoader
{
public:
	struct TerrainClassData{
		//This struct contains all the data needed to customise terrain bonuses from read
		//txt files

		TerrainClassData():
            unitMainBonuses{},
            unitFamilyBonuses{},
            unitIDBonuses{},
            unitIDMovementCapabilities{}
		{
		}

        std::vector<TerrainTile::UnitMainTypeBonus> unitMainBonuses;
        std::vector<TerrainTile::UnitFamilyTypeBonus> unitFamilyBonuses;
        std::vector<TerrainTile::UnitIDBonus> unitIDBonuses;

        //////////////////////////////////////////////////////////////////

        //This map uses a unit's NAME as a key, and a pair of booleans as the value.
        //The FIRST boolean specifies whether the unit is able to CROSS this terrain
        //tile;
        //The SECOND whether it can STOP in it.

        //I opted to make this only possible through string entry for now, in the interest of
        //avoiding too much overhead, taking into account this will be constantly accessed
        //by UnitTile::distanceFrom()
        std::map<std::string, std::pair<bool,bool>> unitIDMovementCapabilities;
	};

	TerrainLoader();
	void load();

	std::map<TerrainTile::TerrainType, std::unique_ptr<TerrainClassData>> customDefinitions{};

private:
	void parse(boost::filesystem::path path);
};

