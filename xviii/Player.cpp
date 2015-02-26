#include "stdafx.h"
#include "Player.h"


Player::Player(World& _world, Nation _nation, sf::Color _colour, std::mt19937& _mt19937, TextureManager& _tm, FontManager& _fm, sf::View _view, std::string _name) :
world{_world},
nation{_nation},
nationColour{_colour},
name{_name},
mt19937{_mt19937},
tm{_tm},
fm{_fm},
view{_view},
deploymentPoints{30},
ready{false}
{
	//Putting this in the initialisation list causes a crash for whatever reason, so 
	//I've moved it down here
	playerFlag = nationToSprite(nation);
}

bool Player::spawnUnit(UnitTile::UnitType _type, sf::Vector2i _worldCoords){

	auto terrain = world.terrainAtMouseCoords(_worldCoords);
	auto cartesianCoords = world.cartesianCoordsAtIndex(world.indexAtTile(*terrain));

	if (nation == Player::Nation::AUS){
		//Because coordinates start at [0,0], in order for Austria to have the same length of spawning
		//as Prussia does, we need to subtract 1
		if (cartesianCoords.y <= (world.getDimensions().y - (world.getDimensions().y/8)) - 1){
			return false;
		}
	}
	else if (nation == Player::Nation::PRU){
		if (cartesianCoords.y >= (world.getDimensions().y / 8)){
			return false;
		}
	}


	UnitTile::unitPtr ptr;
	UnitTile::Direction dir;

	if (_worldCoords.y >= world.getDimensionsInPixels().y / 2){
		dir = UnitTile::Direction::N;
	}
	else{
		dir = UnitTile::Direction::S;
	}

	//Create the appropriate unit

	if (_type == UnitTile::UnitType::INF){
		ptr = std::move(std::unique_ptr<Infantry>(new Infantry(world, mt19937, this, tm, fm, dir)));
	}
	else if (_type == UnitTile::UnitType::CAV){
		ptr = std::move(std::unique_ptr<Cavalry>(new Cavalry(world, mt19937, this, tm, fm, dir)));
	}
	else if (_type == UnitTile::UnitType::CUIR){
		ptr = std::move(std::unique_ptr<Cuirassier>(new Cuirassier(world, mt19937, this, tm, fm, dir)));
	}
	else if (_type == UnitTile::UnitType::DRAG){
		ptr = std::move(std::unique_ptr<Dragoon>(new Dragoon(world, mt19937, this, tm, fm, dir)));
	}
	else if (_type == UnitTile::UnitType::LCAV){
		ptr = std::move(std::unique_ptr<LightCav>(new LightCav(world, mt19937, this, tm, fm, dir)));
	}
	else if (_type == UnitTile::UnitType::ART){
		ptr = std::move(std::unique_ptr<Artillery>(new Artillery(world, mt19937, this, tm, fm, dir)));
	}
	else if (_type == UnitTile::UnitType::MOR){
		ptr = std::move(std::unique_ptr<Mortar>(new Mortar(world, mt19937, this, tm, fm, dir)));
	}
	else if (_type == UnitTile::UnitType::GEN){
		ptr = std::move(std::unique_ptr<General>(new General(world, mt19937, this, tm, fm, dir)));
	}

	//Check its deployment cost

	int cost = ptr->getCost();
	int limit = ptr->getLimit();


	bool canAfford = deploymentPoints - cost >= 0;
	bool overLimit{true};

	//If the limit is 0 (i.e. limitless), overLimit is always false.
	//Otherwise, count all the current units of the same type
	//and make sure they aren't over the limit.

	if (limit == 0){
		overLimit = false;
	}
	else{
		auto unitType = ptr->getUnitType();
		int unitsOfType{0};

		for (auto& unit : world.getCombatLayer()){
			if (unit->getPlayer() == this && unit->getUnitType() == unitType){
				unitsOfType += 1;
			}
		}

		overLimit = (unitsOfType == limit);
	}


	
	if (canAfford){
		if (!overLimit){
			if (world.placeAt(_worldCoords, std::move(ptr))){
				deploymentPoints -= cost;
				return true;
			}
		}
	}

	return false;
}

//Used primarily for loading from a save game
void Player::spawnUnit(UnitTile::UnitType _type, sf::Vector2i _pos, UnitTile::Direction _dir, float _hp, float _mov, bool _hasMoved, bool _hasRotated, bool _hasAttacked, bool _hasHealed){

	UnitTile::unitPtr ptr;

	if (_type == UnitTile::UnitType::INF){
		ptr = std::move(std::unique_ptr<Infantry>(new Infantry(world, mt19937, this, tm, fm, _dir)));
	}
	else if (_type == UnitTile::UnitType::CAV){
		ptr = std::move(std::unique_ptr<Cavalry>(new Cavalry(world, mt19937, this, tm, fm, _dir)));
	}
	else if (_type == UnitTile::UnitType::CUIR){
		ptr = std::move(std::unique_ptr<Cuirassier>(new Cuirassier(world, mt19937, this, tm, fm, _dir)));
	}
	else if (_type == UnitTile::UnitType::DRAG){
		ptr = std::move(std::unique_ptr<Dragoon>(new Dragoon(world, mt19937, this, tm, fm, _dir)));
	}
	else if (_type == UnitTile::UnitType::LCAV){
		ptr = std::move(std::unique_ptr<LightCav>(new LightCav(world, mt19937, this, tm, fm, _dir)));
	}
	else if (_type == UnitTile::UnitType::ART){
		ptr = std::move(std::unique_ptr<Artillery>(new Artillery(world, mt19937, this, tm, fm, _dir)));
	}
	else if (_type == UnitTile::UnitType::MOR){
		ptr = std::move(std::unique_ptr<Mortar>(new Mortar(world, mt19937, this, tm, fm, _dir)));
	}
	else if (_type == UnitTile::UnitType::GEN){
		ptr = std::move(std::unique_ptr<General>(new General(world, mt19937, this, tm, fm, _dir)));
	}

	ptr->sethp(_hp);
	ptr->setMov(_mov);

	ptr->setHasMoved(_hasMoved);
	ptr->setHasRotated(_hasRotated);
	ptr->setHasAttacked(_hasAttacked);
	ptr->setHasHealed(_hasHealed);

	world.placeAt(sf::Vector2i{_pos.x * tm.getSize().x, _pos.y * tm.getSize().y}, std::move(ptr));

}

bool Player::removeUnit(sf::Vector2i _worldCoords){

	auto found = world.unitAtMouseCoords(_worldCoords);

	//If there is a unit at the tile,
	if (found != nullptr){

		if (found->getPlayer() == this){

			auto result = world.removeUnit({_worldCoords});

			if (result != nullptr){
				deploymentPoints += result->getCost();
				result = nullptr;
				return true;
			}
		}
	}

	return false;
}

World& Player::getWorld() const{
    return world;
}


int Player::getDeploymentPoints() const{
	return deploymentPoints;
}

std::string Player::getName() const{
	return name;
}

bool Player::isReady() const{
	return ready;
}

void Player::setReady(bool _value){
	ready = _value;
}

sf::Sprite Player::nationToSprite(Nation _nation){
	
	if (_nation == Nation::AUS){
		sf::Sprite sprite{tm.getSprite(TextureManager::Flag::AUS)};
		return sprite;
	}
	else if (_nation == Nation::PRU){
		sf::Sprite sprite{tm.getSprite(TextureManager::Flag::PRU)};
		return sprite;
	}
}

sf::Sprite Player::getFlag() const{
	return playerFlag;
}