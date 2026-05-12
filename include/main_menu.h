#ifndef MAIN_MENU
#define MAIN_MENU

void CB2_InitMainMenu(void);
void CreateYesNoMenuParameterized(u8 x, u8 y, u16 baseTileNum, u16 baseBlock, u8 yesNoPalNum, u8 winPalNum);
void NewGameBirchSpeech_SetDefaultPlayerName(u8);
void CB2_ReinitMainMenu(void);
void CB2_NewGameBirchSpeech_FromNewMainMenu(void);

#endif /* MAIN_MENU */
