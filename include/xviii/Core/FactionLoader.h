#pragma once

#include "boost/filesystem.hpp"
#include "boost/filesystem/fstream.hpp"

#include "xviii/Core/TextureManager.h"
#include "xviii/Core/Player.h"

class FactionLoader{

public:

    struct FactionClassData{

        FactionClassData(std::string _name, boost::filesystem::path _path) :
			name{_name},
			mPath{_path}
		{
		}

        std::string name;
        std::string textureID;

        boost::filesystem::path mPath;

        std::string languageID{"english"};

    };

    FactionLoader(TextureManager& _tm);
    void load();

    std::map<std::string, FactionClassData> customFactions;

private:
    void parse(boost::filesystem::path path);

    TextureManager& tm;
};
