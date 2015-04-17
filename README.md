Uses <a href="http://sfml-dev.org/">SFML 2.1</a> and <a href="http://www.boost.org/">Boost's</a> filesystem module.  Any units not mentioned in the rules are not fully implemented/ready yet. This is my first real project, hence the generally amateurish code. Inspired by the ideas of a friend.

General
-------
	There are four types of actions:

	
	1) MOVEMENT
			
	2) PARTIAL ROTATION
			*Left/Right (90 degrees)
			
	3) FULL ROTATION
			*180 degrees
	
	4) ATTACK
			*Includes Firing/Charging

		
*INF can either MOVE, PARTIALLY ROTATE, or FULLY ROTATE in addition to attacking.
	
*CAV can either FULLY ROTATE, or PARTIALLY ROTATE in addition to moving/attacking

*However, unless otherwise stated, units may not ROTATE or MOVE at all AFTER attacking.
	
	
*d stands for [6-sided] die; the roll result is multiplied by the modifier, such that
 a roll of 4 with modifiers of 0.5d and 1d will yield 2 and 4 DMG respectively

 
*Incremental modifiers always come after multiplicational ones; a Cuirassier 4 rolling
 against a Dragoon will get a resultant roll of 9 [(2x4) + 1], not 10 [2x(4+1)].


*When a player's GENERAL dies, inflict 2 DMG to all friendly units. General may 
heal a friendly unit for 2 HP once per turn.


*The following units are members of the "CAV family" and will, unless stated otherwise, behave the same as CAV:

	Cuirassier (CUIR)
	Dragoon (DRAG)
	Light Cavalry (LCAV)
	General (GEN)
	

Unit Types & Stats
------------------

	Infantry (INF)
		*HP: 18
		*MOV: 6
		*MAX RANGED DIST: 6
		
	Artillery (ART)
		*HP: 3
		*MOV: 2
		*MAX RANGED DIST: 20
		
	Mortar (MOR)
		*HP: 2
		*MOV: 0
		*MAX RANGED DIST: 15
		
	Cavalry (CAV)
		*HP: 12
		*MOV: 12
		*MAX RANGED DIST: -

	Cuirassier (CUIR)
		*HP:  15
		*MOV: 9
		*MAX RANGED DIST: -
		*CUIR gets +1 to rolls against the CAV family

	Dragoon (DRAG)
		*HP: 10
		*MOV: 12
		*MAX RANGED DIST: 5

	Light Cavalry (LCAV)
		*HP: 9
		*MOV: 15
		*MAX RANGED DIST: -
		
	General (GEN)
		*HP: 5
		*MOV: 6
		*MAX RANGED DIST: 2

---Shooting Dist. Modifiers---
	
	INF
		*6: 	0.5d
		*5-3: 	1d
		*2: 	2d

	ART [ONLY IF ROLL IS 4-6]
		*20-10:	2 DMG 
		*9-2:	4 DMG 
		
	MOR [ONLY IF ROLL IS 4-6]	
		*15-2:	3 DMG 

	DRAG
		*5-9: 0.5d
		*3-4: 1d
		*2: 1.5d

	GEN
		*2:	0.5d
		
---Charge Dir. Modifiers (CAV)---	

	vs. INF
		*Front:	0.5d
		*Flank:	1d
		*Rear:	2d
		
	vs. CAV
		*Front:	1d
		*Flank:	2d
		*Rear:	2d
		
---Charge Dir. Modifiers (LCAV)---

	vs. INF
		*Front: 0.5d
		*Flank: 0.5d
		*Rear: 1d

---Charge Dir. Modifiers (DRAG)---

	vs INF
		*Front: 0.5d
		*Flank: 0.5d
		*Rear: 1d
	
		
---Charge Dir. Modifiers (INF)---

	vs. INF
		*Front: 0.5d
		*Flank: 1d
		*Rear: 1.5d
		
	vs. CAV
		*Front: 1d
		*Flank: 1.5d
		*Rear: 2d

		
Ranged Combat Rules
-------------------


The player rolls a die and the result is multiplied by the unit's dist./dir. modifier. 
	 
EXAMPLE:
	 
Player 1 has INF shooting at Player 2's CAV from 2 tiles away. 
Since INF has a modifier of 2d while shooting from this distance, his roll is multiplied by 2.
Player 1 rolls 4 and inflicts 8 DMG on Player  2's CAV.
	 
	 
ART and MOR are able to fire with a "cone width" of 3, meaning they can shoot not only straight forward, but also one tile to the left and one tile to the right.

	 
Melee Combat Rules
-------------------


	INF vs INF
	
		*Roll dice

		*If difference between player 1 and 2 is less than 3, player with highest roll inflicts 1 DMG

		*If both get the same roll, both take 1 DMG

		*Otherwise, inflict 2 DMG
		
		
	CAV vs CAV:
	
		*Roll dice

		*Same rules as INF vs INF.

	INF vs CAV
	
		*Roll dice

		*Player with higher roll wins

		*If CAV wins, inflict 4 DMG

		*If equal rolls, CAV takes 1 DMG and INF takes 0.5 DMG

		*If INF wins, inflict 2 DMG (and receive 1)
		
	INF/CAV vs ART
	
		*Only INF/CAV rolls

		*If INF/CAV rolls 3 or more, inflict 2 DMG. If 2 or less, both INF/CAV and ART take 3 DMG.

		
	INF/CAV vs MOR
	
		*Only INF/CAV rolls

		*If INF/CAV rolls 3 or more, inflict 2 DMG. If 2 or less, INF/CAV take 0.5 DMG, MOR takes 2 DMG.		
		

	

Deployment Costs
----------------


Each player begins with 30 deployment points, and each unit spawned costs a certain amount.

	INF: 1
	
	CAV: 3 		[Can have max of 5]; applies to entire CAV family tentatively
	
	ARTY: 3 	[Can have max of 5]
	
	MORTAR: 2	[Can have max of 5]
	
	GENERAL: 0	[Can have max of 1]

	
	
In-Game
-------

During the setup phase, each player deploys their units on the game board. 
Players are limited to the far reaches of the map during this phase. In 
order to deploy a unit, you may either click on its sprite or use the 
keyboard shortcuts.

The indicators under the counters represent the unit's current direction,
health, and movement points, respectively. A unit with W 5 4 under it would
therefore represent a state in which it is facing westward, has 5 HP remaining,
and 4 movement points.

Note that the parentheses following the name of a unit is its limit per player, 
not deployment cost.

During the playing phase, players successively command their units by clicking 
on the desired unit and giving it movement/attack/rotation orders while
selected (see below). The currently selected unit is outlined in yellow, while 
units that have already attacked this turn are outlined in red.

Line of Sight
--------------

In addition to movement points and max attacking range, units are limited by their
line of sight. A unit can neither move to a tile, nor attack an enemy, that has an
enemy unit in the way. Friendly units can move past each other; however, with the 
exception of ART and MOR, they cannot fire from behind other friendlies.


Keyboard shortcuts & mouse commands
------------------------------------

---Menu Phase---

	W/Up/S/Down keys & Return
	
Two premade save files are provided for those who just want to dive in without bothering to set up.

---Nation Selection Phase---
	
	Left/A/Right/D keys & Return

---Setup & Playing Phases---

	R - reset zoom level  
	WASD - pan view  
	dash (-) - zoom out  
	equal (=) - zoom in  
	Mouse wheel - zoom out/in  

---Setup Phase---  
	
	LMB - place unit on tile  
	RMB - deselect currently selected sprite, or delete unit at tile  

---Playing Phase---

	LMB - select a unit and issue movement/attack orders  
	RMB - deselect currently selected unit/dismiss current message  

	Up/down/left/right arrow keys - rotate a unit North, South, East, and West respectively

	Z - save
