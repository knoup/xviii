Uses <a href="http://sfml-dev.org/">SFML 2.1</a>.  Any units not mentioned in the rules are not fully implemented/ready yet. This is my first real project, hence the generally amateurish code. Inspired by the ideas of a friend.


Mechanics Guide

--------------------General--------------------

*There are four types of actions

	
	1) MOVEMENT
			
	2) PARTIAL ROTATION
			*Left  		(90 deg.; sideways)
			*Right  	(90 deg.; sideways)
			
	3) FULL ROTATION
		*180 degrees
	
	4) ATTACK
		*Includes Firing/Charging

		
*INF can either MOVE, PARTIALLY ROTATE, or FULLY ROTATE in addition to attacking.
	
*CAV can either FULLY ROTATE, or PARTIALLY ROTATE in addition to moving/attacking	
	
	
*d stands for [6-sided] dice; a roll of 4 with modifiers of 0.5d and 1d will 
yield 2 and 4 DMG respectively; the roll result is multiplied by the modifier
	

*When a player's GENERAL dies, inflict 2 DMG to all friendly units. General may 
heal a unit for 2 health, once per turn.


*The following units are members of the "CAV family" and will, unless when stated otherwise, behave the same as CAV:

	GEN
	

--------------------Unit Types & Stats--------------------

	INF 
		*MOV: 6
		*HP: 18
		*MAX RANGED DIST: 6
		
	ARTY
		*MOV: 2
		*HP: 3
		*MAX RANGED DIST: 20
		
	MORTAR
		*MOV: 0
		*HP: 2
		*MAX RANGED DIST: 15
		
	CAV
		*MOV: 12
		*HP: 12
		*MAX RANGED DIST: -
		
	GENERAL
		*MOV: 6
		*HP: 5
		*MAX RANGED DIST: 2

Shooting Dist. Modifiers:
	
	INF
		*6: 	0.5d
		*5-3: 	1d
		*2-1: 	2d

	ARTY [ONLY IF ROLL IS 4-6]
		*20-10:	2 DMG 
		*9-1:	4 DMG 
		
	MORTAR [ONLY IF ROLL IS 4-6]	
		*15-1:	3 DMG 

	GENERAL
		*2-1:	0.5d
		
Charge Dir. Modifiers (CAV):
		

	vs. INF
		*Front:	0.5d
		*Flank:	1d
		*Rear:	2d
		
	vs. CAV
		*Front:	1d
		*Flank:	2d
		*Rear:	2d
		
		
Charge Dir. Modifiers (INF):

	vs. INF
		*Front: 0.5d
		*Flank: 1d
		*Rear: 1.5d
		
	vs. CAV
		*Front: 1d
		*Flank: 1.5d
		*Rear: 2d

		
--------------------Ranged Combat Rules--------------------


	-The player rolls a dice and the result is multiplied by the unit's dist./dir. modifier. 
	 
	 EXAMPLE:
	 
	 Player 1 has INF shooting at Player 2's CAV from 2 tiles away. 
	 Since INF has a modifier of 2d while shooting from this distance, his roll is multiplied by 2.
	 Player 1 rolls 4 and inflicts 8 DMG on Player  2's CAV.
	 
	 
	 ART and MOR are able to shoot within a "cone width" of 3, meaning they can shoot not only
	 straight forward, but also one tile to the left and one tile to the right

	 
--------------------Melee Combat Rules--------------------


	INF vs INF
	
		*Roll dice

		*If difference between player 1 and 2 is less than 3, player with highest roll inflicts 1 DMG

		*Otherwise, inflict 2 DMG
		
		*If both get the same roll, both take 1 DMG
		
	CAV vs CAV:
	
		*Roll Dice

		*Same rules as INF vs INF.

	INF vs CAV
	
		*Roll dice

		*Player with higher roll wins

		*If CAV wins, inflict 4 DMG

		*If INF wins, inflict 2 DMG (and receive 1)
		
		*If equal rolls, CAV takes 1 DMG and INF takes 0.5
		
	INF/CAV vs ART
	
		*Only INF/CAV rolls

		*If INF/CAV rolls 3 or more, inflict 2 DMG. If 2 or less, both INF/CAV and ART take 3 DMG.

		
	INF/CAV vs MOR
	
		*Only INF/CAV rolls

		*If INF/CAV rolls 3 or more, inflict 2 DMG. If 2 or less, INF/CAV take 0.5 DMG, MOR takes 2 DMG.		
		

	

--------------------Deployment Costs--------------------


	You start with 30 deployment points.

	INF: 1
	
	CAV: 3 		[Max of 5]
	
	ARTY: 3 	[Max of 5]
	
	MORTAR: 2	[Max of 5]
	
	GENERAL: 0	[Max of 1]
	
	
--------------------In-Game--------------------

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
selected (see below). The currently selected unit is outlined in yellow.

--------------------Line of Sight (LoS)--------------------

In addition to movement points and max attacking range, units are limited by their
line of sight. A unit cannot cross to the other side of a tile if it is occupied by
an enemy unit; likewise, a unit cannot attack an enemy on a tile if there is another
enemy unit in the way. Friendly units can move past each other; however, with the exception
of ART and MOR, they cannot fire from behind other friendlies.


--------------------KEYBOARD SHORTCUTS & MOUSE COMMANDS--------------------

---Menu Phase---

	N - Start new game  
	L - Load save game (if any is available)  
	
Note that at the moment only one save is possible; saving will overwrite your last save, so be careful. A premade save file is provided for those who just want to dive in without bothering to set up.

---Setup & Playing Phases---

	R - reset zoom level  
	WSAD - move view  
	dash - zoom out  
	equal - zoom in  
	Mouse wheel - zoom out/in  

---Setup Phase--

	T - spawn infantry  
	Y - spawn cavalry  
	U - spawn general  
	F - spawn artillery  
	G - spawn mortar  
	
	LMB - place unit on tile  
	RMB - deselect currently selected sprite, or delete unit at tile  

---Playing Phase---

	LMB - select a unit and issue movement/attack orders  
	RMB - deselect currently selected unit/dismiss current message  

Up/down/left/right - rotate a unit North, South, East, and West respectively

	Z - toggle save on exit (will overwrite other save if present!)
