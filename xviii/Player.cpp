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
	if (nation != Player::Nation::OTO){

		SpawnableUnit INF(UnitTile::UnitType::INF);
		INF.unitName.setFont(fm.getFont(FontManager::Type::Lucon));
		INF.unitName.setColor(sf::Color::White);
		INF.unitName.setString("INFANTRY");
		INF.unitName.setCharacterSize(12);
		INF.unitName.setOrigin(INF.unitName.getLocalBounds().width / 2, INF.unitName.getLocalBounds().height / 2);

		INF.unitSprite = tm.getSprite(TextureManager::Unit::INF);
		INF.unitSprite.setOrigin(INF.unitSprite.getGlobalBounds().width / 2, INF.unitSprite.getGlobalBounds().height / 2);

		INF.unitSprite.setPosition({430, -130});
		INF.unitName.setPosition({INF.unitSprite.getPosition().x, INF.unitSprite.getPosition().y - 30});

		SpawnableUnit CAV(UnitTile::UnitType::CAV);
		CAV.unitName.setFont(fm.getFont(FontManager::Type::Lucon));
		CAV.unitName.setColor(sf::Color::White);
		CAV.unitName.setString("CAVALRY(5)");
		CAV.unitName.setCharacterSize(12);
		CAV.unitName.setOrigin(CAV.unitName.getLocalBounds().width / 2, CAV.unitName.getLocalBounds().height / 2);

		CAV.unitSprite = tm.getSprite(TextureManager::Unit::CAV);
		CAV.unitSprite.setOrigin(CAV.unitSprite.getGlobalBounds().width / 2, CAV.unitSprite.getGlobalBounds().height / 2);

		CAV.unitSprite.setPosition({530, -130});
		CAV.unitName.setPosition({CAV.unitSprite.getPosition().x, CAV.unitSprite.getPosition().y - 30});

		SpawnableUnit CUIR(UnitTile::UnitType::CUIR);
		CUIR.unitName.setFont(fm.getFont(FontManager::Type::Lucon));
		CUIR.unitName.setColor(sf::Color::White);
		CUIR.unitName.setString("CUIRASSIER(5)");
		CUIR.unitName.setCharacterSize(12);
		CUIR.unitName.setOrigin(CUIR.unitName.getLocalBounds().width / 2, CUIR.unitName.getLocalBounds().height / 2);

		CUIR.unitSprite = tm.getSprite(TextureManager::Unit::CUIR);
		CUIR.unitSprite.setOrigin(CUIR.unitSprite.getGlobalBounds().width / 2, CUIR.unitSprite.getGlobalBounds().height / 2);

		CUIR.unitSprite.setPosition({730, -130});
		CUIR.unitName.setPosition({CUIR.unitSprite.getPosition().x, CUIR.unitSprite.getPosition().y - 30});

		SpawnableUnit DRAG(UnitTile::UnitType::DRAG);
		DRAG.unitName.setFont(fm.getFont(FontManager::Type::Lucon));
		DRAG.unitName.setColor(sf::Color::White);
		DRAG.unitName.setString("DRAGOON(5)");
		DRAG.unitName.setCharacterSize(12);
		DRAG.unitName.setOrigin(DRAG.unitName.getLocalBounds().width / 2, DRAG.unitName.getLocalBounds().height / 2);

		DRAG.unitSprite = tm.getSprite(TextureManager::Unit::DRAG);
		DRAG.unitSprite.setOrigin(DRAG.unitSprite.getGlobalBounds().width / 2, DRAG.unitSprite.getGlobalBounds().height / 2);

		DRAG.unitSprite.setPosition({730, -60});
		DRAG.unitName.setPosition({DRAG.unitSprite.getPosition().x, DRAG.unitSprite.getPosition().y - 30});

		SpawnableUnit LCAV(UnitTile::UnitType::LCAV);
		LCAV.unitName.setFont(fm.getFont(FontManager::Type::Lucon));
		LCAV.unitName.setColor(sf::Color::White);
		LCAV.unitName.setString("LCAV(3)");
		LCAV.unitName.setCharacterSize(12);
		LCAV.unitName.setOrigin(LCAV.unitName.getLocalBounds().width / 2, LCAV.unitName.getLocalBounds().height / 2);

		LCAV.unitSprite = tm.getSprite(TextureManager::Unit::LCAV);
		LCAV.unitSprite.setOrigin(LCAV.unitSprite.getGlobalBounds().width / 2, LCAV.unitSprite.getGlobalBounds().height / 2);

		LCAV.unitSprite.setPosition({630, -60});
		LCAV.unitName.setPosition({LCAV.unitSprite.getPosition().x, LCAV.unitSprite.getPosition().y - 30});

		SpawnableUnit ART(UnitTile::UnitType::ART);
		ART.unitName.setFont(fm.getFont(FontManager::Type::Lucon));
		ART.unitName.setColor(sf::Color::White);
		ART.unitName.setString("ARTILLERY(5)");
		ART.unitName.setCharacterSize(12);
		ART.unitName.setOrigin(ART.unitName.getLocalBounds().width / 2, ART.unitName.getLocalBounds().height / 2);


		ART.unitSprite = tm.getSprite(TextureManager::Unit::ART);
		ART.unitSprite.setOrigin(ART.unitSprite.getGlobalBounds().width / 2, ART.unitSprite.getGlobalBounds().height / 2);

		ART.unitSprite.setPosition({430, -60});
		ART.unitName.setPosition({ART.unitSprite.getPosition().x, ART.unitSprite.getPosition().y - 30});

		SpawnableUnit MOR(UnitTile::UnitType::MOR);
		MOR.unitName.setFont(fm.getFont(FontManager::Type::Lucon));
		MOR.unitName.setColor(sf::Color::White);
		MOR.unitName.setString("MORTAR(5)");
		MOR.unitName.setCharacterSize(12);
		MOR.unitName.setOrigin(MOR.unitName.getLocalBounds().width / 2, MOR.unitName.getLocalBounds().height / 2);

		MOR.unitSprite = tm.getSprite(TextureManager::Unit::MOR);
		MOR.unitSprite.setOrigin(MOR.unitSprite.getGlobalBounds().width / 2, MOR.unitSprite.getGlobalBounds().height / 2);

		MOR.unitSprite.setPosition({530, -60});
		MOR.unitName.setPosition({MOR.unitSprite.getPosition().x, MOR.unitSprite.getPosition().y - 30});

		SpawnableUnit GEN(UnitTile::UnitType::GEN);
		GEN.unitName.setFont(fm.getFont(FontManager::Type::Lucon));
		GEN.unitName.setColor(sf::Color::White);
		GEN.unitName.setString("GENERAL(1)");
		GEN.unitName.setCharacterSize(12);
		GEN.unitName.setOrigin(GEN.unitName.getLocalBounds().width / 2, GEN.unitName.getLocalBounds().height / 2);

		GEN.unitSprite = tm.getSprite(TextureManager::Unit::GEN);
		GEN.unitSprite.setOrigin(GEN.unitSprite.getGlobalBounds().width / 2, GEN.unitSprite.getGlobalBounds().height / 2);

		GEN.unitSprite.setPosition({630, -130});
		GEN.unitName.setPosition({GEN.unitSprite.getPosition().x, GEN.unitSprite.getPosition().y - 30});

		spawnableUnits.emplace_back(INF);
		spawnableUnits.emplace_back(CAV);
		spawnableUnits.emplace_back(CUIR);
		spawnableUnits.emplace_back(DRAG);
		spawnableUnits.emplace_back(LCAV);
		spawnableUnits.emplace_back(ART);
		spawnableUnits.emplace_back(MOR);
		spawnableUnits.emplace_back(GEN);
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
void Player::loadUnit(UnitTile::UnitType _type, sf::Vector2i _pos, UnitTile::Direction _dir, float _hp, float _mov, bool _hasMoved, bool _hasRotated, bool _hasMeleeAttacked, bool _hasRangedAttacked, bool _hasHealed){

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
	ptr->setHasMeleeAttacked(_hasMeleeAttacked);
	ptr->setHasRangedAttacked(_hasRangedAttacked);
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

std::vector<Player::SpawnableUnit>& Player::getSpawnableUnits(){
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