#include "stdafx.h"
#include "Player.h"

static const sf::View bottomView{sf::View{sf::FloatRect(1183, 4800, xResolution, yResolution)}};
static const sf::View topView{sf::View{sf::FloatRect(1183, -50, xResolution, yResolution)}};
static const sf::View centerView{sf::View{sf::FloatRect(1183, 2900, xResolution, yResolution)}};

Player::Player(World& _world, Nation _nation, std::mt19937& _mt19937, TextureManager& _tm, FontManager& _fm, bool _spawnedAtBottom) :
world(_world),
nation{_nation},
mt19937(_mt19937),
tm(_tm),
fm(_fm),
deploymentPoints{30},
ready{false},
spawnedAtBottom{_spawnedAtBottom}
{
	//All nations get these three units
	spawnableUnits.emplace_back(SpawnableUnit(this, UnitTile::UnitType::GEN, {1, 1}));
	spawnableUnits.emplace_back(SpawnableUnit(this, UnitTile::UnitType::ART, {2, 1}));
	spawnableUnits.emplace_back(SpawnableUnit(this, UnitTile::UnitType::MOR, {3, 1}));

	if (nation == Player::Nation::MOL || nation == Player::Nation::WAL){
		spawnableUnits.emplace_back(SpawnableUnit(this, UnitTile::UnitType::DOR, {4, 1}));
		spawnableUnits.emplace_back(SpawnableUnit(this, UnitTile::UnitType::VIT, {5, 1}));
		spawnableUnits.emplace_back(SpawnableUnit(this, UnitTile::UnitType::ARN, {6, 1}));
		spawnableUnits.emplace_back(SpawnableUnit(this, UnitTile::UnitType::BOY, {1, 2}));
		spawnableUnits.emplace_back(SpawnableUnit(this, UnitTile::UnitType::HUS, {2, 2}));
		spawnableUnits.emplace_back(SpawnableUnit(this, UnitTile::UnitType::COUR, {3, 2}));
		spawnableUnits.emplace_back(SpawnableUnit(this, UnitTile::UnitType::SEG, {4, 2}));
	}

	else if (nation == Player::Nation::OTO){
		spawnableUnits.emplace_back(SpawnableUnit(this, UnitTile::UnitType::JAN, {4, 1}));
		spawnableUnits.emplace_back(SpawnableUnit(this, UnitTile::UnitType::OINF, {5, 1}));
		spawnableUnits.emplace_back(SpawnableUnit(this, UnitTile::UnitType::SAP, {1, 2}));
		spawnableUnits.emplace_back(SpawnableUnit(this, UnitTile::UnitType::KAP, {2, 2}));
		spawnableUnits.emplace_back(SpawnableUnit(this, UnitTile::UnitType::DELI, {3, 2}));
		spawnableUnits.emplace_back(SpawnableUnit(this, UnitTile::UnitType::AKINCI, {4, 2}));
		spawnableUnits.emplace_back(SpawnableUnit(this, UnitTile::UnitType::TIM, {5, 2}));
		spawnableUnits.emplace_back(SpawnableUnit(this, UnitTile::UnitType::ARTGUARD, {6, 2}));
	}
	else if (nation == Player::Nation::CRI){
		spawnableUnits.emplace_back(SpawnableUnit(this, UnitTile::UnitType::COSINF, {4, 1}));
		spawnableUnits.emplace_back(SpawnableUnit(this, UnitTile::UnitType::CRICAV, {5, 1}));
		spawnableUnits.emplace_back(SpawnableUnit(this, UnitTile::UnitType::KAP, {6, 1}));
	}
	else if (nation == Player::Nation::IME){
		spawnableUnits.emplace_back(SpawnableUnit(this, UnitTile::UnitType::METTOP, {4, 1}));
		spawnableUnits.emplace_back(SpawnableUnit(this, UnitTile::UnitType::KACI, {5, 1}));
		spawnableUnits.emplace_back(SpawnableUnit(this, UnitTile::UnitType::AMKH, {1, 2}));
		spawnableUnits.emplace_back(SpawnableUnit(this, UnitTile::UnitType::KKV, {2, 2}));
		spawnableUnits.emplace_back(SpawnableUnit(this, UnitTile::UnitType::PIT, {3, 2}));
		spawnableUnits.emplace_back(SpawnableUnit(this, UnitTile::UnitType::KMKH, {4, 2}));
		spawnableUnits.emplace_back(SpawnableUnit(this, UnitTile::UnitType::DON, {5, 2}));
	}
	//Europeans
	else{
		spawnableUnits.emplace_back(SpawnableUnit(this, UnitTile::UnitType::INF, {4, 1}));
		spawnableUnits.emplace_back(SpawnableUnit(this, UnitTile::UnitType::GRE, {5, 1}));
		spawnableUnits.emplace_back(SpawnableUnit(this, UnitTile::UnitType::LINF, {6, 1}));
		spawnableUnits.emplace_back(SpawnableUnit(this, UnitTile::UnitType::SAP, {1, 2}));
		spawnableUnits.emplace_back(SpawnableUnit(this, UnitTile::UnitType::CAV, {2, 2}));
		spawnableUnits.emplace_back(SpawnableUnit(this, UnitTile::UnitType::CUIR, {3, 2}));
		spawnableUnits.emplace_back(SpawnableUnit(this, UnitTile::UnitType::DRAG, {4, 2}));
		spawnableUnits.emplace_back(SpawnableUnit(this, UnitTile::UnitType::LCAV, {5, 2}));
		spawnableUnits.emplace_back(SpawnableUnit(this, UnitTile::UnitType::FOOT, {6, 2}));
		spawnableUnits.emplace_back(SpawnableUnit(this, UnitTile::UnitType::ARTGUARD, {7, 2}));
	}


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

bool Player::spawnUnit(UnitTile::UnitType _type, sf::Vector2i _worldCoords){

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

	//Create the appropriate unit

	switch (_type){
		//type, class, string, texture
	#define X(type, cl, str, texture)\
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
			units.emplace_back(std::move(ptr));
			return true;
		}
	}

	return false;
}

//For loading from a save game
void Player::loadUnit(UnitTile::UnitType _type, sf::Vector2i _pos, UnitTile::Direction _dir, float _hp, float _mov, bool _hasMoved, bool _hasRotated, bool _hasMeleeAttacked, bool _hasRangedAttacked, bool _hasHealed){

	UnitTile::unitPtr ptr;

		switch (_type){
			//type, class, string, texture
	#define X(type, cl, str, texture)\
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
	ptr->setHasMeleeAttacked(_hasMeleeAttacked);
	ptr->setHasRangedAttacked(_hasRangedAttacked);
	ptr->setHasHealed(_hasHealed);


	ptr->spawn(world.terrainAtPixelPos(sf::Vector2i{_pos.x * tm.getSize().x, _pos.y * tm.getSize().y}));
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
			//temporarily move the unit out of unit vector(so that it does not get
			//instantly deleted as it goes out of scope), erase it, then return it
			auto temp = std::move(unique_unit);
			units.erase(std::remove(units.begin(), units.end(), unique_unit), units.end());
			return temp;
		}
	}
	

	return nullptr;
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

const std::vector<Player::SpawnableUnit>& Player::getSpawnableUnits() const{
	return spawnableUnits;
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

const std::vector<UnitTile::unitPtr>& Player::getUnits() const{
	return units;
}

void Player::drawUnits(sf::RenderTarget &target, sf::RenderStates states) const{
	for (auto& unit : units){
		if (unit == nullptr){
			std::cout << "wawawaw" << std::endl;
		}
		unit->draw(target, states);
	}
}