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
	goto_if_eq TestMapConnection_EventScript_Trigger_NoPokemonWalkSouth_2
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


TestMapConnection_EventScript_PinchHitter_Pokeball::
# 54 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	lockall
# 55 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 56 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	msgbox TestMapConnection_EventScript_PinchHitter_Pokeball_Text_0
# 57 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	showmonpic SPECIES_LEDIAN, 10, 3
# 58 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	givemon SPECIES_LEDIAN, 50, ITEM_NONE, ITEM_POKE_BALL, NATURE_ADAMANT, 2
# 59 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	givemon SPECIES_WEEDLE, 5
# 60 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	setflag FLAG_SYS_POKEMON_GET
# 61 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	setflag FLAG_BADGE01_GET
# 62 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	setflag FLAG_BADGE02_GET
# 63 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	setflag FLAG_BADGE03_GET
# 64 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	setflag FLAG_BADGE04_GET
# 65 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	setflag FLAG_BADGE05_GET
# 66 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	setflag FLAG_BADGE06_GET
# 67 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	setflag FLAG_BADGE07_GET
# 68 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	setflag FLAG_BADGE08_GET
# 69 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	removeobject 4
# 70 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	waitmessage
# 71 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	hidemonpic
# 72 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	releaseall
	end


TestMapConnection_EventScript_Weedle_Pokeball::
# 79 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	lockall
# 80 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	msgbox TestMapConnection_EventScript_Weedle_Pokeball_Text_0
# 81 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	waitmessage
# 82 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	showmonpic SPECIES_WEEDLE, 10, 3
# 83 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	givemon SPECIES_WEEDLE, 5, ITEM_NONE, ITEM_POKE_BALL, NATURE_DOCILE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, MOVE_POISON_STING
# 84 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	setflag FLAG_SYS_POKEMON_GET
# 85 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	hidemonpic
# 86 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	releaseall
	end


TestMapConnection_EventScript_PinchHitter_Trainer::
# 93 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	trainerbattle_single TRAINER_WYATT, TestMapConnection_Text_PinchHitter_TrainerIntro, TestMapConnection_Text_PinchHitter_TrainerLose
# 94 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	msgbox TestMapConnection_EventScript_PinchHitter_Trainer_Text_0
# 95 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	waitmessage
	end


TestMapConnection_EventScript_Chimecho_Pokeball::
# 131 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	lockall
# 132 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	msgbox TestMapConnection_EventScript_Chimecho_Pokeball_Text_0
# 133 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	waitmessage
# 134 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	showmonpic SPECIES_CHIMECHO, 10, 3
# 135 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	givemon SPECIES_CHIMECHO, 50, ITEM_NONE, ITEM_POKE_BALL, NATURE_CALM, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, MOVE_SING
# 136 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	setflag FLAG_SYS_POKEMON_GET
# 137 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	hidemonpic
# 138 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	releaseall
	end


TestMapConnection_EventScript_Resonate_Trainer::
# 145 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	trainerbattle_single TRAINER_WYATT, TestMapConnection_Text_Resonate_TrainerIntro, TestMapConnection_Text_Resonate_TrainerLose
# 146 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	msgbox TestMapConnection_EventScript_Resonate_Trainer_Text_0
# 147 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
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

TestMapConnection_EventScript_PinchHitter_Pokeball_Text_0:
# 56 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	.string "You found a special Poké Ball!\nIt contains a Ledian to test Pinch Hitter.$"

TestMapConnection_EventScript_Weedle_Pokeball_Text_0:
# 80 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	.string "A tiny partner appears!\nThis gives a level 5 Weedle for partner-effect tests.$"

TestMapConnection_EventScript_PinchHitter_Trainer_Text_0:
# 94 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	.string "Battle complete. Check if Ledian transformed when it became the last Pokémon.$"

TestMapConnection_EventScript_Chimecho_Pokeball_Text_0:
# 132 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	.string "You found a special Poké Ball!\nIt contains a Chimecho to test Resonate.$"

TestMapConnection_EventScript_Resonate_Trainer_Text_0:
# 146 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	.string "Battle complete. Check Resonate interactions: status bounce and damaging reflect.$"

TestMapConnection_Text_PinchHitter_TrainerIntro::
# 99 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	.string "This battle is for testing Pinch Hitter.\nMake a move to let Ledian's ability activate.$"

TestMapConnection_Text_PinchHitter_TrainerLose::
# 104 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	.string "Nice work testing Pinch Hitter!\nObserve whether Ledian transformed.$"

TestMapConnection_Text_Trainer_Test1_Intro::
# 109 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	.string "Testing again? Okay, lets go!$"

TestMapConnection_Text_Trainer_Test1_Lose::
# 114 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	.string "Woohoo! Well done!$"

TestMapConnection_Text_Resonate_TrainerIntro::
# 151 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	.string "This battle tests Resonate. Watch how sound moves are handled.$"

TestMapConnection_Text_Resonate_TrainerLose::
# 156 "data/maps/LittlerootTown_TestMapConnection/scripts.pory"
	.string "Resonate test complete. Verify messages and HP changes.$"
