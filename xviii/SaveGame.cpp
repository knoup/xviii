#include "stdafx.h"
#include "SaveGame.h"

#include "Game.h"

Player::Nation stringToNation(std::string _name){
	if (_name == "Austria"){
		return Player::Nation::AUS;
	}
	else if (_name == "Prussia"){
		return Player::Nation::PRU;
	}
}

UnitTile::UnitType stringToUnitType(std::string _type){
	if (_type == "inf"){
		return UnitTile::UnitType::INF;
	}
	else if (_type == "cav"){
		return UnitTile::UnitType::CAV;
	}
	else if (_type == "cuir"){
		return UnitTile::UnitType::CUIR;
	}
	else if (_type == "drag"){
		return UnitTile::UnitType::DRAG;
	}
	else if (_type == "lcav"){
		return UnitTile::UnitType::LCAV;
	}
	else if (_type == "art"){
		return UnitTile::UnitType::ART;
	}
	else if (_type == "mor"){
		return UnitTile::UnitType::MOR;
	}
	else if (_type == "gen"){
		return UnitTile::UnitType::GEN;
	}
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


SaveGame::SaveGame(Game* _game) : 
game{_game}
{
}

void SaveGame::create(){
	std::ofstream save;
	save.open("save.dat");

	save << "turn=" << game->elapsedTurns << std::endl;
	save << "player=" << game->currentPlayer->getName() << std::endl;
	save << "AustriaCam=" << game->Player1.view.getCenter().x << " " << game->Player1.view.getCenter().y << std::endl;
	save << "PrussiaCam=" << game->Player2.view.getCenter().x << " " << game->Player2.view.getCenter().y << std::endl;

	save << std::endl;

	for (auto& unit : game->mWorld.getCombatLayer()){
		sf::Vector2i coords{game->mWorld.cartesianCoordsAtIndex(game->mWorld.indexAtTile(*unit))};

		save << "{" << std::endl;

		save << "type=" << unit->typeToString(unit->getUnitType()) << std::endl;
		save << "faction=" << unit->getPlayer()->getName() << std::endl;
		save << "pos=" << coords.x + 1 << " " << coords.y + 1 << std::endl;
		save << "dir=" << unit->dirToString(unit->getDir()) << std::endl;
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
}


/*
TODO	
Make formatting less rigid so that e.g. a space doesn't break everything
*/
void SaveGame::parse(){
	std::ifstream save;
	save.open("save.dat");

	std::string line;


	while (save && std::getline(save, line)){
		if (line.find("turn=") != std::string::npos){
			int turn{std::stoi(line.substr(5))};
			game->elapsedTurns = turn;
		}

		else if (line.find("player=") != std::string::npos){
			Player::Nation nation{stringToNation(line.substr(7))};

			if (nation == Player::Nation::AUS){
				game->currentPlayer = &game->Player1;
			}

			else if (nation == Player::Nation::PRU){
				game->currentPlayer = &game->Player2;
			}

			game->currentView = &game->currentPlayer->view;
		}

		else if (line.find("AustriaCam=") != std::string::npos){
			std::stringstream temp(line);
			temp.ignore(11);

			sf::Vector2f view;

			temp >> view.x >> view.y;

			game->Player1.view.setCenter(view.x, view.y);
		}

		else if (line.find("PrussiaCam=") != std::string::npos){
			std::stringstream temp(line);
			temp.ignore(11);

			sf::Vector2f view;

			temp >> view.x >> view.y;

			game->Player2.view.setCenter(view.x, view.y);

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

				else if (line.find("faction=") != std::string::npos){
					Player::Nation nation{stringToNation(line.substr(8))};

					if (nation == Player::Nation::AUS){
						player = &game->Player1;
					}
					else if (nation == Player::Nation::PRU){
						player = &game->Player2;
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