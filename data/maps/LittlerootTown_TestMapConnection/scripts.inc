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
	return


TestMapConnection_EventScript_Pokeball1::
# 14 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	lockall
# 15 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	showmonpic SPECIES_SCYTHER, 10, 3
# 16 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	msgbox TestMapConnection_EventScript_Pokeball1_Text_0
# 17 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	givemon SPECIES_SCYTHER, 15, ITEM_NONE, ITEM_POKE_BALL, NATURE_ADAMANT, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, MOVE_EARTHQUAKE
# 18 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	givemon SPECIES_MILOTIC, 15, ITEM_FLAME_ORB, ITEM_POKE_BALL, NATURE_MODEST, 0
# 19 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 20 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	setflag FLAG_BADGE01_GET
# 21 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	setflag FLAG_SYS_POKEMON_GET
# 22 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	removeobject 3
# 23 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	hidemonpic
# 24 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	setflag FLAG_UNUSED_0x020
# 25 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	releaseall
	return


TestMapConnection_EventScript_Trigger_NoPokemonWalkSouth::
	getpartysize
# 0 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_le TestMapConnection_EventScript_Trigger_NoPokemonWalkSouth_1
	return

TestMapConnection_EventScript_Trigger_NoPokemonWalkSouth_1:
# 32 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	lockall
# 33 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	applymovement LOCALID_PLAYER, TestMapConnection_EventScript_Trigger_NoPokemonWalkSouth_Movement_0
# 34 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	releaseall
	return


TestMapConnection_EventScript_Trainer_Test1::
# 40 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	trainerbattle_single TRAINER_WYATT, TestMapConnection_Text_Trainer_Test1_Intro, TestMapConnection_Text_Trainer_Test1_Lose
# 41 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	msgBox TestMapConnection_EventScript_Trainer_Test1_Text_0
# 43 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	waitmessage
	end


# 33 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
TestMapConnection_EventScript_Trigger_NoPokemonWalkSouth_Movement_0:
# 33 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	walk_down
	step_end

TestMapConnection_EventScript_OldMan_Text_0:
# 6 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	.string "Ah, you're testing out some\n"
	.string "developer features? Good stuff.$"

TestMapConnection_EventScript_Pokeball1_Text_0:
# 16 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	.string "You recieved Scyther and ...?!$"

TestMapConnection_EventScript_Trainer_Test1_Text_0:
# 41 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	.string "Did you find out what you needed to?\n"
	.string "I hope so!$"

TestMapConnection_Text_Trainer_Test1_Intro::
# 47 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	.string "Testing again? Okay, lets go!$"

TestMapConnection_Text_Trainer_Test1_Lose::
# 52 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	.string "Woohoo! Well done!$"
