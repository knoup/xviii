-------------------------------------------------------------
All unit definitions must have the following line

[UNIT DEFINITION]

as the very first line in the file. The name of the file will serve as the unit's ID, the name with which you will be able to define bonuses.

[NATION]:
{
	DEFINE:Austria
	DEFINE:Prussia
}

In the shown format, nations to whom this unit is available must be defined. The names of the nations must be one of those of the factions defined in assets/factions. Optionally, DEFINE:ALL can be used to make the unit available to all nations.

[NAME]:Infantry
[SHORT]: inf
[SPRITE]:inf
[MAIN_TYPE]:INF
[FAMILY_TYPE]:INF

[NAME] is the unit's name. Note that 2 units may have the same name, as long as the ID (name of the .txt file itself) is different.
[SHORT] is the shorthand version of the name.
[SPRITE] specifies the unit's sprite. These are simply filenames of sprites in assets/gfx/units. Note that
these images must be in a .png format.
[MAIN_TYPE] specifies the unit's primary type and is vital for behavior.
[FAMILY_TYPE] does not have any explicit effects, but is used to further classify units for bonuses.

[SQUAREFORMATION]:1
[SQUAREFORMATIONMODIFIER]:1

SQUAREFORMATION denotes whether the unit is capable of going into square formation,
while SQUAREFORMATIONMODIFIER specifies the (multiplicational) modifier this unit gets when fighting
units in square formation (no matter the flank)

[LIMBER]:0
[LANCER]:0

These determine whether the unit is a lancer (no effect for non-cav units) and whether
the unit uses the limber mechanic.

[WATERCROSSER]:1

This determines whether the unit is capable of crossing water tiles without the need for a bridge.

[HP]:
[MOV]:
[COST]:
[LIMIT]


[COST] specifies the unit's deployment point cost
[LIMIT] specifies the maximum amount of units of this type that can be deployed per player (0 for unlimited)

[SKIRMISH]:
[FRIGHTENING]:
[HALFRANGEDDAMAGE]:
[MELEE]:

[SKIRMISH] specifies whether the unit is capable of skirmishing. Depending on certain criteria, the unit may still be able to move after attacking with this flag activated.

[FRIGHTENING] specifies whether the unit gets the frightening bonus against other units.

[HALFRANGEDDAMAGE] specifies whether the unit takes half the damage from ranged attacks.

[MELEE] specifies whether the unit is capable of melee combat.

[CONE_WIDTH] specifies, for units that can shoot, their horizontal shooting range. For example, a cone width of 3 means they can shoot straight ahead and to both one tile east and west.

[SHOOTS_OVER_UNITS] specifies if a unit is able to shoot despite a unit being in the way

[SHOTS_PER_TURN] and [CHARGES_PER_TURN] specify how many times a unit is able to perform a ranged attack and a melee attack per turn, respectively.


FULL LIST OF ESSENTIAL FLAGS (these must be included in every unit description):

[NATIONS]:
[STRING]:
[SPRITE]:
[MAIN_TYPE]:
[FAMILY_TYPE]:
[ERA]:
[SQUAREFORMATION]:
[SQUAREFORMATIONMODIFIER]:
[LIMBER]:
[LANCER]:
[WATERCROSSER]:
[HP]:
[MOV]:
[COST]:
[LIMIT]:
[SKIRMISH]:
[FRIGHTENING]:
[HALFRANGEDDDAMAGE]:
[MELEE]:
[CONE_WIDTH]:
[SHOOTS_OVER_UNITS]:
[SHOTS_PER_TURN]:
[CHARGES_PER_TURN]:

The remaining ([FLANK], [RANGED], [BRIDGE_ATTACK], [HEALING], [MELEE_BONUS]) can optionally be excluded if they are not needed. [CONE_WIDTH] and [SHOOTS_OVER_UNITS] can be excluded if the unit has no ranged capability; otherwise, they will default to 1 and 0, respectively. Same with [SHOTS_PER_TURN] and [CHARGES_PER_TURN], which default to 1 and 1.

-------------------------------------------------------------

FLANK ENTRY PROPERTIES:

Define for main types only.

[FLANK]
	{
		DEFINE:INF
		{
		DEFINE:FRONT:0.5
		DEFINE:SIDE: 1.5
		DEFINE:REAR: 0.5
		}

		DEFINE:CAV
		{
		DEFINE:FRONT:0.5
		DEFINE:SIDE: 0.5
		DEFINE:REAR: 0.5
		}


--------------------------------
RANGED DEFINITION PROPERTIES:

Place the range with the furthest max distance first, in descending order

[RANGED]
	{
	DEFINE:6,6,0.5,1,1,6
	DEFINE:3,5,1,0,1,6
	DEFINE:2,2,2,0,1,6
	}


The first and second number are the ranges
The third number is the modifier
The fourth number specifies whether the damage is fixed (1) or multiplied by your roll (0)
The fifth and sixth numbers are the thresholds that your original die roll must be in between to hit

[BRIDGE_ATTACK] works exactly like this as well.
---------------------------------
HEALING DEFINITION PROPERTIES:


[HEALING]
	{
	DEFINE:1,6,2
	}

First and second numbers are ranges
3rd number is the healing value

Again, descending order

------------------------------------
BONUS PROPERTIES

[MELEE_BONUS]
	{
		DEFINE:MAIN:INF:2,0,1,1
		DEFINE:FAMILY:HINF:3,1,1,0
		DEFINE:UNITID:infant_tree:3,1,0,0
	}

DEFINE:MAIN for main types
DEFINE:FAMILY for family types

(see above)

First number is modifier value, second number specifies whether it is additional or multiplicational
3rd specifies whether this bonus applies when attacking, and 4th when defending


-----------------------------------------------------------------------------------------------------

----Valid units----

DEFINE:INF 			-Infantry
DEFINE:CAV 			-Cavalry
DEFINE:ART 			-Artillery
DEFINE:MOR 			-Mortar
DEFINE:GEN 			-General (behaves as Cavalry)
DEFINE:ARTGUARD 	-Artillery Guard (behaves as Infantry)
DEFINE:SAPPER 		-Sapper (behaves as Infantry)

----Valid Family Types---

DEFINE:LINF 	-Light Infantry
DEFINE:INF 		-Infantry
DEFINE:HINF 	-Heavy Infantry
DEFINE:CAV 		-Cavalry
DEFINE:ART 		-Artillery
DEFINE:IRR 		-Irregulars

----Valid Eras---

DEFINE:ALL
DEFINE:MID
DEFINE:EARLY
DEFINE:LATE