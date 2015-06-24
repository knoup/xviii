#include "xviii/Headers/stdafx.h"
#include "xviii/Core/TerrainLoader.h"

TerrainLoader::TerrainLoader()
{
    //Initialise a "definition" for each terrain type with empty parameters. If there is anything relevant in bonuses.txt,
    //it will modify the contents of the appropriate definition

    #define TERRAINDATA std::move(std::unique_ptr<TerrainClassData>(new TerrainClassData()))

    customDefinitions.emplace(TerrainTile::TerrainType::MEADOW, TERRAINDATA);
    customDefinitions.emplace(TerrainTile::TerrainType::MUD, TERRAINDATA);
    customDefinitions.emplace(TerrainTile::TerrainType::SLOPES, TERRAINDATA);
    customDefinitions.emplace(TerrainTile::TerrainType::HILLS, TERRAINDATA);
    customDefinitions.emplace(TerrainTile::TerrainType::ROAD, TERRAINDATA);
    customDefinitions.emplace(TerrainTile::TerrainType::URBAN, TERRAINDATA);
    customDefinitions.emplace(TerrainTile::TerrainType::WOODS, TERRAINDATA);
    customDefinitions.emplace(TerrainTile::TerrainType::WATER, TERRAINDATA);
    customDefinitions.emplace(TerrainTile::TerrainType::PBRIDGE, TERRAINDATA);

    #undef TERRAINDATA
}

void TerrainLoader::load(){
	boost::filesystem::recursive_directory_iterator end;

	for (boost::filesystem::recursive_directory_iterator it("assets/terrain"); it != end; ++it){
        if(it->path().filename().leaf().stem() == "bonuses"){
            parse(it->path());
        }
	}
}

void TerrainLoader::parse(boost::filesystem::path path){
	std::ifstream terrainData;
	terrainData.open(path.string());

	std::string currentLine;

	#define AFTERCOLON currentLine.substr(currentLine.find(":") + 1, currentLine.size() - 1)
	#define EXISTS != std::string::npos

	std::getline(terrainData, currentLine);
	if (!(currentLine.find("TERRAIN DEFINITION") EXISTS)){
		return;
	}

	while (terrainData && std::getline(terrainData, currentLine)){

		if (currentLine.find("DEFINE_TERRAIN:") EXISTS){

            TerrainTile::TerrainType terrainType;

		    std::string tempstr = AFTERCOLON;

                #define X(_terrainType, _cl, _texture, _str)\
					if(tempstr == _str){\
						terrainType = _terrainType;\
					}
					TERRAINPROPERTIES
					#undef X

            TerrainClassData* current = (customDefinitions.at(terrainType)).get();

			std::getline(terrainData, currentLine);

			while (currentLine.find("}") == std::string::npos){

				if (currentLine.find("DEFINE:") EXISTS){
					std::string str(AFTERCOLON);
					//2:modifier
					//1: modifier is additional
					//0: not in melee
					//1: in ranged
					//1: when attacking
					//0: not when defending

					////MAIN:INF:2,1,0,1,1,0
					std::string first_part = str.substr(0, str.find_first_of(":"));

					size_t pos1 = str.find_first_of(":");
					size_t pos2 = str.find_last_of(":");

					pos1 += 1;
					pos2 -= pos1;

					std::string second_part = str.substr(pos1, pos2);

                    //As an example, let's pretend we have this:
					//str = MAIN:INF:2,1,0,1,1,0
					//first_part = MAIN
					//second_part = INF

					//get "2,1,0,1,1,0 "
					std::string last_part(str.substr(str.find_last_of(":") + 1, str.size()));

					std::vector<std::string> argsAsStrings;

					std::stringstream ss(last_part);
					std::string item;

					while (std::getline(ss, item, ',')){
						argsAsStrings.push_back(item);
					}

					std::stringstream arg1AsString(argsAsStrings[0]);
					std::stringstream arg2AsString(argsAsStrings[1]);
					std::stringstream arg3AsString(argsAsStrings[2]);
					std::stringstream arg4AsString(argsAsStrings[3]);
					std::stringstream arg5AsString(argsAsStrings[4]);
					std::stringstream arg6AsString(argsAsStrings[5]);

					float arg1; //2
					int arg2;   //1
					int arg3;   //0
					int arg4;   //1
					int arg5;   //1
					int arg6;   //0

					arg1AsString >> arg1;
					arg2AsString >> arg2;
					arg3AsString >> arg3;
					arg4AsString >> arg4;
					arg5AsString >> arg5;
					arg6AsString >> arg6;

                    if(first_part == "MAIN"){
                        UnitTile::UnitType mainType;

						#define X(_str, _mainType, cl)\
						if(second_part == _str){\
							mainType = _mainType;\
						}
						MAINTYPEPROPERTIES
						#undef X

                        //mainType = INF;

                        current->unitMainBonuses.emplace_back(mainType, arg1, arg2, arg3, arg4, arg5, arg6);
                    }

                    else if (first_part == "FAMILY"){
                        UnitTile::UnitFamily familyType;

						#define X(_str, _familyType)\
						if(second_part == _str){\
							familyType = _familyType;\
                        }
						FAMILYTYPEPROPERTIES
						#undef X

                        //familyType = INF;

                        current->unitFamilyBonuses.emplace_back(familyType, arg1, arg2, arg3, arg4, arg5, arg6);
                    }

                    else if(first_part == "STRING"){
                        current->unitStringBonuses.emplace_back(second_part, arg1, arg2, arg3, arg4, arg5, arg6);
                    }

				}

				std::getline(terrainData, currentLine);
			}

		}

	}

	#undef AFTERCOLON
	#undef EXISTS

	terrainData.close();
}
