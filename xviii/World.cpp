#include "stdafx.h"
#include "World.h"

#include "RiverAnt.h"

World::World(TextureManager& _tm, sf::Vector2i _dimensions, std::mt19937& _mt19937) :
tm(_tm),
dimensions{_dimensions},
dimensionsInPixels{sf::Vector2i(dimensions.x * tm.getSize().x, dimensions.y * tm.getSize().y)},
mt19937(_mt19937),
mTexture{tm.getTerrainTexture()}
{
	mVertices.setPrimitiveType(sf::PrimitiveType::Quads);
	mVertices.resize(dimensions.x * dimensions.y * 4);

	//Begin by filling the map with meadows

	//////////////////////////////////////////////////////////////////////////////////////////////////////
	sf::IntRect terrainRekt = tm.getTerrainRekt(TextureManager::Terrain::MEADOW);

	
	//Here, we create the tiles

	for (int c{0}; c < dimensions.y; ++c){
		for (int r{0}; r < dimensions.x; ++r){
			TerrainTile::terrainPtr tile(new Meadow(this, tm, {float(r * tm.getSize().x), float(c * tm.getSize().y)}));
			terrainLayer.push_back(std::move(tile));

		}
	}

}

void World::generateRandomWorld(){

	//Now, we create the "ants"
	//////////////////////////////////////////////////////////////////////////////////////////////////////

	std::vector < std::unique_ptr<Ant> > ants;

	ants.push_back(std::unique_ptr<Ant>(new Ant(this, TerrainTile::TerrainType::WOODS, 100)));
	ants.push_back(std::unique_ptr<Ant>(new Ant(this, TerrainTile::TerrainType::WOODS, 100)));
	ants.push_back(std::unique_ptr<Ant>(new Ant(this, TerrainTile::TerrainType::WOODS, 15)));
	ants.push_back(std::unique_ptr<Ant>(new Ant(this, TerrainTile::TerrainType::WOODS, 75)));
	ants.push_back(std::unique_ptr<Ant>(new Ant(this, TerrainTile::TerrainType::WOODS, 50)));
	ants.push_back(std::unique_ptr<Ant>(new Ant(this, TerrainTile::TerrainType::WOODS, 100)));
	ants.push_back(std::unique_ptr<Ant>(new Ant(this, TerrainTile::TerrainType::URBAN, 5)));
	ants.push_back(std::unique_ptr<Ant>(new Ant(this, TerrainTile::TerrainType::URBAN, 15)));
	ants.push_back(std::unique_ptr<Ant>(new Ant(this, TerrainTile::TerrainType::URBAN, 15)));
	ants.push_back(std::unique_ptr<Ant>(new Ant(this, TerrainTile::TerrainType::URBAN, 10)));;
	ants.push_back(std::unique_ptr<Ant>(new Ant(this, TerrainTile::TerrainType::WOODS, 100)));
	ants.push_back(std::unique_ptr<Ant>(new Ant(this, TerrainTile::TerrainType::WOODS, 30)));
	ants.push_back(std::unique_ptr<Ant>(new Ant(this, TerrainTile::TerrainType::WOODS, 30)));
	ants.push_back(std::unique_ptr<Ant>(new Ant(this, TerrainTile::TerrainType::WOODS, 30)));
	ants.push_back(std::unique_ptr<Ant>(new Ant(this, TerrainTile::TerrainType::WOODS, 30)));
	ants.push_back(std::unique_ptr<Ant>(new Ant(this, TerrainTile::TerrainType::MUD, 42)));
	ants.push_back(std::unique_ptr<Ant>(new Ant(this, TerrainTile::TerrainType::MUD, 20)));
	ants.push_back(std::unique_ptr<Ant>(new Ant(this, TerrainTile::TerrainType::MUD, 20)));
	ants.push_back(std::unique_ptr<Ant>(new Ant(this, TerrainTile::TerrainType::MUD, 10)));
	ants.push_back(std::unique_ptr<Ant>(new Ant(this, TerrainTile::TerrainType::MUD, 25)));
	ants.push_back(std::unique_ptr<RiverAnt>(new RiverAnt(this, 300)));
	ants.push_back(std::unique_ptr<RiverAnt>(new RiverAnt(this, 220)));
	ants.push_back(std::unique_ptr<RiverAnt>(new RiverAnt(this, 400)));


	for (auto& ant : ants){
		ant->crawl();
	}
}

//Returns the index of the tile at the position
/*
For example, if you click at 45,244, it will return the the index of the tile
at that position, according to the following format:

[1][2][3][4][5][6][7][8][9][10]
[11][12][13] etc...

Depending on the dimensions of the world, obviously

*/
int World::indexAtMouseCoords(sf::Vector2i _pos){
	return  int{_pos.x / tm.getSize().x} +int{_pos.y / tm.getSize().y} *dimensions.x;
}

//This function is somewhat similar to the one above, except it takes in the x and y coords directly:
//for example, in a 5x3 vector, indexAtCartesianCoords(4,2) would give the index of the last element.

//N.B.: Takes TRUE coordinates, +1. Valid ranges are (0,0) -> (size.x - 1, size.y - 1)

int World::indexAtCartesianCoords(sf::Vector2i _pos){
	return int{_pos.x} +int{_pos.y} *dimensions.x;
}

int World::indexAtTile(Tile& _tile){
	return indexAtMouseCoords(sf::Vector2i{_tile.left(), _tile.top()});
}

//This function takes the TRUE coordinates (5,2) and gives you the index:
sf::Vector2i World::cartesianCoordsAtIndex(int _index){
	return{_index % dimensions.x, _index/dimensions.x};
}

//Returns true if unit is succesfully placed
bool World::placeAt(sf::Vector2i _pos, UnitTile::unitPtr ptr){

	//If out of bounds, return false immediately
	if (_pos.x >= getDimensionsInPixels().x || _pos.y >= getDimensionsInPixels().y ||
		_pos.x <= 0 || _pos.y <= 0){
		
		return false;
	}

	//Otherwise
    //If a tile is found at the spot, cache a pointer to it in  "here"

    TerrainTile* here = terrainLayer[indexAtMouseCoords(_pos)].get();

    //A special if/else case to handle the combatLayer being empty (i.e. first unit placed)

    if (!unitLayer.empty()){

        bool vacant{true};

        for (auto& unit : unitLayer){
            //If the tile is occupied by a unit
            if (unit->getTilePos() == here){
                vacant = false;
                }
            }

        if (vacant){
            ptr->spawn(here);
            unitLayer.push_back(std::move(ptr));
            return true;
            }
        }

    else{
        ptr->spawn(here);
        unitLayer.push_back(std::move(ptr));
        return true;
        }


    return false;
}

UnitTile* World::unitAtMouseCoords(sf::Vector2i _pos){
	//If out of bounds, return nullptr immediately
	if (_pos.x >= getDimensionsInPixels().x || _pos.y >= getDimensionsInPixels().y ||
		_pos.x <= 0 || _pos.y <= 0){

		return nullptr;
	}


	TerrainTile* here = terrainLayer[indexAtMouseCoords(_pos)].get();

	for (auto& unit : unitLayer){
		if (unit->getTilePos() == here){
			return unit.get();
		}
	}

	return nullptr;
}

//TODO: find a more optimal way of doing this?
UnitTile* World::unitAt(TerrainTile* _terrain){
	for (auto& unit : unitLayer){
		if (unit->getTilePos() == _terrain){
			return unit.get();
		}
	}

	return nullptr;
}

TerrainTile* World::terrainAtMouseCoords(sf::Vector2i _pos){
	if (_pos.x >= getDimensionsInPixels().x || _pos.y >= getDimensionsInPixels().y ||
		_pos.x <= 0 || _pos.y <= 0){

		return nullptr;
	}

	return terrainLayer[indexAtMouseCoords(_pos)].get();
}

TerrainTile* World::terrainAtCartesianCoords(sf::Vector2i _pos){
	int index = indexAtCartesianCoords(_pos);
	return terrainLayer[index].get();
}

//The standard function for deleting units.
//Returns a pointer to the unit deleted; nullptr if nothing was deleted

UnitTile::unitPtr World::removeUnit(sf::Vector2i _pos){

	//If out of bounds, return nullptr immediately
	if (_pos.x >= getDimensionsInPixels().x || _pos.y >= getDimensionsInPixels().y ||
		_pos.x <= 0 || _pos.y <= 0){

		return nullptr;
	}

	TerrainTile* here = terrainLayer[indexAtMouseCoords(_pos)].get();

        for(auto& unit : unitLayer){

            if(unit->getTilePos() == here){

                //If a unit is found, temporarily move that unit out of combatLayer (so that
                //it does not get instantly deleted as it goes out of scope), erase it from
                //unitLayer, and return it.
                auto result = std::move(unit);
                unitLayer.erase(std::remove(unitLayer.begin(), unitLayer.end(), unit), unitLayer.end());
                return result;

            }

        }

	return nullptr;
}

UnitTile::unitPtr World::removeUnit(UnitTile* _ptr){
	for (auto& unit : unitLayer){
		if (unit.get() == _ptr){
			//If a unit is found, temporarily move that unit out of combatLayer (so that
			//it does not get instantly deleted as it goes out of scope), erase it from
			//unitLayer, and return it.

			auto result = std::move(unit);
			unitLayer.erase(std::remove(unitLayer.begin(), unitLayer.end(), unit), unitLayer.end());
			return result;
		}
	}
}

const std::vector<UnitTile::unitPtr>& World::getCombatLayer() const{
	return unitLayer;
}


void World::draw(sf::RenderTarget &target, sf::RenderStates states) const{

    target.draw(mVertices,&mTexture);

	for (auto& unit : unitLayer){
		unit->draw(target, states);
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
	damagedUnits.emplace_back(unit);
}

void World::clearDamagedUnits(){
	damagedUnits.clear();
}