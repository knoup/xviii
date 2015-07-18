#include "xviii/Headers/stdafx.h"
#include "xviii/Core/SaveGame.h"

#include "xviii/Core/Game.h"
#include <boost/algorithm/string/find.hpp>

Player::Nation stringToNation(std::string _name){
	//nation, flag, name
	#define X(nat, fla, str)\
	if (_name == str)\
		return nat;
	NATIONPROPERTIES
	#undef X

	return Player::Nation::ALL;
}

UnitTile::Direction stringToDir(std::string _dir){
	if (_dir == "N"){
		return UnitTile::Direction::N;
	}
	else if (_dir == "E"){
		return UnitTile::Direction::E;
	}
	else if (_dir == "S"){
		return UnitTile::Direction::S;
	}
	else if (_dir == "W"){
		return UnitTile::Direction::W;
	}

	return UnitTile::Direction::N;
}

/*
std::string toRomanNumerals(int n){
	std::string result;

	std::vector<std::pair<int, std::string>> romanNumerals;

	romanNumerals.push_back(std::make_pair(100, "C"));
	romanNumerals.push_back(std::make_pair(90, "XC"));
	romanNumerals.push_back(std::make_pair(50, "L"));
	romanNumerals.push_back(std::make_pair(40, "XL"));
	romanNumerals.push_back(std::make_pair(10, "X"));
	romanNumerals.push_back(std::make_pair(9, "IX"));
	romanNumerals.push_back(std::make_pair(5, "V"));
	romanNumerals.push_back(std::make_pair(4, "IV"));
	romanNumerals.push_back(std::make_pair(1, "I"));
	romanNumerals.push_back(std::make_pair(0, ""));

	for (std::vector<std::pair<int, std::string>>::iterator it{romanNumerals.begin()}; it->first > 0; ++it){
		while (n >= it->first){
			result += it->second;
			n -= it->first;
		}
	}

	return result;

}*/


SaveGame::SaveGame(Game* _game) :
game{_game}
{
}

bool SaveGame::create(){

	#define INDENT "\t"

	if (!boost::filesystem::exists("save")){
		boost::filesystem::create_directory("save");
	}

	std::string saveName{"turn_" + std::to_string(game->mWorld.getElapsedTurns())};

	//Check if a file with the same name exists

	boost::filesystem::recursive_directory_iterator end;

	for (boost::filesystem::recursive_directory_iterator it("save"); it != end; ++it){
		if (it->path().filename().leaf().stem() == saveName){
			saveName += "i";
		}
	}

	boost::filesystem::ofstream save;

	save.open("save\\" + saveName + ".dat");

	save << "turn=" << game->mWorld.getElapsedTurns() << std::endl;
	std::string eraString;
	World::Era currentEra = game->mWorld.getEra();

		#define X(_str, _era)\
		if(_era == currentEra){\
			eraString = _str;\
		}
		ERAPROPERTIES
		#undef X

	save << "era=" << eraString << std::endl;
	save << "player1=" << game->Player1->getName() << std::endl;
	save << "player2=" << game->Player2->getName() << std::endl;
	save << "player1Cam=" << game->Player1->view.getCenter().x << " " << game->Player1->view.getCenter().y << std::endl;
	save << "player2Cam=" << game->Player2->view.getCenter().x << " " << game->Player2->view.getCenter().y << std::endl;
	save << "currentPlayer=";

	if (game->currentPlayer == game->Player1){
		save << "player1";
	}
	else if (game->currentPlayer == game->Player2){
		save << "player2";
	}

	save << std::endl;
	save << std::endl;

	//Save terrain data

	save << "w{" << std::endl;

	int worldSizeIndex = game->mWorld.terrainLayer.size();

	for (int i{0}; i < worldSizeIndex; ++i){
		TerrainTile::TerrainType currentType = game->mWorld.terrainLayer[i]->getTerrainType();

		//Don't write MEADOW files. Since a lot of tiles will be meadows, this significantly reduces
		//the save file size (and there's less to load)
		if (currentType == TerrainTile::TerrainType::MEADOW){
			continue;
		}

		save << INDENT << std::to_string(i) << "=";

		switch (currentType){
			//type, class, texture, string
			#define X(_type, cl, texture, str)\
			case(_type):\
			save << str;\
			break;
			TERRAINPROPERTIES
			#undef X
		}

        //"Duct tape code" - make this cleaner in the future
        ///////////////////////////////////////////////////////////////
		if(currentType == TerrainTile::TerrainType::BRIDGE){
            Bridge* p = static_cast<Bridge*>(game->mWorld.terrainLayer[i].get());

            if(p->getOrientation() == TerrainTile::Orientation::VERTICAL){
                save << ":" << 0;
            }
            else{
                save << ":" << 1;
            }
            save << ":" << std::to_string(p->getHp());
		}

		else if(currentType == TerrainTile::TerrainType::TBRIDGE){
            TBridge* t = static_cast<TBridge*>(game->mWorld.terrainLayer[i].get());

            if(t->getOrientation() == TerrainTile::Orientation::VERTICAL){
                save << ":" << 0;
            }
            else{
                save << ":" << 1;
            }
            save << ":" << std::to_string(t->getHp());
		}

		///////////////////////////////////////////////////////////////

		save << std::endl;
	}

	save << "}w" << std::endl;
	save << std::endl;

	for (auto& player : game->mPlayers){
		for (auto& unit : player->getUnits()){
			sf::Vector2i coords{game->mWorld.cartesianPosAtIndex(game->mWorld.indexAtTile(*unit))};

			save << "u{" << std::endl;

			save << INDENT << "type=" << unit->getName() << std::endl;
			save << INDENT << "faction=";

			if (unit->getPlayer() == game->Player1){
				save  << "player1";
			}
			else if (unit->getPlayer() == game->Player2){
				save << "player2";
			}

			save << std::endl;
			save << INDENT << "pos=" << coords.x + 1 << " " << coords.y + 1 << std::endl;
			save << INDENT << "dir=" << unit->dirToString() << std::endl;
			save << INDENT << "hp=" << unit->roundFloat(unit->gethp()) << std::endl;
			save << INDENT << "mov=" << unit->getMov() << std::endl;
			save << INDENT << "hasMoved=" << unit->getHasMoved() << std::endl;
			save << INDENT << "hasPartialRotated=" << unit->getHasPartialRotated() << std::endl;
			save << INDENT << "hasFullRotated=" << unit->getHasFullRotated() << std::endl;
			save << INDENT << "hasMeleeAttacked=" << unit->getHasMeleeAttacked() << std::endl;
			save << INDENT << "hasRangedAttacked=" << unit->getHasRangedAttacked() << std::endl;
			//No point in saving hasHealed if the unit cannot heal anyway; it will be initialised
			//to false by default
			if (unit->canHeal()){
				save << INDENT << "hasHealed=" << unit->getHasHealed() << std::endl;
			}

			if (unit->hasSquareFormationAbility()){
				save << INDENT << "squareFormationActive=" << unit->getSquareFormationActive() << std::endl;
			}

			if (unit->hasLimberAbility()){
				save << INDENT << "limber=" << unit->getLimber() << std::endl;
			}

			if (unit->hasLancerAbility()){
				save << INDENT << "lancerBonusReady=" << unit->getLancerBonusReady() << std::endl;
			}

			save << "}u" << std::endl;
			save << std::endl;
		}
	}

	save.close();
	return true;

}

void SaveGame::parse(boost::filesystem::path _dir){
	std::ifstream save;
	save.open(_dir.string());

	std::string line;

	#define AFTEREQUALS line.substr(line.find("=") + 1, line.size() - 1)

	while (save && std::getline(save, line)){
		if (line.find("turn=") != std::string::npos){
			int turn{std::stoi(AFTEREQUALS)};
			game->mWorld.setElapsedTurns(turn);
		}

		else if (line.find("era=") != std::string::npos){
			std::string str = AFTEREQUALS;

			#define X(_str, _era)\
			if(str == _str):\
				game->mWorld.setEra(_era);\
			ERAPROPERTIES
			#undef X
		}

		else if (line.find("player1=") != std::string::npos){
			Player::Nation nation{stringToNation(AFTEREQUALS)};

			game->Player1 = new Player({game->mManager, game->mWorld, nation, game->mtengine, true});
			game->mPlayers.emplace_back(game->Player1);
		}

		else if (line.find("player1Cam=") != std::string::npos){
			std::stringstream temp(AFTEREQUALS);

			sf::Vector2f view;

			temp >> view.x >> view.y;

			game->Player1->view.setCenter(view.x, view.y);
		}

		else if (line.find("player2=") != std::string::npos){
			Player::Nation nation{stringToNation(AFTEREQUALS)};

			game->Player2 = new Player({game->mManager, game->mWorld, nation, game->mtengine, false});
			game->mPlayers.emplace_back(game->Player2);
		}

		else if (line.find("player2Cam=") != std::string::npos){
			std::stringstream temp(AFTEREQUALS);

			sf::Vector2f view;

			temp >> view.x >> view.y;

			game->Player2->view.setCenter(view.x, view.y);

		}

		else if (line.find("currentPlayer=") != std::string::npos){
			std::string playerStr{AFTEREQUALS};

			if (playerStr == "player1"){
				game->currentPlayer = game->Player1;
				game->currentView = &game->Player1->view;
			}
			else if (playerStr == "player2"){
				game->currentPlayer = game->Player2;
				game->currentView = &game->Player2->view;
			}
		}


		//This algorithm fills in unreported tiles with MEADOWS automatically; for example, if we have in the save file
		//423=woods
		//479=water
		//522=urban
		//Tiles 424-478 and 480-521 will be filled with MEADOWS.
		//Furthermore, a check is made at the end to ensure there are no missing final tiles

		else if (line.find("w{") != std::string::npos){

			std::getline(save, line);

			//trueIndex starts at 0 and is incremented whenever a tile is created
			int trueIndex{0};
			//currentIndex simply stores the index of the current tile being read from the save file
			int currentIndex{0};

			sf::Vector2f currentPos{};

			while (line.find("}w") == std::string::npos){
				//At this point, our string is something like
				//3124=woods

				currentIndex = std::stoi(line.substr(0, line.find("=")));
				std::string currentTypeStr = AFTEREQUALS;

				while (trueIndex < currentIndex){
					currentPos = game->mWorld.pixelPosAtIndex(trueIndex);
					game->mWorld.terrainLayer[trueIndex] = std::move(std::unique_ptr<Meadow>(new Meadow(game->mWorld, currentPos)));
					trueIndex++;
				}

				currentPos = game->mWorld.pixelPosAtIndex(currentIndex);

				if(currentTypeStr.find("permbridge") != std::string::npos){
                    auto ptr = std::move(std::unique_ptr<Bridge>(new Bridge(game->mWorld, currentPos)));

                    //Our string might look like
                    //bridge:0:4

                    size_t pos1{0};
                    //Find the position of the first colon
                    pos1 = currentTypeStr.find(":");
                    //And the second
                    size_t pos2{0};
                    pos2 = currentTypeStr.find(":", pos1+1);



                    if(pos1 != std::string::npos && pos2 != std::string::npos){
                        std::string num1 = currentTypeStr.substr(pos1 + 1, pos2-1 - pos1);

                        if(std::stoi(num1) == 0){
                            ptr->flip(TerrainTile::Orientation::VERTICAL);
                        }
                        else{
                            ptr->flip(TerrainTile::Orientation::HORIZONTAL);
                        }

                        std::string num2 = currentTypeStr.substr(pos2+1, currentTypeStr.size() - 1);
                        int hp = std::stoi(num2);
                        ptr->setHp(hp);
                    }

                    game->mWorld.permanentBridges.push_back(ptr.get());
                    game->mWorld.terrainLayer[currentIndex] = std::move(ptr);
				}

				else if(currentTypeStr.find("tempbridge") != std::string::npos){
                    auto ptr = std::move(std::unique_ptr<TBridge>(new TBridge(game->mWorld, currentPos)));

                    size_t pos1{0};
                    //Find the position of the first colon
                    pos1 = currentTypeStr.find(":");
                    //And the second
                    size_t pos2{0};
                    pos2 = currentTypeStr.find(":", pos1+1);



                    if(pos1 != std::string::npos && pos2 != std::string::npos){
                        std::string num1 = currentTypeStr.substr(pos1 + 1, pos2-1 - pos1);

                        if(std::stoi(num1) == 0){
                            ptr->flip(TerrainTile::Orientation::VERTICAL);
                        }
                        else{
                            ptr->flip(TerrainTile::Orientation::HORIZONTAL);
                        }

                        std::string num2 = currentTypeStr.substr(pos2+1, currentTypeStr.size() - 1);
                        int hp = std::stoi(num2);
                        ptr->setHp(hp);
                    }

                    game->mWorld.temporaryBridges.push_back(ptr.get());
                    game->mWorld.terrainLayer[currentIndex] = std::move(ptr);
				}


                else{
				//type, class, texture, string
				#define X(_type, cl, texture, str)\
					if(currentTypeStr == str)\
						game->mWorld.terrainLayer[currentIndex] = std::move(std::unique_ptr<cl>(new cl(game->mWorld, currentPos)));
				TERRAINPROPERTIES
				#undef X

                }

                trueIndex++;
				std::getline(save, line);
			}

			currentIndex += 1;

			while (currentIndex <= ((game->mWorld.getDimensions().x * game->mWorld.getDimensions().y) -1 )){
				currentPos = game->mWorld.pixelPosAtIndex(currentIndex);
				game->mWorld.terrainLayer[currentIndex] = std::move(std::unique_ptr<Meadow>(new Meadow(game->mWorld, currentPos)));
				currentIndex++;
			}

            game->mWorld.connectBridges();
		}

		else if (line.find("u{") != std::string::npos){

			//Keeping these uninitialised for the moment to ensure I catch any bugs

			std::string name;
			Player* player{nullptr};
			sf::Vector2i pos;
			UnitTile::Direction dir;
			float hp;
			float mov;
			bool hasMoved;
			bool hasPartialRotated;
			bool hasFullRotated;
			bool hasMeleeAttacked;
			bool hasRangedAttacked;
			bool hasHealed{false};

			bool squareFormationActive{false};
			bool limber{false};
			bool lancerBonusReady{false};

			while (line.find("}u") == std::string::npos){


				if (line.find("type=") != std::string::npos){
					name = AFTEREQUALS;
				}

				else if (line.find("faction=") != std::string::npos){
					std::string nation{(AFTEREQUALS)};

					if (nation == "player1"){
						player = game->Player1;
					}
					else if (nation == "player2"){
						player = game->Player2;
					}
				}

				else if (line.find("pos=") != std::string::npos){
					std::stringstream temp(AFTEREQUALS);

					temp >> pos.x >> pos.y;

					//For convenience, coordinates are displayed to the player starting from 1; thus,
					//0,0 would actually be 1, 1

					pos.x -= 1;
					pos.y -= 1;
				}

				else if (line.find("dir=") != std::string::npos){
					dir = stringToDir(AFTEREQUALS);
				}

				else if (line.find("hp=") != std::string::npos){
					//Have to use the same method as for pos, otherwise floats get rounded...
					std::stringstream temp(AFTEREQUALS);

					temp >> hp;
				}

				else if (line.find("mov=") != std::string::npos){
					mov = std::stoi(AFTEREQUALS);
				}

				else if (line.find("hasMoved=") != std::string::npos){
					hasMoved = std::stoi(AFTEREQUALS);
				}

				else if (line.find("hasPartialRotated=") != std::string::npos){
					hasPartialRotated = std::stoi(AFTEREQUALS);
				}

				else if (line.find("hasFullRotated=") != std::string::npos){
					hasFullRotated = std::stoi(AFTEREQUALS);
				}

				else if (line.find("hasMeleeAttacked=") != std::string::npos){
					hasMeleeAttacked = std::stoi(AFTEREQUALS);
				}

				else if (line.find("hasRangedAttacked=") != std::string::npos){
					hasRangedAttacked = std::stoi(AFTEREQUALS);
				}
				else if (line.find("hasHealed=") != std::string::npos){
					hasHealed = std::stoi(AFTEREQUALS);
				}

				else if (line.find("squareFormationActive=") != std::string::npos){
					squareFormationActive = std::stoi(AFTEREQUALS);
				}

				else if (line.find("limber=") != std::string::npos){
					limber = std::stoi(AFTEREQUALS);
				}

				else if (line.find("lancerBonusReady=") != std::string::npos){
					lancerBonusReady = std::stoi(AFTEREQUALS);
				}


				std::getline(save, line);

			}


			player->loadUnit(name, pos, dir, hp, mov, hasMoved, hasPartialRotated, hasFullRotated, hasMeleeAttacked, hasRangedAttacked, hasHealed, squareFormationActive, limber, lancerBonusReady);

		}


	}

	#undef AFTEREQUALS

}

//Older version of the world parsing algorithm that requires every tile's type be reported
/*
else if (line.find("w{") != std::string::npos){

	std::getline(save, line);

	while (line.find("}w") == std::string::npos){
		//At this point, our string is something like
		//3124=meadow

		int currentIndex = std::stoi(line.substr(0, line.find("=")));
		std::string currentTypeStr = AFTEREQUALS;

		sf::Vector2f currentPos = game->mWorld.pixelPosAtIndex(currentIndex);

		//type, class, texture, string
		#define X(_type, cl, texture, str)\
		if(currentTypeStr == str)\
				game->mWorld.terrainLayer[currentIndex] = std::move(std::unique_ptr<cl>(new cl(&game->mWorld, game->mTextureManager, currentPos)));
			TERRAINPROPERTIES
			#undef X

			std::getline(save, line);
	}

}
*/
