LittlerootTown_TestMapConnection_2_MapScripts::
	.byte 0


TestMapConnection_2_DigSiteTest::
# 5 "data/maps/LittlerootTown_TestMapConnection_2/scripts.pory"
	lockall
# 6 "data/maps/LittlerootTown_TestMapConnection_2/scripts.pory"
	msgbox TestMapConnection_2_DigSiteTest_Text_0
# 7 "data/maps/LittlerootTown_TestMapConnection_2/scripts.pory"
	waitmessage
# 8 "data/maps/LittlerootTown_TestMapConnection_2/scripts.pory"
	fadescreen FADE_TO_BLACK
# 9 "data/maps/LittlerootTown_TestMapConnection_2/scripts.pory"
	startmininghere 0
# 10 "data/maps/LittlerootTown_TestMapConnection_2/scripts.pory"
	releaseall
	return


TestMapConnection_2_DigSiteTest_Text_0:
# 6 "data/maps/LittlerootTown_TestMapConnection_2/scripts.pory"
	.string "Lets start digging!$"
