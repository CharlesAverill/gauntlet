EverGrandeCity_HallOfFame_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, EverGrandeCity_HallOfFame_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, EverGrandeCity_HallOfFame_OnWarp
	.byte 0

EverGrandeCity_HallOfFame_OnWarp:
	map_script_2 VAR_TEMP_1, 0, EverGrandeCity_HallOfFame_EventScript_TurnPlayerNorth
	.2byte 0

EverGrandeCity_HallOfFame_EventScript_TurnPlayerNorth::
	clearflag FLAG_UNUSED_0x040
	turnobject LOCALID_PLAYER, DIR_NORTH
	end

EverGrandeCity_HallOfFame_OnFrame:
	.2byte 0

EverGrandeCity_HallOfFame_EventScript_PokemonSelector::
	lock
	faceplayer
	goto_if_set FLAG_UNUSED_0x040, EverGrandeCity_HallOfFame_EventScript_AlreadySelected
	goto_if_set FLAG_SYS_POKEMON_GET, EverGrandeCity_HallOfFame_EventScript_AskSwitch
	msgbox EverGrandeCity_HallOfFame_Text_CheckBag
	release
	end

EverGrandeCity_HallOfFame_EventScript_AskSwitch::
	msgbox EverGrandeCity_HallOfFame_Text_AskSwitch, MSGBOX_YESNO
	switch VAR_RESULT
	case YES, EverGrandeCity_HallOfFame_EventScript_ProceedToChoose
	case NO, EverGrandeCity_HallOfFame_EventScript_DontSwitch
	goto EverGrandeCity_HallOfFame_EventScript_DontSwitch

EverGrandeCity_HallOfFame_EventScript_ProceedToChoose::
	msgbox EverGrandeCity_HallOfFame_Text_ChooseYourPokemon, MSGBOX_DEFAULT
	setvar VAR_TEMP_2, 1 @ Min species (Bulbasaur)
	setvar VAR_TEMP_3, 151 @ Max species (Mew)
	goto EverGrandeCity_HallOfFame_EventScript_BinarySearch

EverGrandeCity_HallOfFame_EventScript_DontSwitch::
	msgbox EverGrandeCity_HallOfFame_Text_DontSwitch, MSGBOX_DEFAULT
	release
	end

EverGrandeCity_HallOfFame_EventScript_BinarySearch::
	@ VAR_TEMP_4 = VAR_TEMP_2 + VAR_TEMP_3 via loop
	copyvar VAR_TEMP_4, VAR_TEMP_2
	copyvar VAR_TEMP_5, VAR_TEMP_3

EverGrandeCity_HallOfFame_EventScript_AddLoop::
	goto_if_eq VAR_TEMP_5, 0, EverGrandeCity_HallOfFame_EventScript_AddDone
	addvar VAR_TEMP_4, 1
	subvar VAR_TEMP_5, 1
	goto EverGrandeCity_HallOfFame_EventScript_AddLoop

EverGrandeCity_HallOfFame_EventScript_AddDone::
	@ VAR_TEMP_5 = VAR_TEMP_4 / 2 via loop
	setvar VAR_TEMP_5, 0

EverGrandeCity_HallOfFame_EventScript_DivLoop::
	goto_if_lt VAR_TEMP_4, 2, EverGrandeCity_HallOfFame_EventScript_DivDone
	subvar VAR_TEMP_4, 2
	addvar VAR_TEMP_5, 1
	goto EverGrandeCity_HallOfFame_EventScript_DivLoop

EverGrandeCity_HallOfFame_EventScript_DivDone::
	copyvar VAR_TEMP_4, VAR_TEMP_5
	goto EverGrandeCity_HallOfFame_EventScript_ShowMidpoint

EverGrandeCity_HallOfFame_EventScript_ShowMidpoint::
	bufferspeciesname STR_VAR_1, VAR_TEMP_4
	msgbox EverGrandeCity_HallOfFame_Text_DoYouWantThisPokemon, MSGBOX_YESNO
	switch VAR_RESULT
	case YES, EverGrandeCity_HallOfFame_EventScript_Selected
	case NO, EverGrandeCity_HallOfFame_EventScript_AskHigherLower
	goto EverGrandeCity_HallOfFame_EventScript_AskHigherLower

EverGrandeCity_HallOfFame_EventScript_AskHigherLower::
	message EverGrandeCity_HallOfFame_Text_HigherLowerOrStartOver
	waitmessage
	dynmultipush EverGrandeCity_HallOfFame_Text_Higher, 0
	dynmultipush EverGrandeCity_HallOfFame_Text_Lower, 1
	dynmultipush EverGrandeCity_HallOfFame_Text_StartOver, 2
	dynmultistack 20, 8, TRUE, 6, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	switch VAR_RESULT
	case 0, EverGrandeCity_HallOfFame_EventScript_Higher
	case 1, EverGrandeCity_HallOfFame_EventScript_Lower
	case 2, EverGrandeCity_HallOfFame_EventScript_StartOver
	goto EverGrandeCity_HallOfFame_EventScript_StartOver

EverGrandeCity_HallOfFame_EventScript_Higher::
	@ Set new min to midpoint + 1
	copyvar VAR_TEMP_2, VAR_TEMP_4
	addvar VAR_TEMP_2, 1
	goto_if_gt VAR_TEMP_2, VAR_TEMP_3, EverGrandeCity_HallOfFame_EventScript_NoMoreOptions
	goto EverGrandeCity_HallOfFame_EventScript_BinarySearch

EverGrandeCity_HallOfFame_EventScript_Lower::
	@ Set new max to midpoint - 1
	copyvar VAR_TEMP_3, VAR_TEMP_4
	subvar VAR_TEMP_3, 1
	goto_if_lt VAR_TEMP_3, VAR_TEMP_2, EverGrandeCity_HallOfFame_EventScript_NoMoreOptions
	goto EverGrandeCity_HallOfFame_EventScript_BinarySearch

EverGrandeCity_HallOfFame_EventScript_StartOver::
	setvar VAR_TEMP_2, 1
	setvar VAR_TEMP_3, 151
	goto EverGrandeCity_HallOfFame_EventScript_BinarySearch

EverGrandeCity_HallOfFame_EventScript_NoMoreOptions::
	msgbox EverGrandeCity_HallOfFame_Text_NoMoreOptions, MSGBOX_DEFAULT
	goto EverGrandeCity_HallOfFame_EventScript_StartOver

EverGrandeCity_HallOfFame_EventScript_Selected::
	copyvar VAR_TEMP_TRANSFERRED_SPECIES, VAR_TEMP_4
	bufferspeciesname STR_VAR_1, VAR_TEMP_TRANSFERRED_SPECIES
	msgbox EverGrandeCity_HallOfFame_Text_YouChoseThisPokemon, MSGBOX_DEFAULT
	removepartymon 0
	givemon VAR_TEMP_TRANSFERRED_SPECIES, 50, ITEM_NONE, BALL_MASTER
	setflag FLAG_UNUSED_0x040
	releaseall
	end

EverGrandeCity_HallOfFame_EventScript_AlreadySelected::
	msgbox EverGrandeCity_HallOfFame_Text_AlreadyHavePokemon, MSGBOX_DEFAULT
	release
	end

EverGrandeCity_HallOfFame_EventScript_GameClearMale::
	setrespawn HEAL_LOCATION_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F
	fadescreenspeed FADE_TO_BLACK, 24
	special GameClear
	waitstate
	releaseall
	end

EverGrandeCity_HallOfFame_EventScript_GameClearFemale::
	setrespawn HEAL_LOCATION_LITTLEROOT_TOWN_MAYS_HOUSE_2F
	fadescreenspeed FADE_TO_BLACK, 24
	special GameClear
	waitstate
	releaseall
	end

EverGrandeCity_HallOfFame_Movement_WalkIntoHallOfFame1:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

EverGrandeCity_HallOfFame_Movement_WalkIntoHallOfFame2:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end


HemlockTown_BerrySeller::
	lock
	faceplayer
	message HemlockTown_ImTheBerrySeller
	waitmessage
	faceplayer
	pokemart HemlockTown_BerrySeller_Items
	msgbox gText_PleaseComeAgain
	release
	end

	.align 2
HemlockTown_BerrySeller_Items::
	.2byte ITEM_POMEG_BERRY
	.2byte ITEM_KELPSY_BERRY
	.2byte ITEM_QUALOT_BERRY
	.2byte ITEM_HONDEW_BERRY
	.2byte ITEM_GREPA_BERRY
	.2byte ITEM_TAMATO_BERRY
	.2byte ITEM_NONE
	pokemartlistend

TMSeller::
	lock
	faceplayer
	message ImTheTMSeller
	waitmessage
	faceplayer
	pokemart HemlockTown_TMSeller_Items
	msgbox gText_PleaseComeAgain
	release
	end

	.align 2
HemlockTown_TMSeller_Items::
	.2byte ITEM_TM01
	.2byte ITEM_TM02
	.2byte ITEM_TM03
	.2byte ITEM_TM04
	.2byte ITEM_TM05
	.2byte ITEM_TM06
	.2byte ITEM_TM07
	.2byte ITEM_TM08
	.2byte ITEM_TM09
	.2byte ITEM_TM10
	.2byte ITEM_TM11
	.2byte ITEM_TM12
	.2byte ITEM_TM13
	.2byte ITEM_TM14
	.2byte ITEM_TM15
	.2byte ITEM_TM16
	.2byte ITEM_TM17
	.2byte ITEM_TM18
	.2byte ITEM_TM19
	.2byte ITEM_TM20
	.2byte ITEM_TM21
	.2byte ITEM_TM22
	.2byte ITEM_TM23
	.2byte ITEM_TM24
	.2byte ITEM_TM25
	.2byte ITEM_TM26
	.2byte ITEM_TM27
	.2byte ITEM_TM28
	.2byte ITEM_TM29
	.2byte ITEM_TM30
	.2byte ITEM_TM31
	.2byte ITEM_TM32
	.2byte ITEM_TM33
	.2byte ITEM_TM34
	.2byte ITEM_TM35
	.2byte ITEM_TM36
	.2byte ITEM_TM37
	.2byte ITEM_TM38
	.2byte ITEM_TM39
	.2byte ITEM_TM40
	.2byte ITEM_TM41
	.2byte ITEM_TM42
	.2byte ITEM_TM43
	.2byte ITEM_TM44
	.2byte ITEM_TM45
	.2byte ITEM_TM46
	.2byte ITEM_TM47
	.2byte ITEM_TM48
	.2byte ITEM_TM49
	.2byte ITEM_TM50
	.2byte ITEM_NONE
	pokemartlistend

HemlockTown_ImTheBerrySeller::
	.string "Hey there, I'm the BERRY Seller!\p"
	.string "How can I help you?$"

ImTheTMSeller::
	.string "Hey there, I'm the TM Seller!\p"
	.string "How can I help you?$"

EverGrandeCity_HallOfFame_Text_HereWeHonorLeagueChampions:
	.string "WALLACE: This room…\p"
	.string "This is where we keep records of\n"
	.string "POKéMON that prevailed through\l"
	.string "harsh battles.\p"
	.string "It is here that the LEAGUE CHAMPIONS\n"
	.string "are honored.$"

EverGrandeCity_HallOfFame_Text_LetsRecordYouAndYourPartnersNames:
	.string "WALLACE: Come on, let's record your\n"
	.string "name as a TRAINER who triumphed over\l"
	.string "the POKéMON LEAGUE, and the names of\l"
	.string "the partners who battled with you.$"

EverGrandeCity_HallOfFame_Text_CheckBag:
	.string "Why don't you check the bag by the\n"
	.string "pedestal, first?$"	

EverGrandeCity_HallOfFame_Text_ChooseYourPokemon:
	.string "Let me help you choose your POKéMON.$"

EverGrandeCity_HallOfFame_Text_DoYouWantThisPokemon:
	.string "Do you want {STR_VAR_1}?$"

EverGrandeCity_HallOfFame_Text_HigherLowerOrStartOver:
	.string "Higher number, lower number,\n"
	.string "or start over?$"

EverGrandeCity_HallOfFame_Text_NoMoreOptions:
	.string "There are no more POKéMON in that range.\n"
	.string "Let's start over.$"

EverGrandeCity_HallOfFame_Text_YouChoseThisPokemon:
	.string "Excellent choice!\p"
	.string "You have chosen {STR_VAR_1}!\p"
	.string "Now touch the pedestal to begin\n"
	.string "your GAUNTLET challenge!$"

EverGrandeCity_HallOfFame_Text_AlreadyHavePokemon:
	.string "You already have your partner POKéMON.\n"
	.string "Touch the pedestal to begin the challenge!$"

EverGrandeCity_HallOfFame_Text_Higher:
	.string "Higher$"

EverGrandeCity_HallOfFame_Text_Lower:
	.string "Lower$"

EverGrandeCity_HallOfFame_Text_StartOver:
	.string "Start over$"

EverGrandeCity_HallOfFame_Text_AskSwitch:
	.string "You already have a POKéMON.\n"
	.string "Would you like to switch it?$"

EverGrandeCity_HallOfFame_Text_DontSwitch:
	.string "Very well. Come back if you change your mind.$"
