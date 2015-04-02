#include "stdafx.h"
#include "SaveGame.h"

#include "Game.h"

Player::Nation stringToNation(std::string _name){
	//nation, flag, name
	#define X(nat, fla, str)\
	if (_name == str)\
		return nat;
	NATIONPROPERTIES
	#undef X
}

UnitTile::UnitType stringToUnitType(std::string _str){
	//UnitType, class, shorthand name
	#define X(type, cl, str)\
	if(_str == str)\
		return type;
	UNITPROPERTIES
	#undef X
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
	if (!boost::filesystem::exists("save")){
		boost::filesystem::create_directory("save");
	}

	std::string saveName{"turn_" + std::to_string(game->elapsedTurns)};

	//Check if a file with the same name exists

	boost::filesystem::recursive_directory_iterator end;

	for (boost::filesystem::recursive_directory_iterator it("save"); it != end; ++it){
		if (it->path().filename().leaf().stem() == saveName){
			saveName += "i";
		}
	}

	/*
	I cannot figure out why the following does not work. After several few successful iterations,
	index tends to get stuck at around 9. I have a feeling it's related to the order. Nonetheless,
	until I can figure it out, I will do it the old fashioned way.

	int index{0};

	for (boost::filesystem::recursive_directory_iterator it("save"); it != end; ++it){
		if (it->path().filename() == saveName + toRomanNumerals(index) ){
			++index;
		}
	}

	saveName += toRomanNumerals(index);	*/

	boost::filesystem::ofstream save;

	save.open("save\\" + saveName + ".dat");

	save << "turn=" << game->elapsedTurns << std::endl;
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

	std::cout << std::endl;

	save << std::endl;

	for (auto& unit : game->mWorld.getCombatLayer()){
		sf::Vector2i coords{game->mWorld.cartesianCoordsAtIndex(game->mWorld.indexAtTile(*unit))};

		save << "{" << std::endl;

		save << "type=" << unit->typeToString() << std::endl;
		save << "faction=" << unit->getPlayer()->getName() << std::endl;
		save << "pos=" << coords.x + 1 << " " << coords.y + 1 << std::endl;
		save << "dir=" << unit->dirToString() << std::endl;
		save << "hp=" << unit->roundFloat(unit->gethp()) << std::endl;
		save << "mov=" << unit->getMov() << std::endl;
		save << "hasMoved=" << unit->getHasMoved() << std::endl;
		save << "hasRotated=" << unit->getHasRotated() << std::endl;
		save << "hasAttacked=" << unit->getHasAttacked() << std::endl;

		if (unit->getUnitType() == UnitTile::UnitType::GEN){
			save << "hasHealed=" << unit->getHasHealed() << std::endl;
		}

		save << "}" << std::endl;
		save << std::endl;
	}

	save.close();
	return true;

}


/*
TODO
Make formatting less rigid so that e.g. a space doesn't break everything
*/
void SaveGame::parse(boost::filesystem::path _dir){
	std::ifstream save;
	save.open(_dir.string());

	std::string line;


	while (save && std::getline(save, line)){
		if (line.find("turn=") != std::string::npos){
			int turn{std::stoi(line.substr(5))};
			game->elapsedTurns = turn;
		}

		else if (line.find("player1=") != std::string::npos){
			Player::Nation nation{stringToNation(line.substr(8))};

			game->Player1 = new Player({game->mWorld, nation, game->mtengine, game->mTextureManager, game->mFontManager, true});
		}

		else if (line.find("player1Cam=") != std::string::npos){
			std::stringstream temp(line);
			temp.ignore(11);

			sf::Vector2f view;

			temp >> view.x >> view.y;

			game->Player1->view.setCenter(view.x, view.y);
		}

		else if (line.find("player2=") != std::string::npos){
			Player::Nation nation{stringToNation(line.substr(8))};

			game->Player2 = new Player({game->mWorld, nation, game->mtengine, game->mTextureManager, game->mFontManager, false});
		}

		else if (line.find("player2Cam=") != std::string::npos){
			std::stringstream temp(line);
			temp.ignore(11);

			sf::Vector2f view;

			temp >> view.x >> view.y;

			game->Player2->view.setCenter(view.x, view.y);

		}

		else if (line.find("currentPlayer=") != std::string::npos){
			std::string playerStr{line.substr(14)};

			if (playerStr == "player1"){
				game->currentPlayer = game->Player1;
				game->currentView = &game->Player1->view;
			}
			else if (playerStr == "player2"){
				game->currentPlayer = game->Player2;
				game->currentView = &game->Player2->view;
			}
		}

		else if (line.find("{") != std::string::npos){

			UnitTile::UnitType type;
			Player* player{nullptr};
			sf::Vector2i pos;
			UnitTile::Direction dir;
			float hp;
			float mov;
			bool hasMoved;
			bool hasRotated;
			bool hasAttacked;
			bool hasHealed{false};

			while (line.find("}") == std::string::npos){


				if (line.find("type=") != std::string::npos){
					type = stringToUnitType(line.substr(5));
				}

				/*In the interest of keeping the save files easily readable, rather than saving each unit's 
				faction as simply player1 or player2, we save it as the faction name and then, after the players
				are loaded, check which player it belongs to*/

				else if (line.find("faction=") != std::string::npos){
					Player::Nation nation{stringToNation(line.substr(8))};

					if (nation == game->Player1->getNation()){
						player = game->Player1;
					}
					else if (nation == game->Player2->getNation()){
						player = game->Player2;
					}
				}

				else if (line.find("pos=") != std::string::npos){
					std::stringstream temp(line);
					temp.ignore(4);

					temp >> pos.x >> pos.y;

					//For convenience, coordinates are displayed to the player starting from 1; thus, 
					//0,0 would actually be 1, 1

					pos.x -= 1;
					pos.y -= 1;
				}

				else if (line.find("dir=") != std::string::npos){
					dir = stringToDir(line.substr(4));
				}

				else if (line.find("hp=") != std::string::npos){
					//Have to use the same method as for pos, otherwise floats get rounded...
					std::stringstream temp(line);
					temp.ignore(3);

					temp >> hp;
				}

				else if (line.find("mov=") != std::string::npos){
					mov = std::stoi(line.substr(4));
				}

				else if (line.find("hasMoved=") != std::string::npos){
					hasMoved = std::stoi(line.substr(9));
				}

				else if (line.find("hasRotated=") != std::string::npos){
					hasRotated = std::stoi(line.substr(11));
				}

				else if (line.find("hasAttacked=") != std::string::npos){
					hasAttacked = std::stoi(line.substr(12));
				}

				else if (line.find("hasHealed=") != std::string::npos){
					hasHealed = std::stoi(line.substr(10));
				}


				std::getline(save, line);

			}


			player->loadUnit(type, pos, dir, hp, mov, hasMoved, hasRotated, hasAttacked, hasHealed);

		}


	}

}