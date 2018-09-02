typedef int COLOR;

enum eGameStages
{
	eGAME_STAGE_NONE = -1,
	eGAME_STAGE_INIT,
	eGAME_STAGE_MENU,
	eGAME_STAGE_PLAY,
	eGAME_STAGE_MAX
};

enum eUITypes
{
	eUI_WINDOW = 0,
	eUI_BASE,
	eUI_TEXT,
	eUI_BUTTON
};

enum eUIWindow
{
	eUI_MENU = 0,
	eUI_ROOM_SETTINGS,
	eUI_GAME,
	eUI_MAX,
};

enum eGameRole
{
	eROLE_NONE = 0,
	eROLE_X = -1,
	eROLE_O = 1
};