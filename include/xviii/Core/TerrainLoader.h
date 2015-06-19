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

        std::vector<TerrainTile::UnitMainTypeBonus> unitMainBonuses;
        std::vector<TerrainTile::UnitFamilyTypeBonus> unitFamilyBonuses;
        std::vector<TerrainTile::UnitStringBonus> unitStringBonuses;
	};

	TerrainLoader();
	void load();

	std::map<TerrainTile::TerrainType, TerrainClassData> customDefinitions;

private:
	void parse(boost::filesystem::path path);
};

