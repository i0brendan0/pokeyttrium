#include "global.h"
#include "battle.h"
#include "battle_message.h"
#include "main.h"
#include "menu.h"
#include "menu_helpers.h"
#include "scanline_effect.h"
#include "palette.h"
#include "sprite.h"
#include "item.h"
#include "task.h"
#include "bg.h"
#include "gpu_regs.h"
#include "window.h"
#include "text.h"
#include "text_window.h"
#include "international_string_util.h"
#include "strings.h"
#include "list_menu.h"
#include "malloc.h"
#include "string_util.h"
#include "data2.h"
#include "reset_rtc_screen.h"
#include "reshow_battle_screen.h"
#include "constants/abilities.h"
#include "constants/moves.h"
#include "constants/items.h"
#include "constants/rgb.h"

#define MAX_MODIFY_DIGITS 4

struct BattleDebugModifyArrows
{
    u8 arrowSpriteId[2];
    u16 minValue;
    u16 maxValue;
    u16 currValue;
    u8 currentDigit;
    u8 maxDigits;
    u8 charDigits[MAX_MODIFY_DIGITS];
    void *modifiedValPtr;
    u8 typeOfVal;
};

struct BattleDebugMenu
{
    u8 battlerId;
    u8 battlerWindowId;

    u8 mainListWindowId;
    u8 mainListTaskId;
    u8 currentMainListItemId;

    u8 secondaryListWindowId;
    u8 secondaryListTaskId;
    u8 currentSecondaryListItemId;
    u8 secondaryListItemCount;

    u8 modifyWindowId;

    u8 activeWindow;

    struct BattleDebugModifyArrows modifyArrows;
    const struct BitfieldInfo *bitfield;
    bool8 battlerWasChanged[MAX_BATTLERS_COUNT];
};

struct __attribute__((__packed__)) BitfieldInfo
{
    u8 bitsCount;
    u8 currBit;
};

enum
{
    LIST_ITEM_MOVES,
    LIST_ITEM_ABILITY,
    LIST_ITEM_HELD_ITEM,
    LIST_ITEM_TYPES,
    LIST_ITEM_STATS,
    LIST_ITEM_STAT_STAGES,
    LIST_ITEM_STATUS1,
    LIST_ITEM_STATUS2,
    LIST_ITEM_STATUS3,
    LIST_ITEM_SIDE_STATUS,
    LIST_ITEM_VARIOUS,
    LIST_ITEM_COUNT
};

enum
{
    ACTIVE_WIN_MAIN,
    ACTIVE_WIN_SECONDARY,
    ACTIVE_WIN_MODIFY
};

enum
{
    VAL_U8,
    VAL_U16,
    VAL_U32,
    VAL_BITFIELD_8,
    VAL_BITFIELD_16,
    VAL_BITFIELD_32,
    VAR_SIDE_STATUS
};

enum
{
    LIST_SIDE_REFLECT,
    LIST_SIDE_LIGHTSCREEN,
    LIST_SIDE_SPIKES,
    LIST_SIDE_SAFEGUARD,
    LIST_SIDE_MIST
};

// const rom data
static const u8 sText_Ability[] = _("Ability");
static const u8 sText_Moves[] = _("Moves");
static const u8 sText_Stats[] = _("Stats");
static const u8 sText_StatStages[] = _("Stat Stages");
static const u8 sText_Status1[] = _("Status1");
static const u8 sText_Status2[] = _("Status2");
static const u8 sText_Status3[] = _("Status3");
static const u8 sText_HeldItem[] = _("Held Item");
static const u8 sText_SideStatus[] = _("Side Status");
static const u8 sText_MaxHp[] = _("HP Max");
static const u8 sText_CurrHp[] = _("HP Current");
static const u8 sText_Freeze[] = _("Freeze");
static const u8 sText_ToxicPoison[] = _("Toxic Poison");
static const u8 sText_ToxicCounter[] = _("Toxic Counter");
static const u8 sText_Flinch[] = _("Flinch");
static const u8 sText_Uproar[] = _("Uproar");
static const u8 sText_Bide[] = _("Bide");
static const u8 sText_LockConfuse[] = _("Lock Confuse");
static const u8 sText_MultipleTurns[] = _("MultipleTurns");
static const u8 sText_FocusEnergy[] = _("Focus Energy");
static const u8 sText_Transformed[] = _("Transformed");
static const u8 sText_Recharge[] = _("Recharge");
static const u8 sText_Rage[] = _("Rage");
static const u8 sText_Substitute[] = _("Substitute");
static const u8 sText_DestinyBond[] = _("Destiny Bond");
static const u8 sText_CantEscape[] = _("Cant Escape");
static const u8 sText_Nightmare[] = _("Nightmare");
static const u8 sText_Cursed[] = _("Cursed");
static const u8 sText_Foresight[] = _("Foresighted");
static const u8 sText_DefenseCurl[] = _("Def Curled");
static const u8 sText_Tormented[] = _("Tormented");
static const u8 sText_AlwaysHits[] = _("Sure Hit");
static const u8 sText_ChargedUp[] = _("Charged Up");
static const u8 sText_Rooted[] = _("Rooted");
static const u8 sText_Yawned[] = _("Yawned");
static const u8 sText_Minimized[] = _("Minimized");
static const u8 sText_NoCrit[] = _("No Crit");
static const u8 sText_Imprisoned[] = _("Imprison");
static const u8 sText_Reflect[] = _("Reflect");
static const u8 sText_LightScreen[] = _("Light Screen");
static const u8 sText_Spikes[] = _("Spikes");
static const u8 sText_Safeguard[] = _("Safeguard");
static const u8 sText_Mist[] = _("Mist");
static const u8 sText_ShowOpponentHP[] = _("Opponent Hp");
static const u8 sText_Types[] = _("Types");

static const u8 sText_EmptyString[] = _("");

static const struct BitfieldInfo sStatus1Bitfield[] =
{
    {/*Sleep*/ 3, 0},
    {/*Poison*/ 1, 3},
    {/*Burn*/ 1, 4},
    {/*Freeze*/ 1, 5},
    {/*Paralysis*/1, 6},
    {/*Toxic Poison*/ 1, 7},
    {/*Toxic Counter*/ 4, 8},
};

static const struct BitfieldInfo sStatus2Bitfield[] =
{
    {/*Confusion*/ 3, 0},
    {/*Flinch*/ 1, 3},
    {/*Uproar*/ 3, 4},
    // Bit 7 is unused.
    {/*Bide*/ 2, 8},
    {/*Lock Confuse*/ 2, 10},
    {/*Multiple Turns*/ 1, 12},
    // Wrap bits are omitted. Done in various.
    // In Love bits are omitted. Done in various.
    {/*Transformed*/ 1, 21},
    {/*Recharge*/ 1, 22},
    {/*Rage*/ 1, 23},
    {/*Substitute*/ 1, 24},
    {/*Destiny bond*/ 1, 25},
    {/*Can't escape*/ 1, 26},
    {/*Nightmares*/ 1, 27},
    {/*Cursed*/ 1, 28},
    {/*Foresighted*/ 1, 29},
    {/*Defense Curled*/ 1, 30},
    {/*Tormented*/ 1, 31},
};

static const struct BitfieldInfo sStatus3Bitfield[] =
{
    {/*Always hits*/ 2, 4},
    //*Perish Song*/ 1, 5},
    // On Air 1, 6,
    // Underground 1, 7,
    {/*Minimized*/ 1, 8},
    {/*Charged Up*/ 1, 9},
    {/*Rooted*/ 1, 10},
    {/*Yawn*/ 2, 11},
    {/*Imprison*/ 1, 13},
    // Grudge 1, 14,
    {/*No Crit*/ 1, 15},
};

static const struct ListMenuItem sMainListItems[] =
{
    {sText_Moves, LIST_ITEM_MOVES},
    {sText_Ability, LIST_ITEM_ABILITY},
    {sText_HeldItem, LIST_ITEM_HELD_ITEM},
    {sText_Types, LIST_ITEM_TYPES},
    {sText_Stats, LIST_ITEM_STATS},
    {sText_StatStages, LIST_ITEM_STAT_STAGES},
    {sText_Status1, LIST_ITEM_STATUS1},
    {sText_Status2, LIST_ITEM_STATUS2},
    {sText_Status3, LIST_ITEM_STATUS3},
    {sText_SideStatus, LIST_ITEM_SIDE_STATUS},
};

static const struct ListMenuItem sStatsListItems[] =
{
    {sText_CurrHp, 0},
    {sText_MaxHp, 1},
    {gText_Attack, 2},
    {gText_Defense, 3},
    {gText_Speed, 4},
    {gText_SpAtk, 5},
    {gText_SpDef, 6},
};

static const struct ListMenuItem sStatus1ListItems[] =
{
    {gText_Sleep, 0},
    {gText_Poison, 1},
    {gText_Burn, 2},
    {sText_Freeze, 3},
    {gText_Paralysis, 4},
    {sText_ToxicPoison, 5},
    {sText_ToxicCounter, 6},
};

static const struct ListMenuItem sStatus2ListItems[] =
{
    {gText_Confusion, 0},
    {sText_Flinch, 1},
    {sText_Uproar, 2},
    {sText_Bide, 3},
    {sText_LockConfuse, 4},
    {sText_MultipleTurns, 5},
    {sText_FocusEnergy, 6},
    {sText_Recharge, 7},
    {sText_Rage, 8},
    {sText_Substitute, 9},
    {sText_DestinyBond, 10},
    {sText_CantEscape, 11},
    {sText_Nightmare, 12},
    {sText_Cursed, 13},
    {sText_Foresight, 14},
    {sText_DefenseCurl, 15},
    {sText_Tormented, 16},
};

static const struct ListMenuItem sStatus3ListItems[] =
{
    {sText_AlwaysHits, 0},
    {sText_Minimized, 1},
    {sText_ChargedUp, 2},
    {sText_Rooted, 3},
    {sText_Yawned, 4},
    {sText_Imprisoned, 5},
    {sText_NoCrit, 6},
};

static const struct ListMenuItem sSideStatusListItems[] =
{
    {sText_Reflect, LIST_SIDE_REFLECT},
    {sText_LightScreen, LIST_SIDE_LIGHTSCREEN},
    {sText_Spikes, LIST_SIDE_SPIKES},
    {sText_Safeguard, LIST_SIDE_SAFEGUARD},
    {sText_Mist, LIST_SIDE_MIST},
};

static const struct ListMenuItem sSecondaryListItems[] =
{
    {sText_EmptyString, 0},
    {sText_EmptyString, 1},
    {sText_EmptyString, 2},
    {sText_EmptyString, 3},
    {sText_EmptyString, 4},
    {sText_EmptyString, 5},
    {sText_EmptyString, 6},
    {sText_EmptyString, 7},
    {sText_EmptyString, 8},
};


static const struct ListMenuTemplate sMainListTemplate =
{
    .items = sMainListItems,
    .moveCursorFunc = NULL,
    .unk_08 = NULL,
    .totalItems = ARRAY_COUNT(sMainListItems),
    .maxShowed = 6,
    .windowId = 0,
    .unk_11 = 0,
    .unk_12 = 8,
    .cursor_X = 0,
    .upText_Y = 1,
    .cursorPal = 2,
    .fillValue = 1,
    .cursorShadowPal = 3,
    .lettersSpacing = 1,
    .unk_16_3 = 0,
    .scrollMultiple = LIST_NO_MULTIPLE_SCROLL,
    .fontId = 1,
    .cursorKind = 0
};

static const struct ListMenuTemplate sSecondaryListTemplate =
{
    .items = sSecondaryListItems,
    .moveCursorFunc = NULL,
    .unk_08 = NULL,
    .totalItems = 0,
    .maxShowed = 0,
    .windowId = 0,
    .unk_11 = 0,
    .unk_12 = 8,
    .cursor_X = 0,
    .upText_Y = 1,
    .cursorPal = 2,
    .fillValue = 1,
    .cursorShadowPal = 3,
    .lettersSpacing = 1,
    .unk_16_3 = 0,
    .scrollMultiple = LIST_NO_MULTIPLE_SCROLL,
    .fontId = 1,
    .cursorKind = 0
};


static const struct WindowTemplate sMainListWindowTemplate =
{
    .priority = 0,
    .tilemapLeft = 1,
    .tilemapTop = 3,
    .width = 9,
    .height = 12,
    .paletteNum = 0xF,
    .baseBlock = 0x2
};

static const struct WindowTemplate sSecondaryListWindowTemplate =
{
    .priority = 0,
    .tilemapLeft = 12,
    .tilemapTop = 3,
    .width = 10,
    .height = 2,
    .paletteNum = 0xF,
    .baseBlock = 0xA0
};

static const struct WindowTemplate sModifyWindowTemplate =
{
    .priority = 0,
    .tilemapLeft = 25,
    .tilemapTop = 2,
    .width = 4,
    .height = 2,
    .paletteNum = 0xF,
    .baseBlock = 0x200
};

static const struct WindowTemplate sBattlerWindowTemplate =
{
    .priority = 0,
    .tilemapLeft = 10,
    .tilemapTop = 0,
    .width = 14,
    .height = 2,
    .paletteNum = 0xF,
    .baseBlock = 0x300
};

static const struct BgTemplate sBgTemplates[] =
{
   {
       .bg = 0,
       .charBaseIndex = 0,
       .mapBaseIndex = 31,
       .screenSize = 0,
       .paletteMode = 0,
       .priority = 1,
       .baseTile = 0
   },
   {
       .bg = 1,
       .charBaseIndex = 2,
       .mapBaseIndex = 29,
       .screenSize = 0,
       .paletteMode = 0,
       .priority = 0,
       .baseTile = 0
   }
};

static const u8 sBitsToMaxDigit[] =
{
    [0] = 0,
    [1] = 1, // max 1
    [2] = 1, // max 3
    [3] = 1, // max 7
    [4] = 2, // max 15
    [5] = 2, // max 31
    [6] = 2, // max 63
    [7] = 3, // max 127
    [8] = 3, // max 255
};

static const bool8 sHasChangeableEntries[LIST_ITEM_COUNT] =
{
    [LIST_ITEM_MOVES] = TRUE,
    [LIST_ITEM_ABILITY] = TRUE,
    [LIST_ITEM_TYPES] = TRUE,
    [LIST_ITEM_HELD_ITEM] = TRUE,
    [LIST_ITEM_STAT_STAGES] = TRUE,
};

static const u16 sBgColor[] = {RGB_WHITE};

// this file's functions
static void Task_DebugMenuFadeOut(u8 taskId);
static void Task_DebugMenuProcessInput(u8 taskId);
static void Task_DebugMenuFadeIn(u8 taskId);
static void PrintOnBattlerWindow(u8 windowId, u8 battlerId);
static void UpdateWindowsOnChangedBattler(struct BattleDebugMenu *data);
static void CreateSecondaryListMenu(struct BattleDebugMenu *data);
static void PrintSecondaryEntries(struct BattleDebugMenu *data);
static void DestroyModifyArrows(struct BattleDebugMenu *data);
static void PrintDigitChars(struct BattleDebugMenu *data);
static void SetUpModifyArrows(struct BattleDebugMenu *data);
static void UpdateBattlerValue(struct BattleDebugMenu *data);
static void UpdateMonData(struct BattleDebugMenu *data);
static u8 *GetSideStatusValue(struct BattleDebugMenu *data, bool32 changeStatus, bool32 statusTrue);
static bool32 TryMoveDigit(struct BattleDebugModifyArrows *modArrows, bool32 moveUp);

// code
static struct BattleDebugMenu *GetStructPtr(u8 taskId)
{
    u8 *taskDataPtr = (u8*)(&gTasks[taskId].data[0]);

    return (struct BattleDebugMenu*)(T1_READ_PTR(taskDataPtr));
}

static void SetStructPtr(u8 taskId, void *ptr)
{
    u32 structPtr = (u32)(ptr);
    u8 *taskDataPtr = (u8*)(&gTasks[taskId].data[0]);

    taskDataPtr[0] = structPtr >> 0;
    taskDataPtr[1] = structPtr >> 8;
    taskDataPtr[2] = structPtr >> 16;
    taskDataPtr[3] = structPtr >> 24;
}

static void MainCB2(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
}

static void VBlankCB(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

void CB2_BattleDebugMenu(void)
{
    u8 taskId;
    struct BattleDebugMenu *data;

    switch (gMain.state)
    {
    default:
    case 0:
        SetVBlankCallback(NULL);
        gMain.state++;
        break;
    case 1:
        ResetVramOamAndBgCntRegs();
        SetGpuReg(REG_OFFSET_DISPCNT, 0);
        ResetBgsAndClearDma3BusyFlags(0);
        InitBgsFromTemplates(0, sBgTemplates, ARRAY_COUNT(sBgTemplates));
        ResetAllBgsCoordinates();
        FreeAllWindowBuffers();
        DeactivateAllTextPrinters();
        SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP);
        ShowBg(0);
        ShowBg(1);
        gMain.state++;
        break;
    case 2:
        ResetPaletteFade();
        ScanlineEffect_Stop();
        ResetTasks();
        ResetSpriteData();
        gMain.state++;
        break;
    case 3:
        LoadPalette(sBgColor, 0, 2);
        LoadPalette(GetOverworldTextboxPalettePtr(), 0xf0, 16);
        gMain.state++;
        break;
    case 4:
        taskId = CreateTask(Task_DebugMenuFadeIn, 0);
        data = AllocZeroed(sizeof(struct BattleDebugMenu));
        SetStructPtr(taskId, data);

        data->battlerId = gBattleStruct->debugBattler;
        data->battlerWindowId = AddWindow(&sBattlerWindowTemplate);
        PutWindowTilemap(data->battlerWindowId);
        PrintOnBattlerWindow(data->battlerWindowId, data->battlerId);

        data->mainListWindowId = AddWindow(&sMainListWindowTemplate);

        gMultiuseListMenuTemplate = sMainListTemplate;
        gMultiuseListMenuTemplate.windowId = data->mainListWindowId;
        data->mainListTaskId = ListMenuInit(&gMultiuseListMenuTemplate, 0, 0);

        data->currentMainListItemId = 0;
        data->activeWindow = ACTIVE_WIN_MAIN;
        data->secondaryListTaskId = 0xFF;
        CopyWindowToVram(data->mainListWindowId, 3);
        gMain.state++;
        break;
    case 5:
        BeginNormalPaletteFade(-1, 0, 0x10, 0, 0);
        SetVBlankCallback(VBlankCB);
        SetMainCallback2(MainCB2);
        return;
    }
}

static void Task_DebugMenuFadeIn(u8 taskId)
{
    if (!gPaletteFade.active)
        gTasks[taskId].func = Task_DebugMenuProcessInput;
}

static void Task_DebugMenuProcessInput(u8 taskId)
{
    s32 listItemId = 0;
    struct BattleDebugMenu *data = GetStructPtr(taskId);

    // Exit the menu.
    if (gMain.newKeys & SELECT_BUTTON)
    {
        BeginNormalPaletteFade(-1, 0, 0, 0x10, 0);
        gTasks[taskId].func = Task_DebugMenuFadeOut;
        return;
    }

    // Try changing active battler.
    if (gMain.newKeys & R_BUTTON)
    {
        if (data->battlerId++ == gBattlersCount - 1)
            data->battlerId = 0;
        UpdateWindowsOnChangedBattler(data);
    }
    else if (gMain.newKeys & L_BUTTON)
    {
        if (data->battlerId-- == 0)
            data->battlerId = gBattlersCount - 1;
        UpdateWindowsOnChangedBattler(data);
    }

    // A main list item is active, handle input.
    if (data->activeWindow == ACTIVE_WIN_MAIN)
    {
        listItemId = ListMenuHandleInputGetItemId(data->mainListTaskId);
        if (listItemId != LIST_B_PRESSED && listItemId != LIST_NOTHING_CHOSEN && listItemId < LIST_ITEM_COUNT)
        {
            data->currentMainListItemId = listItemId;

            // Create the secondary menu list.
            CreateSecondaryListMenu(data);
            PrintSecondaryEntries(data);
            data->activeWindow = ACTIVE_WIN_SECONDARY;
        }
    }
    // Secondary list is active, handle input.
    else if (data->activeWindow == ACTIVE_WIN_SECONDARY)
    {
        listItemId = ListMenuHandleInputGetItemId(data->secondaryListTaskId);
        if (listItemId == LIST_B_PRESSED)
        {
            DestroyListMenuTask(data->secondaryListTaskId, NULL, NULL);
            sub_8198070(data->secondaryListWindowId, TRUE);
            RemoveWindow(data->secondaryListWindowId);
            data->activeWindow = ACTIVE_WIN_MAIN;
            data->secondaryListTaskId = 0xFF;
        }
        else if (listItemId != LIST_NOTHING_CHOSEN)
        {
            data->currentSecondaryListItemId = listItemId;
            data->modifyWindowId = AddWindow(&sModifyWindowTemplate);
            PutWindowTilemap(data->modifyWindowId);
            CopyWindowToVram(data->modifyWindowId, 3);
            SetUpModifyArrows(data);
            PrintDigitChars(data);
            data->activeWindow = ACTIVE_WIN_MODIFY;
        }
    }
    // Handle value modifying.
    else if (data->activeWindow == ACTIVE_WIN_MODIFY)
    {
        if (gMain.newKeys & (B_BUTTON | A_BUTTON))
        {
            sub_8198070(data->modifyWindowId, TRUE);
            RemoveWindow(data->modifyWindowId);
            DestroyModifyArrows(data);
            data->activeWindow = ACTIVE_WIN_SECONDARY;
        }
        else if (gMain.newKeys & DPAD_RIGHT)
        {
            if (data->modifyArrows.currentDigit != (data->modifyArrows.maxDigits - 1))
            {
                data->modifyArrows.currentDigit++;
                gSprites[data->modifyArrows.arrowSpriteId[0]].pos2.x += 6;
                gSprites[data->modifyArrows.arrowSpriteId[1]].pos2.x += 6;
            }
        }
        else if (gMain.newKeys & DPAD_LEFT)
        {
            if (data->modifyArrows.currentDigit != 0)
            {
                data->modifyArrows.currentDigit--;
                gSprites[data->modifyArrows.arrowSpriteId[0]].pos2.x -= 6;
                gSprites[data->modifyArrows.arrowSpriteId[1]].pos2.x -= 6;
            }
        }
        else if (gMain.newKeys & DPAD_UP)
        {
            if (TryMoveDigit(&data->modifyArrows, TRUE))
            {
                PrintDigitChars(data);
                UpdateBattlerValue(data);
                PrintSecondaryEntries(data);
            }
        }
        else if (gMain.newKeys & DPAD_DOWN)
        {
            if (TryMoveDigit(&data->modifyArrows, FALSE))
            {
                PrintDigitChars(data);
                UpdateBattlerValue(data);
                PrintSecondaryEntries(data);
            }
        }
    }
}

static void Task_DebugMenuFadeOut(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        struct BattleDebugMenu *data = GetStructPtr(taskId);
        DestroyListMenuTask(data->mainListTaskId, 0, 0);
        if (data->secondaryListTaskId != 0xFF)
            DestroyListMenuTask(data->secondaryListTaskId, 0, 0);

        FreeAllWindowBuffers();
        UpdateMonData(data);
        gBattleStruct->debugBattler = data->battlerId;
        Free(data);
        DestroyTask(taskId);
        SetMainCallback2(ReshowBattleScreenAfterMenu);
    }
}

static void PrintOnBattlerWindow(u8 windowId, u8 battlerId)
{
    u8 text[POKEMON_NAME_LENGTH + 10];

    text[0] = CHAR_0 + battlerId;
    text[1] = CHAR_SPACE;
    text[2] = CHAR_HYPHEN;
    text[3] = CHAR_SPACE;
    StringCopy(&text[4], gBattleMons[battlerId].nickname);

    FillWindowPixelBuffer(windowId, 0x11);
    PrintTextOnWindow(windowId, 1, text, 0, 0, 0, NULL);
    CopyWindowToVram(windowId, 3);
}

static void UpdateWindowsOnChangedBattler(struct BattleDebugMenu *data)
{
    PrintOnBattlerWindow(data->battlerWindowId, data->battlerId);
    if (data->secondaryListTaskId != 0xFF)
    {
        DestroyListMenuTask(data->secondaryListTaskId, 0, 0);
        RemoveWindow(data->secondaryListWindowId);
        CreateSecondaryListMenu(data);
        data->currentSecondaryListItemId = 0;
        PrintSecondaryEntries(data);
    }
    if (data->activeWindow == ACTIVE_WIN_MODIFY)
    {
        DestroyModifyArrows(data);
        SetUpModifyArrows(data);
        PrintDigitChars(data);
    }
}


static void CreateSecondaryListMenu(struct BattleDebugMenu *data)
{
    struct WindowTemplate winTemplate;
    struct ListMenuTemplate listTemplate;
    u8 itemsCount = 1;

    winTemplate = sSecondaryListWindowTemplate;
    listTemplate = sSecondaryListTemplate;

    switch (data->currentMainListItemId)
    {
    case LIST_ITEM_ABILITY:
    case LIST_ITEM_HELD_ITEM:
        itemsCount = 1;
        break;
    case LIST_ITEM_TYPES:
        itemsCount = 2;
        break;
    case LIST_ITEM_MOVES:
        itemsCount = 4;
        break;
    case LIST_ITEM_STATS:
        listTemplate.items = sStatsListItems;
        itemsCount = ARRAY_COUNT(sStatsListItems);
        break;
    case LIST_ITEM_STAT_STAGES:
        itemsCount = 7;
        break;
    case LIST_ITEM_STATUS1:
        listTemplate.items = sStatus1ListItems;
        itemsCount = ARRAY_COUNT(sStatus1ListItems);
        data->bitfield = sStatus1Bitfield;
        break;
    case LIST_ITEM_STATUS2:
        listTemplate.items = sStatus2ListItems;
        itemsCount = ARRAY_COUNT(sStatus2ListItems);
        data->bitfield = sStatus2Bitfield;
        winTemplate.height = 1;
        break;
    case LIST_ITEM_STATUS3:
        listTemplate.items = sStatus3ListItems;
        itemsCount = ARRAY_COUNT(sStatus3ListItems);
        data->bitfield = sStatus3Bitfield;
        break;
    case LIST_ITEM_SIDE_STATUS:
        listTemplate.items = sSideStatusListItems;
        itemsCount = ARRAY_COUNT(sSideStatusListItems);
        break;
    }

    data->secondaryListItemCount = itemsCount;
    winTemplate.height *= itemsCount;
    data->secondaryListWindowId = AddWindow(&winTemplate);

    listTemplate.totalItems = itemsCount;
    listTemplate.maxShowed = itemsCount;
    if (listTemplate.maxShowed > 7 && !sHasChangeableEntries[data->currentMainListItemId])
        listTemplate.maxShowed = 7;
    listTemplate.windowId = data->secondaryListWindowId;

    data->secondaryListTaskId = ListMenuInit(&listTemplate, 0, 0);
    CopyWindowToVram(data->secondaryListWindowId, 3);
}

static void PadString(const u8 *src, u8 *dst)
{
    u32 i;

    for (i = 0; i < 17 && src[i] != EOS; i++)
        dst[i] = src[i];

    for (; i < 17; i++)
        dst[i] = CHAR_SPACE;

    dst[i] = EOS;
}

static void PrintSecondaryEntries(struct BattleDebugMenu *data)
{
    u8 text[20];
    s32 i;
    struct TextSubPrinter printer;
    u8 yMultiplier;

    // Do not print entries if they are not changing.
    if (!sHasChangeableEntries[data->currentMainListItemId])
        return;

    yMultiplier = (GetFontAttribute(sSecondaryListTemplate.fontId, 1) + sSecondaryListTemplate.unk_16_3);

    printer.windowId = data->secondaryListWindowId;
    printer.fontId = 1;
    printer.fontColor_l = 0;
    printer.letterSpacing = 0;
    printer.lineSpacing = 1;
    printer.fgColor = 2;
    printer.bgColor = 1;
    printer.shadowColor = 3;
    printer.x = sSecondaryListTemplate.unk_12;
    printer.currentX = sSecondaryListTemplate.unk_12;
    printer.current_text_offset = text;

    switch (data->currentMainListItemId)
    {
    case LIST_ITEM_MOVES:
        for (i = 0; i < 4; i++)
        {
            PadString(gMoveNames[gBattleMons[data->battlerId].moves[i]], text);
            printer.currentY = printer.y = (i * yMultiplier) + sSecondaryListTemplate.upText_Y;
            AddTextPrinter(&printer, 0, NULL);
        }
        break;
    case LIST_ITEM_ABILITY:
        PadString(gAbilityNames[gBattleMons[data->battlerId].ability], text);
        printer.currentY = printer.y = sSecondaryListTemplate.upText_Y;
        AddTextPrinter(&printer, 0, NULL);
        break;
    case LIST_ITEM_HELD_ITEM:
        PadString(ItemId_GetName(gBattleMons[data->battlerId].item), text);
        printer.currentY = printer.y = sSecondaryListTemplate.upText_Y;
        AddTextPrinter(&printer, 0, NULL);
        break;
    case LIST_ITEM_TYPES:
        for (i = 0; i < 2; i++)
        {
            u8 *types = &gBattleMons[data->battlerId].type1;

            PadString(gTypeNames[types[i]], text);
            printer.currentY = printer.y = (i * yMultiplier) + sSecondaryListTemplate.upText_Y;
            AddTextPrinter(&printer, 0, NULL);
        }
        break;
    case LIST_ITEM_STAT_STAGES:
        for (i = 0; i < 7; i++)
        {
            u8 *txtPtr = StringCopy(text, gStatNamesTable[STAT_ATK + i]);
            txtPtr[0] = CHAR_SPACE;
            if (gBattleMons[data->battlerId].statStages[STAT_ATK + i] >= 6)
            {
                txtPtr[1] = CHAR_PLUS;
                txtPtr[2] = CHAR_0 + (gBattleMons[data->battlerId].statStages[STAT_ATK + i] - 6);
            }
            else
            {
                txtPtr[1] = CHAR_HYPHEN;
                txtPtr[2] = CHAR_6 - (gBattleMons[data->battlerId].statStages[STAT_ATK + i]);
            }
            txtPtr[3] = EOS;

            PadString(text, text);
            printer.currentY = printer.y = (i * yMultiplier) + sSecondaryListTemplate.upText_Y;
            AddTextPrinter(&printer, 0, NULL);
        }
        break;
    }
}

static void DestroyModifyArrows(struct BattleDebugMenu *data)
{
    FreeSpritePaletteByTag(gSpritePalette_RtcArrow.tag);
    if (data->modifyArrows.arrowSpriteId[0] != 0xFF)
        DestroySprite(&gSprites[data->modifyArrows.arrowSpriteId[0]]);
    if (data->modifyArrows.arrowSpriteId[1] != 0xFF)
        DestroySprite(&gSprites[data->modifyArrows.arrowSpriteId[1]]);
}

static void PrintDigitChars(struct BattleDebugMenu *data)
{
    s32 i;
    u8 text[MAX_MODIFY_DIGITS + 1];

    for (i = 0; i < data->modifyArrows.maxDigits; i++)
        text[i] = data->modifyArrows.charDigits[i];

    text[i] = EOS;

    PrintTextOnWindow(data->modifyWindowId, 1, text, 3, 0, 0, NULL);
}

static const u32 GetBitfieldToAndValue(u32 currBit, u32 bitsCount)
{
    u32 i;
    u32 toAnd = 0;

    for (i = 0; i < bitsCount; i++)
        toAnd |= (1 << (currBit + i));

    return toAnd;
}

static const u32 GetBitfieldValue(u32 value, u32 currBit, u32 bitsCount)
{
    return (value & (GetBitfieldToAndValue(currBit, bitsCount))) >> currBit;
}

static void UpdateBattlerValue(struct BattleDebugMenu *data)
{
    switch (data->modifyArrows.typeOfVal)
    {
    case VAL_U8:
        *(u8*)(data->modifyArrows.modifiedValPtr) = data->modifyArrows.currValue;
        break;
    case VAL_U16:
        *(u16*)(data->modifyArrows.modifiedValPtr) = data->modifyArrows.currValue;
        break;
    case VAL_U32:
        *(u32*)(data->modifyArrows.modifiedValPtr) = data->modifyArrows.currValue;
        break;
    case VAL_BITFIELD_32:
        *(u32*)(data->modifyArrows.modifiedValPtr) &= ~(GetBitfieldToAndValue(data->bitfield[data->currentSecondaryListItemId].currBit, data->bitfield[data->currentSecondaryListItemId].bitsCount));
        *(u32*)(data->modifyArrows.modifiedValPtr) |= (data->modifyArrows.currValue << data->bitfield[data->currentSecondaryListItemId].currBit);
        break;
    case VAR_SIDE_STATUS:
        *GetSideStatusValue(data, TRUE, data->modifyArrows.currValue != 0) = data->modifyArrows.currValue;
        break;
    }
    data->battlerWasChanged[data->battlerId] = TRUE;
}

static u32 CharDigitsToValue(u8 *charDigits, u8 maxDigits)
{
    s32 i;
    u8 id = 0;
    u32 newValue = 0;
    u8 valueDigits[MAX_MODIFY_DIGITS];

    for (i = 0; i < MAX_MODIFY_DIGITS; i++)
        valueDigits[i] = charDigits[i] - CHAR_0;

    if (maxDigits >= MAX_MODIFY_DIGITS)
        newValue += valueDigits[id++] * 1000;
    if (maxDigits >= MAX_MODIFY_DIGITS - 1)
        newValue += valueDigits[id++] * 100;
    if (maxDigits >= MAX_MODIFY_DIGITS - 2)
        newValue += valueDigits[id++] * 10;
    if (maxDigits >= MAX_MODIFY_DIGITS - 3)
        newValue += valueDigits[id++];

    return newValue;
}

static void ValueToCharDigits(u8 *charDigits, u32 newValue, u8 maxDigits)
{
    s32 i;
    u8 valueDigits[MAX_MODIFY_DIGITS];
    u8 id = 0;

    if (maxDigits >= MAX_MODIFY_DIGITS)
        valueDigits[id++] = newValue / 1000;
    if (maxDigits >= MAX_MODIFY_DIGITS - 1)
        valueDigits[id++] = (newValue % 1000) / 100;
    if (maxDigits >= MAX_MODIFY_DIGITS - 2)
        valueDigits[id++] = (newValue % 100) / 10;
    if (maxDigits >= MAX_MODIFY_DIGITS - 3)
        valueDigits[id++] = newValue % 10;

    for (i = 0; i < MAX_MODIFY_DIGITS; i++)
        charDigits[i] = valueDigits[i] + CHAR_0;
}

static u8 *GetSideStatusValue(struct BattleDebugMenu *data, bool32 changeStatus, bool32 statusTrue)
{
    struct SideTimer *sideTimer = &gSideTimers[GET_BATTLER_SIDE(data->battlerId)];

    switch (data->currentSecondaryListItemId)
    {
    case LIST_SIDE_REFLECT:
        if (changeStatus)
        {
            if (statusTrue)
                *(u16*)(data->modifyArrows.modifiedValPtr) |= SIDE_STATUS_REFLECT;
            else
                *(u16*)(data->modifyArrows.modifiedValPtr) &= ~(SIDE_STATUS_REFLECT);
            sideTimer->reflectBattlerId = data->battlerId;
        }
        return &sideTimer->reflectTimer;
    case LIST_SIDE_LIGHTSCREEN:
        if (changeStatus)
        {
            if (statusTrue)
                *(u16*)(data->modifyArrows.modifiedValPtr) |= SIDE_STATUS_LIGHTSCREEN;
            else
                *(u16*)(data->modifyArrows.modifiedValPtr) &= ~(SIDE_STATUS_LIGHTSCREEN);
            sideTimer->lightscreenBattlerId = data->battlerId;
        }
        return &sideTimer->lightscreenTimer;
    case LIST_SIDE_SPIKES:
        if (changeStatus)
        {
            if (statusTrue)
                *(u16*)(data->modifyArrows.modifiedValPtr) |= SIDE_STATUS_SPIKES;
            else
                *(u16*)(data->modifyArrows.modifiedValPtr) &= ~(SIDE_STATUS_SPIKES);
        }
        return &sideTimer->spikesAmount;
    case LIST_SIDE_SAFEGUARD:
        if (changeStatus)
        {
            if (statusTrue)
                *(u16*)(data->modifyArrows.modifiedValPtr) |= SIDE_STATUS_SAFEGUARD;
            else
                *(u16*)(data->modifyArrows.modifiedValPtr) &= ~(SIDE_STATUS_SAFEGUARD);
            sideTimer->safeguardBattlerId = data->battlerId;
        }
        return &sideTimer->safeguardTimer;
    case LIST_SIDE_MIST:
        if (changeStatus)
        {
            if (statusTrue)
                *(u16*)(data->modifyArrows.modifiedValPtr) |= SIDE_STATUS_MIST;
            else
                *(u16*)(data->modifyArrows.modifiedValPtr) &= ~(SIDE_STATUS_MIST);
            sideTimer->mistBattlerId = data->battlerId;
        }
        return &sideTimer->mistTimer;
    default:
        return NULL;
    }
}

static void SetUpModifyArrows(struct BattleDebugMenu *data)
{
    LoadSpritePalette(&gSpritePalette_RtcArrow);
    data->modifyArrows.arrowSpriteId[0] = CreateSprite(&gSpriteTemplate_RtcArrow, 207, 12, 0);
    data->modifyArrows.arrowSpriteId[1] = CreateSprite(&gSpriteTemplate_RtcArrow, 207, 36, 0);
    gSprites[data->modifyArrows.arrowSpriteId[1]].animNum = 1;
    switch (data->currentMainListItemId)
    {
    case LIST_ITEM_ABILITY:
        data->modifyArrows.minValue = 0;
        data->modifyArrows.maxValue = ABILITIES_COUNT - 1;
        data->modifyArrows.maxDigits = 3;
        data->modifyArrows.modifiedValPtr = &gBattleMons[data->battlerId].ability;
        data->modifyArrows.typeOfVal = VAL_U8;
        data->modifyArrows.currValue = gBattleMons[data->battlerId].ability;
        break;
    case LIST_ITEM_MOVES:
        data->modifyArrows.minValue = 0;
        data->modifyArrows.maxValue = MOVES_COUNT - 1;
        data->modifyArrows.maxDigits = 3;
        data->modifyArrows.modifiedValPtr = &gBattleMons[data->battlerId].moves[data->currentSecondaryListItemId];
        data->modifyArrows.typeOfVal = VAL_U16;
        data->modifyArrows.currValue = gBattleMons[data->battlerId].moves[data->currentSecondaryListItemId];
        break;
    case LIST_ITEM_HELD_ITEM:
        data->modifyArrows.minValue = 0;
        data->modifyArrows.maxValue = ITEMS_COUNT - 1;
        data->modifyArrows.maxDigits = 3;
        data->modifyArrows.modifiedValPtr = &gBattleMons[data->battlerId].item;
        data->modifyArrows.typeOfVal = VAL_U16;
        data->modifyArrows.currValue = gBattleMons[data->battlerId].item;
        break;
    case LIST_ITEM_TYPES:
        data->modifyArrows.minValue = 0;
        data->modifyArrows.maxValue = NUMBER_OF_MON_TYPES - 1;
        data->modifyArrows.maxDigits = 2;
        data->modifyArrows.modifiedValPtr = (u8*)((&gBattleMons[data->battlerId].type1) + data->currentSecondaryListItemId);
        data->modifyArrows.typeOfVal = VAL_U8;
        data->modifyArrows.currValue = *(u8*)((&gBattleMons[data->battlerId].type1) + data->currentSecondaryListItemId);
        break;
    case LIST_ITEM_STATS:
        data->modifyArrows.minValue = 0;
        data->modifyArrows.maxValue = 9999;
        data->modifyArrows.maxDigits = 4;
        if (data->currentSecondaryListItemId == 0)
        {
            data->modifyArrows.modifiedValPtr = &gBattleMons[data->battlerId].hp;
            data->modifyArrows.currValue = gBattleMons[data->battlerId].hp;
            data->modifyArrows.maxValue = gBattleMons[data->battlerId].maxHP;
        }
        else if (data->currentSecondaryListItemId == 1)
        {
            data->modifyArrows.modifiedValPtr = &gBattleMons[data->battlerId].maxHP;
            data->modifyArrows.currValue = gBattleMons[data->battlerId].maxHP;
        }
        else
        {
            data->modifyArrows.modifiedValPtr = (u16*)((&gBattleMons[data->battlerId].attack) + (data->currentSecondaryListItemId - 2));
            data->modifyArrows.currValue = *(u16*)((&gBattleMons[data->battlerId].attack) + (data->currentSecondaryListItemId - 2));
        }
        data->modifyArrows.typeOfVal = VAL_U16;
        break;
    case LIST_ITEM_STAT_STAGES:
        data->modifyArrows.minValue = 0;
        data->modifyArrows.maxValue = 12;
        data->modifyArrows.maxDigits = 2;
        data->modifyArrows.modifiedValPtr = &gBattleMons[data->battlerId].statStages[data->currentSecondaryListItemId + STAT_ATK];
        data->modifyArrows.typeOfVal = VAL_U8;
        data->modifyArrows.currValue = gBattleMons[data->battlerId].statStages[data->currentSecondaryListItemId + STAT_ATK];
        break;
    case LIST_ITEM_STATUS1:
        data->modifyArrows.modifiedValPtr = &gBattleMons[data->battlerId].status1;
        data->modifyArrows.currValue = GetBitfieldValue(gBattleMons[data->battlerId].status1, data->bitfield[data->currentSecondaryListItemId].currBit, data->bitfield[data->currentSecondaryListItemId].bitsCount);
        data->modifyArrows.typeOfVal = VAL_BITFIELD_32;
        goto CASE_ITEM_STATUS;
    case LIST_ITEM_STATUS2:
        data->modifyArrows.modifiedValPtr = &gBattleMons[data->battlerId].status2;
        data->modifyArrows.currValue = GetBitfieldValue(gBattleMons[data->battlerId].status2, data->bitfield[data->currentSecondaryListItemId].currBit, data->bitfield[data->currentSecondaryListItemId].bitsCount);
        data->modifyArrows.typeOfVal = VAL_BITFIELD_32;
        goto CASE_ITEM_STATUS;
    case LIST_ITEM_STATUS3:
        data->modifyArrows.modifiedValPtr = &gStatuses3[data->battlerId];
        data->modifyArrows.currValue = GetBitfieldValue(gStatuses3[data->battlerId], data->bitfield[data->currentSecondaryListItemId].currBit, data->bitfield[data->currentSecondaryListItemId].bitsCount);
        data->modifyArrows.typeOfVal = VAL_BITFIELD_32;
        goto CASE_ITEM_STATUS;
    CASE_ITEM_STATUS:
        data->modifyArrows.minValue = 0;
        data->modifyArrows.maxValue = (1 << data->bitfield[data->currentSecondaryListItemId].bitsCount) - 1;
        data->modifyArrows.maxDigits = sBitsToMaxDigit[data->bitfield[data->currentSecondaryListItemId].bitsCount];
        break;
    case LIST_ITEM_SIDE_STATUS:
        data->modifyArrows.minValue = 0;

        if (data->currentSecondaryListItemId == LIST_SIDE_SPIKES)
            data->modifyArrows.maxValue = 3;
        else
            data->modifyArrows.maxValue = 9;

        data->modifyArrows.maxDigits = 2;
        data->modifyArrows.modifiedValPtr = &gSideStatuses[GET_BATTLER_SIDE(data->battlerId)];
        data->modifyArrows.typeOfVal = VAR_SIDE_STATUS;
        data->modifyArrows.currValue = *GetSideStatusValue(data, FALSE, FALSE);
        break;
    }

    data->modifyArrows.currentDigit = 0;
    ValueToCharDigits(data->modifyArrows.charDigits, data->modifyArrows.currValue, data->modifyArrows.maxDigits);
}

static bool32 TryMoveDigit(struct BattleDebugModifyArrows *modArrows, bool32 moveUp)
{
    s32 i;
    u8 charDigits[MAX_MODIFY_DIGITS];
    u32 newValue;

    for (i = 0; i < MAX_MODIFY_DIGITS; i++)
        charDigits[i] = modArrows->charDigits[i];

    if (moveUp)
    {
        if (charDigits[modArrows->currentDigit] == CHAR_9)
            charDigits[modArrows->currentDigit] = CHAR_0;
        else
            charDigits[modArrows->currentDigit]++;
    }
    else
    {
        if (charDigits[modArrows->currentDigit] == CHAR_0)
            charDigits[modArrows->currentDigit] = CHAR_9;
        else
            charDigits[modArrows->currentDigit]--;
    }

    newValue = CharDigitsToValue(charDigits, modArrows->maxDigits);
    if (newValue > modArrows->maxValue || newValue < modArrows->minValue)
    {
        return FALSE;
    }
    else
    {
        modArrows->currValue = newValue;
        for (i = 0; i < MAX_MODIFY_DIGITS; i++)
             modArrows->charDigits[i] = charDigits[i];
        return TRUE;
    }
}

static void UpdateMonData(struct BattleDebugMenu *data)
{
    s32 i, j;

    for (i = 0; i < MAX_BATTLERS_COUNT; i++)
    {
        if (data->battlerWasChanged[i])
        {
            struct Pokemon *mon;
            struct BattlePokemon *battleMon = &gBattleMons[i];

            if (GetBattlerSide(i) == B_SIDE_PLAYER)
                mon = &gPlayerParty[gBattlerPartyIndexes[i]];
            else
                mon = &gEnemyParty[gBattlerPartyIndexes[i]];

            SetMonData(mon, MON_DATA_HELD_ITEM, &battleMon->item);
            SetMonData(mon, MON_DATA_STATUS, &battleMon->status1);
            SetMonData(mon, MON_DATA_HP, &battleMon->hp);
            SetMonData(mon, MON_DATA_MAX_HP, &battleMon->maxHP);
            for (j = 0; j < 4; j++)
                SetMonData(mon, MON_DATA_MOVE1 + j, &battleMon->moves[j]);
        }
    }
}
