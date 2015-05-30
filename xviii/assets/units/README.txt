Flank, Ranged, and Healing entries are optional. Not adding ranged or healing entries will not give the unit those capabilities.

Valid nations:

Austria
Bavaria
Commonwealth
Crimea
France
GBR
Imereti
Moldavia
Ottoman Empire
Portugal
Prussia
Russia
Saxony
Spain
Sweden
Venice
Wallachia
Persia

Valid sprites: 

INF
CAV
CUIR
LCAV
DRAG
ART
MOR
GEN
GRE
SAP
HINF
ARTGUARD
PIKE
LAN
ARMLAN
IRR
HARCH
LART
LDRAG

Valid units:

INF
CAV
ART
MOR
GEN
ARTGUARD

LINF
INF
HINF
CAV
ART

FLANK ENTRY PROPERTIES:

Define for main types only.

FLANK
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

RANGED
	{
	DEFINE:6,6,0.5,1,1,6
	DEFINE:3,5,1,0,1,6
	DEFINE:2,2,2,0,1,6
	}


The first and second number are the ranges
The third number is the modifier
The fourth number specifies whether the damage is fixed (1) or multiplied by your roll (0)
The fifth and sixth numbers are the thresholds that your original die roll must be in between to hit
---------------------------------
HEALING DEFINITION PROPERTIES:


HEALING
	{
	DEFINE:1,6,2
	}

First and second numbers are ranges
3rd number is the healing value

Again, descending order

------------------------------------
BONUS PROPERTIES

MELEE_BONUS
	{
		DEFINE:MAIN:INF:2,0,1,1
		DEFINE:FAMILY:HINF:3,1,1,0
	}

DEFINE:MAIN for main types
DEFINE:FAMILY for family types

(see above)

First number is modifier value, second number specifies whether it is additional or multiplicational
3rd specifies whether this bonus applies when attacking, and 4th when defending


---------------
