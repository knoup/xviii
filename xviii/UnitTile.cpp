#include "stdafx.h"
#include "UnitTile.h"

#include "Player.h"
#include "World.h"

#include "UnitLoader.h"


bool UnitTile::getMelee() const{ return unitLoader.customClasses.at(name).melee; };
bool UnitTile::getSkirmish() const{ return unitLoader.customClasses.at(name).skirmish; };
bool UnitTile::getFrightening() const { return unitLoader.customClasses.at(name).frightening; };
bool UnitTile::getHalfRangedDamage() const { return unitLoader.customClasses.at(name).halfRangedDamage; };
bool UnitTile::getLancer() const{ return unitLoader.customClasses.at(name).lancer; };
bool UnitTile::canHeal() const{ return !(unitLoader.customClasses.at(name).healingRangeValues.empty()); };
bool UnitTile::canRangedAttack() const{ return !(unitLoader.customClasses.at(name).rangedAttackDistValues.empty()); };

int UnitTile::getCost() const{ return unitLoader.customClasses.at(name).cost; };
int UnitTile::getLimit() const{ return unitLoader.customClasses.at(name).limit; };
int UnitTile::getMaxHp() const{ return unitLoader.customClasses.at(name).maxHp; };
int UnitTile::getMaxMov() const{ return unitLoader.customClasses.at(name).maxMov; };

void UnitTile::applyModifiers(UnitTile* _unit, bool _attacking){
	UnitTile::UnitType mainType = _unit->getUnitType();
	UnitTile::UnitFamily familyType = _unit->getUnitFamilyType();
	std::string unitName = _unit->getName();

	auto bonusesVsMainTypes = unitLoader.customClasses.at(name).bonusesVsMainTypes;
	auto bonusesVsFamilyTypes = unitLoader.customClasses.at(name).bonusesVsFamilyTypes;
	auto bonusesVsNames = unitLoader.customClasses.at(name).bonusesVsNames;

	for (auto& bonus : bonusesVsMainTypes){
		if (bonus.mainType == mainType){
			UnitTile::Modifier modType;
			if ((!_attacking && bonus.whenDefending) || (_attacking && bonus.whenAttacking)){
				if (bonus.modifierIsAdditional){
					modType = Modifier::ADDITIONAL;
				}
				else{
					modType = Modifier::MULTIPLICATIONAL;
				}
				modVector.emplace_back(modType, bonus.modifier);
			}
		}
	}

	for (auto& bonus : bonusesVsFamilyTypes){
		if (bonus.familyType == familyType){
			UnitTile::Modifier modType;
			if ((!_attacking && bonus.whenDefending) || (_attacking && bonus.whenAttacking)){
				if (bonus.modifierIsAdditional){
					modType = Modifier::ADDITIONAL;
				}
				else{
					modType = Modifier::MULTIPLICATIONAL;
				}
				modVector.emplace_back(modType, bonus.modifier);
			}
		}
	}

	for (auto& bonus : bonusesVsNames){
		if (bonus.name == unitName){
			UnitTile::Modifier modType;
			if ((!_attacking && bonus.whenDefending) || (_attacking && bonus.whenAttacking)){
				if (bonus.modifierIsAdditional){
					modType = Modifier::ADDITIONAL;
				}
				else{
					modType = Modifier::MULTIPLICATIONAL;
				}
				modVector.emplace_back(modType, bonus.modifier);
			}
		}
	}
}

float UnitTile::getFlankModifier(UnitType _mainType, Modifier _flank) const{
	auto vec = unitLoader.customClasses.at(name).flankModifierValues;

	for (auto& flankModifier : vec){
		if (flankModifier.type == _mainType){
			switch (_flank){
			case Modifier::FRONT_FLANK:
				return flankModifier.front;
				break;
			case Modifier::SIDE_FLANK:
				return flankModifier.side;
				break;
			case Modifier::REAR_FLANK:
				return flankModifier.rear;
				break;
			}
		}
	}

	return 0;
}

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

//virtual
int UnitTile::getMaxRange() const{
	if (!canRangedAttack()){
		return 0;
	}
	else{
		//Of course, assuming the elements of rangedAttackDistValues were inserted in order of
		//furthest to shortest distances, the first element's upper threshold should represent
		//the furthest a unit can possibly shoot
		return unitLoader.customClasses.at(name).rangedAttackDistValues[0].upperThreshold;
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

std::string UnitTile::modToString(ModifierReport _mod){
	//All modifiers are multiplicational, except (obviously) ADDITIONAL
	switch (_mod.modType){
	case Modifier::NONE:
		return{"none"};
		break;

	case Modifier::ADDITIONAL:
	case Modifier::MULTIPLICATIONAL:
		if (_mod.modFloat >= 0){
			return{"bonus"};
		}
		else{
			return{"malus"};
		}
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

UnitTile::UnitTile(UnitLoader& _unitLoader, World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, TextureManager::Unit id, std::string _name, UnitTile::UnitType type, UnitTile::UnitFamily familyType, Direction _dir) :
unitLoader(_unitLoader),
Tile(_world, tm, id),
mt19937(_mt19937),
name{_name},
unitType{type},
unitFamilyType{familyType},
player{_belongsToPlayer},
dir{_dir},
hp{0},
mov{0},
terrain{nullptr}

{
	unitFlag = player->getNationFlag();

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

	hp = getMaxHp();
	mov = getMaxMov();
}

void UnitTile::spawn(TerrainTile* terrainTile){
	if (terrain != nullptr){
		terrain->resetUnit();
	}

	terrain = terrainTile;
	terrainTile->setUnit(this);
	sprite.setPosition(terrainTile->getPixelPos());
	unitFlag.setPosition(terrainTile->getPixelPos());
	yellowOutline.setPosition(terrainTile->getPixelPos());
	redOutline.setPosition(terrainTile->getPixelPos());
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
	sf::Vector2i currentCoords{world.cartesianPosAtIndex(world.indexAtTile(*terrain))};

	//Get the coordinates of the tile to be moved to
	sf::Vector2i toMoveToCoords{world.cartesianPosAtIndex(world.indexAtTile(*_terrainTile))};

	sf::Vector2i vectorDist = distanceFrom(_terrainTile, validMovDirection, validAttackDirection, obstructionPresent, inMovementRange, inRangedAttackRange);

	if (dir == Direction::N || dir == Direction::S){
		movExpended = abs(vectorDist.y);
	}
	else{
		movExpended = abs(vectorDist.x);
	}

	if (obstructionPresent){
		return OBSTRUCTION_PRESENT_MOV;
	}

	else if (validMovDirection && inMovementRange){
		terrain->resetUnit();
		terrain = _terrainTile;
		_terrainTile->setUnit(this);
		mov -= movExpended;
		sprite.setPosition(_terrainTile->getPixelPos());
		unitFlag.setPosition(_terrainTile->getPixelPos());
		yellowOutline.setPosition(_terrainTile->getPixelPos());
		redOutline.setPosition(_terrainTile->getPixelPos());
		updateStats();
		return MOV_SUCCESS + std::to_string(toMoveToCoords.x + 1) + ", " + std::to_string(toMoveToCoords.y + 1);
	}

	else if (validMovDirection && !inMovementRange){
		return{NO_MOV};
	}

	else if (!validMovDirection){
		return{INVALID_DIR_MOV};
	}

}

//Virtual
void UnitTile::reset(){
	calculateEffectiveMov();
	hasHealed = false;
	hasMoved = false;
	hasPartialRotated = false;
	hasFullRotated = false;
	hasMeleeAttacked = false;
	hasRangedAttacked = false;
	updateStats();
}

std::string UnitTile::heal(UnitTile* _unit){
	if (canHeal()){
		sf::Vector2i thisPos = getCartesianPos();
		sf::Vector2i friendlyPos = _unit->getCartesianPos();

		sf::Vector2i difference = (thisPos - friendlyPos);
		difference.x = abs(difference.x);
		difference.y = abs(difference.y);

		float healingAmount{0};

		for (auto & healingRange : unitLoader.customClasses.at(name).healingRangeValues){
			if ((healingRange.lowerThreshold == 0 && healingRange.upperThreshold == 0)
				||
				difference.x >= healingRange.lowerThreshold && difference.y >= healingRange.lowerThreshold
				&&
				difference.x <= healingRange.upperThreshold && difference.y <= healingRange.upperThreshold){

				healingAmount = healingRange.healingAmount;
			}
		}

		if (healingAmount == 0){
			return OUT_OF_RANGE + std::to_string(unitLoader.customClasses.at(name).healingRangeValues[0].upperThreshold);
		}
		else if (_unit == this){
			return CANNOT_HEAL_SELF;
		}
		else if (hasHealed){
			return ALREADY_HEALED;
		}
		else if (_unit->gethp() == _unit->getMaxHp()){
			return AT_MAX_HP;
		}
		else {
			float hp = _unit->gethp();
			float max = _unit->getMaxHp();
			float hpDifference = max - hp;

			hasHealed = true;

			if (hpDifference >= healingAmount){
				return _unit->beHealed(healingAmount);
			}
			else{
				return _unit->beHealed(hpDifference);
			}
		}
	}

	return CANNOT_HEAL;
}

std::string UnitTile::beHealed(float num){
	hp += num;
	updateStats();
	std::string str;
	str = HEAL_SUCCESS + roundFloat(num);
	return str;
}

std::string UnitTile::attack(UnitTile* unit){
	bool validMovDirection{false};
	bool validAttackDirection{false};
	bool obstructionPresent{false};
	bool inMovementRange{false};
	bool inRangedAttackRange{false};

	sf::Vector2i vectorDist = distanceFrom(unit->terrain, validMovDirection, validAttackDirection, obstructionPresent, inMovementRange, inRangedAttackRange);
	int dist{0};

	if (dir == Direction::N || dir == Direction::S){
		dist = abs(vectorDist.y);
	}
	else{
		dist = abs(vectorDist.x);
	}

	if (hasMeleeAttacked || hasRangedAttacked){
		return{ALREADY_ATTACKED};
	}

	if (obstructionPresent){
		return{OBSTRUCTION_PRESENT_ATK};
	}

	if (!validAttackDirection){
		return{INVALID_DIR_ATK};
	}

	if (dist > 1 && dist > getMaxRange()){
		std::string result{OUT_OF_RANGE + std::to_string(getMaxRange())};
		return result;
	}

	// Ranged	////////////////////////////////////////////////////
	if (dist > 1){
		return this->rangedAttack(unit, dist);
	}

	// Melee	///////////////////////////////////////////////////

	if (dist == 1 && !getMelee()){
		return NO_MELEE;
	}
	
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

	this->modVector.emplace_back(flank, getFlankModifier(unit->getUnitType(), flank));

	
	//Apply unit-specific modifiers
	this->applyModifiers(unit, true);
	unit->applyModifiers(this, false);

	//Double dispatch, hence the reverse order
	return unit->meleeAttack(this);
}	


bool UnitTile::isHostile(UnitTile* _tile){
	if (player != _tile->getPlayer()){
		return true;
	}
	else{
		return false;
	}
}

void UnitTile::takeDamage(UnitTile* attacker, float& _dmg, int distance){
	if (attacker->getFrightening() && distance == 1){
		_dmg += 1;
	}

	if (distance > 1 && getHalfRangedDamage()){
		_dmg *= 0.5;
	}

	hp -= _dmg;
	world.addToDamagedUnits(this);
}

bool UnitTile::removeIfDead(){
	if (hp < 0.4){
		player->removeUnit(this);
		return true;
	}
	return false;
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

	if (hasMeleeAttacked || hasRangedAttacked){
		target.draw(redOutline);
	}

	if (highlighted){
		target.draw(yellowOutline);
	}
}

/*
Because this is one of the most important functions, and looks intimidating, I felt the need to document it well

N.B.: This function assumes the reference variables are initialised as false!!

This function, first of all, determines your main and secondary axes and their positive and negative parts. It then:

-Checks if your destination tile is a valid attacking direction (valid movement dirs are always valid attack dirs, but not vice 
versa),

-If so, continues forward and sets _validAttackingDirection as true; if not, return the distance and don't touch any variables

-Checks if your distance is 1 and you cannot shoot at close range; if that is so,
	-Check if your target is diagonal in relation to you,
		-If so, set _validAttackingDirection to false

-Checks if you are within ranged attacking range, and set _inRangedAttackRange as true if so

-Checks if your destination tile is a valid moving direction, and sets _validMovDirection as true if so
	-Also, if it is a valid moving direction, checks if it is within your current movement range, setting _inMovementRange as true if so

-Checks if there are obstructions in the way, and sets _obstructionPresent as true if so

In addition, this function takes three optional parameters: canShootOverUnits, canShootAtCloseRange, coneWidth, which default to false,
false, and 1, respectively

canShootOverUnits specifies whether this unit has the ability to bypass LoS with regards to ranged attacking, and coneWidth specifies
the horizontal ranged attacking range this distance has. Most units (such as infantry) cannot shoot "past" other units, and can only
shoot straight forward. Artillery and mortar are excellent contrasting examples; they can shoot over units and have a 3-wide attacking
range.
*/

//virtual
sf::Vector2i UnitTile::distanceFrom(TerrainTile* _terrain, bool& _validMovDirection, bool& _validAttackDirection, bool& _obstructionPresent, bool& _inMovementRange, bool& _inRangedAttackRange, bool canShootOverUnits, int coneWidth){
	//coneWidth represents the width units can fire at. It should always be an odd number; 1 for the center, and 2/4/6 etc. for the sides

	//Excluding the center, obviously
	coneWidth /= 2;

	sf::Vector2i currentCoords{terrain->getCartesianPos()};
	sf::Vector2i toMoveToCoords{_terrain->getCartesianPos()};

	//Check if there is a unit at the terrain tile;
	UnitTile* unitAtTile = world.unitAtTerrain(_terrain);

	bool destinationIsUnit = (unitAtTile != nullptr);

	int dist{0};

	int PRIMARYAXIS_POSITIVE;
	int PRIMARYAXIS_NEGATIVE;
	int SECONDARYAXIS_POSITIVE;
	int SECONDARYAXIS_NEGATIVE;

	switch (dir){
	case UnitTile::Direction::N:
		PRIMARYAXIS_POSITIVE = currentCoords.y;
		PRIMARYAXIS_NEGATIVE = toMoveToCoords.y;
		SECONDARYAXIS_POSITIVE = toMoveToCoords.x;
		SECONDARYAXIS_NEGATIVE = currentCoords.x;
		break;

	case UnitTile::Direction::E:
		PRIMARYAXIS_POSITIVE = toMoveToCoords.x;
		PRIMARYAXIS_NEGATIVE = currentCoords.x;
		SECONDARYAXIS_POSITIVE = toMoveToCoords.y;
		SECONDARYAXIS_NEGATIVE = currentCoords.y;
		break;

	case UnitTile::Direction::S:
		PRIMARYAXIS_POSITIVE = toMoveToCoords.y;
		PRIMARYAXIS_NEGATIVE = currentCoords.y;
		SECONDARYAXIS_POSITIVE = toMoveToCoords.x;
		SECONDARYAXIS_NEGATIVE = currentCoords.x;
		break;


	case UnitTile::Direction::W:
		PRIMARYAXIS_POSITIVE = currentCoords.x;
		PRIMARYAXIS_NEGATIVE = toMoveToCoords.x;
		SECONDARYAXIS_POSITIVE = toMoveToCoords.y;
		SECONDARYAXIS_NEGATIVE = currentCoords.y;
		break;
	}


	dist = (PRIMARYAXIS_POSITIVE - PRIMARYAXIS_NEGATIVE);

	if (PRIMARYAXIS_NEGATIVE < PRIMARYAXIS_POSITIVE
		&& ((SECONDARYAXIS_POSITIVE >= SECONDARYAXIS_NEGATIVE - coneWidth) && (SECONDARYAXIS_POSITIVE <= SECONDARYAXIS_NEGATIVE + coneWidth))){

		_validAttackDirection = true;

		if (dist == 1 && getMelee()){
			if (!((SECONDARYAXIS_POSITIVE >= SECONDARYAXIS_NEGATIVE) && (SECONDARYAXIS_POSITIVE <= SECONDARYAXIS_NEGATIVE))){
				_validAttackDirection = false;
			}
		}

		if (PRIMARYAXIS_POSITIVE - PRIMARYAXIS_NEGATIVE <= getMaxRange()){
			_inRangedAttackRange = true;
		}

		if (SECONDARYAXIS_POSITIVE == SECONDARYAXIS_NEGATIVE){
			_validMovDirection = true;

			//There is no point in having _inMovementRange true if the direction isn't valid, so the check
			//is nested within the directional check
			if (PRIMARYAXIS_POSITIVE - PRIMARYAXIS_NEGATIVE <= mov){
				_inMovementRange = true;
			}
		}

		//For loop is for checking if the LoS is clear
		for (int i{PRIMARYAXIS_POSITIVE - 1}; i > PRIMARYAXIS_NEGATIVE; --i){

			//If an obstruction has already been found, no need to keep searching, just exit loop
			if (_obstructionPresent){
				break;
			}

			UnitTile* unit;

			if (dir == Direction::N || dir == Direction::S){
				unit = world.unitAtTerrain(world.terrainAtCartesianPos({SECONDARYAXIS_POSITIVE, i}));
			}
			else{
				unit = world.unitAtTerrain(world.terrainAtCartesianPos({i, SECONDARYAXIS_POSITIVE}));
			}

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

	return{toMoveToCoords - currentCoords};

}

int UnitTile::distanceFrom(Tile* _tile){
	sf::Vector2i currentCoords{world.cartesianPosAtIndex(world.indexAtTile(*terrain))};
	sf::Vector2i toMoveToCoords{world.cartesianPosAtIndex(world.indexAtTile(*_tile))};

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


std::string UnitTile::attackReport(int distance, UnitTile* attacker, UnitTile* defender, int attackerRoll, int defenderRoll, float attackerInflicted, float defenderInflicted, bool retreat){
	std::stringstream result;

	std::vector<ModifierReport>& attackerModifiers = attacker->modVector;
	std::vector<ModifierReport>& defenderModifiers = defender->modVector;

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

	result << "Combat:    " << attacker->getPlayer()->getName().substr(0, 3) + " " + attacker->name + "[" + attacker->dirToString() + "] " << " vs. " << defender->getPlayer()->getName().substr(0, 3) + " " + defender->name + "[" + defender->dirToString() + "]" << "; ";

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
			if (mod.modType == UnitTile::Modifier::ADDITIONAL || mod.modType == UnitTile::Modifier::ATK){
				std::string append{mod.modFloat >= 0 ? "+" : ""};
				result << "[" + modToString(mod) + ": " + append + roundFloat(mod.modFloat) + "]";
			}
			else{
				result << "[" + modToString(mod) + ": " + roundFloat(mod.modFloat) + "d]";
			}
		}
	}

	if (attacker->getFrightening() && distance == 1 && attackerInflicted > 0){
		result << "[frightening: +1DMG]";
	}

	result << "\n";

	result << defender->getPlayer()->getName().substr(0, 3) + " Mod:   ";

	if (retreat){
		result << "(retreat!) ";
	}

	for (auto& mod : defenderModifiers){
		if (mod.modFloat != 0){
			if (mod.modType == UnitTile::Modifier::ADDITIONAL || mod.modType == UnitTile::Modifier::ATK){
				std::string append{mod.modFloat >= 0 ? "+" : ""};
				result << "[" + modToString(mod) + ": " + append + roundFloat(mod.modFloat) + "]";
			}
			else{
				result << "[" + modToString(mod) + ": " + roundFloat(mod.modFloat) + "d]";
			}
		}
	}

	if (defender->getFrightening() && distance == 1 && defenderInflicted > 0){
		result << "[frightening: +1DMG]";
	}

	return result.str();
}

void UnitTile::multRollByModifiers(float &originalRoll){
	for (auto& mod : modVector){
		if (mod.modFloat != 0){
			if (mod.modType != Modifier::ADDITIONAL){
				originalRoll *= mod.modFloat;
			}
		}
	}


	for (auto& mod : modVector){
		if (mod.modFloat != 0){
			if (mod.modType == Modifier::ADDITIONAL){
			originalRoll += mod.modFloat;
			}
		}
	}

	//If the roll goes below 1, pop it up back to 1
	if (originalRoll < 1.001){
		originalRoll = 1;
	}
}

void UnitTile::calculateEffectiveMov(){
	UnitTile* general = player->getGeneral();

	if (general == nullptr){
		//Implicitly rounded down
		setMov(getMaxMov()*0.65);
	}
	else{
		sf::Vector2i generalPos = general->getCartesianPos();
		sf::Vector2i currentPos = getCartesianPos();
		sf::Vector2i distance = currentPos - generalPos;
		distance.x = abs(distance.x);
		distance.y = abs(distance.y);

		if (distance.x >= 21 || distance.y >= 21){
			if (distance.x <= 34 && distance.y <= 34){
				setMov(getMaxMov()*0.75);
			}
			else{
				setMov(getMaxMov()*0.65);
			}
		}
		else{
			setMov(getMaxMov());
		}

	}
}

std::string UnitTile::rangedAttack(UnitTile* unit, int distance){

	std::uniform_int_distribution<int> distribution(1, 6);

	int thisRoll_int{distribution(mt19937)};

	float thisRoll = thisRoll_int;

	float damageDealt{0};

	float distanceModifier{0};

	int lowerDieThreshold{1};
	int upperDieThreshold{6};
	bool modifierIsDamage{false};

	for (auto& item : unitLoader.customClasses.at(name).rangedAttackDistValues){
		if (distance >= item.lowerThreshold && distance <= item.upperThreshold){
			distanceModifier = item.distModifier;
			modifierIsDamage = item.modifierIsDamage;
			lowerDieThreshold = item.lowerDieThreshold;
			upperDieThreshold = item.upperDieThreshold;
			continue;
		}
	}

	if (!modifierIsDamage){
		modVector.emplace_back(Modifier::DISTANCE, distanceModifier);

		multRollByModifiers(thisRoll);
		damageDealt += thisRoll;
	}
	else{
		modVector.emplace_back(Modifier::DISTANCE, 1);

		multRollByModifiers(thisRoll);
		damageDealt = distanceModifier;
	}

	if (thisRoll_int >= lowerDieThreshold && thisRoll_int <= upperDieThreshold){
		unit->takeDamage(this, damageDealt, distance);
	}
	else{
		damageDealt = 0;
	}

	mov = 0;
	this->updateStats();
	unit->updateStats();
	hasRangedAttacked = true;


	/*
	Units that can skirmish need to be able to rotate a second time sometimes. Take the following scenario, for instance:
	A LINF is facing south.
		-It turns north
		-It fires at an enemy
	Its skirmisher bonus should be usable now, and it should be able to turn south again.
	*/

	if (getSkirmish()){
		hasFullRotated = false;
	}

	return attackReport(distance, this, unit, thisRoll_int, 0, damageDealt, 0);
}

UnitTile::~UnitTile(){
	//Required for this to be an abstract class
}