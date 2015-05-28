#include "stdafx.h"
#include "UnitLoader.h"


UnitLoader::UnitLoader()
{
}

void UnitLoader::load(){
	boost::filesystem::recursive_directory_iterator end;

	for (boost::filesystem::recursive_directory_iterator it("assets/units"); it != end; ++it){
		parse(it->path());
	}
}

void UnitLoader::parse(boost::filesystem::path path){
	//Create a new UnitClassData; initialise its name as "temp" while we get it from the file itself
	std::unique_ptr<UnitClassData> newClass = std::move(std::unique_ptr<UnitClassData>(new UnitClassData("temp", path)));

	std::ifstream unitData;
	unitData.open(path.string());

	std::string currentLine;

	#define AFTERCOLON currentLine.substr(currentLine.find(":") + 1, currentLine.size() - 1)
	#define EXISTS != std::string::npos

	while (unitData && std::getline(unitData, currentLine)){
		//
		//NATIONS SHOULD GO HERE
		//

		if (currentLine.find("STRING:") EXISTS){
			newClass->name = AFTERCOLON;
		}

		//
		//SPRITES SHOULD GO HERE
		//

		//
		//MAIN TYPES SHOULD GO HERE
		//

		//
		//FAMILY TYPES SHOULD GO HERE
		//

		else if (currentLine.find("HP:") EXISTS){
			newClass->maxHp = std::stoi(AFTERCOLON);
		}

		else if (currentLine.find("MOV:") EXISTS){
			newClass->maxMov = std::stoi(AFTERCOLON);
		}

		else if (currentLine.find("COST:") EXISTS){
			newClass->cost = std::stoi(AFTERCOLON);
		}

		else if (currentLine.find("MELEE:") EXISTS){
			newClass->melee = std::stoi(AFTERCOLON);
		}

		else if (currentLine.find("SKIRMISH:") EXISTS){
			newClass->skirmish = std::stoi(AFTERCOLON);
		}

		else if (currentLine.find("FRIGHTENING:") EXISTS){
			newClass->frightening = std::stoi(AFTERCOLON);
		}

		else if (currentLine.find("LANCER:") EXISTS){
			newClass->lancer = std::stoi(AFTERCOLON);
		}

		else if (currentLine.find("RANGED") EXISTS){
			std::getline(unitData, currentLine);

			while (currentLine.find("}") == std::string::npos){
				if (currentLine.find("DEFINE:") EXISTS){
					std::string str = AFTERCOLON;

					std::vector<float> rangeArgs;

					size_t pos = 0;

					while ((pos = str.find(":")) != std::string::npos){
						rangeArgs.push_back(std::stoi(str.substr(0, pos)));
						str.erase(0, pos + 1);
					}

					newClass->rangedAttackDistValues.emplace_back(rangeArgs[0], rangeArgs[1], rangeArgs[2], rangeArgs[3], rangeArgs[4], rangeArgs[5]);

					std::getline(unitData, currentLine);
				}

			}
		}

		else if (currentLine.find("HEALING") EXISTS){
			std::getline(unitData, currentLine);

			while (currentLine.find("}") == std::string::npos){
				if (currentLine.find("DEFINE:") EXISTS){
					std::string str = AFTERCOLON;

					std::vector<float> healingArgs;

					size_t pos = 0;

					while ((pos = str.find(":")) != std::string::npos){
						healingArgs.push_back(std::stoi(str.substr(0, pos)));
						str.erase(0, pos + 1);
					}

					newClass->healingRangeValues.emplace_back(healingArgs[0], healingArgs[1], healingArgs[2]);

					std::getline(unitData, currentLine);
				}

			}
		}
	}
}