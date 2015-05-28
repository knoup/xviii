#pragma once

#include "TerrainTile.h"
#include "FontManager.h"

#include <random>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <math.h>

#include "messages.h"

//The last entry, the texture enum, is used only for the selectable units at selection menu. They are NOT used to determine
//actual unit sprites past that point.
#define UNITPROPERTIES\
	X(UnitTile::UnitType::ART, Artillery, "art", TextureManager::Unit::ART)\
	X(UnitTile::UnitType::CAV, Cavalry, "cav", TextureManager::Unit::CAV)\
	X(UnitTile::UnitType::CUIR, Cuirassier, "cuir", TextureManager::Unit::CUIR )\
	X(UnitTile::UnitType::DRAG, Dragoon, "drag", TextureManager::Unit::DRAG)\
	X(UnitTile::UnitType::GEN, General, "gen", TextureManager::Unit::GEN)\
	X(UnitTile::UnitType::INF, Infantry, "inf", TextureManager::Unit::INF)\
	X(UnitTile::UnitType::LCAV, LightCav, "lcav", TextureManager::Unit::LCAV)\
	X(UnitTile::UnitType::MOR, Mortar, "mor", TextureManager::Unit::MOR)\
	X(UnitTile::UnitType::AKINCI, Akinci, "akinci", TextureManager::Unit::DRAG)\
	X(UnitTile::UnitType::DELI, Deli, "deli", TextureManager::Unit::LCAV)\
	X(UnitTile::UnitType::TIM, Timarioti, "tim", TextureManager::Unit::CAV)\
	X(UnitTile::UnitType::KAP, Kapikulu, "kap", TextureManager::Unit::ARMLAN)\
	X(UnitTile::UnitType::GRE, Grenadier, "gre", TextureManager::Unit::GRE)\
	X(UnitTile::UnitType::JAN, Janissary, "jan", TextureManager::Unit::GRE)\
	X(UnitTile::UnitType::OINF, OttoInf, "o inf", TextureManager::Unit::INF)\
	X(UnitTile::UnitType::LINF, LightInf, "linf", TextureManager::Unit::LINF)\
	X(UnitTile::UnitType::SAP, Sapper, "sap", TextureManager::Unit::SAP)\
	X(UnitTile::UnitType::CRICAV, CrimeanCav, "cr cav", TextureManager::Unit::HARCH)\
	X(UnitTile::UnitType::COSINF, CossackInf, "cos inf", TextureManager::Unit::INF)\
	X(UnitTile::UnitType::KMKH, KhevMkhedrebi, "khev mkh", TextureManager::Unit::CUIR)\
	X(UnitTile::UnitType::PIT, PitsisKatsebi, "pit kat", TextureManager::Unit::CAV)\
	X(UnitTile::UnitType::DON, DonCossack, "don cos", TextureManager::Unit::LCAV)\
	X(UnitTile::UnitType::AMKH, AbrMkhedrebi, "abr mkh", TextureManager::Unit::DRAG)\
	X(UnitTile::UnitType::METTOP, MetTop, "met top", TextureManager::Unit::INF)\
	X(UnitTile::UnitType::KACI, KudzeKaci, "kud kaci", TextureManager::Unit::LINF)\
	X(UnitTile::UnitType::FOOT, FootGuard, "footguard", TextureManager::Unit::HINF)\
	X(UnitTile::UnitType::KKV, KhevKveitebi, "khev kvei", TextureManager::Unit::HINF)\
	X(UnitTile::UnitType::HUS, Hussar, "hussar", TextureManager::Unit::LCAV)\
	X(UnitTile::UnitType::COUR, Courtin, "courtin", TextureManager::Unit::CAV)\
	X(UnitTile::UnitType::SEG, Segbans, "segbans", TextureManager::Unit::DRAG)\
	X(UnitTile::UnitType::BOY, Boyar, "boyar", TextureManager::Unit::LAN)\
	X(UnitTile::UnitType::DOR, Dorunaby, "dorunaby", TextureManager::Unit::GRE)\
	X(UnitTile::UnitType::VIT, Vitae, "vitae", TextureManager::Unit::LINF)\
	X(UnitTile::UnitType::ARN, Arnauts, "arnauts", TextureManager::Unit::INF)\
	X(UnitTile::UnitType::ARTGUARD, ArtGuard, "art guard", TextureManager::Unit::ARTGUARD)\
	X(UnitTile::UnitType::PIKE, Pikemen, "pikemen", TextureManager::Unit::PIKE)\
	X(UnitTile::UnitType::LAN, Lancer, "lancer", TextureManager::Unit::LAN)\
	X(UnitTile::UnitType::MUT, Mutteferrika, "mutte", TextureManager::Unit::DRAG)\
	X(UnitTile::UnitType::MARZ, Marzas, "marzas", TextureManager::Unit::CAV)\
	X(UnitTile::UnitType::AZAP, Azaps, "azaps", TextureManager::Unit::IRR)\
	X(UnitTile::UnitType::TTINF, TatarInf, "tatar", TextureManager::Unit::LINF)\
	X(UnitTile::UnitType::MUL, Mulizamy, "mulizamy", TextureManager::Unit::CUIR)\
	X(UnitTile::UnitType::GUL, Gul, "gul", TextureManager::Unit::ARMLAN)\
	X(UnitTile::UnitType::PCAV, PersianCav, "per cav", TextureManager::Unit::HARCH)\
	X(UnitTile::UnitType::CURCI, Curci, "curci", TextureManager::Unit::DRAG)\
	X(UnitTile::UnitType::PINF, PersianInf, "per inf", TextureManager::Unit::INF)\
	X(UnitTile::UnitType::KINF, KurdishInf, "kurd inf", TextureManager::Unit::LINF)

class Player;

class Infantry;
class Cavalry;
class Cuirassier;
class Dragoon;
class LightCav;
class Artillery;
class Mortar;
class General;
class Akinci;
class Deli;
class Timarioti;
class Kapikulu;
class Grenadier;
class Janissary;
class OttoInf;
class LightInf;
class Sapper;
class CrimeanCav;
class CossackInf;
class KhevMkhedrebi;
class PitsisKatsebi;
class DonCossack;
class AbrMkhedrebi;
class MetTop;
class KudzeKaci;
class FootGuard;
class KhevKveitebi;
class Hussar;
class Courtin;
class Segbans;
class Boyar;
class Dorunaby;
class Vitae;
class Arnauts;
class ArtGuard;
class Pikemen;
class Lancer;
class Mutteferrika;
class Marzas;
class Azaps;
class TatarInf;
class Mulizamy;
class Gul;
class PersianCav;
class Curci;
class PersianInf;
class KurdishInf;

class UnitTile : public Tile
{
public:
	using unitPtr = std::unique_ptr<UnitTile>;

	enum class Direction{ N, E, S, W };

	enum class Modifier{NONE, ADDITIONAL, ATK, DISTANCE, FRONT_FLANK, SIDE_FLANK, REAR_FLANK};

	enum class UnitType{INF, CAV, CUIR, LCAV, DRAG, 
						ART, MOR, GEN, AKINCI, DELI, 
						TIM, KAP, GRE, JAN, OINF, 
						LINF, SAP, CRICAV, COSINF, KMKH, 
						AMKH, PIT, DON, METTOP, KACI, 
						FOOT, KKV, HUS, COUR, SEG, 
						BOY, DOR, VIT, ARN, ARTGUARD, 
						PIKE, LAN, MUT, MARZ, AZAP,
						TTINF, MUL, GUL, PCAV, CURCI,
						PINF, KINF};

	//Each UnitFamily generally has its own combat rules. LINF, however, does not, and for the moment, HINF's
	//is identical to INF.
	enum class UnitFamily{LINF_FAMILY, INF_FAMILY, HINF_FAMILY, CAV_FAMILY, ART_FAMILY};

	//Used for storing modifier information

	struct ModifierReport{

		ModifierReport(Modifier _modType, float _modFloat) : 
		modType{_modType},
		modFloat{_modFloat}
		{
		}

		Modifier modType;
		float modFloat;
	};

	struct RangedAttackRange{
		RangedAttackRange(int _lower, int _upper, float _distModifier) :
			lowerThreshold{_lower},
			upperThreshold{_upper},
			distModifier{_distModifier}
		{
		}

		//The lower and upper thresholds specify the range at which the accompanying distModifier will 
		//take effect. For example, if:
		//lowerThreshold = 3;
		//upperThreshold = 5;
		//distModifier = 1.5;
		//Then the unit will get a distance modifier of 1.5 when shooting at a distance between 3 and 5 (inclusive)

		int lowerThreshold;
		int upperThreshold;
		float distModifier;
	};

	struct HealingRange{
		HealingRange(int _lower, int _upper, float _healingAmount) :
			lowerThreshold{_lower},
			upperThreshold{_upper},
			healingAmount{_healingAmount}
		{
		}

		//Note that an upper and lower threshold of both 0 means unlimited healing range

		int lowerThreshold;
		int upperThreshold;
		float healingAmount;
	};

	UnitTile(World& _world, std::mt19937&, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, TextureManager::Unit id, UnitType type, UnitFamily familyType, Direction _dir);
	//Create a virtual destructor, signifying this is an abstract class
	virtual ~UnitTile() = 0;

	//Getters
	//////////////////////////////////////////////////////////////////////////////////////////////////

	//Non-Virtual
	inline TerrainTile* getTerrain() const{ return terrain; };
	inline Player* getPlayer() const{ return player; };
	inline UnitType getUnitType() const{ return unitType; };
	inline UnitFamily getUnitFamilyType() const { return unitFamilyType; };
	inline float gethp() const{ return hp; };
	inline int getMov() const{	return mov;	};
	inline UnitTile::Direction getDir() const{ return dir; };

	inline bool getHasMoved() const{ return hasMoved; };
	inline bool getHasPartialRotated() const{ return hasPartialRotated; };
	inline bool getHasFullRotated() const{ return hasFullRotated; };
	inline bool getHasAnyRotated() const{ return (hasPartialRotated || hasFullRotated); };
	inline bool getHasMeleeAttacked() const{ return hasMeleeAttacked; };
	inline bool getHasRangedAttacked() const{ return hasRangedAttacked; };
	inline bool getHasAnyAttacked() const{ return (hasMeleeAttacked || hasRangedAttacked); };
	inline bool getHasHealed() const{ return hasHealed; };

	//Virtual
	inline virtual int getCost() const{ return 100; };
	inline virtual int getLimit() const{ return 1; };
	inline virtual int getMaxHp() const{ return 0; };
	inline virtual int getMaxMov() const{ return 0; };
	int getMaxRange() const;

	inline bool canHeal() const{ return !healingRangeValues.empty(); };
	inline bool canRangedAttack() const{ return !rangedAttackDistValues.empty(); };
	//UNLESS OTHERWISE MENTIONED IN THE CLASS HEADER, THESE FUNCTIONS WILL DEFAULT TO:
	/////
	inline virtual bool canMelee() const{ return true; };
	//Determines whether the unit can skirmish or not (skirmishing gives the ability to fully rotate after firing, and have 2 movement points left over)
	inline virtual bool canSkirmish(){ return false; };
	//Determines whether the unit gets the "frightening" bonus (+1 damage if any damage dealt)
	inline virtual bool frightening(){ return false; };
	inline virtual bool hasLancerBonus(){ return false; };
	/////

	//Each class will have an overloaded definition returning its specific flank modifier for either 
	//INF or CAV family units. In the interest of keeping the modifiers static, each class will have 
	//its own implementation of essentially the same function.
	inline virtual float getFlankModifier(UnitFamily _family, Modifier _flank) const{ return 0; };

	//////////////////////////////////////////////////////////////////////////////////////////////////

	//Setters
	//////////////////////////////////////////////////////////////////////////////////////////////////

	inline void sethp(float _hp){ hp = _hp; };
	inline void setMov(float _mov){ mov = _mov; };
	inline void setDir(Direction _dir){ dir = _dir; };
	inline void setHasMoved(bool _hasMoved){ hasMoved = _hasMoved; };
	inline void setHasPartialRotated(bool _hasPartialRotated){ hasPartialRotated = _hasPartialRotated; };
	inline void setHasFullRotated(bool _hasFullRotated){ hasFullRotated = _hasFullRotated; };
	inline void setHasMeleeAttacked(bool _value){ hasMeleeAttacked = _value; };
	inline void setHasRangedAttacked(bool _value){ hasRangedAttacked = _value; };
	inline void setHasHealed(bool _value){ hasHealed = _value; };

	//////////////////////////////////////////////////////////////////////////////////////////////////

	//The following are applicable only for some children
	inline virtual void setUniqueVariable(bool _uniqueVariable){};
	inline virtual bool getUniqueVariable() const{ return false; };

	//////////////////////////////////////////////////////////////////////////////////////////////////

	//Other - Virtual
	//////////////////////////////////////////////////////////////////////////////////////////////////

	virtual void takeDamage(UnitTile* attacker, float& _dmg, int distance);
	virtual std::string moveTo(TerrainTile* _terrainTile);
	//Called at the end of every turn;
	virtual void reset();
	inline virtual std::string rotate(Direction _dir){ return{}; };

	//This function is unit-specific, and checks for such things as vs. family bonuses/maluses. The bool specifies
	//whether the unit is attacking or defending
	inline virtual void preMeleeAttack(UnitTile* unit, bool attacking){};

	//Needed for double dispatch
	virtual std::string meleeAttack(UnitTile* _unit) = 0;

	inline virtual std::string meleeAttack(Infantry* inf){ return{}; };
	inline virtual std::string meleeAttack(Cavalry* cav){ return{}; };
	inline virtual std::string meleeAttack(Artillery* art){ return{}; };
	inline virtual std::string meleeAttack(Mortar* mor){ return{}; };

	virtual std::string rangedAttack(UnitTile* unit, int distance);

	//Further documented in UnitTile.cpp
	virtual sf::Vector2i distanceFrom(TerrainTile* _terrain, bool& _validMovDirection, bool& _validAttackDirection, bool& _obstructionPresent, bool& _inMovementRange, bool& _inRangedAttackRange, bool canShootOverUnits = false, int coneWidth = 1);

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	//////////////////////////////////////////////////////////////////////////////////////////////////


	//Other - Non Virtual
	//////////////////////////////////////////////////////////////////////////////////////////////////
	std::string heal(UnitTile* _unit);
	std::string beHealed(float num);
	void calculateEffectiveMov();

	//Returns true if dead
	bool removeIfDead();

	UnitTile::Direction opposite(UnitTile::Direction _dir);

	//Spawn is very similar to moveTo, but is only used during the setup phase; it costs no movement 
	void spawn(TerrainTile* terrainTile);

	//This function is in charge of initiating combat by determining distance, flank, etc. and calling either
	//meleeAttack() or rangedAttack()
	std::string attack(UnitTile* _unit);

	bool isHostile(UnitTile* _tile);

    //Manages the position of the sf::Text numbers (hp and movement)
	void updateStats();

	//Overloaded version that only gets the distance and doesn't take in bools
	int distanceFrom(Tile* _tile);

	std::string dirToString();
	std::string modToString(ModifierReport _mod);
	std::string typeToString();

	std::string attackReport(int distance, UnitTile* attacker, UnitTile* defender, int attackerRoll, int defenderRoll, float attackerInflicted, float defenderInflicted, bool retreat = false);	

	void multRollByModifiers(float &originalRoll);
	std::string roundFloat(const double x);

	//////////////////////////////////////////////////////////////////////////////////////////////////

	//Data member
	std::vector<ModifierReport> modVector;

protected:
	//Elements must be inserted in order of furthest to shortest distances; the first 
	//element's upper threshold should represent the furthest a unit can shoot
	std::vector<RangedAttackRange> rangedAttackDistValues;
	std::vector<HealingRange> healingRangeValues;

	std::mt19937& mt19937;

	//Pointer to the player the unit belongs to
	Player* player;

	//The unit's current direction (NESW)
	Direction dir;

	//In addition to each player having a flag, each unit itself must have a flag sprite too
	sf::Sprite unitFlag;
	//Pointer to the terrain tile that the unit is on. This is only to be used for units, to indicate
	//where they are easily and efficiently, since a unit must always be on a terrain tile
	TerrainTile* terrain;

	//For (yellow) outlining
	sf::RectangleShape yellowOutline;
	//For (red) outlining
	sf::RectangleShape redOutline;

	//The visual representations of the stats
    sf::Text dirText;
	sf::Text hpText;
	sf::Text movText;

	UnitType unitType;
	UnitFamily unitFamilyType;

	float hp;
	int mov;

	bool hasMoved{false};
	bool hasPartialRotated{false};
	bool hasFullRotated{false};
	bool hasMeleeAttacked{false};
	bool hasRangedAttacked{false};
	bool hasHealed{false};
};

