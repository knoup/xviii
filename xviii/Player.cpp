#include "stdafx.h"
#include "Player.h"

#include "UnitLoader.h"
#include "SpawnableUnit.h"

static const sf::View bottomView{sf::View{sf::FloatRect(1183, 4800, xResolution, yResolution)}};
static const sf::View topView{sf::View{sf::FloatRect(1183, -50, xResolution, yResolution)}};
static const sf::View centerView{sf::View{sf::FloatRect(1183, 2900, xResolution, yResolution)}};

Player::Player(UnitLoader& _unitLoader, World& _world, Nation _nation, std::mt19937& _mt19937, TextureManager& _tm, FontManager& _fm, bool _spawnedAtBottom) :
unitLoader(_unitLoader),
world(_world),
general{nullptr},
nation{_nation},
mt19937(_mt19937),
tm(_tm),
fm(_fm),
deploymentPoints{maxDeploymentPoints},
ready{false},
spawnedAtBottom{_spawnedAtBottom}
{
	sf::Vector2i idealDimensions{7, 2};

	for (auto& customClass : unitLoader.customClasses){
		for (auto& customNation : customClass.second.nations){
			if (customNation == nation && (customClass.second.era == world.getEra() || customClass.second.era == World::Era::ALL || world.getEra() == World::Era::ALL)){
				int index = spawnableUnits.size();
				spawnableUnits.emplace_back(this, customClass.second.name, 
				sf::Vector2i((index % idealDimensions.x) + 1, (index / idealDimensions.x) + 1));
				break;
			}
		}
	}

	switch (nation){
			//nation, flag, name
	#define X(nat,fla,str)\
		case(nat):\
		nationFlag = tm.getSprite(fla);\
		name = str;\
		break;
		NATIONPROPERTIES
	#undef X
	}

	//DISABLED FOR TESTING PURPOSES
	/*
	if (spawnedAtBottom){
		view = bottomView;
	}
	else{
		view = topView;
	*/

	view = centerView;
}

bool Player::spawnUnit(std::string _name, sf::Vector2i _worldCoords){

	auto terrain = world.terrainAtPixelPos(_worldCoords);
	auto cartesianCoords = world.cartesianPosAtIndex(world.indexAtTile(*terrain));

	UnitTile::unitPtr ptr;
	UnitTile::Direction dir;

	if (spawnedAtBottom){
		//Because coordinates start at [0,0], in order for the bottom spawner to have the same length of spawning
		//as the top spawner does, we need to subtract 1

		//DISABLED FOR TESTING PURPOSES
		/*
		if (cartesianCoords.y <= (world.getDimensions().y - (world.getDimensions().y/8)) - 1){
			return false;
		}
		*/
		dir = UnitTile::Direction::N;
	}
	else{
		//DISABLED FOR TESTING PURPOSES
		/*
		if (cartesianCoords.y >= (world.getDimensions().y / 8)){
			return false;
		}
		*/
		dir = UnitTile::Direction::S;
	}

	TextureManager::Unit _texture = unitLoader.customClasses.at(_name).texture;
	UnitTile::UnitType _type = unitLoader.customClasses.at(_name).unitType;
	UnitTile::UnitFamily _familyType = unitLoader.customClasses.at(_name).unitFamilyType;

	//Create the appropriate unit
	switch (_type){
		//string, type, class
		#define X(str, type, cl)\
		case(type):\
			ptr = std::move(std::unique_ptr<cl>(new cl(unitLoader, world, mt19937, this, tm, fm, _texture, _name, _type, _familyType, dir)));\
			break;
		MAINTYPEPROPERTIES
		#undef X
	}
	

	//Check its deployment cost

	int cost = ptr->getCost();
	int limit = ptr->getLimit();


	bool canAfford = deploymentPoints - cost >= 0;
	bool overLimit{false};

	//If the limit is 0 (i.e. limitless), overLimit is always false.
	//Otherwise, count all the current units of the same type
	//and make sure they aren't over the limit.

	if(limit != 0){
		auto unitType = ptr->getUnitType();
		int unitsOfType{0};

		for (auto& unit : units){
			if (unit->getUnitType() == unitType){
				unitsOfType += 1;
			}
		}

		overLimit = (unitsOfType == limit);
	}


	if (canAfford && !overLimit){
		if (world.canBePlacedAtPixelPos(_worldCoords)){
			deploymentPoints -= cost;
			ptr->spawn(world.terrainAtPixelPos(_worldCoords));

			if (_type == UnitTile::UnitType::GEN){
				general = ptr.get();
			}

			units.emplace_back(std::move(ptr));

			return true;
		}
	}

	return false;
}

//For loading from a save game
void Player::loadUnit(std::string _name, sf::Vector2i _pos, UnitTile::Direction _dir, float _hp, float _mov, bool _hasMoved, bool _hasPartialRotated, bool _hasFullRotated, bool _hasMeleeAttacked, bool _hasRangedAttacked, bool _hasHealed, bool _uniqueVariable){

	TextureManager::Unit _texture = unitLoader.customClasses.at(_name).texture;
	UnitTile::UnitType _type = unitLoader.customClasses.at(_name).unitType;
	UnitTile::UnitFamily _familyType = unitLoader.customClasses.at(_name).unitFamilyType;

	UnitTile::unitPtr ptr;

	//Create the appropriate unit
	switch (_type){
		//string, type, class
		#define X(str, type, cl)\
			case(type):\
				ptr = std::move(std::unique_ptr<cl>(new cl(unitLoader, world, mt19937, this, tm, fm, _texture, _name, _type, _familyType, _dir)));\
				break;
		MAINTYPEPROPERTIES
		#undef X
	}

	ptr->sethp(_hp);
	ptr->setMov(_mov);

	ptr->setHasMoved(_hasMoved);
	ptr->setHasPartialRotated(_hasPartialRotated);
	ptr->setHasFullRotated(_hasFullRotated);
	ptr->setHasMeleeAttacked(_hasMeleeAttacked);
	ptr->setHasRangedAttacked(_hasRangedAttacked);
	ptr->setHasHealed(_hasHealed);
	ptr->setUniqueVariable(_uniqueVariable);


	ptr->spawn(world.terrainAtPixelPos(sf::Vector2i{_pos.x * tm.getSize().x, _pos.y * tm.getSize().y}));

	if (_type == UnitTile::UnitType::GEN){
		general = ptr.get();
	}

	units.emplace_back(std::move(ptr));
}

UnitTile::unitPtr Player::removeUnit(sf::Vector2i _worldCoords){
	if (!(_worldCoords.x > 0 && _worldCoords.y > 0
		&&
		_worldCoords.x < world.getDimensionsInPixels().x
		&&
		_worldCoords.y < world.getDimensionsInPixels().y)){

		return nullptr;
	}

	auto found = world.unitAtPixelPos(_worldCoords);

	//If there is a unit at the tile,
	if (found != nullptr){
		if (found->getPlayer() == this){
			//Search units for the unique pointer corresponding to found...
			for (auto& unique_unit : units){
				if (unique_unit.get() == found){
					deploymentPoints += found->getCost();
					unique_unit->getTerrain()->resetUnit();

					if (unique_unit->getUnitType() == UnitTile::UnitType::GEN){
						general = nullptr;
					}
					//temporarily move the unit out of unit vector(so that it does not get
					//instantly deleted as it goes out of scope), erase it, then return it
					auto temp = std::move(unique_unit);
					units.erase(std::remove(units.begin(), units.end(), unique_unit), units.end());
					return temp;
				}
			}
		}
	}

	return nullptr;
}

UnitTile::unitPtr Player::removeUnit(UnitTile* _unit){
	if (_unit == nullptr){
		return nullptr;
	}
	

	//Search units for the unique pointer corresponding to found...
	for (auto& unique_unit : units){
		if (unique_unit.get() == _unit){
			deploymentPoints += _unit->getCost();
			unique_unit->getTerrain()->resetUnit();

			if (unique_unit->getUnitType() == UnitTile::UnitType::GEN){
				general = nullptr;
			}
			//temporarily move the unit out of unit vector(so that it does not get
			//instantly deleted as it goes out of scope), erase it, then return it
			auto temp = std::move(unique_unit);
			units.erase(std::remove(units.begin(), units.end(), unique_unit), units.end());
			return temp;
		}
	}
	

	return nullptr;
}

void Player::drawUnits(sf::RenderTarget &target, sf::RenderStates states) const{
	for (auto& unit : units){
		unit->draw(target, states);
	}
}