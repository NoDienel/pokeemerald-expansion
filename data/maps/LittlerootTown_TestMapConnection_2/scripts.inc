LittlerootTown_TestMapConnection_2_MapScripts::
	.byte 0


TestMapConnection_2_GiveDynamite::
# 5 "data/maps/LittlerootTown_TestMapConnection_2/scripts.pory"
	lockall
# 6 "data/maps/LittlerootTown_TestMapConnection_2/scripts.pory"
	removeobject 1
# 7 "data/maps/LittlerootTown_TestMapConnection_2/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 8 "data/maps/LittlerootTown_TestMapConnection_2/scripts.pory"
	giveitem ITEM_MINING_DYNAMITE
# 9 "data/maps/LittlerootTown_TestMapConnection_2/scripts.pory"
	waitmessage
# 10 "data/maps/LittlerootTown_TestMapConnection_2/scripts.pory"
	releaseall
	return


TestMapConnection_2_DigSiteTest::
# 15 "data/maps/LittlerootTown_TestMapConnection_2/scripts.pory"
	lockall
# 16 "data/maps/LittlerootTown_TestMapConnection_2/scripts.pory"
	msgbox TestMapConnection_2_DigSiteTest_Text_0
# 17 "data/maps/LittlerootTown_TestMapConnection_2/scripts.pory"
	waitmessage
# 18 "data/maps/LittlerootTown_TestMapConnection_2/scripts.pory"
	fadescreen FADE_TO_BLACK
# 19 "data/maps/LittlerootTown_TestMapConnection_2/scripts.pory"
	startmininghere LOCATIONID_TEST_1
# 20 "data/maps/LittlerootTown_TestMapConnection_2/scripts.pory"
	releaseall
	return


TestMapConnection_2_DigSiteTest_Text_0:
# 16 "data/maps/LittlerootTown_TestMapConnection_2/scripts.pory"
	.string "Lets start digging!$"
