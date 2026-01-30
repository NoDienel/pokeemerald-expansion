# 1 "data/maps/MossdeepCity/scripts.pory"

# 2 "data/maps/MossdeepCity/scripts.pory"
MossdeepCity_MapScripts::
# 3 "data/maps/MossdeepCity/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, MossdeepCity_OnTransition
# 4 "data/maps/MossdeepCity/scripts.pory"
	.byte 0
# 5 "data/maps/MossdeepCity/scripts.pory"

# 6 "data/maps/MossdeepCity/scripts.pory"
MossdeepCity_OnTransition:
# 7 "data/maps/MossdeepCity/scripts.pory"
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_1
# 8 "data/maps/MossdeepCity/scripts.pory"
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_2
# 9 "data/maps/MossdeepCity/scripts.pory"
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_3
# 10 "data/maps/MossdeepCity/scripts.pory"
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_4
# 11 "data/maps/MossdeepCity/scripts.pory"
	call_if_set FLAG_SYS_WEATHER_CTRL, Common_EventScript_SetAbnormalWeather
# 12 "data/maps/MossdeepCity/scripts.pory"
	end
# 13 "data/maps/MossdeepCity/scripts.pory"

# 14 "data/maps/MossdeepCity/scripts.pory"
MossdeepCity_EventScript_PokefanF::
# 15 "data/maps/MossdeepCity/scripts.pory"
	lock
# 16 "data/maps/MossdeepCity/scripts.pory"
	faceplayer
# 17 "data/maps/MossdeepCity/scripts.pory"
	goto_if_set FLAG_RECEIVED_HM_DIVE, MossdeepCity_EventScript_PokefanFMagmaGone
# 18 "data/maps/MossdeepCity/scripts.pory"
	msgbox MossdeepCity_Text_SpaceCenterReceivedLetter, MSGBOX_DEFAULT
# 19 "data/maps/MossdeepCity/scripts.pory"
	release
# 20 "data/maps/MossdeepCity/scripts.pory"
	end
# 21 "data/maps/MossdeepCity/scripts.pory"

# 22 "data/maps/MossdeepCity/scripts.pory"
MossdeepCity_EventScript_PokefanFMagmaGone::
# 23 "data/maps/MossdeepCity/scripts.pory"
	msgbox MossdeepCity_Text_SpaceCenterLaunchingRockets, MSGBOX_DEFAULT
# 24 "data/maps/MossdeepCity/scripts.pory"
	release
# 25 "data/maps/MossdeepCity/scripts.pory"
	end
# 26 "data/maps/MossdeepCity/scripts.pory"

# 27 "data/maps/MossdeepCity/scripts.pory"
MossdeepCity_EventScript_Sailor::
# 28 "data/maps/MossdeepCity/scripts.pory"
	lock
# 29 "data/maps/MossdeepCity/scripts.pory"
	faceplayer
# 30 "data/maps/MossdeepCity/scripts.pory"
	goto_if_set FLAG_RECEIVED_HM_DIVE, MossdeepCity_EventScript_SailorMagmaGone
# 31 "data/maps/MossdeepCity/scripts.pory"
	msgbox MossdeepCity_Text_MossdeepTargetedByMagma, MSGBOX_DEFAULT
# 32 "data/maps/MossdeepCity/scripts.pory"
	release
# 33 "data/maps/MossdeepCity/scripts.pory"
	end
# 34 "data/maps/MossdeepCity/scripts.pory"

# 35 "data/maps/MossdeepCity/scripts.pory"
MossdeepCity_EventScript_SailorMagmaGone::
# 36 "data/maps/MossdeepCity/scripts.pory"
	msgbox MossdeepCity_Text_FeelReliefOnLand, MSGBOX_DEFAULT
# 37 "data/maps/MossdeepCity/scripts.pory"
	release
# 38 "data/maps/MossdeepCity/scripts.pory"
	end
# 39 "data/maps/MossdeepCity/scripts.pory"

# 40 "data/maps/MossdeepCity/scripts.pory"
MossdeepCity_EventScript_NinjaBoy::
# 41 "data/maps/MossdeepCity/scripts.pory"
	msgbox MossdeepCity_Text_WailmerWatching, MSGBOX_NPC
# 42 "data/maps/MossdeepCity/scripts.pory"
	end
# 43 "data/maps/MossdeepCity/scripts.pory"

# 44 "data/maps/MossdeepCity/scripts.pory"
MossdeepCity_EventScript_ExpertM::
# 45 "data/maps/MossdeepCity/scripts.pory"
	msgbox MossdeepCity_Text_LifeNeedsSeaToLive, MSGBOX_NPC
# 46 "data/maps/MossdeepCity/scripts.pory"
	end
# 47 "data/maps/MossdeepCity/scripts.pory"

# 48 "data/maps/MossdeepCity/scripts.pory"
MossdeepCity_EventScript_Girl::
# 49 "data/maps/MossdeepCity/scripts.pory"
	msgbox MossdeepCity_Text_NiceIfWorldCoveredByFlowers, MSGBOX_NPC
# 50 "data/maps/MossdeepCity/scripts.pory"
	end
# 51 "data/maps/MossdeepCity/scripts.pory"

# 52 "data/maps/MossdeepCity/scripts.pory"
MossdeepCity_EventScript_Woman::
# 53 "data/maps/MossdeepCity/scripts.pory"
	msgbox MossdeepCity_Text_SpecialSpaceCenterRock, MSGBOX_NPC
# 54 "data/maps/MossdeepCity/scripts.pory"
	end
# 55 "data/maps/MossdeepCity/scripts.pory"

# 56 "data/maps/MossdeepCity/scripts.pory"
MossdeepCity_EventScript_WhiteRock::
# 57 "data/maps/MossdeepCity/scripts.pory"
	msgbox MossdeepCity_Text_ItsAWhiteRock, MSGBOX_SIGN
# 58 "data/maps/MossdeepCity/scripts.pory"
	end
# 59 "data/maps/MossdeepCity/scripts.pory"

# 60 "data/maps/MossdeepCity/scripts.pory"
MossdeepCity_EventScript_GymSign::
# 61 "data/maps/MossdeepCity/scripts.pory"
	msgbox MossdeepCity_Text_GymSign, MSGBOX_SIGN
# 62 "data/maps/MossdeepCity/scripts.pory"
	end
# 63 "data/maps/MossdeepCity/scripts.pory"

# 64 "data/maps/MossdeepCity/scripts.pory"
MossdeepCity_EventScript_CitySign::
# 65 "data/maps/MossdeepCity/scripts.pory"
	msgbox MossdeepCity_Text_CitySign, MSGBOX_SIGN
# 66 "data/maps/MossdeepCity/scripts.pory"
	end
# 67 "data/maps/MossdeepCity/scripts.pory"

# 68 "data/maps/MossdeepCity/scripts.pory"
MossdeepCity_EventScript_SpaceCenterSign::
# 69 "data/maps/MossdeepCity/scripts.pory"
	msgbox MossdeepCity_Text_SpaceCenterSign, MSGBOX_SIGN
# 70 "data/maps/MossdeepCity/scripts.pory"
	end
# 71 "data/maps/MossdeepCity/scripts.pory"

# 72 "data/maps/MossdeepCity/scripts.pory"
MossdeepCity_EventScript_VisitedMossdeep::
# 73 "data/maps/MossdeepCity/scripts.pory"
	setflag FLAG_VISITED_MOSSDEEP_CITY
# 74 "data/maps/MossdeepCity/scripts.pory"
	setvar VAR_TEMP_1, 1
# 75 "data/maps/MossdeepCity/scripts.pory"
	end
# 76 "data/maps/MossdeepCity/scripts.pory"

# 77 "data/maps/MossdeepCity/scripts.pory"
MossdeepCity_Movement_MaxieGestureToSpaceCenter:
# 78 "data/maps/MossdeepCity/scripts.pory"
	delay_16
# 79 "data/maps/MossdeepCity/scripts.pory"
	face_right
# 80 "data/maps/MossdeepCity/scripts.pory"
	delay_16
# 81 "data/maps/MossdeepCity/scripts.pory"
	delay_16
# 82 "data/maps/MossdeepCity/scripts.pory"
	delay_16
# 83 "data/maps/MossdeepCity/scripts.pory"
	delay_16
# 84 "data/maps/MossdeepCity/scripts.pory"
	face_left
# 85 "data/maps/MossdeepCity/scripts.pory"
	delay_16
# 86 "data/maps/MossdeepCity/scripts.pory"
	delay_16
# 87 "data/maps/MossdeepCity/scripts.pory"
	step_end
# 88 "data/maps/MossdeepCity/scripts.pory"

# 89 "data/maps/MossdeepCity/scripts.pory"
MossdeepCity_Movement_GruntFaceSpaceCenter:
# 90 "data/maps/MossdeepCity/scripts.pory"
	face_right
# 91 "data/maps/MossdeepCity/scripts.pory"
	delay_16
# 92 "data/maps/MossdeepCity/scripts.pory"
	delay_16
# 93 "data/maps/MossdeepCity/scripts.pory"
	delay_16
# 94 "data/maps/MossdeepCity/scripts.pory"
	step_end
# 95 "data/maps/MossdeepCity/scripts.pory"

# 96 "data/maps/MossdeepCity/scripts.pory"
MossdeepCity_Movement_MaxieEnterSpaceCenter:
# 97 "data/maps/MossdeepCity/scripts.pory"
	walk_down
# 98 "data/maps/MossdeepCity/scripts.pory"
	walk_right
# 99 "data/maps/MossdeepCity/scripts.pory"
	walk_right
# 100 "data/maps/MossdeepCity/scripts.pory"
	walk_down
# 101 "data/maps/MossdeepCity/scripts.pory"
	walk_down
# 102 "data/maps/MossdeepCity/scripts.pory"
	walk_down
# 103 "data/maps/MossdeepCity/scripts.pory"
	walk_right
# 104 "data/maps/MossdeepCity/scripts.pory"
	walk_right
# 105 "data/maps/MossdeepCity/scripts.pory"
	walk_right
# 106 "data/maps/MossdeepCity/scripts.pory"
	walk_right
# 107 "data/maps/MossdeepCity/scripts.pory"
	walk_right
# 108 "data/maps/MossdeepCity/scripts.pory"
	walk_right
# 109 "data/maps/MossdeepCity/scripts.pory"
	walk_right
# 110 "data/maps/MossdeepCity/scripts.pory"
	step_end
# 111 "data/maps/MossdeepCity/scripts.pory"

# 112 "data/maps/MossdeepCity/scripts.pory"
MossdeepCity_Movement_Grunt1EnterSpaceCenter:
# 113 "data/maps/MossdeepCity/scripts.pory"
	delay_16
# 114 "data/maps/MossdeepCity/scripts.pory"
	delay_8
# 115 "data/maps/MossdeepCity/scripts.pory"
	walk_down
# 116 "data/maps/MossdeepCity/scripts.pory"
	walk_down
# 117 "data/maps/MossdeepCity/scripts.pory"
	walk_down
# 118 "data/maps/MossdeepCity/scripts.pory"
	walk_right
# 119 "data/maps/MossdeepCity/scripts.pory"
	walk_right
# 120 "data/maps/MossdeepCity/scripts.pory"
	walk_right
# 121 "data/maps/MossdeepCity/scripts.pory"
	walk_down
# 122 "data/maps/MossdeepCity/scripts.pory"
	walk_down
# 123 "data/maps/MossdeepCity/scripts.pory"
	walk_down
# 124 "data/maps/MossdeepCity/scripts.pory"
	walk_right
# 125 "data/maps/MossdeepCity/scripts.pory"
	walk_right
# 126 "data/maps/MossdeepCity/scripts.pory"
	walk_right
# 127 "data/maps/MossdeepCity/scripts.pory"
	walk_right
# 128 "data/maps/MossdeepCity/scripts.pory"
	walk_right
# 129 "data/maps/MossdeepCity/scripts.pory"
	walk_right
# 130 "data/maps/MossdeepCity/scripts.pory"
	walk_right
# 131 "data/maps/MossdeepCity/scripts.pory"
	step_end
# 132 "data/maps/MossdeepCity/scripts.pory"

# 133 "data/maps/MossdeepCity/scripts.pory"
MossdeepCity_Movement_Grunt2EnterSpaceCenter:
# 134 "data/maps/MossdeepCity/scripts.pory"
	delay_16
# 135 "data/maps/MossdeepCity/scripts.pory"
	delay_8
# 136 "data/maps/MossdeepCity/scripts.pory"
	walk_down
# 137 "data/maps/MossdeepCity/scripts.pory"
	walk_down
# 138 "data/maps/MossdeepCity/scripts.pory"
	walk_right
# 139 "data/maps/MossdeepCity/scripts.pory"
	walk_right
# 140 "data/maps/MossdeepCity/scripts.pory"
	walk_right
# 141 "data/maps/MossdeepCity/scripts.pory"
	walk_down
# 142 "data/maps/MossdeepCity/scripts.pory"
	walk_down
# 143 "data/maps/MossdeepCity/scripts.pory"
	walk_down
# 144 "data/maps/MossdeepCity/scripts.pory"
	walk_right
# 145 "data/maps/MossdeepCity/scripts.pory"
	walk_right
# 146 "data/maps/MossdeepCity/scripts.pory"
	walk_right
# 147 "data/maps/MossdeepCity/scripts.pory"
	walk_right
# 148 "data/maps/MossdeepCity/scripts.pory"
	walk_right
# 149 "data/maps/MossdeepCity/scripts.pory"
	walk_right
# 150 "data/maps/MossdeepCity/scripts.pory"
	walk_right
# 151 "data/maps/MossdeepCity/scripts.pory"
	step_end
# 152 "data/maps/MossdeepCity/scripts.pory"

# 153 "data/maps/MossdeepCity/scripts.pory"
MossdeepCity_Movement_Grunt3EnterSpaceCenter:
# 154 "data/maps/MossdeepCity/scripts.pory"
	delay_16
# 155 "data/maps/MossdeepCity/scripts.pory"
	delay_8
# 156 "data/maps/MossdeepCity/scripts.pory"
	walk_down
# 157 "data/maps/MossdeepCity/scripts.pory"
	walk_right
# 158 "data/maps/MossdeepCity/scripts.pory"
	walk_right
# 159 "data/maps/MossdeepCity/scripts.pory"
	walk_right
# 160 "data/maps/MossdeepCity/scripts.pory"
	walk_down
# 161 "data/maps/MossdeepCity/scripts.pory"
	walk_down
# 162 "data/maps/MossdeepCity/scripts.pory"
	walk_down
# 163 "data/maps/MossdeepCity/scripts.pory"
	walk_right
# 164 "data/maps/MossdeepCity/scripts.pory"
	walk_right
# 165 "data/maps/MossdeepCity/scripts.pory"
	walk_right
# 166 "data/maps/MossdeepCity/scripts.pory"
	walk_right
# 167 "data/maps/MossdeepCity/scripts.pory"
	walk_right
# 168 "data/maps/MossdeepCity/scripts.pory"
	walk_right
# 169 "data/maps/MossdeepCity/scripts.pory"
	walk_right
# 170 "data/maps/MossdeepCity/scripts.pory"
	step_end
# 171 "data/maps/MossdeepCity/scripts.pory"

# 172 "data/maps/MossdeepCity/scripts.pory"
MossdeepCity_Movement_Grunt4EnterSpaceCenter:
# 173 "data/maps/MossdeepCity/scripts.pory"
	delay_16
# 174 "data/maps/MossdeepCity/scripts.pory"
	delay_8
# 175 "data/maps/MossdeepCity/scripts.pory"
	walk_right
# 176 "data/maps/MossdeepCity/scripts.pory"
	walk_right
# 177 "data/maps/MossdeepCity/scripts.pory"
	walk_right
# 178 "data/maps/MossdeepCity/scripts.pory"
	walk_down
# 179 "data/maps/MossdeepCity/scripts.pory"
	walk_down
# 180 "data/maps/MossdeepCity/scripts.pory"
	walk_down
# 181 "data/maps/MossdeepCity/scripts.pory"
	walk_right
# 182 "data/maps/MossdeepCity/scripts.pory"
	walk_right
# 183 "data/maps/MossdeepCity/scripts.pory"
	walk_right
# 184 "data/maps/MossdeepCity/scripts.pory"
	walk_right
# 185 "data/maps/MossdeepCity/scripts.pory"
	walk_right
# 186 "data/maps/MossdeepCity/scripts.pory"
	walk_right
# 187 "data/maps/MossdeepCity/scripts.pory"
	walk_right
# 188 "data/maps/MossdeepCity/scripts.pory"
	step_end
# 189 "data/maps/MossdeepCity/scripts.pory"

# 190 "data/maps/MossdeepCity/scripts.pory"
MossdeepCity_EventScript_Man::
# 191 "data/maps/MossdeepCity/scripts.pory"
	lock
# 192 "data/maps/MossdeepCity/scripts.pory"
	faceplayer
# 193 "data/maps/MossdeepCity/scripts.pory"
	msgbox MossdeepCity_Text_SurfExhilarating, MSGBOX_DEFAULT
# 194 "data/maps/MossdeepCity/scripts.pory"
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
# 195 "data/maps/MossdeepCity/scripts.pory"
	waitmovement 0
# 196 "data/maps/MossdeepCity/scripts.pory"
	release
# 197 "data/maps/MossdeepCity/scripts.pory"
	end
# 198 "data/maps/MossdeepCity/scripts.pory"

# 199 "data/maps/MossdeepCity/scripts.pory"
MossdeepCity_EventScript_KingsRockBoy::
# 200 "data/maps/MossdeepCity/scripts.pory"
	lock
# 201 "data/maps/MossdeepCity/scripts.pory"
	faceplayer
# 202 "data/maps/MossdeepCity/scripts.pory"
	goto_if_set FLAG_RECEIVED_KINGS_ROCK, MossdeepCity_EventScript_ReceivedKingsRock
# 203 "data/maps/MossdeepCity/scripts.pory"
	msgbox MossdeepCity_Text_WantKingsRockStevenGaveMe, MSGBOX_YESNO
# 204 "data/maps/MossdeepCity/scripts.pory"
	goto_if_eq VAR_RESULT, NO, MossdeepCity_EventScript_DeclineKingsRock
# 205 "data/maps/MossdeepCity/scripts.pory"
	msgbox MossdeepCity_Text_YouCanKeepIt, MSGBOX_DEFAULT
# 206 "data/maps/MossdeepCity/scripts.pory"
	giveitem ITEM_KINGS_ROCK
# 207 "data/maps/MossdeepCity/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
# 208 "data/maps/MossdeepCity/scripts.pory"
	setflag FLAG_RECEIVED_KINGS_ROCK
# 209 "data/maps/MossdeepCity/scripts.pory"
	release
# 210 "data/maps/MossdeepCity/scripts.pory"
	end
# 211 "data/maps/MossdeepCity/scripts.pory"

# 212 "data/maps/MossdeepCity/scripts.pory"
MossdeepCity_EventScript_ReceivedKingsRock::
# 213 "data/maps/MossdeepCity/scripts.pory"
	msgbox MossdeepCity_Text_StevensHouseOverThere, MSGBOX_DEFAULT
# 214 "data/maps/MossdeepCity/scripts.pory"
	release
# 215 "data/maps/MossdeepCity/scripts.pory"
	end
# 216 "data/maps/MossdeepCity/scripts.pory"

# 217 "data/maps/MossdeepCity/scripts.pory"
MossdeepCity_EventScript_DeclineKingsRock::
# 218 "data/maps/MossdeepCity/scripts.pory"
	msgbox MossdeepCity_Text_WhatToDoWithWeirdRock, MSGBOX_DEFAULT
# 219 "data/maps/MossdeepCity/scripts.pory"
	release
# 220 "data/maps/MossdeepCity/scripts.pory"
	end
# 221 "data/maps/MossdeepCity/scripts.pory"

# 222 "data/maps/MossdeepCity/scripts.pory"
MossdeepCity_EventScript_BlackBelt::
# 223 "data/maps/MossdeepCity/scripts.pory"
	msgbox MossdeepCity_Text_SootopolisNewGymLeader, MSGBOX_NPC
# 224 "data/maps/MossdeepCity/scripts.pory"
	end
# 225 "data/maps/MossdeepCity/scripts.pory"

# 226 "data/maps/MossdeepCity/scripts.pory"
MossdeepCity_Movement_PlayerWatchScottExit:
# 227 "data/maps/MossdeepCity/scripts.pory"
	delay_16
# 228 "data/maps/MossdeepCity/scripts.pory"
	delay_16
# 229 "data/maps/MossdeepCity/scripts.pory"
	walk_in_place_faster_left
# 230 "data/maps/MossdeepCity/scripts.pory"
	step_end
# 231 "data/maps/MossdeepCity/scripts.pory"

# 232 "data/maps/MossdeepCity/scripts.pory"
MossdeepCity_Movement_ScottExitNorth:
# 233 "data/maps/MossdeepCity/scripts.pory"
	walk_left
# 234 "data/maps/MossdeepCity/scripts.pory"
	walk_left
# 235 "data/maps/MossdeepCity/scripts.pory"
	walk_left
# 236 "data/maps/MossdeepCity/scripts.pory"
	walk_left
# 237 "data/maps/MossdeepCity/scripts.pory"
	walk_left
# 238 "data/maps/MossdeepCity/scripts.pory"
	walk_left
# 239 "data/maps/MossdeepCity/scripts.pory"
	walk_left
# 240 "data/maps/MossdeepCity/scripts.pory"
	walk_left
# 241 "data/maps/MossdeepCity/scripts.pory"
	walk_left
# 242 "data/maps/MossdeepCity/scripts.pory"
	step_end
# 243 "data/maps/MossdeepCity/scripts.pory"

# 244 "data/maps/MossdeepCity/scripts.pory"
MossdeepCity_Movement_ScottExitEast:
# 245 "data/maps/MossdeepCity/scripts.pory"
	walk_down
# 246 "data/maps/MossdeepCity/scripts.pory"
	walk_left
# 247 "data/maps/MossdeepCity/scripts.pory"
	walk_left
# 248 "data/maps/MossdeepCity/scripts.pory"
	walk_left
# 249 "data/maps/MossdeepCity/scripts.pory"
	walk_left
# 250 "data/maps/MossdeepCity/scripts.pory"
	walk_left
# 251 "data/maps/MossdeepCity/scripts.pory"
	walk_left
# 252 "data/maps/MossdeepCity/scripts.pory"
	walk_left
# 253 "data/maps/MossdeepCity/scripts.pory"
	walk_left
# 254 "data/maps/MossdeepCity/scripts.pory"
	walk_left
# 255 "data/maps/MossdeepCity/scripts.pory"
	step_end
# 256 "data/maps/MossdeepCity/scripts.pory"

# 257 "data/maps/MossdeepCity/scripts.pory"
MossdeepCity_Text_WantKingsRockStevenGaveMe:
# 258 "data/maps/MossdeepCity/scripts.pory"
	.string "I got this from STEVEN, but I don't\n"
# 259 "data/maps/MossdeepCity/scripts.pory"
	.string "know what it's good for.\p"
# 260 "data/maps/MossdeepCity/scripts.pory"
	.string "I think it's called KING'S ROCK.\n"
# 261 "data/maps/MossdeepCity/scripts.pory"
	.string "Do you want it?$"
# 262 "data/maps/MossdeepCity/scripts.pory"

# 263 "data/maps/MossdeepCity/scripts.pory"
MossdeepCity_Text_YouCanKeepIt:
# 264 "data/maps/MossdeepCity/scripts.pory"
	.string "Why would you want it?\n"
# 265 "data/maps/MossdeepCity/scripts.pory"
	.string "You're weird.\p"
# 266 "data/maps/MossdeepCity/scripts.pory"
	.string "You can keep it, but keep it a secret\n"
# 267 "data/maps/MossdeepCity/scripts.pory"
	.string "from STEVEN.$"
# 268 "data/maps/MossdeepCity/scripts.pory"

# 269 "data/maps/MossdeepCity/scripts.pory"
MossdeepCity_Text_StevensHouseOverThere:
# 270 "data/maps/MossdeepCity/scripts.pory"
	.string "STEVEN's house is right over there!$"
# 271 "data/maps/MossdeepCity/scripts.pory"

# 272 "data/maps/MossdeepCity/scripts.pory"
MossdeepCity_Text_WhatToDoWithWeirdRock:
# 273 "data/maps/MossdeepCity/scripts.pory"
	.string "Yeah, you think so, too! What are you\n"
# 274 "data/maps/MossdeepCity/scripts.pory"
	.string "supposed to do with some weird rock?$"
# 275 "data/maps/MossdeepCity/scripts.pory"

# 276 "data/maps/MossdeepCity/scripts.pory"
MossdeepCity_Text_WailmerWatching:
# 277 "data/maps/MossdeepCity/scripts.pory"
	.string "Around MOSSDEEP, you can see wild\n"
# 278 "data/maps/MossdeepCity/scripts.pory"
	.string "WAILMER.\p"
# 279 "data/maps/MossdeepCity/scripts.pory"
	.string "It's called, uh…\n"
# 280 "data/maps/MossdeepCity/scripts.pory"
	.string "What was it now…\p"
# 281 "data/maps/MossdeepCity/scripts.pory"
	.string "WAI, WAI, WAI…\p"
# 282 "data/maps/MossdeepCity/scripts.pory"
	.string "WAILMER watching!$"
# 283 "data/maps/MossdeepCity/scripts.pory"

# 284 "data/maps/MossdeepCity/scripts.pory"
MossdeepCity_Text_SpaceCenterReceivedLetter:
# 285 "data/maps/MossdeepCity/scripts.pory"
	.string "The island's SPACE CENTER has been\n"
# 286 "data/maps/MossdeepCity/scripts.pory"
	.string "launching huge rockets.\p"
# 287 "data/maps/MossdeepCity/scripts.pory"
	.string "There's been some kind of an uproar\n"
# 288 "data/maps/MossdeepCity/scripts.pory"
	.string "over a letter they received recently.$"
# 289 "data/maps/MossdeepCity/scripts.pory"

# 290 "data/maps/MossdeepCity/scripts.pory"
MossdeepCity_Text_SpaceCenterLaunchingRockets:
# 291 "data/maps/MossdeepCity/scripts.pory"
	.string "The island's SPACE CENTER has been\n"
# 292 "data/maps/MossdeepCity/scripts.pory"
	.string "launching huge rockets.$"
# 293 "data/maps/MossdeepCity/scripts.pory"

# 294 "data/maps/MossdeepCity/scripts.pory"
MossdeepCity_Text_MossdeepTargetedByMagma:
# 295 "data/maps/MossdeepCity/scripts.pory"
	.string "I heard from a SAILOR buddy that\n"
# 296 "data/maps/MossdeepCity/scripts.pory"
	.string "TEAM AQUA set up shop in LILYCOVE.\p"
# 297 "data/maps/MossdeepCity/scripts.pory"
	.string "I also heard that someone came along\n"
# 298 "data/maps/MossdeepCity/scripts.pory"
	.string "and wiped the floor with them!\p"
# 299 "data/maps/MossdeepCity/scripts.pory"
	.string "But MOSSDEEP here's been targeted\n"
# 300 "data/maps/MossdeepCity/scripts.pory"
	.string "by that TEAM MAGMA.\p"
# 301 "data/maps/MossdeepCity/scripts.pory"
	.string "If you want to know what they're up to,\n"
# 302 "data/maps/MossdeepCity/scripts.pory"
	.string "go visit the SPACE CENTER.$"
# 303 "data/maps/MossdeepCity/scripts.pory"

# 304 "data/maps/MossdeepCity/scripts.pory"
MossdeepCity_Text_FeelReliefOnLand:
# 305 "data/maps/MossdeepCity/scripts.pory"
	.string "I'm a SAILOR, so the sea's obviously\n"
# 306 "data/maps/MossdeepCity/scripts.pory"
	.string "more important to me.\p"
# 307 "data/maps/MossdeepCity/scripts.pory"
	.string "But you know? When I get back on land\n"
# 308 "data/maps/MossdeepCity/scripts.pory"
	.string "after a long voyage, I do feel relief!$"
# 309 "data/maps/MossdeepCity/scripts.pory"

# 310 "data/maps/MossdeepCity/scripts.pory"
MossdeepCity_Text_NiceIfWorldCoveredByFlowers:
# 311 "data/maps/MossdeepCity/scripts.pory"
	.string "Wouldn't it be nice?\p"
# 312 "data/maps/MossdeepCity/scripts.pory"
	.string "If the whole world was covered in\n"
# 313 "data/maps/MossdeepCity/scripts.pory"
	.string "plants and flowers like this island?$"
# 314 "data/maps/MossdeepCity/scripts.pory"

# 315 "data/maps/MossdeepCity/scripts.pory"
MossdeepCity_Text_LifeNeedsSeaToLive:
# 316 "data/maps/MossdeepCity/scripts.pory"
	.string "All life needs the sea to live, even\n"
# 317 "data/maps/MossdeepCity/scripts.pory"
	.string "though it makes its home on the land.\p"
# 318 "data/maps/MossdeepCity/scripts.pory"
	.string "Life, having run its course, becomes\n"
# 319 "data/maps/MossdeepCity/scripts.pory"
	.string "soil and returns to the land.\p"
# 320 "data/maps/MossdeepCity/scripts.pory"
	.string "And the sea is always connected to\n"
# 321 "data/maps/MossdeepCity/scripts.pory"
	.string "the land.\p"
# 322 "data/maps/MossdeepCity/scripts.pory"
	.string "Yes, like the very shoreline here.$"
# 323 "data/maps/MossdeepCity/scripts.pory"

# 324 "data/maps/MossdeepCity/scripts.pory"
MossdeepCity_Text_SurfExhilarating:
# 325 "data/maps/MossdeepCity/scripts.pory"
	.string "A voyage on a ship is fine.\p"
# 326 "data/maps/MossdeepCity/scripts.pory"
	.string "But crossing the sea with POKéMON\n"
# 327 "data/maps/MossdeepCity/scripts.pory"
	.string "using SURF…\p"
# 328 "data/maps/MossdeepCity/scripts.pory"
	.string "Now that's an exhilarating trip!\n"
# 329 "data/maps/MossdeepCity/scripts.pory"
	.string "Wouldn't you agree, youngster?$"
# 330 "data/maps/MossdeepCity/scripts.pory"

# 331 "data/maps/MossdeepCity/scripts.pory"
MossdeepCity_Text_SpecialSpaceCenterRock:
# 332 "data/maps/MossdeepCity/scripts.pory"
	.string "This rock has a special meaning to\n"
# 333 "data/maps/MossdeepCity/scripts.pory"
	.string "the people at the SPACE CENTER.\p"
# 334 "data/maps/MossdeepCity/scripts.pory"
	.string "They put it here as their wish for\n"
# 335 "data/maps/MossdeepCity/scripts.pory"
	.string "their rockets to fly safely.\p"
# 336 "data/maps/MossdeepCity/scripts.pory"
	.string "When you make a wish, what do you use?\n"
# 337 "data/maps/MossdeepCity/scripts.pory"
	.string "Do you wish upon a star?\p"
# 338 "data/maps/MossdeepCity/scripts.pory"
	.string "I use a wish tag to make it happen.\n"
# 339 "data/maps/MossdeepCity/scripts.pory"
	.string "That's what I do.$"
# 340 "data/maps/MossdeepCity/scripts.pory"

# 341 "data/maps/MossdeepCity/scripts.pory"
MossdeepCity_Text_ItsAWhiteRock:
# 342 "data/maps/MossdeepCity/scripts.pory"
	.string "It's a white rock.$"
# 343 "data/maps/MossdeepCity/scripts.pory"

# 344 "data/maps/MossdeepCity/scripts.pory"
MossdeepCity_Text_GymSign:
# 345 "data/maps/MossdeepCity/scripts.pory"
	.string "MOSSDEEP CITY POKéMON GYM\n"
# 346 "data/maps/MossdeepCity/scripts.pory"
	.string "LEADERS: LIZA & TATE\p"
# 347 "data/maps/MossdeepCity/scripts.pory"
	.string "“The mystic combination!”$"
# 348 "data/maps/MossdeepCity/scripts.pory"

# 349 "data/maps/MossdeepCity/scripts.pory"
MossdeepCity_Text_CitySign:
# 350 "data/maps/MossdeepCity/scripts.pory"
	.string "MOSSDEEP CITY\n"
# 351 "data/maps/MossdeepCity/scripts.pory"
	.string "“Our slogan: Cherish POKéMON!”$"
# 352 "data/maps/MossdeepCity/scripts.pory"

# 353 "data/maps/MossdeepCity/scripts.pory"
MossdeepCity_Text_SpaceCenterSign:
# 354 "data/maps/MossdeepCity/scripts.pory"
	.string "MOSSDEEP SPACE CENTER\n"
# 355 "data/maps/MossdeepCity/scripts.pory"
	.string "“The closest place to space.”$"
# 356 "data/maps/MossdeepCity/scripts.pory"

# 357 "data/maps/MossdeepCity/scripts.pory"
MossdeepCity_Text_ScottSomethingWrongWithTown:
# 358 "data/maps/MossdeepCity/scripts.pory"
	.string "SCOTT: {PLAYER}{KUN}, feeling good?\n"
# 359 "data/maps/MossdeepCity/scripts.pory"
	.string "I'm doing great!\p"
# 360 "data/maps/MossdeepCity/scripts.pory"
	.string "I'd heard MOSSDEEP's GYM LEADER is\n"
# 361 "data/maps/MossdeepCity/scripts.pory"
	.string "pretty strong, so I decided to come\l"
# 362 "data/maps/MossdeepCity/scripts.pory"
	.string "take a look-see for myself.\p"
# 363 "data/maps/MossdeepCity/scripts.pory"
	.string "But there's something wrong about\n"
# 364 "data/maps/MossdeepCity/scripts.pory"
	.string "this town.\p"
# 365 "data/maps/MossdeepCity/scripts.pory"
	.string "People are going on about a warning\n"
# 366 "data/maps/MossdeepCity/scripts.pory"
	.string "letter and the SPACE CENTER…\p"
# 367 "data/maps/MossdeepCity/scripts.pory"
	.string "I don't think it concerns me in any\n"
# 368 "data/maps/MossdeepCity/scripts.pory"
	.string "way, though.$"
# 369 "data/maps/MossdeepCity/scripts.pory"

# 370 "data/maps/MossdeepCity/scripts.pory"
MossdeepCity_Text_SootopolisNewGymLeader:
# 371 "data/maps/MossdeepCity/scripts.pory"
	.string "Ahh… It feels great letting the waves\n"
# 372 "data/maps/MossdeepCity/scripts.pory"
	.string "wash over my feet…\p"
# 373 "data/maps/MossdeepCity/scripts.pory"
	.string "Speaking of the waves, you know that\n"
# 374 "data/maps/MossdeepCity/scripts.pory"
	.string "island city SOOTOPOLIS?\p"
# 375 "data/maps/MossdeepCity/scripts.pory"
	.string "I think the GYM there had a new\n"
# 376 "data/maps/MossdeepCity/scripts.pory"
	.string "LEADER come in.\p"
# 377 "data/maps/MossdeepCity/scripts.pory"
	.string "People tell me the new LEADER once\n"
# 378 "data/maps/MossdeepCity/scripts.pory"
	.string "mentored WALLACE.$"

MossdeepCity_EventScript_GhostGirlAppear::
	return


MossdeepCity_EventScript_GhostGirlGone::
	return

