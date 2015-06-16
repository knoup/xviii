#include "xviii/Headers/stdafx.h"
#include "xviii/Core/World.h"

#include "xviii/Terrain/RiverAnt.h"

World::World(TextureManager& _tm, sf::Vector2i _dimensions, boost::random::mt19937& _mt19937) :
tm(_tm),
dimensions{_dimensions},
dimensionsInPixels{sf::Vector2i(dimensions.x * tm.getSize().x, dimensions.y * tm.getSize().y)},
mt19937(_mt19937),
mTerrainTexture(tm.getTerrainTexture())
{
	//era = Era::ALL;

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
			TerrainTile::terrainPtr tile(new Meadow(*this, tm, {float(r * tm.getSize().x), float(c * tm.getSize().y)}));
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
	ants.push_back(std::unique_ptr<Ant>(new Ant(*this, TerrainTile::TerrainType::MUD, 42)));
	ants.push_back(std::unique_ptr<Ant>(new Ant(*this, TerrainTile::TerrainType::MUD, 20)));
	ants.push_back(std::unique_ptr<Ant>(new Ant(*this, TerrainTile::TerrainType::MUD, 20)));
	ants.push_back(std::unique_ptr<Ant>(new Ant(*this, TerrainTile::TerrainType::MUD, 10)));
	ants.push_back(std::unique_ptr<Ant>(new Ant(*this, TerrainTile::TerrainType::MUD, 25)));
	ants.push_back(std::unique_ptr<RiverAnt>(new RiverAnt(*this, 300)));
	ants.push_back(std::unique_ptr<RiverAnt>(new RiverAnt(*this, 220)));
	ants.push_back(std::unique_ptr<RiverAnt>(new RiverAnt(*this, 400)));


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
int World::indexAtPixelPos(sf::Vector2i _pos) const{
	return  int{_pos.x / tm.getSize().x} +int{_pos.y / tm.getSize().y} *dimensions.x;
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

//Takes in an index and returns the theoretical position of this object, whether it exists or not.
//Does not access terrainLayer, therefore making it useful when you want to find what the position
//of an uninitialised terrain tile tile would be
sf::Vector2f World::pixelPosAtIndex(int _index) const{
	return {sf::Vector2f(cartesianPosAtIndex(_index).x * tm.getSize().x, cartesianPosAtIndex(_index).y * tm.getSize().y)};
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

UnitTile* World::unitAtPixelPos(sf::Vector2i _pos){
	UnitTile* unitHere = terrainLayer[indexAtPixelPos(_pos)].get()->getUnit();

	if (unitHere != nullptr){
		return unitHere;
	}

	return nullptr;
}


UnitTile* World::unitAtTerrain(TerrainTile* _terrain){
	return unitAtPixelPos(sf::Vector2i(_terrain->getPixelPos()));
}

TerrainTile* World::terrainAtPixelPos(sf::Vector2i _pos){
	return terrainLayer[indexAtPixelPos(_pos)].get();
}

TerrainTile* World::terrainAtCartesianPos(sf::Vector2i _pos){
	int index = indexAtCartesianPos(_pos);
	return terrainLayer[index].get();
}

void World::draw(sf::RenderTarget &target, sf::RenderStates states) const{
	target.draw(mTerrainVertices, &mTerrainTexture);
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
