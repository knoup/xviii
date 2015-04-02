#include "stdafx.h"
#include "Player.h"

static const sf::View bottomView{sf::View{sf::FloatRect(1183, 4800, xResolution, yResolution)}};
static const sf::View topView{sf::View{sf::FloatRect(1183, -50, xResolution, yResolution)}};

Player::Player(World& _world, Nation _nation, std::mt19937& _mt19937, TextureManager& _tm, FontManager& _fm, bool _spawnedAtBottom) :
world{_world},
nation{_nation},
mt19937{_mt19937},
tm{_tm},
fm{_fm},
deploymentPoints{30},
ready{false},
spawnedAtBottom{_spawnedAtBottom}
{
	switch (nation){
			//nation, flag, name
	#define X(nat,fla,str)\
		case(nat):\
		playerFlag = tm.getSprite(fla);\
		name = str;\
		break;
		NATIONPROPERTIES
	#undef X
	}

	if (spawnedAtBottom){
		view = bottomView;
	}
	else{
		view = topView;
	}
}

bool Player::spawnUnit(UnitTile::UnitType _type, sf::Vector2i _worldCoords){

	auto terrain = world.terrainAtMouseCoords(_worldCoords);
	auto cartesianCoords = world.cartesianCoordsAtIndex(world.indexAtTile(*terrain));

	UnitTile::unitPtr ptr;
	UnitTile::Direction dir;

	if (spawnedAtBottom){
		//Because coordinates start at [0,0], in order for the bottom spawner to have the same length of spawning
		//as the top spawner does, we need to subtract 1
		if (cartesianCoords.y <= (world.getDimensions().y - (world.getDimensions().y/8)) - 1){
			return false;
		}

		dir = UnitTile::Direction::N;
	}
	else{
		if (cartesianCoords.y >= (world.getDimensions().y / 8)){
			return false;
		}

		dir = UnitTile::Direction::S;
	}

	//Create the appropriate unit

	switch (_type){
	#define X(type, cl, str)\
		case(type):\
			ptr = std::move(std::unique_ptr<cl>(new cl(world, mt19937, this, tm, fm, dir)));\
			break;
		UNITPROPERTIES
	#undef X
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

//For loading from a save game
void Player::loadUnit(UnitTile::UnitType _type, sf::Vector2i _pos, UnitTile::Direction _dir, float _hp, float _mov, bool _hasMoved, bool _hasRotated, bool _hasAttacked, bool _hasHealed){

	UnitTile::unitPtr ptr;

		switch (_type){
	#define X(type, cl, str)\
		case(type):\
			ptr = std::move(std::unique_ptr<cl>(new cl(world, mt19937, this, tm, fm, _dir)));\
			break;
		UNITPROPERTIES
	#undef X
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

const World& Player::getWorld() const{
    return world;
}


int Player::getDeploymentPoints() const{
	return deploymentPoints;
}

std::string Player::getName() const{
	return name;
}

sf::Color Player::getColour() const{
	return nationColour;
}

Player::Nation Player::getNation() const{
	return nation;
}

bool Player::isReady() const{
	return ready;
}

void Player::setReady(bool _value){
	ready = _value;
}

sf::Sprite Player::getFlag() const{
	return playerFlag;
}