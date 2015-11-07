#include "xviii/Headers/stdafx.h"
#include "xviii/Core/World.h"

#include "xviii/Terrain/RiverAnt.h"
#include "xviii/Terrain/BridgeAnt.h"

#include "xviii/Core/Player.h"

World::World(MasterManager& _mManager, sf::Vector2i _dimensions) :
masterManager{_mManager},
dimensions{_dimensions},
dimensionsInPixels{sf::Vector2i(dimensions.x * masterManager.textureManager->getSize().x, dimensions.y * masterManager.textureManager->getSize().y)},
mTerrainTexture(masterManager.textureManager->getTerrainTexture()),
currentTime{}
{
	mTerrainVertices.setPrimitiveType(sf::PrimitiveType::Quads);
	mTerrainVertices.resize(dimensions.x * dimensions.y * 4);

	//Begin by filling the map with meadows

	//////////////////////////////////////////////////////////////////////////////////////////////////////

	//Initialise an "empty" world
	for (int c{0}; c < dimensions.y; ++c){
		for (int r{0}; r < dimensions.x; ++r){
			terrainLayer.push_back(nullptr);
		}
	}

}

void World::generateRandomWorld(Era _era){

	setEra(_era);

	terrainLayer.clear();

	//Do a first pass, filling the world with meadows
	for (int c{0}; c < dimensions.y; ++c){
		for (int r{0}; r < dimensions.x; ++r){
			TerrainTile::terrainPtr tile(new Meadow(*this, {float(r * masterManager.textureManager->getSize().x), float(c * masterManager.textureManager->getSize().y)}));
			terrainLayer.push_back(std::move(tile));
		}
	}

	//Now, we create the "ants"
	//////////////////////////////////////////////////////////////////////////////////////////////////////

	std::vector < std::unique_ptr<Ant> > ants;

	ants.push_back(std::unique_ptr<Ant>(new Ant(*this, TerrainTile::TerrainType::WOODS, 100)));
	ants.push_back(std::unique_ptr<Ant>(new Ant(*this, TerrainTile::TerrainType::WOODS, 100)));
	ants.push_back(std::unique_ptr<Ant>(new Ant(*this, TerrainTile::TerrainType::WOODS, 15)));
	ants.push_back(std::unique_ptr<Ant>(new Ant(*this, TerrainTile::TerrainType::WOODS, 75)));
	ants.push_back(std::unique_ptr<Ant>(new Ant(*this, TerrainTile::TerrainType::WOODS, 50)));
	ants.push_back(std::unique_ptr<Ant>(new Ant(*this, TerrainTile::TerrainType::WOODS, 100)));
	ants.push_back(std::unique_ptr<Ant>(new Ant(*this, TerrainTile::TerrainType::URBAN, 5)));
	ants.push_back(std::unique_ptr<Ant>(new Ant(*this, TerrainTile::TerrainType::URBAN, 15)));
	ants.push_back(std::unique_ptr<Ant>(new Ant(*this, TerrainTile::TerrainType::URBAN, 15)));
	ants.push_back(std::unique_ptr<Ant>(new Ant(*this, TerrainTile::TerrainType::URBAN, 10)));;
	ants.push_back(std::unique_ptr<Ant>(new Ant(*this, TerrainTile::TerrainType::WOODS, 100)));
	ants.push_back(std::unique_ptr<Ant>(new Ant(*this, TerrainTile::TerrainType::WOODS, 30)));
	ants.push_back(std::unique_ptr<Ant>(new Ant(*this, TerrainTile::TerrainType::WOODS, 30)));
	ants.push_back(std::unique_ptr<Ant>(new Ant(*this, TerrainTile::TerrainType::WOODS, 30)));
	ants.push_back(std::unique_ptr<Ant>(new Ant(*this, TerrainTile::TerrainType::WOODS, 30)));

	//Mud undergoing an overhaul; currently disabled

	//ants.push_back(std::unique_ptr<Ant>(new Ant(*this, TerrainTile::TerrainType::MUD, 42)));
	//ants.push_back(std::unique_ptr<Ant>(new Ant(*this, TerrainTile::TerrainType::MUD, 20)));
	//ants.push_back(std::unique_ptr<Ant>(new Ant(*this, TerrainTile::TerrainType::MUD, 20)));
	//ants.push_back(std::unique_ptr<Ant>(new Ant(*this, TerrainTile::TerrainType::MUD, 10)));
	//ants.push_back(std::unique_ptr<Ant>(new Ant(*this, TerrainTile::TerrainType::MUD, 25)));

	ants.push_back(std::unique_ptr<RiverAnt>(new RiverAnt(*this, 300)));
	ants.push_back(std::unique_ptr<RiverAnt>(new RiverAnt(*this, 220)));
	ants.push_back(std::unique_ptr<RiverAnt>(new RiverAnt(*this, 400)));

	ants.push_back(std::unique_ptr<BridgeAnt>(new BridgeAnt(*this, 2)));


	for (auto& ant : ants){
		ant->crawl();
	}

	connectBridges();
}

//Returns the index of the tile at the position
/*
For example, if you click at 45,244, it will return the the index of the tile
at that position, according to the following format:

[1][2][3][4][5][6][7][8][9][10]
[11][12][13] etc...

Depending on the dimensions of the world, obviously

*/
int World::indexAtPixelPos(sf::Vector2i _pos) const{
	return  int{_pos.x / masterManager.textureManager->getSize().x} +int{_pos.y / masterManager.textureManager->getSize().y} *dimensions.x;
}

//This function is somewhat similar to the one above, except it takes in the x and y coords directly:
//for example, in a 5x3 vector, indexAtCartesianPos(4,2) would give the index of the last element.

//N.B.: Takes TRUE coordinates, +1. Valid ranges are (0,0) -> (size.x - 1, size.y - 1)

int World::indexAtCartesianPos(sf::Vector2i _pos) const{
	return int{_pos.x} +int{_pos.y} *dimensions.x;
}

int World::indexAtTile(Tile& _tile) const{
	return indexAtPixelPos(sf::Vector2i{_tile.left(), _tile.top()});
}

sf::Vector2i World::cartesianPosAtIndex(int _index) const{
	return{_index % dimensions.x, _index/dimensions.x};
}

sf::Vector2i World::cartesianPosAtPixelPos(sf::Vector2i _pos) const{
    return cartesianPosAtIndex(indexAtPixelPos(_pos));
}

sf::Vector2f World::pixelPosAtCartesianPos(sf::Vector2i _pos) const{
    return pixelPosAtIndex(indexAtCartesianPos(_pos));
}
//Takes in an index and returns the theoretical position of this object, whether it exists or not.
//Does not access terrainLayer, therefore making it useful when you want to find what the position
//of an uninitialised terrain tile tile would be
sf::Vector2f World::pixelPosAtIndex(int _index) const{
	return {sf::Vector2f(cartesianPosAtIndex(_index).x * masterManager.textureManager->getSize().x, cartesianPosAtIndex(_index).y * masterManager.textureManager->getSize().y)};
}

//Returns true if can be placed at this position
bool World::canBePlacedAtPixelPos(sf::Vector2i _pos){

	//If out of bounds, return false immediately
	if (_pos.x >= getDimensionsInPixels().x || _pos.y >= getDimensionsInPixels().y ||
		_pos.x <= 0 || _pos.y <= 0){

		return false;
	}

    TerrainTile* here = terrainLayer[indexAtPixelPos(_pos)].get();

	if (here->getUnit() == nullptr){
		return true;
	}
	else{
		return false;
	}
}

bool World::canBePlacedAtCartesianPos(sf::Vector2i _pos){

	//If out of bounds, return false immediately
	if (_pos.x > getDimensions().x - 1 || _pos.y > getDimensions().y - 1 ||
		_pos.x < 0 || _pos.y < 0){

		return false;
	}

	TerrainTile* here = terrainLayer[indexAtCartesianPos(_pos)].get();

	if (here->getUnit() == nullptr){
		return true;
	}
	else{
		return false;
	}
}

bool World::pixelPosOutOfBounds(sf::Vector2i _pos){
    if (_pos.x >= getDimensionsInPixels().x || _pos.y >= getDimensionsInPixels().y ||
		_pos.x <= 0 || _pos.y <= 0){

		return true;
	}

	return false;
}

bool World::cartesianPosOutOfBounds(sf::Vector2i _pos){
    if (_pos.x > getDimensions().x - 1 || _pos.y > getDimensions().y - 1 ||
		_pos.x < 0 || _pos.y < 0){

		return true;
	}

	return false;
}

UnitTile* World::unitAtPixelPos(sf::Vector2i _pos){
	UnitTile* unitHere = terrainLayer[indexAtPixelPos(_pos)].get()->getUnit();

	if (unitHere != nullptr){
		return unitHere;
	}

	return nullptr;
}


UnitTile* World::unitAtTerrain(TerrainTile* _terrain){
    if(_terrain == nullptr){
        return nullptr;
    }

	return(_terrain->getUnit());
}

TerrainTile* World::terrainAtPixelPos(sf::Vector2i _pos){
	return terrainLayer[indexAtPixelPos(_pos)].get();
}

TerrainTile* World::terrainAtCartesianPos(sf::Vector2i _pos){
	int index = indexAtCartesianPos(_pos);

	if(index > terrainLayer.size() - 1){
        return nullptr;
	}

	return terrainLayer[index].get();
}

void World::draw(sf::RenderTarget &target, sf::RenderStates states) const{
	target.draw(mTerrainVertices, &mTerrainTexture);

	for(auto& t : temporaryBridges){
        target.draw(t->hpText);
	}

	for(auto& b : permanentBridges){
        target.draw(b->hpText);
	}
}

sf::Vector2i World::getDimensions() const{
    return dimensions;
}

sf::Vector2i World::getDimensionsInPixels() const{
    return dimensionsInPixels;
}

const std::vector<UnitTile*>& World::getDamagedUnits() const{
	return damagedUnits;
}

void World::addToDamagedUnits(UnitTile* unit){
	//Removing the check may cause a crash in the rare cases where takeDamage() is called
	//twice in the same function on the same unit, such as during infantry breakthroughs.
	if (!(std::find(damagedUnits.begin(), damagedUnits.end(), unit) != damagedUnits.end())){
		damagedUnits.emplace_back(unit);
	}
}

void World::clearDamagedUnits(){
	//Remove the unit if it's dead; if it isn't, update stats
	for (auto& unit : damagedUnits){
		if (!unit->removeIfDead()){
			unit->updateStats();
		}
	}

	damagedUnits.clear();
}

void World::toggleBridge(TerrainTile* terrain, TerrainTile::Orientation _or){
    int index = indexAtTile(*terrain);
    UnitTile* unit = terrain->getUnit();

    //This part gave me headaches for hours.
    //It is crucial to reset the unit's terrain pointer, because the function spawn() below resets
    //the terrain pointer's unit pointer; needless to say, spawn() is not designed to be used on
    //removed tiles. Remove the following check if you want to spend your night debugging cryptic
    //compiler messages.

    if(unit != nullptr){
        unit->resetTerrain();
    }

    for(auto it = visibleTiles.begin(); it != visibleTiles.end(); ){
        if(*it == terrain){
            it = visibleTiles.erase(it);
        }
        else{
            it++;
        }
    }

    if(terrain->getTerrainType() == TerrainTile::TerrainType::WATER){
        auto ptr =  std::move(std::unique_ptr<Bridge>(new Bridge{*this, terrain->getPixelPos()}));
        permanentBridges.push_back(ptr.get());
        ptr->flip(_or);
        ptr->connect();
        terrainLayer[index] = std::move(ptr);

        if(unit != nullptr){
            unit->spawn(terrainLayer[index].get());
        }
    }

    else if(terrain->getTerrainType() == TerrainTile::TerrainType::BRIDGE){
        Bridge* b = static_cast<Bridge*>(terrainLayer[index].get());
        b->disconnect();

        permanentBridges.erase(std::remove(permanentBridges.begin(), permanentBridges.end(), terrainLayer[index].get()), permanentBridges.end());
        terrainLayer[index] =  std::move(std::unique_ptr<Water>(new Water{*this, terrain->getPixelPos()}));

        //We're going to let clearDamagedUnits() take care of unit deletion, so here, we'll simply
        //remove all the unit's remaining HP
        if(unit != nullptr){
            float damage = unit->gethp();
            unit->takeDamage(nullptr, damage, 0);
        }

        visibleTiles.insert(terrainLayer[index].get());
        highlightVisibleTiles();
    }
}


void World::toggleTBridge(TerrainTile* terrain, TerrainTile::Orientation _or){
    int index = indexAtTile(*terrain);
    UnitTile* unit = terrain->getUnit();

    //This part gave me headaches for hours.
    //It is crucial to reset the unit's terrain pointer, because the function spawn() below resets
    //the terrain pointer's unit pointer; needless to say, spawn() is not designed to be used on
    //removed tiles. Remove the following check if you want to spend your night debugging cryptic
    //compiler messages.

    if(unit != nullptr){
        unit->resetTerrain();
    }

    for(auto it = visibleTiles.begin(); it!= visibleTiles.end();){
        if(*it == terrain){
            it = visibleTiles.erase(it);
        }
        else{
            it++;
        }
    }

    if(terrain->getTerrainType() == TerrainTile::TerrainType::WATER){
        auto ptr = std::move(std::unique_ptr<TBridge>(new TBridge{*this, terrain->getPixelPos()}));
        temporaryBridges.push_back(ptr.get());
        ptr->flip(_or);
        ptr->connect();
        terrainLayer[index] = std::move(ptr);

        if(unit != nullptr){
            unit->spawn(terrainLayer[index].get());
        }

        visibleTiles.insert(terrainLayer[index].get());
        highlightVisibleTiles();
    }

    else if(terrain->getTerrainType() == TerrainTile::TerrainType::TBRIDGE){
        Bridge* b = static_cast<Bridge*>(terrainLayer[index].get());
        b->disconnect();

        temporaryBridges.erase(std::remove(temporaryBridges.begin(), temporaryBridges.end(), terrainLayer[index].get()), temporaryBridges.end());
        terrainLayer[index] =  std::move(std::unique_ptr<Water>(new Water{*this, terrain->getPixelPos()}));

        //We're going to let clearDamagedUnits() take care of unit deletion, so here, we'll simply
        //remove all the unit's remaining HP
        if(unit != nullptr){
            float damage = unit->gethp();
            unit->takeDamage(nullptr, damage, 0);
        }

        visibleTiles.insert(terrainLayer[index].get());
        highlightVisibleTiles();
    }
}

void World::connectBridges(){
    //Potential TODO:
    //Optimise the algorithm for bridge connecting. As it is, some redundant checks may be redone. It doesn't matter
    //too much performance-wise, but still

    for (auto& Bridge : permanentBridges){
        Bridge->connect();
    }

    for (auto& Bridge : temporaryBridges){
        Bridge->connect();
    }
}

void World::wearDownTempBridges(TerrainTile* currentTile, TerrainTile* destinationTile){
    sf::Vector2i currentCoords = currentTile->getCartesianPos();
    sf::Vector2i destinationCoords = destinationTile->getCartesianPos();

    //Do a quick check to see if they do not share any coordinates

    if((currentCoords.x != destinationCoords.x) && (currentCoords.y != destinationCoords.y)){
        return;
    }

    int CURRENTCOORDS_PRIMARY;
	int CURRENTCOORDS_SECONDARY;
	int DESTINATIONCOORDS_PRIMARY;
	int DESTINATIONCOORDS_SECONDARY;
	bool VERTICAL{false};
	bool HORIZONTAL{false};
	bool POSITIVE{false};

    //North || South
	if(currentCoords.y > destinationCoords.y || currentCoords.y < destinationCoords.y){

        if(currentCoords.y < destinationCoords.y){
            POSITIVE = true;
        }

		CURRENTCOORDS_PRIMARY = currentCoords.y;
		CURRENTCOORDS_SECONDARY = currentCoords.x;
		DESTINATIONCOORDS_PRIMARY = destinationCoords.y;
		DESTINATIONCOORDS_SECONDARY = destinationCoords.x;
		VERTICAL = true;
    }

    //East || west
	else if(currentCoords.x < destinationCoords.x || currentCoords.x > destinationCoords.x){

        if(currentCoords.x < destinationCoords.x){
            POSITIVE = true;
        }
		CURRENTCOORDS_PRIMARY = currentCoords.x;
		CURRENTCOORDS_SECONDARY = currentCoords.y;
		DESTINATIONCOORDS_PRIMARY = destinationCoords.x;
		DESTINATIONCOORDS_SECONDARY = destinationCoords.y;
		HORIZONTAL = true;
    }


    //We don't want the actual destination tile to be worn down; it will be worn down
    //when the unit moves away from it afterwards

    int i{CURRENTCOORDS_PRIMARY };

    do{
        TerrainTile* terrainHere{nullptr};

        if(VERTICAL){
            terrainHere = terrainAtCartesianPos({CURRENTCOORDS_SECONDARY, i});
        }
        else if(HORIZONTAL){
            terrainHere = terrainAtCartesianPos({i,CURRENTCOORDS_SECONDARY});
        }


        if(terrainHere->getTerrainType() == TerrainTile::TerrainType::TBRIDGE){
            TBridge* t = static_cast<TBridge*>(terrainHere);
            t->takeDamage(1);
        }

        if(POSITIVE){
            i += 1;
        }
        else{
            i -= 1;
        }
    }

    while((i < DESTINATIONCOORDS_PRIMARY && POSITIVE) || (i > DESTINATIONCOORDS_PRIMARY && !POSITIVE));


	return;
}

void World::turnlyUpdate(){
    boost::random::uniform_int_distribution<int> dist(1, 100);

    incrementElapsedTurns();
    getCurrentTime().increment();

    //The weather will tend to change every ~8 hours, or 480 minutes.
    //Ideally, something like this:

    //1 hour  (60)  -> 4%
    //2 hours (120) -> 6%
    //3 hours (180) -> 8%
    //4 hours (240) -> 12.5%
    //5 hours (300) -> 16%
    //6 hours (360) -> 24%
    //7 hours (420) -> 30%
    //8 hours (480) -> 40%

    for(auto& effect : weatherEffects){
        effect.second += minutesPerTurn;
    }

    auto effect = std::begin(weatherEffects);
    while(effect != std::end(weatherEffects)){

        int removeEffect{dist(masterManager.randomEngine)};
        //For instance, if the effect has been there for 240 minutes, it will have an
        //40% chance of being removed. There is a hard cap of 80%.

        int totalChance = effect->second / 15;
        if(totalChance > 50){
            totalChance = 50;
        }

        if(removeEffect <= totalChance){
            effect = weatherEffects.erase(effect);
        }
        else{
            effect++;
        }

    }

    int hourlyChance = 20;
    int turnlyChance = hourlyChance / (60/minutesPerTurn);

    int randomRoll{dist(masterManager.randomEngine)};

    if (randomRoll <= turnlyChance){
        addWeather();
    }


    unhighlightVisibleTiles();
    visibleTiles.clear();
}

void World::addWeather(){
    boost::random::uniform_int_distribution<int> dist(1, 100);

    bool fogPresent{false};
    bool rainPresent{false};

    for(auto& effect : weatherEffects){
        if(effect.first == Weather::HEAVY_FOG || effect.first == Weather::LIGHT_FOG){
            fogPresent = true;
        }
        else if(effect.first == Weather::HEAVY_RAIN || effect.first == Weather::LIGHT_RAIN){
            rainPresent = true;
        }
    }

    int randomRoll{dist(masterManager.randomEngine)};
    int randomRoll2{dist(masterManager.randomEngine)};

    if(randomRoll >= 65 && !fogPresent){

        if(randomRoll2 <= 75){
            addWeatherEffect(Weather::LIGHT_FOG, 0);
        }
        else{
            addWeatherEffect(Weather::HEAVY_FOG, 0);
        }
    }

    else if (!rainPresent){
        if(randomRoll2 <= 75){
            addWeatherEffect(Weather::LIGHT_RAIN, 0);
        }
        else{
            addWeatherEffect(Weather::HEAVY_RAIN, 0);
        }
    }

}

int World::getWeatherUnitViewDistance() const{
    int weatherUnitViewDistance{0};

    for(auto& effect : weatherEffects){
        #define X(_str, _weather, _u, _f)\
            if(_weather == effect.first)\
                weatherUnitViewDistance += _u;
            WEATHERPROPERTIES
            #undef X
    }

    return weatherUnitViewDistance;
}

int World::getWeatherFlagViewDistance() const{
    int weatherFlagViewDistance{0};

    for(auto& effect : weatherEffects){
        #define X(_str, _weather, _u, _f)\
            if(_weather == effect.first)\
                weatherFlagViewDistance += _f;
            WEATHERPROPERTIES
            #undef X
    }

    return weatherFlagViewDistance;

}

void World::calculateViewDistance(UnitTile* unit){

    //IMPORTANT:
    //Due to the fact that Tile::getCartesianPos() bases its result on the physical location of the sprite,
    //which for units can be in disagreement with its real position, we use getTruePosition() instead.

    sf::Vector2i currentPos = unit->getTruePosition();

    int unitViewDistance = unit->getDefaultUnitViewDistance() - getWeatherUnitViewDistance();
    int flagViewDistance = unit->getDefaultFlagViewDistance() - getWeatherFlagViewDistance();

    if(unitViewDistance < 1){
        unitViewDistance = 1;
    }
    if(flagViewDistance < 1){
        flagViewDistance = 1;
    }

    unit->setCurrentUnitViewDistance(unitViewDistance);
    unit->setCurrentFlagViewDistance(flagViewDistance);

    Player* owner = unit->getPlayer();

    for (int y{-1 * flagViewDistance}; y <= flagViewDistance; ++y){
        for(int x{-1 * flagViewDistance}; x <= flagViewDistance; ++x){

            sf::Vector2i adjacentPos{currentPos.x + x, currentPos.y + y};

            TerrainTile* terrainHere = terrainAtCartesianPos(adjacentPos);

            if(terrainHere == nullptr){
                continue;
            }

            UnitTile* targetUnit = terrainHere->getUnit();

            if (targetUnit != nullptr){
                if(targetUnit->getPlayer() != owner){
                    targetUnit->drawFlag = true;
                    targetUnit->updateStats();
                }
            }
        }
    }

    for (int y{-1 * unitViewDistance}; y <= unitViewDistance; ++y){
        for(int x{-1 * unitViewDistance}; x <= unitViewDistance; ++x){

            sf::Vector2i adjacentPos{currentPos.x + x, currentPos.y + y};

            TerrainTile* terrainHere = terrainAtCartesianPos(adjacentPos);

            if(terrainHere == nullptr){
                continue;
            }

            UnitTile* targetUnit = terrainHere->getUnit();
            visibleTiles.insert(terrainHere);

            if (targetUnit != nullptr){
                if(targetUnit->getPlayer() != owner){
                    targetUnit->drawUnit = true;
                    targetUnit->updateStats();
                }
            }
        }
    }


}

void World::highlightVisibleTiles(){
    for(auto& tile : visibleTiles){
        tile->setColor(sf::Color{255,255,255,255});
        tile->refreshVertexArray();
    }
}

void World::unhighlightVisibleTiles(){
    for(auto& tile : visibleTiles){
        tile->setColor(sf::Color{255,255,255,170});
        tile->refreshVertexArray();
    }
}

void World::highlightAllTiles(){
    for(auto& tile : terrainLayer){
        tile->setColor(sf::Color{255,255,255,255});
        tile->refreshVertexArray();
    }
}

void World::unhighlightAllTiles(){
    for(auto& tile : terrainLayer){
        tile->setColor(sf::Color{255,255,255,170});
        tile->refreshVertexArray();
    }
}
