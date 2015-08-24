#include "xviii/Headers/stdafx.h"
#include "xviii/Core/UnitLoader.h"

UnitLoader::UnitLoader(TextureManager& _tm) :
tm(_tm)
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

	std::getline(unitData, currentLine);
	if (!(currentLine.find("UNIT DEFINITION") EXISTS)){
		return;
	}

	while (unitData && std::getline(unitData, currentLine)){

        if (currentLine.find("NATIONS:") EXISTS){
			std::getline(unitData, currentLine);

            while (currentLine.find("}") == std::string::npos){
				if (currentLine.find("DEFINE:") EXISTS){

					std::string str = AFTERCOLON;
                    newClass->availableFactions.emplace_back(str);

				}

				std::getline(unitData, currentLine);
			}
		}

        else if (currentLine.find("STRING:") EXISTS){
			newClass->name = AFTERCOLON;
		}

		else if (currentLine.find("SPRITE:") EXISTS){
			newClass->textureID = AFTERCOLON;
		}

		else if (currentLine.find("MAIN_TYPE:") EXISTS){
			std::string str = AFTERCOLON;

			#define X(_str, mainType, cl)\
			if(str == _str){\
				newClass->unitType = mainType;\
									}
			MAINTYPEPROPERTIES
			#undef X
		}

		else if (currentLine.find("FAMILY_TYPE:") EXISTS){
			std::string str = AFTERCOLON;

			#define X(_str, familyType)\
			if(str == _str){\
				newClass->unitFamilyType = familyType;\
			}
			FAMILYTYPEPROPERTIES
			#undef X
		}

		else if (currentLine.find("ERA") EXISTS){
			std::getline(unitData, currentLine);

			while (currentLine.find("}") == std::string::npos){

				if (currentLine.find("DEFINE:") EXISTS){
					std::string str = AFTERCOLON;

					#define X(_str, _era)\
					if(str == _str){\
						newClass->eras.push_back(_era);\
					}
						ERAPROPERTIES
					#undef X
					}

					std::getline(unitData, currentLine);
			}
		}

		else if (currentLine.find("SQUAREFORMATION:") EXISTS){
			newClass->hasSquareFormationAbility = std::stoi(AFTERCOLON);
		}

		else if (currentLine.find("SQUAREFORMATIONMODIFIER:") EXISTS){
			std::stringstream ss(AFTERCOLON);
			ss >> newClass->squareFormationModifier;
		}

		else if (currentLine.find("LIMBER:") EXISTS){
			newClass->hasLimberAbility = std::stoi(AFTERCOLON);
		}

		else if (currentLine.find("LANCER:") EXISTS){
			newClass->hasLancerAbility = std::stoi(AFTERCOLON);
		}

		else if (currentLine.find("WATERCROSSER:") EXISTS){
			newClass->waterCrosser = std::stoi(AFTERCOLON);
		}

		else if (currentLine.find("HP:") EXISTS){
			newClass->maxHp = std::stoi(AFTERCOLON);
		}

		else if (currentLine.find("MOV:") EXISTS){
			newClass->maxMov = std::stoi(AFTERCOLON);
		}

		else if (currentLine.find("COST:") EXISTS){
			newClass->cost = std::stoi(AFTERCOLON);
		}

		else if (currentLine.find("LIMIT:") EXISTS){
			newClass->limit = std::stoi(AFTERCOLON);
		}

		else if (currentLine.find("SKIRMISH:") EXISTS){
			newClass->skirmish = std::stoi(AFTERCOLON);
		}

		else if (currentLine.find("FRIGHTENING:") EXISTS){
			newClass->frightening = std::stoi(AFTERCOLON);
		}

		else if (currentLine.find("HALFRANGEDDAMAGE:") EXISTS){
			newClass->halfRangedDamage = std::stoi(AFTERCOLON);
		}

		else if (currentLine.find("MELEE:") EXISTS){
			newClass->melee = std::stoi(AFTERCOLON);
		}

		else if (currentLine.find("FLANK") EXISTS){
			std::getline(unitData, currentLine);

			while (currentLine.find("}") == std::string::npos){

				if (currentLine.find("DEFINE:") EXISTS){
					//DEFINE:INF
					std::string str = AFTERCOLON;

					UnitTile::UnitType mainType;

					#define X(_str, _mainType, cl)\
					if(str == _str){\
						mainType = _mainType;\
					}
					MAINTYPEPROPERTIES
					#undef X

						std::getline(unitData, currentLine);

					UnitTile::FlankModifiers flankModifier{mainType};

					while (currentLine.find("}") == std::string::npos){
						if (currentLine.find("DEFINE:") EXISTS){
							str = AFTERCOLON;
							//str = "FRONT:0.5"

							std::string direction_str;

							std::string::size_type pos = str.find(':');

							if (pos != std::string::npos){
								direction_str = str.substr(0, pos);
							}

							//Stringstream to extract the modifier, to preserve decimals
							std::stringstream ss(str.substr(str.find(":") + 1, str.size() - 1));

							//Initialise the modifier as 0; modifiers of 0 are ignored in combat. In case there is
							//an empty string afterwards, nothing bad will happen.
							float modifier{0};

							if (!ss.str().empty()){
								ss >> modifier;
							}

							if (direction_str == "FRONT"){
								flankModifier.front = modifier;
							}
							else if (direction_str == "SIDE"){
								flankModifier.side = modifier;
							}
							else if (direction_str == "REAR"){
								flankModifier.rear = modifier;
							}
						}

						std::getline(unitData, currentLine);
					}

					newClass->flankModifierValues.emplace_back(flankModifier);
				}

				std::getline(unitData, currentLine);
			}

		}

		else if (currentLine.find("RANGED") EXISTS || currentLine.find("BRIDGE_ATTACK") EXISTS){
                bool ranged{currentLine.find("RANGED") EXISTS};
                bool bridge{currentLine.find("BRIDGE_ATTACK") EXISTS};

			std::getline(unitData, currentLine);

			while (currentLine.find("}") == std::string::npos){
				if (currentLine.find("DEFINE:") EXISTS){
					std::string str = AFTERCOLON;

					std::vector<float> rangeArgs;

					size_t pos = 0;

					//We do the whole mess with stringstream because regular stoi trunctuates
					//decimals, and we don't want that. We do an extra go at the end to catch the
					//last variable that isn't done in the loop.

					while ((pos = str.find(",")) != std::string::npos){
						std::string temp = str.substr(0, pos);
						std::stringstream ss(temp);
						float arg;
						ss >> arg;
						rangeArgs.push_back(arg);
						str.erase(0, pos + 1);
					}

					std::string temp = str.substr(0, pos);
					std::stringstream ss(temp);
					float arg;
					ss >> arg;
					rangeArgs.push_back(arg);

                    if(ranged){
                        newClass->rangedAttackDistValues.emplace_back(rangeArgs[0], rangeArgs[1], rangeArgs[2], rangeArgs[3], rangeArgs[4], rangeArgs[5]);
                    }
                    else if(bridge){
                        newClass->bridgeAttackDistValues.emplace_back(rangeArgs[0], rangeArgs[1], rangeArgs[2], rangeArgs[3], rangeArgs[4], rangeArgs[5]);
                    }

				}

				std::getline(unitData, currentLine);
			}
		}

		else if (currentLine.find("HEALING") EXISTS){
			std::getline(unitData, currentLine);

			while (currentLine.find("}") == std::string::npos){
				if (currentLine.find("DEFINE:") EXISTS){
					std::string str = AFTERCOLON;

					std::vector<float> healingArgs;

					size_t pos = 0;

					//We do the whole mess with stringstream because regular stoi trunctuates
					//decimals, and we don't want that. We do an extra go at the end to catch the
					//last variable that isn't done in the loop.

					while ((pos = str.find(",")) != std::string::npos){
						std::string temp = str.substr(0, pos);
						std::stringstream ss(temp);
						float arg;
						ss >> arg;
						healingArgs.push_back(arg);
						str.erase(0, pos + 1);
					}

					std::string temp = str.substr(0, pos);
					std::stringstream ss(temp);
					float arg;
					ss >> arg;
					healingArgs.push_back(arg);

					newClass->healingRangeValues.emplace_back(healingArgs[0], healingArgs[1], healingArgs[2]);

				}

				std::getline(unitData, currentLine);
			}
		}

		else if (currentLine.find("MELEE_BONUS") EXISTS){
			std::getline(unitData, currentLine);

			while (currentLine.find("}") == std::string::npos){

				if (currentLine.find("DEFINE:") EXISTS){
					std::string str(AFTERCOLON);
					//MAIN:INF:2,0

					//get "MAIN"
					std::string first_part = str.substr(0, str.find_first_of(":"));

					size_t pos1 = str.find_first_of(":");
					size_t pos2 = str.find_last_of(":");

					pos1 += 1;
					pos2 -= pos1;

					//get "INF"
					std::string second_part = str.substr(pos1, pos2);

					//str = MAIN:INF:2,0
					//first_part = MAIN
					//second_part = INF

					//get "2,0,1,1"
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

					float arg1;
					int arg2;
					int arg3;
					int arg4;

					arg1AsString >> arg1;
					arg2AsString >> arg2;
					arg3AsString >> arg3;
					arg4AsString >> arg4;

					if (first_part == "MAIN"){

						UnitTile::UnitType mainType;

						#define X(_str, _mainType, cl)\
						if(second_part == _str){\
							mainType = _mainType;\
						}
						MAINTYPEPROPERTIES
						#undef X

							//mainType = INF;

							newClass->bonusesVsMainTypes.emplace_back(mainType, arg1, arg2, arg3, arg4);

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

							newClass->bonusesVsFamilyTypes.emplace_back(familyType, arg1, arg2, arg3, arg4);
					}

					else if (first_part == "NAME"){
						newClass->bonusesVsNames.emplace_back(second_part, arg1, arg2, arg3, arg4);
					}

					else{
						break;
					}

				}

				std::getline(unitData, currentLine);
			}

		}

	}

	#undef AFTERCOLON
	#undef EXISTS

	unitData.close();
	customClasses.emplace(newClass->name, std::move(*newClass));
}
