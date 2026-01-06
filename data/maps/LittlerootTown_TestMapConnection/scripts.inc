LittlerootTown_TestMapConnection_MapScripts::
	.byte 0


TestMapConnection_EventScript_OldMan::
# 5 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	lockall
# 6 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	msgbox TestMapConnection_EventScript_OldMan_Text_0
# 8 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	waitmessage
# 9 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	releaseall
	end


TestMapConnection_EventScript_Pokeball1::
# 15 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	lockall
# 16 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 17 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	showmonpic SPECIES_SCYTHER, 10, 3
# 18 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	msgbox TestMapConnection_EventScript_Pokeball1_Text_0
# 19 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	givemon SPECIES_SCYTHER, 15, ITEM_NONE, ITEM_POKE_BALL, NATURE_ADAMANT, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, MOVE_EARTHQUAKE
# 20 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	givemon SPECIES_MILOTIC, 15, ITEM_FLAME_ORB, ITEM_POKE_BALL, NATURE_MODEST, 0
# 21 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	setflag FLAG_BADGE01_GET
# 22 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	setflag FLAG_SYS_POKEMON_GET
# 23 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	removeobject 3
# 24 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	waitmessage
# 25 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	hidemonpic
# 26 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	setflag FLAG_UNUSED_0x020
# 27 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	releaseall
	end


TestMapConnection_EventScript_Trigger_NoPokemonWalkSouth::
	getpartysize
# 0 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_le TestMapConnection_EventScript_Trigger_NoPokemonWalkSouth_2
TestMapConnection_EventScript_Trigger_NoPokemonWalkSouth_1:
	end

TestMapConnection_EventScript_Trigger_NoPokemonWalkSouth_2:
# 35 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	lockall
# 36 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	applymovement LOCALID_PLAYER, TestMapConnection_EventScript_Trigger_NoPokemonWalkSouth_Movement_0
# 37 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	releaseall
	goto TestMapConnection_EventScript_Trigger_NoPokemonWalkSouth_1


TestMapConnection_EventScript_Trainer_Test1::
# 44 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	trainerbattle_single TRAINER_WYATT, TestMapConnection_Text_Trainer_Test1_Intro, TestMapConnection_Text_Trainer_Test1_Lose
# 45 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	msgBox TestMapConnection_EventScript_Trainer_Test1_Text_0
# 47 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	waitmessage
	end


# 36 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
TestMapConnection_EventScript_Trigger_NoPokemonWalkSouth_Movement_0:
# 36 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	walk_down
	step_end

TestMapConnection_EventScript_OldMan_Text_0:
# 6 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	.string "Ah, you're testing out some\n"
	.string "developer features? Good stuff.$"

TestMapConnection_EventScript_Pokeball1_Text_0:
# 18 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	.string "You recieved Scyther and ...?!$"

TestMapConnection_EventScript_Trainer_Test1_Text_0:
# 45 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	.string "Did you find out what you needed to?\n"
	.string "I hope so!$"

TestMapConnection_Text_Trainer_Test1_Intro::
# 51 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	.string "Testing again? Okay, lets go!$"

TestMapConnection_Text_Trainer_Test1_Lose::
# 56 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	.string "Woohoo! Well done!$"
