#pragma once

#include "boost/filesystem.hpp"
#include "boost/filesystem/fstream.hpp"

#include "xviii/Core/TextureManager.h"
#include "xviii/Core/Player.h"

class FactionLoader{

public:

    struct FactionClassData{

        FactionClassData(std::string _factionID, boost::filesystem::path _path) :
			factionID{_factionID},
			displayName{},
			shortDisplayName{},
			textureID{},
			mPath{_path},
			languageID{"english"},
			factionCulture{},
			availableInCustomBattles{true}
		{
		}

        //A faction's display name is the way it appears in-game.
        //ex: Prussia
        //It is initialised as the factionID just in case a name is not specified
        //(which shouldn't happen, but whatever)

        //A faction's ID is the way it appears in the files. For example,
        //PRU. The nation's ID is the name of the .txt defining the faction

        //A faction's textureID is the name of the file (png) located in
        //assets/gfx/factions that the faction uses as its flag.

        std::string factionID;
        std::string displayName;
        std::string shortDisplayName;
        std::string textureID;

        boost::filesystem::path mPath;

        std::string languageID;
        std::string factionCulture;
        bool availableInCustomBattles;

    };

    FactionLoader(TextureManager& _tm);
    void load();

    std::map<std::string, FactionClassData> customFactions;

private:
    void parse(boost::filesystem::path path);

    TextureManager& tm;
};
