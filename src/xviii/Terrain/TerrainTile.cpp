#include "xviii/Headers/stdafx.h"
#include "xviii/Terrain/TerrainTile.h"

#include "xviii/Core/World.h"
#include "xviii/Core/TerrainLoader.h"

/*
Here, we create the vertices for the vertex array. The reason we're using
a vertex array to draw rather than just drawing each terrain tiles' individual sprites is because it is far
more efficient; terrain tiles still have their own sprites, used elsewhere in the game's logic. The only
purpose of the vertex array is to make drawing more efficient.

Unit tiles still use traditional sprites, however, because it greatly simplifies movement and such.
It makes sense for terrain tiles though since they never move.
*/

TerrainTile::TerrainTile(TerrainLoader& _terrainLoader, World& _world, TextureManager& tm, TextureManager::Terrain textType, TerrainType terrainType, sf::Vector2f _pos) :
Tile(_world, tm, textType),
terrainLoader(_terrainLoader),
terrainType{terrainType},
unit{nullptr}
{
	sprite.setPosition(_pos);

	//Update the vertex array at this tile:
	const sf::Vector2i currentCartesianPos{int(_pos.x / tm.getSize().x), int(_pos.y / tm.getSize().y)};
	sf::IntRect currentRekt{sprite.getTextureRect()};

	sf::Vertex* quad = &world.mTerrainVertices[(currentCartesianPos.x + currentCartesianPos.y*world.getDimensions().x) * 4];

	quad[0].position = sf::Vector2f(_pos.x, _pos.y);
	quad[1].position = sf::Vector2f(_pos.x + tm.getSize().x, _pos.y);
	quad[2].position = sf::Vector2f(_pos.x + tm.getSize().x, _pos.y + tm.getSize().y);
	quad[3].position = sf::Vector2f(_pos.x, _pos.y + tm.getSize().y);

	quad[0].texCoords = sf::Vector2f(currentRekt.left, currentRekt.top);
	quad[1].texCoords = sf::Vector2f(currentRekt.left + currentRekt.width, currentRekt.top);
	quad[2].texCoords = sf::Vector2f(currentRekt.left + currentRekt.width, currentRekt.top + currentRekt.height);
	quad[3].texCoords = sf::Vector2f(currentRekt.left, currentRekt.top + currentRekt.height);
}

void TerrainTile::setPos(sf::Vector2f _pos){
	sprite.setPosition(_pos);
}

TerrainTile::TerrainType TerrainTile::getTerrainType() const{
	return terrainType;
}

void TerrainTile::setUnit(UnitTile* _unit){
	unit = _unit;
}

UnitTile* TerrainTile::getUnit(){
	return unit;
}

void TerrainTile::resetUnit(){
	unit = nullptr;
}

void TerrainTile::applyModifiers(UnitTile* _unit, int _distance, bool _attacking){
    std::string name = _unit->getName();
    UnitTile::UnitType mainType = _unit->getUnitType();
    UnitTile::UnitFamily familyType = _unit->getUnitFamilyType();


    auto& unitMainBonuses = (terrainLoader.customDefinitions.at(terrainType).unitMainBonuses);
    auto& unitFamilyBonuses = (terrainLoader.customDefinitions.at(terrainType).unitFamilyBonuses);
    auto& unitStringBonuses = (terrainLoader.customDefinitions.at(terrainType).unitStringBonuses);

    /////////////////////////////////////////////////////////////////////////////////////////
    for(auto& bonus : unitMainBonuses){
        if(bonus.mainType == mainType){
            if((bonus.inMelee && _distance == 1 || bonus.inRanged && _distance > 1)
               &&
               (bonus.whenAttacking && _attacking || bonus.whenDefending && !_attacking)){
                    _unit->modVector.emplace_back(UnitTile::Modifier::TERRAIN, bonus.modifier, bonus.isAdditional);
               }
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////

     for(auto& bonus : unitFamilyBonuses){
        if(bonus.familyType == familyType){
            if((bonus.inMelee && _distance == 1 || bonus.inRanged && _distance > 1)
               &&
               (bonus.whenAttacking && _attacking || bonus.whenDefending && !_attacking)){
                    _unit->modVector.emplace_back(UnitTile::Modifier::TERRAIN, bonus.modifier, bonus.isAdditional);
               }
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////

     for(auto& bonus : unitStringBonuses){
        if(bonus.name == name){
            if((bonus.inMelee && _distance == 1 || bonus.inRanged && _distance > 1)
               &&
               (bonus.whenAttacking && _attacking || bonus.whenDefending && !_attacking)){
                    _unit->modVector.emplace_back(UnitTile::Modifier::TERRAIN, bonus.modifier, bonus.isAdditional);
               }
        }
    }
}

void TerrainTile::draw(sf::RenderTarget &target, sf::RenderStates states) const{
	target.draw(sprite, states);
}

TerrainTile::~TerrainTile(){
}
