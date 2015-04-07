#include "stdafx.h"
#include "UnitTile.h"

#include "Player.h"
#include "World.h"


UnitTile::Direction UnitTile::opposite(UnitTile::Direction _dir){
	switch (_dir){

	case UnitTile::Direction::N:
		return UnitTile::Direction::S;
		break;

	case UnitTile::Direction::S:
		return UnitTile::Direction::N;
		break;

	case UnitTile::Direction::E:
		return UnitTile::Direction::W;
		break;

	case UnitTile::Direction::W:
		return UnitTile::Direction::E;
		break;
	}
}

std::string UnitTile::roundFloat(const double x) {
	std::stringstream ss;
	ss << std::fixed;

	//This portion checks if it is "whole" (.0) or "half" (.5)
	//and sets precision accordingly, so that if the number is just
	//5 it will display as 5 rather than the redundant 5.0 and if
	//it is 5.5 it will display as 5.5

	int test = static_cast<int>(x * 10) % 10;

	if (test == 5){
		ss.precision(1);		
	}
	else{
		ss.precision(0);
	}

	//

	ss << x;
	return ss.str();
}


std::string UnitTile::dirToString(){
    switch(dir){
    case UnitTile::Direction::N:
        return "N";
        break;

    case UnitTile::Direction::E:
        return "E";
        break;

    case UnitTile::Direction::S:
        return "S";
        break;

    case UnitTile::Direction::W:
        return "W";
        break;
    }
}

std::string UnitTile::modToString(Modifier _mod){
	switch (_mod){
	case Modifier::NONE:
		return{"none"};
		break;

	case Modifier::VSCAV:
		return{"vs.cav"};
		break;

	case Modifier::DISTANCE:
		return{"distance"};
		break;

	case Modifier::FRONT_FLANK:
		return{"front flank"};
		break;

	case Modifier::SIDE_FLANK:
		return{"side flank"};
		break;

	case Modifier::REAR_FLANK:
		return{"rear flank"};
		break;
	}
}

std::string UnitTile::typeToString(){
	switch (unitType){
	#define X(unitType, cl, str)\
		case (unitType):\
		return str;\
		break;
	UNITPROPERTIES
	#undef X
	}
}

UnitTile::UnitTile(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, TextureManager::Unit id, UnitTile::UnitType type, UnitTile::UnitFamily familyType, Direction _dir) :
Tile(tm, id),
world{_world},
mt19937{_mt19937},
unitType{type},
unitFamilyType{familyType},
player{_belongsToPlayer},
dir{_dir},
hp{0},
mov{0},
at{nullptr}

{
	unitFlag = player->getFlag();

    dirText.setString(dirToString());

    dirText.setFont(fm.getFont(FontManager::Type::Arial));
    hpText.setFont(fm.getFont(FontManager::Type::Arial));
    movText.setFont(fm.getFont(FontManager::Type::Arial));

    dirText.setCharacterSize(15);
    hpText.setCharacterSize(15);
    movText.setCharacterSize(15);

    dirText.setColor(sf::Color(0,0,180));
    hpText.setColor(sf::Color::Red);
    movText.setColor(sf::Color::Black);

	yellowOutline.setPosition(sprite.getPosition().x, sprite.getPosition().y);
	yellowOutline.setSize(sf::Vector2f(tm.getSize().x, tm.getSize().y));
	yellowOutline.setOutlineColor(sf::Color::Yellow);
	yellowOutline.setOutlineThickness(-1);
	yellowOutline.setFillColor(sf::Color::Transparent);

	redOutline.setPosition(sprite.getPosition().x, sprite.getPosition().y);
	redOutline.setSize(sf::Vector2f(tm.getSize().x, tm.getSize().y));
	redOutline.setOutlineColor(sf::Color::Red);
	redOutline.setOutlineThickness(-1);
	redOutline.setFillColor(sf::Color::Transparent);
}

void UnitTile::spawn(TerrainTile* terrainTile){
	at = terrainTile;
	sprite.setPosition(terrainTile->getPos());
	unitFlag.setPosition(terrainTile->getPos());
	yellowOutline.setPosition(terrainTile->getPos());
	redOutline.setPosition(terrainTile->getPos());
	updateStats();
}

//Virtual
std::string UnitTile::moveTo(TerrainTile* _terrainTile){
	bool validMovDirection{false};
	bool validAttackDirection{false};
	bool obstructionPresent{false};
	bool inMovementRange{false};
	bool inRangedAttackRange{false};
	int movExpended{0};

	//Get the coordinates of the current tile the unit is at
	sf::Vector2i currentCoords{world.cartesianCoordsAtIndex(world.indexAtTile(*at))};

	//Get the coordinates of the tile to be moved to
	sf::Vector2i toMoveToCoords{world.cartesianCoordsAtIndex(world.indexAtTile(*_terrainTile))};

	movExpended = distanceFrom(_terrainTile, validMovDirection, validAttackDirection, obstructionPresent, inMovementRange, inRangedAttackRange);

	if (obstructionPresent){
		return "Invalid move order: line of sight not clear";
	}

	else if (validMovDirection && inMovementRange){
		at = _terrainTile;
		mov -= movExpended;
		sprite.setPosition(_terrainTile->getPos());
		unitFlag.setPosition(_terrainTile->getPos());
		yellowOutline.setPosition(_terrainTile->getPos());
		redOutline.setPosition(_terrainTile->getPos());
		updateStats();
		return "Successfully moved to (" + std::to_string(toMoveToCoords.x + 1) + ", " + std::to_string(toMoveToCoords.y + 1) + ")";
	}

	else if (validMovDirection && !inMovementRange){
		return{"Invalid move order: not enough mov"};
	}

	else if (!validMovDirection){
		return{"Invalid move order: hrzntl or wrong dir"};
	}

}

//Virtual
void UnitTile::reset(){
	mov = getMaxMov();
	hasMoved = false;
	hasRotated = false;
	hasAttacked = false;
	updateStats();
}

//Virtual
std::string UnitTile::rotate(UnitTile::Direction _dir){
	return{};
}

//Virtual
std::string UnitTile::interactWithFriendly(UnitTile* _unit){
	return{};
}

//Virtual
std::string UnitTile::heal(){
	if (hp <= getMaxHp() - 2){
		hp += 2;
		updateStats();
		return{"Successfully healed for 2"};
	}
	else{
		float amountToHeal{getMaxHp() - hp};
		hp += amountToHeal;
		updateStats();
		//Error in compiler if I don't do it this way
		std::string result{"Successfully healed for " + roundFloat(amountToHeal)};
		return result;
	}

	return{};
}

//Virtual
int UnitTile::getMaxHp() const{
	return 0;
}

//Virtual
int UnitTile::getMaxMov() const{
	return 0;
}

//Virtual
int UnitTile::getMaxRange() const{
	return 0;
}

std::string UnitTile::attack(UnitTile* unit){
	bool validMovDirection{false};
	bool validAttackDirection{false};
	bool obstructionPresent{false};
	bool inMovementRange{false};
	bool inRangedAttackRange{false};

	int dist{distanceFrom(unit->at, validMovDirection, validAttackDirection, obstructionPresent, inMovementRange, inRangedAttackRange)};

	if (hasAttacked){
		return{"Cannot attack any more"};
	}

	if (obstructionPresent){
		return{"Invalid attack order: line of sight not clear"};
	}

	if (!validAttackDirection){
		return{"Invalid attack order: hrzntl or wrong dir"};
	}

	if (dist > 1 && dist > getMaxRange()){
		std::string result{"Out of max range (" + std::to_string(getMaxRange()) + ")"};
		return result;
	}

	// Ranged	////////////////////////////////////////////////////
	if (dist > 1){
		return this->rangedAttack(unit, dist);
	}

	// Melee	///////////////////////////////////////////////////
	
	UnitTile::Modifier flank{Modifier::FRONT_FLANK};

	//Determine flank direction

	//... both units are facing the same direction:
	if (this->getDir() == unit->getDir()){
		flank = Modifier::REAR_FLANK;
	}
	//... units are facing opposite directions:
	else if (this->getDir() == opposite(unit->getDir())){
		flank = Modifier::FRONT_FLANK;
	}
	else{
		flank = Modifier::SIDE_FLANK;
	}

	//Add the flank modifier to this unit's modVector. See particular unit's getFlankModifier() for details.
	this->modVector.emplace_back(flank, getFlankModifier(unit->getUnitFamilyType(), flank));
	
	if ((this->getUnitType() == UnitType::CUIR || this->getUnitType() == UnitType::DELI) && unit->getUnitFamilyType() == UnitFamily::CAV_FAMILY){
		this->modVector.emplace_back(Modifier::VSCAV, 1);
	}

	if ((unit->getUnitType() == UnitType::CUIR || unit->getUnitType() == UnitType::DELI) && this->getUnitFamilyType() == UnitFamily::CAV_FAMILY){
		unit->modVector.emplace_back(Modifier::VSCAV, 1);
	}

	//Double dispatch, hence the reverse order
	return unit->meleeAttack(this);
}	

//Virtual
std::string UnitTile::meleeAttack(Infantry* inf){
	return{};
}
//Virtual
std::string UnitTile::meleeAttack(Cavalry* cav){
	return{};
}

//Virtual
std::string UnitTile::meleeAttack(Cuirassier* cuir){
	return{};
}

//Virtual
std::string UnitTile::meleeAttack(Dragoon* drag){
	return{};
}

//Virtual
std::string UnitTile::meleeAttack(LightCav* lcav){
	return{};
}

//Virtual
std::string UnitTile::meleeAttack(Artillery* art){
	return{};
}
//Virtual
std::string UnitTile::meleeAttack(Mortar* mor){
	return{};
}
//Virtual
std::string UnitTile::meleeAttack(General* gen){
	return{};
}
//Virtual
std::string UnitTile::meleeAttack(Akinci* aki){
	return{};
}

//Virtual
std::string UnitTile::meleeAttack(Deli* deli){
	return{};
}


//Virtual
std::string UnitTile::rangedAttack(UnitTile* unit, int distance){
	return{};
}

//Virtual
float UnitTile::getFlankModifier(UnitFamily _family, Modifier _flank) const{
	return 0;
}

TerrainTile* UnitTile::getTilePos() const{
	return at;
}

Player* UnitTile::getPlayer() const{
	return player;
}

bool UnitTile::isHostile(UnitTile* _tile){
	if (player != _tile->getPlayer()){
		return true;
	}
	else{
		return false;
	}
}

UnitTile::UnitType UnitTile::getUnitType() const{
	return unitType;
}

UnitTile::UnitFamily UnitTile::getUnitFamilyType() const{
	return unitFamilyType;
}

int UnitTile::getCost() const{
	return deploymentCost;
}

int UnitTile::getLimit() const{
	return limit;
}

float UnitTile::gethp() const{
	return hp;
}

int UnitTile::getMov() const{
	return mov;
}

void UnitTile::takeDamage(float _dmg){
	hp -= _dmg;
	world.addToDamagedUnits(this);
}

bool UnitTile::removeIfDead(){
	if (hp < 0.4){
		world.removeUnit(this);
		return true;
	}
	return false;
}

UnitTile::Direction UnitTile::getDir() const{
	return dir;
}

void UnitTile::updateStats(){

	//Update the stats
	dirText.setString(dirToString());
	movText.setString(std::to_string(mov));
	hpText.setString(roundFloat(hp));

	//Update the physical position of the stats
    //This algorithm attempts to place the numbers in as even a space as possible:
    auto spriteSize = sprite.getLocalBounds();
	auto spritePos = sprite.getPosition();

    int combinedWidth = dirText.getLocalBounds().width + hpText.getLocalBounds().width + movText.getLocalBounds().width;
    int edgeSize = (spriteSize.width - combinedWidth) / 4;

    dirText.setPosition(spritePos.x + edgeSize, spritePos.y + spriteSize.height);
    movText.setPosition(spritePos.x + spriteSize.width - edgeSize - movText.getLocalBounds().width, spritePos.y + spriteSize.height);
    hpText.setPosition((dirText.getPosition().x + dirText.getLocalBounds().width + movText.getPosition().x) / 2 - hpText.getLocalBounds().width / 2 , spritePos.y + spriteSize.height);
}

void UnitTile::draw(sf::RenderTarget &target, sf::RenderStates states) const{
	target.draw(sprite, states);
	target.draw(unitFlag);
	target.draw(dirText);
	target.draw(hpText);
	target.draw(movText);

	if (hasAttacked){
		target.draw(redOutline);
	}

	if (highlighted){
		target.draw(yellowOutline);
	}
}

/*
Because this is one of the most important functions, and looks intimidating, I felt the need to document it well

N.B.: This function assumes the reference variables are initialised as false!!

This function does slightly different things depending on your direction, but the idea is as follows:

-Checks if your destination tile is a valid attacking direction (valid movement dirs are always valid attack dirs, but not vice 
versa),

-If so, continues forward and sets _validAttackingDirection as true; if not, return the distance and don't touch any variables

-Checks if you are within ranged attacking range, and set _inRangedAttackRange as true if so

-Checks if your destination tile is a valid moving direction, and sets _validMovDirection as true if so
	-Also, if it is a valid moving direction, checks if it is within your current movement range, setting _inMovementRange as true if so

-Checks if there are obstructions in the way, and sets _obstructionPresent as true if so

In addition, this function takes two optional parameters: canShootOverUnits and coneWidth, which default to false and 1, respectively

canShootOverUnits determines whether this unit has the ability to bypass LoS with regards to ranged attacking, and coneWidth specifies
the horizontal ranged attacking range this distance has. Most units (such as infantry) cannot shoot "past" other units, and can only
shoot straight forward. Artillery and mortar are excellent contrasting examples; they can shoot over units and have a 3-wide attacking
range
*/

//virtual
int UnitTile::distanceFrom(TerrainTile* _terrain, bool& _validMovDirection, bool& _validAttackDirection, bool& _obstructionPresent, bool& _inMovementRange, bool& _inRangedAttackRange, bool canShootOverUnits, int coneWidth){
	//coneWidth represents the width units can fire at. It should always be an odd number; 1 for the center, and 2/4/6 etc. for the sides

	//Excluding the center, obviously
	coneWidth /= 2;

	sf::Vector2i currentCoords{world.cartesianCoordsAtIndex(world.indexAtTile(*at))};
	sf::Vector2i toMoveToCoords{world.cartesianCoordsAtIndex(world.indexAtTile(*_terrain))};

	//Check if there is a unit at the terrain tile;
	UnitTile* unitAtTile = world.unitAt(_terrain);

	bool destinationIsUnit = (unitAtTile != nullptr);

	switch (dir){
	case UnitTile::Direction::N:
		if (toMoveToCoords.y < currentCoords.y
			&& ((toMoveToCoords.x >= currentCoords.x-coneWidth) && (toMoveToCoords.x <=currentCoords.x + coneWidth))){

			_validAttackDirection = true;

			if (currentCoords.y - toMoveToCoords.y <= getMaxRange()){
				_inRangedAttackRange = true;
			}

			if (toMoveToCoords.x == currentCoords.x){
				_validMovDirection = true;

				//There is no point in having _inMovementRange true if the direction isn't valid, so the check
				//is nested within the directional check
				if (currentCoords.y - toMoveToCoords.y <= mov){
					_inMovementRange = true;
				}
			}

			//For loop is for checking if the LoS is clear
			for (int i{currentCoords.y - 1}; i > toMoveToCoords.y; --i){

				//If an obstruction has already been found, no need to keep searching, just exit loop
				if (_obstructionPresent){
					break;
				}

				auto unit = world.unitAt(world.terrainAtCartesianCoords({currentCoords.x, i}));

				if (unit != nullptr){
					bool unitIsFriendly{unit->getPlayer() == this->getPlayer()};

					if (destinationIsUnit){
						if (!canShootOverUnits){
							_obstructionPresent = true;
						}
					}
					else if (!destinationIsUnit){
						if (!unitIsFriendly){
							_obstructionPresent = true;
						}
					}
				}
			}
		}

		return (currentCoords.y - toMoveToCoords.y);
		break;

	case UnitTile::Direction::E:
		if (toMoveToCoords.x > currentCoords.x
			&& (toMoveToCoords.y >= currentCoords.y - coneWidth) &&(toMoveToCoords.y <= currentCoords.y + coneWidth)){

			_validAttackDirection = true;

			if (toMoveToCoords.x - currentCoords.x <= getMaxRange()){
				_inRangedAttackRange = true;
			}

			if (toMoveToCoords.y == currentCoords.y){
				_validMovDirection = true;

				//There is no point in having _inMovementRange true if the direction isn't valid, so the check
				//is nested within the directional check
				if (toMoveToCoords.x - currentCoords.x <= mov){
					_inMovementRange = true;
				}
			}

			//For loop is for checking if the LoS is clear
			for (int i{currentCoords.x + 1}; i < toMoveToCoords.x; ++i){

				//If an obstruction has already been found, no need to keep searching, just exit loop
				if (_obstructionPresent){
					break;
				}

				auto unit = world.unitAt(world.terrainAtCartesianCoords({i, currentCoords.y}));

				if (unit != nullptr){
					bool unitIsFriendly{unit->getPlayer() == this->getPlayer()};

					if (destinationIsUnit){
						if (!canShootOverUnits){
							_obstructionPresent = true;
						}
					}
					else if (!destinationIsUnit){
						if (!unitIsFriendly){
							_obstructionPresent = true;
						}
					}
				}
			}
		}

		return (toMoveToCoords.x - currentCoords.x);
		break;

	case UnitTile::Direction::S:
		if (toMoveToCoords.y > currentCoords.y
			&& (toMoveToCoords.x >= currentCoords.x - coneWidth) && (toMoveToCoords.x <= currentCoords.x + coneWidth)){

			_validAttackDirection = true;

			if (toMoveToCoords.y - currentCoords.y <= getMaxRange()){
				_inRangedAttackRange = true;
			}

			if (toMoveToCoords.x == currentCoords.x){
				_validMovDirection = true;

				//There is no point in having _inMovementRange true if the direction isn't valid, so the check
				//is nested within the directional check
				if (toMoveToCoords.y - currentCoords.y <= mov){
					_inMovementRange = true;
				}
			}

			//For loop is for checking if the LoS is clear
			for (int i{currentCoords.y + 1}; i < toMoveToCoords.y; ++i){

				//If an obstruction has already been found, no need to keep searching, just exit loop
				if (_obstructionPresent){
					break;
				}

				auto unit = world.unitAt(world.terrainAtCartesianCoords({currentCoords.x, i}));

				if (unit != nullptr){
					bool unitIsFriendly{unit->getPlayer() == this->getPlayer()};

					if (destinationIsUnit){
						if (!canShootOverUnits){
							_obstructionPresent = true;
						}
					}
					else if (!destinationIsUnit){
						if (!unitIsFriendly){
							_obstructionPresent = true;
						}
					}
				}
			}

		}

		return (toMoveToCoords.y - currentCoords.y);
		break;

	case UnitTile::Direction::W:
		if (toMoveToCoords.x < currentCoords.x
			&& (toMoveToCoords.y >= currentCoords.y - coneWidth) && (toMoveToCoords.y <= currentCoords.y + coneWidth)){

			_validAttackDirection = true;

			if (currentCoords.x - toMoveToCoords.x <= getMaxRange()){
				_inRangedAttackRange = true;
			}

			if (toMoveToCoords.y == currentCoords.y){
				_validMovDirection = true;

				//There is no point in having _inMovementRange true if the direction isn't valid, so the check
				//is nested within the directional check
				if (currentCoords.x - toMoveToCoords.x <= mov){
					_inMovementRange = true;
				}
			}

			//For loop is for checking if the LoS is clear
			for (int i{currentCoords.x - 1}; i > toMoveToCoords.x; --i){


				//If an obstruction has already been found, no need to keep searching, just exit loop
				if (_obstructionPresent){
					break;
				}

				auto unit = world.unitAt(world.terrainAtCartesianCoords({i, currentCoords.y}));

				if (unit != nullptr){
					bool unitIsFriendly{unit->getPlayer() == this->getPlayer()};

					if (destinationIsUnit){
						if (!canShootOverUnits){
							_obstructionPresent = true;
						}
					}
					else if (!destinationIsUnit){
						if (!unitIsFriendly){
							_obstructionPresent = true;
						}
					}
				}
			}

		}

		return (currentCoords.x - toMoveToCoords.x);
		break;
	}

}

int UnitTile::distanceFrom(Tile* _tile){
	sf::Vector2i currentCoords{world.cartesianCoordsAtIndex(world.indexAtTile(*at))};
	sf::Vector2i toMoveToCoords{world.cartesianCoordsAtIndex(world.indexAtTile(*_tile))};

	switch (dir){
	case UnitTile::Direction::N:
		return (currentCoords.y - toMoveToCoords.y);
		break;

	case UnitTile::Direction::E:
		return (toMoveToCoords.x - currentCoords.x);
		break;

	case UnitTile::Direction::S:
		return (toMoveToCoords.y - currentCoords.y);
		break;

	case UnitTile::Direction::W:
		return (currentCoords.x - toMoveToCoords.x);
		break;
	}

}


std::string UnitTile::attackReport(int distance, UnitTile* attacker, UnitTile* defender, int attackerRoll, int defenderRoll, float attackerInflicted, float defenderInflicted, std::vector<UnitTile::ModifierReport>& attackerModifiers, std::vector<UnitTile::ModifierReport>& defenderModifiers){
	std::stringstream result;

	std::string attackerRollString{};

	if (!attackerModifiers.empty()){

		float finalAttackerRoll{float(attackerRoll)};

		this->multRollByModifiers(finalAttackerRoll);

		attackerRollString = attacker->getPlayer()->getName().substr(0, 3) + " " + std::to_string(attackerRoll) + " -> " + roundFloat(finalAttackerRoll);
	}
	else{
		attackerRollString = attacker->getPlayer()->getName().substr(0, 3) + " " + std::to_string(attackerRoll);
	}

	std::string defenderRollString{};

	if (!defenderModifiers.empty()){
		float finalDefenderRoll{float(defenderRoll)};

		defender->multRollByModifiers(finalDefenderRoll);

		defenderRollString = defender->getPlayer()->getName().substr(0, 3) + " " + std::to_string(defenderRoll) + " -> " + roundFloat(finalDefenderRoll);
	}
	else{
		defenderRollString = defender->getPlayer()->getName().substr(0, 3) + " " + std::to_string(defenderRoll);
	}

	std::string attackerInflictedString{attacker->getPlayer()->getName().substr(0, 3) + " -" + roundFloat(defenderInflicted)};
	std::string defenderInflictedString{defender->getPlayer()->getName().substr(0, 3) + " -" + roundFloat(attackerInflicted)};

	result << "Combat:    " << attacker->getPlayer()->getName().substr(0, 3) + " " + attacker->typeToString() + "[" + attacker->dirToString() + "] " << " vs. " << defender->getPlayer()->getName().substr(0, 3) + " " + defender->typeToString() + "[" + defender->dirToString() + "]" << "; ";

	if (distance == 1){
		result << "melee";
	}
	else{
		result << "dist. " << std::to_string(distance);
	}

	result << std::endl;

	result << "Rolls:     ";
	
	//Using > 0.0.1 instead of != 0 because of float quirks

	if (attackerRoll > 0.01){
		result << attackerRollString;
	}

	if (attackerRoll > 0.01 && defenderRoll > 0.01){
		result << " | ";
	}

	if (defenderRoll > 0.01){
		result << defenderRollString;
	}

	result << "\n";
	result << "HP:        ";

	if (defenderInflicted > 0.01){
		result << attackerInflictedString;

		//If the HP is less than 0.5, it means they are about to be deleted due to death...
		
		if (attacker->gethp() < 0.4){
			result << " (killed)";
			if (attacker->getUnitType() == UnitTile::UnitType::GEN){
				result << "; -2HP to all " + attacker->getPlayer()->getName().substr(0, 3) + "!";
			}
		}
	}

	if (defenderInflicted > 0.01 && attackerInflicted > 0.01){
		result << " | ";
	}

	if (attackerInflicted > 0.01){
		result << defenderInflictedString;

		//If the HP is less than 0.5, it means they are about to be deleted due to death...

		if (defender->gethp() < 0.4){
			result << " (killed)";
			if (defender->getUnitType() == UnitTile::UnitType::GEN){
				result << "; -2HP to all " + defender->getPlayer()->getName().substr(0, 3) + "!";
			}
		}
	}

	result << "\n";


	result << attacker->getPlayer()->getName().substr(0, 3) + " Mod:   ";

	for (auto& mod : attackerModifiers){
		if (mod.modFloat != 0){
			if (mod.modType == UnitTile::Modifier::VSCAV){
				result << "[" + modToString(mod.modType) + ": +" + roundFloat(mod.modFloat) + "]";
			}
			else{
				result << "[" + modToString(mod.modType) + ": " + roundFloat(mod.modFloat) + "d]";
			}
		}
	}

	result << "\n";

	result << defender->getPlayer()->getName().substr(0, 3) + " Mod:   ";

	for (auto& mod : defenderModifiers){
		if (mod.modFloat != 0){
			if (mod.modType == UnitTile::Modifier::VSCAV){
				result << "[" + modToString(mod.modType) + ": +" + roundFloat(mod.modFloat) + "]";
			}
			else{
				result << "[" + modToString(mod.modType) + ": " + roundFloat(mod.modFloat) + "d]";
			}
		}
	}

	return result.str();
}

void UnitTile::multRollByModifiers(float &originalRoll){
	//Anything besides the VSCAV modifier is a multiplication modifier; apply them first. Also,
	//ignore any modifier with a value of 0.
	for (auto& mod : modVector){
		if (mod.modType != Modifier::VSCAV && mod.modFloat != 0){
			originalRoll *= mod.modFloat;
		}
	}

	//Then add the value to the final resultant roll
	for (auto& mod : modVector){
		if (mod.modType == Modifier::VSCAV  && mod.modFloat != 0){
			originalRoll += mod.modFloat;
		}
	}
}

std::string UnitTile::outOfRange(){
	std::string result{"Out of max range {" + std::to_string(getMaxRange()) + "}"};
	return result;
}

bool UnitTile::getHasMoved() const{
	return hasMoved;
}

bool UnitTile::getHasRotated() const{
	return hasRotated;
}

bool UnitTile::getHasAttacked() const{
	return hasAttacked;
}

bool UnitTile::getHasHealed() const{
	return false;
}

void UnitTile::sethp(float _hp){
	hp = _hp;
}

void UnitTile::setMov(float _mov){
	mov = _mov;
}

void UnitTile::setHasMoved(bool _hasMoved){
	hasMoved = _hasMoved;
}

void UnitTile::setHasRotated(bool _hasRotated){
	hasRotated = _hasRotated;
}

void UnitTile::setHasAttacked(bool _hasAttacked){
	hasAttacked = _hasAttacked;
}

void UnitTile::setHasHealed(bool _hasHealed){

}

UnitTile::~UnitTile(){
	//Required for this to be an abstract class
}
