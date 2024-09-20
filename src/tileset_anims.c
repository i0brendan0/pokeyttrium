#include "global.h"
#include "graphics.h"
#include "palette.h"
#include "util.h"
#include "battle_transition.h"
#include "task.h"
#include "battle_transition.h"
#include "fieldmap.h"

static EWRAM_DATA struct {
    const u16 *src;
    u16 *dest;
    u16 size;
} sTilesetDMA3TransferBuffer[20] = {0};

static u8 sTilesetDMA3TransferBufferSize;
static u16 sPrimaryTilesetAnimCounter;
static u16 sPrimaryTilesetAnimCounterMax;
static u16 sSecondaryTilesetAnimCounter;
static u16 sSecondaryTilesetAnimCounterMax;
static void (*sPrimaryTilesetAnimCallback)(u16);
static void (*sSecondaryTilesetAnimCallback)(u16);

static void _InitPrimaryTilesetAnimation(void);
static void _InitSecondaryTilesetAnimation(void);
static void TilesetAnim_General(u16);
static void TilesetAnim_Building(u16);
static void TilesetAnim_Rustboro(u16);
static void TilesetAnim_Dewford(u16);
static void TilesetAnim_Slateport(u16);
static void TilesetAnim_Mauville(u16);
static void TilesetAnim_Lavaridge(u16);
static void TilesetAnim_Silveridge(u16);
static void TilesetAnim_EverGrande(u16);
static void TilesetAnim_Pacifidlog(u16);
static void TilesetAnim_Sootopolis(u16);
static void TilesetAnim_BattleFrontierOutsideWest(u16);
static void TilesetAnim_BattleFrontierOutsideEast(u16);
static void TilesetAnim_Underwater(u16);
static void TilesetAnim_SootopolisGym(u16);
static void TilesetAnim_Cave(u16);
static void TilesetAnim_EliteFour(u16);
static void TilesetAnim_MauvilleGym(u16);
static void TilesetAnim_BikeShop(u16);
static void TilesetAnim_BattlePyramid(u16);
static void TilesetAnim_BattleDome(u16);
static void QueueAnimTiles_General_Flower(u16);
static void QueueAnimTiles_General_Water(u16);
static void QueueAnimTiles_General_SandWaterEdge(u16);
static void QueueAnimTiles_General_Waterfall(u16);
static void QueueAnimTiles_General_LandWaterEdge(u16);
static void QueueAnimTiles_Building_TVTurnedOn(u16);
static void QueueAnimTiles_Rustboro_WindyWater(u16, u8);
static void QueueAnimTiles_Rustboro_Fountain(u16);
static void QueueAnimTiles_Dewford_Flag(u16);
static void QueueAnimTiles_Slateport_Balloons(u16);
static void QueueAnimTiles_Mauville_Flowers(u16, u8);
static void QueueAnimTiles_BikeShop_BlinkingLights(u16);
static void QueueAnimTiles_BattlePyramid_Torch(u16);
static void QueueAnimTiles_BattlePyramid_StatueShadow(u16);
static void BlendAnimPalette_BattleDome_FloorLights(u16);
static void BlendAnimPalette_BattleDome_FloorLightsNoBlend(u16);
static void QueueAnimTiles_Lavaridge_Steam(u8);
static void QueueAnimTiles_Lavaridge_Lava(u16);
static void QueueAnimTiles_Silveridge_Chimney(u8);
static void QueueAnimTiles_EverGrande_Flowers(u16, u8);
static void QueueAnimTiles_Pacifidlog_LogBridges(u8);
static void QueueAnimTiles_Pacifidlog_WaterCurrents(u8);
static void QueueAnimTiles_Sootopolis_StormyWater(u16);
static void QueueAnimTiles_Underwater_Seaweed(u8);
static void QueueAnimTiles_Cave_Lava(u16);
static void QueueAnimTiles_BattleFrontierOutsideWest_Flag(u16);
static void QueueAnimTiles_BattleFrontierOutsideEast_Flag(u16);
static void QueueAnimTiles_MauvilleGym_ElectricGates(u16);
static void QueueAnimTiles_SootopolisGym_Waterfalls(u16);
static void QueueAnimTiles_EliteFour_GroundLights(u16);
static void QueueAnimTiles_EliteFour_WallLights(u16);

const u16 gTilesetAnims_General_Flower_Frame1[] = INCBIN_U16("data/tilesets/primary/general/anim/flower/1.4bpp");
const u16 gTilesetAnims_General_Flower_Frame0[] = INCBIN_U16("data/tilesets/primary/general/anim/flower/0.4bpp");
const u16 gTilesetAnims_General_Flower_Frame2[] = INCBIN_U16("data/tilesets/primary/general/anim/flower/2.4bpp");
const u16 tileset_anims_space_0[16] = {};

const u16 *const gTilesetAnims_General_Flower[] = {
    gTilesetAnims_General_Flower_Frame0,
    gTilesetAnims_General_Flower_Frame1,
    gTilesetAnims_General_Flower_Frame0,
    gTilesetAnims_General_Flower_Frame2
};

const u16 gTilesetAnims_General_Water_Frame0[] = INCBIN_U16("data/tilesets/primary/general/anim/water/0.4bpp");
const u16 gTilesetAnims_General_Water_Frame1[] = INCBIN_U16("data/tilesets/primary/general/anim/water/1.4bpp");
const u16 gTilesetAnims_General_Water_Frame2[] = INCBIN_U16("data/tilesets/primary/general/anim/water/2.4bpp");
const u16 gTilesetAnims_General_Water_Frame3[] = INCBIN_U16("data/tilesets/primary/general/anim/water/3.4bpp");
const u16 gTilesetAnims_General_Water_Frame4[] = INCBIN_U16("data/tilesets/primary/general/anim/water/4.4bpp");
const u16 gTilesetAnims_General_Water_Frame5[] = INCBIN_U16("data/tilesets/primary/general/anim/water/5.4bpp");
const u16 gTilesetAnims_General_Water_Frame6[] = INCBIN_U16("data/tilesets/primary/general/anim/water/6.4bpp");
const u16 gTilesetAnims_General_Water_Frame7[] = INCBIN_U16("data/tilesets/primary/general/anim/water/7.4bpp");

const u16 *const gTilesetAnims_General_Water[] = {
    gTilesetAnims_General_Water_Frame0,
    gTilesetAnims_General_Water_Frame1,
    gTilesetAnims_General_Water_Frame2,
    gTilesetAnims_General_Water_Frame3,
    gTilesetAnims_General_Water_Frame4,
    gTilesetAnims_General_Water_Frame5,
    gTilesetAnims_General_Water_Frame6,
    gTilesetAnims_General_Water_Frame7
};

const u16 gTilesetAnims_General_SandWaterEdge_Frame0[] = INCBIN_U16("data/tilesets/primary/general/anim/sand_water_edge/0.4bpp");
const u16 gTilesetAnims_General_SandWaterEdge_Frame1[] = INCBIN_U16("data/tilesets/primary/general/anim/sand_water_edge/1.4bpp");
const u16 gTilesetAnims_General_SandWaterEdge_Frame2[] = INCBIN_U16("data/tilesets/primary/general/anim/sand_water_edge/2.4bpp");
const u16 gTilesetAnims_General_SandWaterEdge_Frame3[] = INCBIN_U16("data/tilesets/primary/general/anim/sand_water_edge/3.4bpp");
const u16 gTilesetAnims_General_SandWaterEdge_Frame4[] = INCBIN_U16("data/tilesets/primary/general/anim/sand_water_edge/4.4bpp");
const u16 gTilesetAnims_General_SandWaterEdge_Frame5[] = INCBIN_U16("data/tilesets/primary/general/anim/sand_water_edge/5.4bpp");
const u16 gTilesetAnims_General_SandWaterEdge_Frame6[] = INCBIN_U16("data/tilesets/primary/general/anim/sand_water_edge/6.4bpp");

const u16 *const gTilesetAnims_General_SandWaterEdge[] = {
    gTilesetAnims_General_SandWaterEdge_Frame0,
    gTilesetAnims_General_SandWaterEdge_Frame1,
    gTilesetAnims_General_SandWaterEdge_Frame2,
    gTilesetAnims_General_SandWaterEdge_Frame3,
    gTilesetAnims_General_SandWaterEdge_Frame4,
    gTilesetAnims_General_SandWaterEdge_Frame5,
    gTilesetAnims_General_SandWaterEdge_Frame6,
    gTilesetAnims_General_SandWaterEdge_Frame0
};

const u16 gTilesetAnims_General_Waterfall_Frame0[] = INCBIN_U16("data/tilesets/primary/general/anim/waterfall/0.4bpp");
const u16 gTilesetAnims_General_Waterfall_Frame1[] = INCBIN_U16("data/tilesets/primary/general/anim/waterfall/1.4bpp");
const u16 gTilesetAnims_General_Waterfall_Frame2[] = INCBIN_U16("data/tilesets/primary/general/anim/waterfall/2.4bpp");
const u16 gTilesetAnims_General_Waterfall_Frame3[] = INCBIN_U16("data/tilesets/primary/general/anim/waterfall/3.4bpp");

const u16 *const gTilesetAnims_General_Waterfall[] = {
    gTilesetAnims_General_Waterfall_Frame0,
    gTilesetAnims_General_Waterfall_Frame1,
    gTilesetAnims_General_Waterfall_Frame2,
    gTilesetAnims_General_Waterfall_Frame3
};

const u16 gTilesetAnims_General_LandWaterEdge_Frame0[] = INCBIN_U16("data/tilesets/primary/general/anim/land_water_edge/0.4bpp");
const u16 gTilesetAnims_General_LandWaterEdge_Frame1[] = INCBIN_U16("data/tilesets/primary/general/anim/land_water_edge/1.4bpp");
const u16 gTilesetAnims_General_LandWaterEdge_Frame2[] = INCBIN_U16("data/tilesets/primary/general/anim/land_water_edge/2.4bpp");
const u16 gTilesetAnims_General_LandWaterEdge_Frame3[] = INCBIN_U16("data/tilesets/primary/general/anim/land_water_edge/3.4bpp");

const u16 *const gTilesetAnims_General_LandWaterEdge[] = {
    gTilesetAnims_General_LandWaterEdge_Frame0,
    gTilesetAnims_General_LandWaterEdge_Frame1,
    gTilesetAnims_General_LandWaterEdge_Frame2,
    gTilesetAnims_General_LandWaterEdge_Frame3
};

const u16 gTilesetAnims_Lavaridge_Steam_Frame0[] = INCBIN_U16("data/tilesets/secondary/lavaridge/anim/steam/0.4bpp");
const u16 gTilesetAnims_Lavaridge_Steam_Frame1[] = INCBIN_U16("data/tilesets/secondary/lavaridge/anim/steam/1.4bpp");
const u16 gTilesetAnims_Lavaridge_Steam_Frame2[] = INCBIN_U16("data/tilesets/secondary/lavaridge/anim/steam/2.4bpp");
const u16 gTilesetAnims_Lavaridge_Steam_Frame3[] = INCBIN_U16("data/tilesets/secondary/lavaridge/anim/steam/3.4bpp");

const u16 *const gTilesetAnims_Lavaridge_Steam[] = {
    gTilesetAnims_Lavaridge_Steam_Frame0,
    gTilesetAnims_Lavaridge_Steam_Frame1,
    gTilesetAnims_Lavaridge_Steam_Frame2,
    gTilesetAnims_Lavaridge_Steam_Frame3
};

const u16 gTilesetAnims_Silveridge_Chimney_Frame0[] = INCBIN_U16("data/tilesets/secondary/silveridge/anim/chimney/0.4bpp");
const u16 gTilesetAnims_Silveridge_Chimney_Frame1[] = INCBIN_U16("data/tilesets/secondary/silveridge/anim/chimney/1.4bpp");
const u16 gTilesetAnims_Silveridge_Chimney_Frame2[] = INCBIN_U16("data/tilesets/secondary/silveridge/anim/chimney/2.4bpp");
const u16 gTilesetAnims_Silveridge_Chimney_Frame3[] = INCBIN_U16("data/tilesets/secondary/silveridge/anim/chimney/3.4bpp");

const u16 *const gTilesetAnims_Silveridge_Chimney[] = {
    gTilesetAnims_Silveridge_Chimney_Frame0,
    gTilesetAnims_Silveridge_Chimney_Frame1,
    gTilesetAnims_Silveridge_Chimney_Frame2,
    gTilesetAnims_Silveridge_Chimney_Frame3
};

const u16 gTilesetAnims_Pacifidlog_LogBridges_Frame0[] = INCBIN_U16("data/tilesets/secondary/pacifidlog/anim/log_bridges/0.4bpp");
const u16 gTilesetAnims_Pacifidlog_LogBridges_Frame1[] = INCBIN_U16("data/tilesets/secondary/pacifidlog/anim/log_bridges/1.4bpp");
const u16 gTilesetAnims_Pacifidlog_LogBridges_Frame2[] = INCBIN_U16("data/tilesets/secondary/pacifidlog/anim/log_bridges/2.4bpp");

const u16 *const gTilesetAnims_Pacifidlog_LogBridges[] = {
    gTilesetAnims_Pacifidlog_LogBridges_Frame0,
    gTilesetAnims_Pacifidlog_LogBridges_Frame1,
    gTilesetAnims_Pacifidlog_LogBridges_Frame2,
    gTilesetAnims_Pacifidlog_LogBridges_Frame1
};

const u16 gTilesetAnims_Underwater_Seaweed_Frame0[] = INCBIN_U16("data/tilesets/secondary/underwater/anim/seaweed/0.4bpp");
const u16 gTilesetAnims_Underwater_Seaweed_Frame1[] = INCBIN_U16("data/tilesets/secondary/underwater/anim/seaweed/1.4bpp");
const u16 gTilesetAnims_Underwater_Seaweed_Frame2[] = INCBIN_U16("data/tilesets/secondary/underwater/anim/seaweed/2.4bpp");
const u16 gTilesetAnims_Underwater_Seaweed_Frame3[] = INCBIN_U16("data/tilesets/secondary/underwater/anim/seaweed/3.4bpp");

const u16 *const gTilesetAnims_Underwater_Seaweed[] = {
    gTilesetAnims_Underwater_Seaweed_Frame0,
    gTilesetAnims_Underwater_Seaweed_Frame1,
    gTilesetAnims_Underwater_Seaweed_Frame2,
    gTilesetAnims_Underwater_Seaweed_Frame3
};

const u16 gTilesetAnims_Pacifidlog_WaterCurrents_Frame0[] = INCBIN_U16("data/tilesets/secondary/pacifidlog/anim/water_currents/0.4bpp");
const u16 gTilesetAnims_Pacifidlog_WaterCurrents_Frame1[] = INCBIN_U16("data/tilesets/secondary/pacifidlog/anim/water_currents/1.4bpp");
const u16 gTilesetAnims_Pacifidlog_WaterCurrents_Frame2[] = INCBIN_U16("data/tilesets/secondary/pacifidlog/anim/water_currents/2.4bpp");
const u16 gTilesetAnims_Pacifidlog_WaterCurrents_Frame3[] = INCBIN_U16("data/tilesets/secondary/pacifidlog/anim/water_currents/3.4bpp");
const u16 gTilesetAnims_Pacifidlog_WaterCurrents_Frame4[] = INCBIN_U16("data/tilesets/secondary/pacifidlog/anim/water_currents/4.4bpp");
const u16 gTilesetAnims_Pacifidlog_WaterCurrents_Frame5[] = INCBIN_U16("data/tilesets/secondary/pacifidlog/anim/water_currents/5.4bpp");
const u16 gTilesetAnims_Pacifidlog_WaterCurrents_Frame6[] = INCBIN_U16("data/tilesets/secondary/pacifidlog/anim/water_currents/6.4bpp");
const u16 gTilesetAnims_Pacifidlog_WaterCurrents_Frame7[] = INCBIN_U16("data/tilesets/secondary/pacifidlog/anim/water_currents/7.4bpp");

const u16 *const gTilesetAnims_Pacifidlog_WaterCurrents[] = {
    gTilesetAnims_Pacifidlog_WaterCurrents_Frame0,
    gTilesetAnims_Pacifidlog_WaterCurrents_Frame1,
    gTilesetAnims_Pacifidlog_WaterCurrents_Frame2,
    gTilesetAnims_Pacifidlog_WaterCurrents_Frame3,
    gTilesetAnims_Pacifidlog_WaterCurrents_Frame4,
    gTilesetAnims_Pacifidlog_WaterCurrents_Frame5,
    gTilesetAnims_Pacifidlog_WaterCurrents_Frame6,
    gTilesetAnims_Pacifidlog_WaterCurrents_Frame7
};

const u16 gTilesetAnims_Mauville_Flower1_Frame0[] = INCBIN_U16("data/tilesets/secondary/mauville/anim/flower_1/0.4bpp");
const u16 gTilesetAnims_Mauville_Flower1_Frame1[] = INCBIN_U16("data/tilesets/secondary/mauville/anim/flower_1/1.4bpp");
const u16 gTilesetAnims_Mauville_Flower1_Frame2[] = INCBIN_U16("data/tilesets/secondary/mauville/anim/flower_1/2.4bpp");
const u16 gTilesetAnims_Mauville_Flower1_Frame3[] = INCBIN_U16("data/tilesets/secondary/mauville/anim/flower_1/3.4bpp");
const u16 gTilesetAnims_Mauville_Flower1_Frame4[] = INCBIN_U16("data/tilesets/secondary/mauville/anim/flower_1/4.4bpp");
const u16 gTilesetAnims_Mauville_Flower2_Frame0[] = INCBIN_U16("data/tilesets/secondary/mauville/anim/flower_2/0.4bpp");
const u16 gTilesetAnims_Mauville_Flower2_Frame1[] = INCBIN_U16("data/tilesets/secondary/mauville/anim/flower_2/1.4bpp");
const u16 gTilesetAnims_Mauville_Flower2_Frame2[] = INCBIN_U16("data/tilesets/secondary/mauville/anim/flower_2/2.4bpp");
const u16 gTilesetAnims_Mauville_Flower2_Frame3[] = INCBIN_U16("data/tilesets/secondary/mauville/anim/flower_2/3.4bpp");
const u16 gTilesetAnims_Mauville_Flower2_Frame4[] = INCBIN_U16("data/tilesets/secondary/mauville/anim/flower_2/4.4bpp");
const u16 tileset_anims_space_1[16] = {};

u16 const gTilesetAnims_Mauville_Flower1_VDests[] = {
    NUM_TILES_IN_PRIMARY + 96,
    NUM_TILES_IN_PRIMARY + 100,
    NUM_TILES_IN_PRIMARY + 104,
    NUM_TILES_IN_PRIMARY + 108,
    NUM_TILES_IN_PRIMARY + 112,
    NUM_TILES_IN_PRIMARY + 116,
    NUM_TILES_IN_PRIMARY + 120,
    NUM_TILES_IN_PRIMARY + 124
};

u16 const gTilesetAnims_Mauville_Flower2_VDests[] = {
    NUM_TILES_IN_PRIMARY + 128,
    NUM_TILES_IN_PRIMARY + 132,
    NUM_TILES_IN_PRIMARY + 136,
    NUM_TILES_IN_PRIMARY + 140,
    NUM_TILES_IN_PRIMARY + 144,
    NUM_TILES_IN_PRIMARY + 148,
    NUM_TILES_IN_PRIMARY + 152,
    NUM_TILES_IN_PRIMARY + 156
};

const u16 *const gTilesetAnims_Mauville_Flower1[] = {
    gTilesetAnims_Mauville_Flower1_Frame0,
    gTilesetAnims_Mauville_Flower1_Frame0,
    gTilesetAnims_Mauville_Flower1_Frame1,
    gTilesetAnims_Mauville_Flower1_Frame2,
    gTilesetAnims_Mauville_Flower1_Frame3,
    gTilesetAnims_Mauville_Flower1_Frame3,
    gTilesetAnims_Mauville_Flower1_Frame3,
    gTilesetAnims_Mauville_Flower1_Frame3,
    gTilesetAnims_Mauville_Flower1_Frame3,
    gTilesetAnims_Mauville_Flower1_Frame3,
    gTilesetAnims_Mauville_Flower1_Frame2,
    gTilesetAnims_Mauville_Flower1_Frame1
};

const u16 *const gTilesetAnims_Mauville_Flower2[] = {
    gTilesetAnims_Mauville_Flower2_Frame0,
    gTilesetAnims_Mauville_Flower2_Frame0,
    gTilesetAnims_Mauville_Flower2_Frame1,
    gTilesetAnims_Mauville_Flower2_Frame2,
    gTilesetAnims_Mauville_Flower2_Frame3,
    gTilesetAnims_Mauville_Flower2_Frame3,
    gTilesetAnims_Mauville_Flower2_Frame3,
    gTilesetAnims_Mauville_Flower2_Frame3,
    gTilesetAnims_Mauville_Flower2_Frame3,
    gTilesetAnims_Mauville_Flower2_Frame3,
    gTilesetAnims_Mauville_Flower2_Frame2,
    gTilesetAnims_Mauville_Flower2_Frame1
};

const u16 *const gTilesetAnims_Mauville_Flower1_B[] = {
    gTilesetAnims_Mauville_Flower1_Frame0,
    gTilesetAnims_Mauville_Flower1_Frame0,
    gTilesetAnims_Mauville_Flower1_Frame4,
    gTilesetAnims_Mauville_Flower1_Frame4
};

const u16 *const gTilesetAnims_Mauville_Flower2_B[] = {
    gTilesetAnims_Mauville_Flower2_Frame0,
    gTilesetAnims_Mauville_Flower2_Frame0,
    gTilesetAnims_Mauville_Flower2_Frame4,
    gTilesetAnims_Mauville_Flower2_Frame4
};

const u16 gTilesetAnims_Rustboro_WindyWater_Frame0[] = INCBIN_U16("data/tilesets/secondary/rustboro/anim/windy_water/0.4bpp");
const u16 gTilesetAnims_Rustboro_WindyWater_Frame1[] = INCBIN_U16("data/tilesets/secondary/rustboro/anim/windy_water/1.4bpp");
const u16 gTilesetAnims_Rustboro_WindyWater_Frame2[] = INCBIN_U16("data/tilesets/secondary/rustboro/anim/windy_water/2.4bpp");
const u16 gTilesetAnims_Rustboro_WindyWater_Frame3[] = INCBIN_U16("data/tilesets/secondary/rustboro/anim/windy_water/3.4bpp");
const u16 gTilesetAnims_Rustboro_WindyWater_Frame4[] = INCBIN_U16("data/tilesets/secondary/rustboro/anim/windy_water/4.4bpp");
const u16 gTilesetAnims_Rustboro_WindyWater_Frame5[] = INCBIN_U16("data/tilesets/secondary/rustboro/anim/windy_water/5.4bpp");
const u16 gTilesetAnims_Rustboro_WindyWater_Frame6[] = INCBIN_U16("data/tilesets/secondary/rustboro/anim/windy_water/6.4bpp");
const u16 gTilesetAnims_Rustboro_WindyWater_Frame7[] = INCBIN_U16("data/tilesets/secondary/rustboro/anim/windy_water/7.4bpp");

u16 const gTilesetAnims_Rustboro_WindyWater_VDests[] = {
    NUM_TILES_IN_PRIMARY + 128,
    NUM_TILES_IN_PRIMARY + 132,
    NUM_TILES_IN_PRIMARY + 136,
    NUM_TILES_IN_PRIMARY + 140,
    NUM_TILES_IN_PRIMARY + 144,
    NUM_TILES_IN_PRIMARY + 148,
    NUM_TILES_IN_PRIMARY + 152,
    NUM_TILES_IN_PRIMARY + 156
};

const u16 *const gTilesetAnims_Rustboro_WindyWater[] = {
    gTilesetAnims_Rustboro_WindyWater_Frame0,
    gTilesetAnims_Rustboro_WindyWater_Frame1,
    gTilesetAnims_Rustboro_WindyWater_Frame2,
    gTilesetAnims_Rustboro_WindyWater_Frame3,
    gTilesetAnims_Rustboro_WindyWater_Frame4,
    gTilesetAnims_Rustboro_WindyWater_Frame5,
    gTilesetAnims_Rustboro_WindyWater_Frame6,
    gTilesetAnims_Rustboro_WindyWater_Frame7
};

const u16 gTilesetAnims_Rustboro_Fountain_Frame0[] = INCBIN_U16("data/tilesets/secondary/rustboro/anim/fountain/0.4bpp");
const u16 gTilesetAnims_Rustboro_Fountain_Frame1[] = INCBIN_U16("data/tilesets/secondary/rustboro/anim/fountain/1.4bpp");
const u16 tileset_anims_space_2[16] = {};

const u16 *const gTilesetAnims_Rustboro_Fountain[] = {
    gTilesetAnims_Rustboro_Fountain_Frame0,
    gTilesetAnims_Rustboro_Fountain_Frame1
};

const u16 gTilesetAnims_Lavaridge_Cave_Lava_Frame0[] = INCBIN_U16("data/tilesets/secondary/cave/anim/lava/0.4bpp");
const u16 gTilesetAnims_Lavaridge_Cave_Lava_Frame1[] = INCBIN_U16("data/tilesets/secondary/cave/anim/lava/1.4bpp");
const u16 gTilesetAnims_Lavaridge_Cave_Lava_Frame2[] = INCBIN_U16("data/tilesets/secondary/cave/anim/lava/2.4bpp");
const u16 gTilesetAnims_Lavaridge_Cave_Lava_Frame3[] = INCBIN_U16("data/tilesets/secondary/cave/anim/lava/3.4bpp");
const u16 gTilesetAnims_Lavaridge_Cave_Lava_Frame4[] = INCBIN_U16("data/tilesets/secondary/cave/anim/lava/4.4bpp");
const u16 gTilesetAnims_Lavaridge_Cave_Lava_Frame5[] = INCBIN_U16("data/tilesets/secondary/cave/anim/lava/5.4bpp");
const u16 gTilesetAnims_Lavaridge_Cave_Lava_Frame6[] = INCBIN_U16("data/tilesets/secondary/cave/anim/lava/6.4bpp");
const u16 gTilesetAnims_Lavaridge_Cave_Lava_Frame7[] = INCBIN_U16("data/tilesets/secondary/cave/anim/lava/7.4bpp");
const u16 tileset_anims_space_3[16] = {};

const u16 *const gTilesetAnims_Lavaridge_Cave_Lava[] = {
    gTilesetAnims_Lavaridge_Cave_Lava_Frame0,
    gTilesetAnims_Lavaridge_Cave_Lava_Frame1,
    gTilesetAnims_Lavaridge_Cave_Lava_Frame2,
    gTilesetAnims_Lavaridge_Cave_Lava_Frame3
};

const u16 gTilesetAnims_EverGrande_Flowers_Frame0[] = INCBIN_U16("data/tilesets/secondary/ever_grande/anim/flowers/0.4bpp");
const u16 gTilesetAnims_EverGrande_Flowers_Frame1[] = INCBIN_U16("data/tilesets/secondary/ever_grande/anim/flowers/1.4bpp");
const u16 gTilesetAnims_EverGrande_Flowers_Frame2[] = INCBIN_U16("data/tilesets/secondary/ever_grande/anim/flowers/2.4bpp");
const u16 gTilesetAnims_EverGrande_Flowers_Frame3[] = INCBIN_U16("data/tilesets/secondary/ever_grande/anim/flowers/3.4bpp");
const u16 gTilesetAnims_EverGrande_Flowers_Frame4[] = INCBIN_U16("data/tilesets/secondary/ever_grande/anim/flowers/4.4bpp");
const u16 gTilesetAnims_EverGrande_Flowers_Frame5[] = INCBIN_U16("data/tilesets/secondary/ever_grande/anim/flowers/5.4bpp");
const u16 gTilesetAnims_EverGrande_Flowers_Frame6[] = INCBIN_U16("data/tilesets/secondary/ever_grande/anim/flowers/6.4bpp");
const u16 gTilesetAnims_EverGrande_Flowers_Frame7[] = INCBIN_U16("data/tilesets/secondary/ever_grande/anim/flowers/7.4bpp");
const u16 tileset_anims_space_4[16] = {};

u16 const gTilesetAnims_EverGrande_VDests[] = {
    NUM_TILES_IN_PRIMARY + 224,
    NUM_TILES_IN_PRIMARY + 228,
    NUM_TILES_IN_PRIMARY + 232,
    NUM_TILES_IN_PRIMARY + 236,
    NUM_TILES_IN_PRIMARY + 240,
    NUM_TILES_IN_PRIMARY + 244,
    NUM_TILES_IN_PRIMARY + 248,
    NUM_TILES_IN_PRIMARY + 252
};

const u16 *const gTilesetAnims_EverGrande_Flowers[] = {
    gTilesetAnims_EverGrande_Flowers_Frame0,
    gTilesetAnims_EverGrande_Flowers_Frame1,
    gTilesetAnims_EverGrande_Flowers_Frame2,
    gTilesetAnims_EverGrande_Flowers_Frame3,
    gTilesetAnims_EverGrande_Flowers_Frame4,
    gTilesetAnims_EverGrande_Flowers_Frame5,
    gTilesetAnims_EverGrande_Flowers_Frame6,
    gTilesetAnims_EverGrande_Flowers_Frame7
};

const u16 gTilesetAnims_Dewford_Flag_Frame0[] = INCBIN_U16("data/tilesets/secondary/dewford/anim/flag/0.4bpp");
const u16 gTilesetAnims_Dewford_Flag_Frame1[] = INCBIN_U16("data/tilesets/secondary/dewford/anim/flag/1.4bpp");
const u16 gTilesetAnims_Dewford_Flag_Frame2[] = INCBIN_U16("data/tilesets/secondary/dewford/anim/flag/2.4bpp");
const u16 gTilesetAnims_Dewford_Flag_Frame3[] = INCBIN_U16("data/tilesets/secondary/dewford/anim/flag/3.4bpp");

const u16 *const gTilesetAnims_Dewford_Flag[] = {
    gTilesetAnims_Dewford_Flag_Frame0,
    gTilesetAnims_Dewford_Flag_Frame1,
    gTilesetAnims_Dewford_Flag_Frame2,
    gTilesetAnims_Dewford_Flag_Frame3
};

const u16 gTilesetAnims_BattleFrontierOutsideWest_Flag_Frame0[] = INCBIN_U16("data/tilesets/secondary/battle_frontier_outside_west/anim/flag/0.4bpp");
const u16 gTilesetAnims_BattleFrontierOutsideWest_Flag_Frame1[] = INCBIN_U16("data/tilesets/secondary/battle_frontier_outside_west/anim/flag/1.4bpp");
const u16 gTilesetAnims_BattleFrontierOutsideWest_Flag_Frame2[] = INCBIN_U16("data/tilesets/secondary/battle_frontier_outside_west/anim/flag/2.4bpp");
const u16 gTilesetAnims_BattleFrontierOutsideWest_Flag_Frame3[] = INCBIN_U16("data/tilesets/secondary/battle_frontier_outside_west/anim/flag/3.4bpp");

const u16 *const gTilesetAnims_BattleFrontierOutsideWest_Flag[] = {
    gTilesetAnims_BattleFrontierOutsideWest_Flag_Frame0,
    gTilesetAnims_BattleFrontierOutsideWest_Flag_Frame1,
    gTilesetAnims_BattleFrontierOutsideWest_Flag_Frame2,
    gTilesetAnims_BattleFrontierOutsideWest_Flag_Frame3
};

const u16 gTilesetAnims_BattleFrontierOutsideEast_Flag_Frame0[] = INCBIN_U16("data/tilesets/secondary/battle_frontier_outside_east/anim/flag/0.4bpp");
const u16 gTilesetAnims_BattleFrontierOutsideEast_Flag_Frame1[] = INCBIN_U16("data/tilesets/secondary/battle_frontier_outside_east/anim/flag/1.4bpp");
const u16 gTilesetAnims_BattleFrontierOutsideEast_Flag_Frame2[] = INCBIN_U16("data/tilesets/secondary/battle_frontier_outside_east/anim/flag/2.4bpp");
const u16 gTilesetAnims_BattleFrontierOutsideEast_Flag_Frame3[] = INCBIN_U16("data/tilesets/secondary/battle_frontier_outside_east/anim/flag/3.4bpp");

const u16 *const gTilesetAnims_BattleFrontierOutsideEast_Flag[] = {
    gTilesetAnims_BattleFrontierOutsideEast_Flag_Frame0,
    gTilesetAnims_BattleFrontierOutsideEast_Flag_Frame1,
    gTilesetAnims_BattleFrontierOutsideEast_Flag_Frame2,
    gTilesetAnims_BattleFrontierOutsideEast_Flag_Frame3
};

const u16 gTilesetAnims_Slateport_Balloons_Frame0[] = INCBIN_U16("data/tilesets/secondary/slateport/anim/balloons/0.4bpp");
const u16 gTilesetAnims_Slateport_Balloons_Frame1[] = INCBIN_U16("data/tilesets/secondary/slateport/anim/balloons/1.4bpp");
const u16 gTilesetAnims_Slateport_Balloons_Frame2[] = INCBIN_U16("data/tilesets/secondary/slateport/anim/balloons/2.4bpp");
const u16 gTilesetAnims_Slateport_Balloons_Frame3[] = INCBIN_U16("data/tilesets/secondary/slateport/anim/balloons/3.4bpp");

const u16 *const gTilesetAnims_Slateport_Balloons[] = {
    gTilesetAnims_Slateport_Balloons_Frame0,
    gTilesetAnims_Slateport_Balloons_Frame1,
    gTilesetAnims_Slateport_Balloons_Frame2,
    gTilesetAnims_Slateport_Balloons_Frame3
};

const u16 gTilesetAnims_Building_TvTurnedOn_Frame0[] = INCBIN_U16("data/tilesets/primary/building/anim/tv_turned_on/0.4bpp");
const u16 gTilesetAnims_Building_TvTurnedOn_Frame1[] = INCBIN_U16("data/tilesets/primary/building/anim/tv_turned_on/1.4bpp");

const u16 *const gTilesetAnims_Building_TvTurnedOn[] = {
    gTilesetAnims_Building_TvTurnedOn_Frame0,
    gTilesetAnims_Building_TvTurnedOn_Frame1
};

const u16 gTilesetAnims_SootopolisGym_SideWaterfall_Frame0[] = INCBIN_U16("data/tilesets/secondary/sootopolis_gym/anim/side_waterfall/0.4bpp");
const u16 gTilesetAnims_SootopolisGym_SideWaterfall_Frame1[] = INCBIN_U16("data/tilesets/secondary/sootopolis_gym/anim/side_waterfall/1.4bpp");
const u16 gTilesetAnims_SootopolisGym_SideWaterfall_Frame2[] = INCBIN_U16("data/tilesets/secondary/sootopolis_gym/anim/side_waterfall/2.4bpp");
const u16 gTilesetAnims_SootopolisGym_FrontWaterfall_Frame0[] = INCBIN_U16("data/tilesets/secondary/sootopolis_gym/anim/front_waterfall/0.4bpp");
const u16 gTilesetAnims_SootopolisGym_FrontWaterfall_Frame1[] = INCBIN_U16("data/tilesets/secondary/sootopolis_gym/anim/front_waterfall/1.4bpp");
const u16 gTilesetAnims_SootopolisGym_FrontWaterfall_Frame2[] = INCBIN_U16("data/tilesets/secondary/sootopolis_gym/anim/front_waterfall/2.4bpp");

const u16 *const gTilesetAnims_SootopolisGym_SideWaterfall[] = {
    gTilesetAnims_SootopolisGym_SideWaterfall_Frame0,
    gTilesetAnims_SootopolisGym_SideWaterfall_Frame1,
    gTilesetAnims_SootopolisGym_SideWaterfall_Frame2
};

const u16 *const gTilesetAnims_SootopolisGym_FrontWaterfall[] = {
    gTilesetAnims_SootopolisGym_FrontWaterfall_Frame0,
    gTilesetAnims_SootopolisGym_FrontWaterfall_Frame1,
    gTilesetAnims_SootopolisGym_FrontWaterfall_Frame2
};

const u16 gTilesetAnims_EliteFour_FloorLight_Frame0[] = INCBIN_U16("data/tilesets/secondary/elite_four/anim/floor_light/0.4bpp");
const u16 gTilesetAnims_EliteFour_FloorLight_Frame1[] = INCBIN_U16("data/tilesets/secondary/elite_four/anim/floor_light/1.4bpp");
const u16 gTilesetAnims_EliteFour_WallLights_Frame0[] = INCBIN_U16("data/tilesets/secondary/elite_four/anim/wall_lights/0.4bpp");
const u16 gTilesetAnims_EliteFour_WallLights_Frame1[] = INCBIN_U16("data/tilesets/secondary/elite_four/anim/wall_lights/1.4bpp");
const u16 gTilesetAnims_EliteFour_WallLights_Frame2[] = INCBIN_U16("data/tilesets/secondary/elite_four/anim/wall_lights/2.4bpp");
const u16 gTilesetAnims_EliteFour_WallLights_Frame3[] = INCBIN_U16("data/tilesets/secondary/elite_four/anim/wall_lights/3.4bpp");
const u16 tileset_anims_space_5[16] = {};

const u16 *const gTilesetAnims_EliteFour_WallLights[] = {
    gTilesetAnims_EliteFour_WallLights_Frame0,
    gTilesetAnims_EliteFour_WallLights_Frame1,
    gTilesetAnims_EliteFour_WallLights_Frame2,
    gTilesetAnims_EliteFour_WallLights_Frame3
};

const u16 *const gTilesetAnims_EliteFour_FloorLight[] = {
    gTilesetAnims_EliteFour_FloorLight_Frame0,
    gTilesetAnims_EliteFour_FloorLight_Frame1
};

const u16 gTilesetAnims_MauvilleGym_ElectricGates_Frame0[] = INCBIN_U16("data/tilesets/secondary/mauville_gym/anim/electric_gates/0.4bpp");
const u16 gTilesetAnims_MauvilleGym_ElectricGates_Frame1[] = INCBIN_U16("data/tilesets/secondary/mauville_gym/anim/electric_gates/1.4bpp");
const u16 tileset_anims_space_6[16] = {};

const u16 *const gTilesetAnims_MauvilleGym_ElectricGates[] = {
    gTilesetAnims_MauvilleGym_ElectricGates_Frame0,
    gTilesetAnims_MauvilleGym_ElectricGates_Frame1
};

const u16 gTilesetAnims_BikeShop_BlinkingLights_Frame0[] = INCBIN_U16("data/tilesets/secondary/bike_shop/anim/blinking_lights/0.4bpp");
const u16 gTilesetAnims_BikeShop_BlinkingLights_Frame1[] = INCBIN_U16("data/tilesets/secondary/bike_shop/anim/blinking_lights/1.4bpp");
const u16 tileset_anims_space_7[16] = {};

const u16 *const gTilesetAnims_BikeShop_BlinkingLights[] = {
    gTilesetAnims_BikeShop_BlinkingLights_Frame0,
    gTilesetAnims_BikeShop_BlinkingLights_Frame1
};

const u16 gTilesetAnims_Sootopolis_StormyWater_Frame0[] = INCBIN_U16("data/tilesets/secondary/sootopolis/anim/stormy_water/0_kyogre.4bpp", "data/tilesets/secondary/sootopolis/anim/stormy_water/0_groudon.4bpp");
const u16 gTilesetAnims_Sootopolis_StormyWater_Frame1[] = INCBIN_U16("data/tilesets/secondary/sootopolis/anim/stormy_water/1_kyogre.4bpp", "data/tilesets/secondary/sootopolis/anim/stormy_water/1_groudon.4bpp");
const u16 gTilesetAnims_Sootopolis_StormyWater_Frame2[] = INCBIN_U16("data/tilesets/secondary/sootopolis/anim/stormy_water/2_kyogre.4bpp", "data/tilesets/secondary/sootopolis/anim/stormy_water/2_groudon.4bpp");
const u16 gTilesetAnims_Sootopolis_StormyWater_Frame3[] = INCBIN_U16("data/tilesets/secondary/sootopolis/anim/stormy_water/3_kyogre.4bpp", "data/tilesets/secondary/sootopolis/anim/stormy_water/3_groudon.4bpp");
const u16 gTilesetAnims_Sootopolis_StormyWater_Frame4[] = INCBIN_U16("data/tilesets/secondary/sootopolis/anim/stormy_water/4_kyogre.4bpp", "data/tilesets/secondary/sootopolis/anim/stormy_water/4_groudon.4bpp");
const u16 gTilesetAnims_Sootopolis_StormyWater_Frame5[] = INCBIN_U16("data/tilesets/secondary/sootopolis/anim/stormy_water/5_kyogre.4bpp", "data/tilesets/secondary/sootopolis/anim/stormy_water/5_groudon.4bpp");
const u16 gTilesetAnims_Sootopolis_StormyWater_Frame6[] = INCBIN_U16("data/tilesets/secondary/sootopolis/anim/stormy_water/6_kyogre.4bpp", "data/tilesets/secondary/sootopolis/anim/stormy_water/6_groudon.4bpp");
const u16 gTilesetAnims_Sootopolis_StormyWater_Frame7[] = INCBIN_U16("data/tilesets/secondary/sootopolis/anim/stormy_water/7_kyogre.4bpp", "data/tilesets/secondary/sootopolis/anim/stormy_water/7_groudon.4bpp");
const u16 tileset_anims_space_8[16] = {};

const u16 gTilesetAnims_Unused1_Frame0[] = INCBIN_U16("data/tilesets/secondary/unused_1/0.4bpp");
const u16 gTilesetAnims_Unused1_Frame1[] = INCBIN_U16("data/tilesets/secondary/unused_1/1.4bpp");
const u16 gTilesetAnims_Unused1_Frame2[] = INCBIN_U16("data/tilesets/secondary/unused_1/2.4bpp");
const u16 gTilesetAnims_Unused1_Frame3[] = INCBIN_U16("data/tilesets/secondary/unused_1/3.4bpp");

const u16 *const gTilesetAnims_Sootopolis_StormyWater[] = {
    gTilesetAnims_Sootopolis_StormyWater_Frame0,
    gTilesetAnims_Sootopolis_StormyWater_Frame1,
    gTilesetAnims_Sootopolis_StormyWater_Frame2,
    gTilesetAnims_Sootopolis_StormyWater_Frame3,
    gTilesetAnims_Sootopolis_StormyWater_Frame4,
    gTilesetAnims_Sootopolis_StormyWater_Frame5,
    gTilesetAnims_Sootopolis_StormyWater_Frame6,
    gTilesetAnims_Sootopolis_StormyWater_Frame7
};

const u16 gTilesetAnims_BattlePyramid_Torch_Frame0[] = INCBIN_U16("data/tilesets/secondary/battle_pyramid/anim/torch/0.4bpp");
const u16 gTilesetAnims_BattlePyramid_Torch_Frame1[] = INCBIN_U16("data/tilesets/secondary/battle_pyramid/anim/torch/1.4bpp");
const u16 gTilesetAnims_BattlePyramid_Torch_Frame2[] = INCBIN_U16("data/tilesets/secondary/battle_pyramid/anim/torch/2.4bpp");
const u16 tileset_anims_space_9[16] = {};

const u16 gTilesetAnims_BattlePyramid_StatueShadow_Frame0[] = INCBIN_U16("data/tilesets/secondary/battle_pyramid/anim/statue_shadow/0.4bpp");
const u16 gTilesetAnims_BattlePyramid_StatueShadow_Frame1[] = INCBIN_U16("data/tilesets/secondary/battle_pyramid/anim/statue_shadow/1.4bpp");
const u16 gTilesetAnims_BattlePyramid_StatueShadow_Frame2[] = INCBIN_U16("data/tilesets/secondary/battle_pyramid/anim/statue_shadow/2.4bpp");
const u16 tileset_anims_space_10[7808] = {};

const u16 gTilesetAnims_Unused2_Frame0[] = INCBIN_U16("data/tilesets/secondary/unused_2/0.4bpp");
const u16 tileset_anims_space_11[224] = {};

const u16 gTilesetAnims_Unused2_Frame1[] = INCBIN_U16("data/tilesets/secondary/unused_2/1.4bpp");

const u16 *const gTilesetAnims_BattlePyramid_Torch[] = {
    gTilesetAnims_BattlePyramid_Torch_Frame0,
    gTilesetAnims_BattlePyramid_Torch_Frame1,
    gTilesetAnims_BattlePyramid_Torch_Frame2
};

const u16 *const gTilesetAnims_BattlePyramid_StatueShadow[] = {
    gTilesetAnims_BattlePyramid_StatueShadow_Frame0,
    gTilesetAnims_BattlePyramid_StatueShadow_Frame1,
    gTilesetAnims_BattlePyramid_StatueShadow_Frame2
};

static const u16 *const sTilesetAnims_BattleDomeFloorLightPals[] = {
    gTilesetAnims_BattleDomePals0_0,
    gTilesetAnims_BattleDomePals0_1,
    gTilesetAnims_BattleDomePals0_2,
    gTilesetAnims_BattleDomePals0_3,
};

static void ResetTilesetAnimBuffer(void)
{
    sTilesetDMA3TransferBufferSize = 0;
    CpuFill32(0, sTilesetDMA3TransferBuffer, sizeof sTilesetDMA3TransferBuffer);
}

static void AppendTilesetAnimToBuffer(const u16 *src, u16 tile, u16 size)
{
    if (sTilesetDMA3TransferBufferSize < 20)
    {
        sTilesetDMA3TransferBuffer[sTilesetDMA3TransferBufferSize].src = src;
        sTilesetDMA3TransferBuffer[sTilesetDMA3TransferBufferSize].dest = (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(tile));
        sTilesetDMA3TransferBuffer[sTilesetDMA3TransferBufferSize].size = size;
        sTilesetDMA3TransferBufferSize ++;
    }
}

void TransferTilesetAnimsBuffer(void)
{
    int i;

    for (i = 0; i < sTilesetDMA3TransferBufferSize; i ++)
        DmaCopy16(3, sTilesetDMA3TransferBuffer[i].src, sTilesetDMA3TransferBuffer[i].dest, sTilesetDMA3TransferBuffer[i].size);

    sTilesetDMA3TransferBufferSize = 0;
}

void InitTilesetAnimations(void)
{
    ResetTilesetAnimBuffer();
    _InitPrimaryTilesetAnimation();
    _InitSecondaryTilesetAnimation();
}

void InitSecondaryTilesetAnimation(void)
{
    _InitSecondaryTilesetAnimation();
}

void UpdateTilesetAnimations(void)
{
    ResetTilesetAnimBuffer();
    if (++sPrimaryTilesetAnimCounter >= sPrimaryTilesetAnimCounterMax)
        sPrimaryTilesetAnimCounter = 0;
    if (++sSecondaryTilesetAnimCounter >= sSecondaryTilesetAnimCounterMax)
        sSecondaryTilesetAnimCounter = 0;

    if (sPrimaryTilesetAnimCallback)
        sPrimaryTilesetAnimCallback(sPrimaryTilesetAnimCounter);
    if (sSecondaryTilesetAnimCallback)
        sSecondaryTilesetAnimCallback(sSecondaryTilesetAnimCounter);
}

static void _InitPrimaryTilesetAnimation(void)
{
    sPrimaryTilesetAnimCounter = 0;
    sPrimaryTilesetAnimCounterMax = 0;
    sPrimaryTilesetAnimCallback = NULL;
    if (gMapHeader.mapLayout->primaryTileset && gMapHeader.mapLayout->primaryTileset->callback)
        gMapHeader.mapLayout->primaryTileset->callback();
}

static void _InitSecondaryTilesetAnimation(void)
{
    sSecondaryTilesetAnimCounter = 0;
    sSecondaryTilesetAnimCounterMax = 0;
    sSecondaryTilesetAnimCallback = NULL;
    if (gMapHeader.mapLayout->secondaryTileset && gMapHeader.mapLayout->secondaryTileset->callback)
        gMapHeader.mapLayout->secondaryTileset->callback();
}

void InitTilesetAnim_General(void)
{
    sPrimaryTilesetAnimCounter = 0;
    sPrimaryTilesetAnimCounterMax = 256;
    sPrimaryTilesetAnimCallback = TilesetAnim_General;
}

void InitTilesetAnim_Building(void)
{
    sPrimaryTilesetAnimCounter = 0;
    sPrimaryTilesetAnimCounterMax = 256;
    sPrimaryTilesetAnimCallback = TilesetAnim_Building;
}

static void TilesetAnim_General(u16 timer)
{
    if (timer % 16 == 0)
        QueueAnimTiles_General_Flower(timer / 16);
    if (timer % 16 == 1)
        QueueAnimTiles_General_Water(timer / 16);
    if (timer % 16 == 2)
        QueueAnimTiles_General_SandWaterEdge(timer / 16);
    if (timer % 16 == 3)
        QueueAnimTiles_General_Waterfall(timer / 16);
    if (timer % 16 == 4)
        QueueAnimTiles_General_LandWaterEdge(timer / 16);
}

static void TilesetAnim_Building(u16 timer)
{
    if (timer % 8 == 0)
        QueueAnimTiles_Building_TVTurnedOn(timer / 8);
}

static void QueueAnimTiles_General_Flower(u16 timer)
{
    u16 i = timer % ARRAY_COUNT(gTilesetAnims_General_Flower);
    AppendTilesetAnimToBuffer(gTilesetAnims_General_Flower[i], 508, 4 * TILE_SIZE_4BPP);
}

static void QueueAnimTiles_General_Water(u16 timer)
{
    u8 i = timer % ARRAY_COUNT(gTilesetAnims_General_Water);
    AppendTilesetAnimToBuffer(gTilesetAnims_General_Water[i], 432, 30 * TILE_SIZE_4BPP);
}

static void QueueAnimTiles_General_SandWaterEdge(u16 timer)
{
    u16 i = timer % ARRAY_COUNT(gTilesetAnims_General_SandWaterEdge);
    AppendTilesetAnimToBuffer(gTilesetAnims_General_SandWaterEdge[i], 464, 10 * TILE_SIZE_4BPP);
}

static void QueueAnimTiles_General_Waterfall(u16 timer)
{
    u16 i = timer % ARRAY_COUNT(gTilesetAnims_General_Waterfall);
    AppendTilesetAnimToBuffer(gTilesetAnims_General_Waterfall[i], 496, 6 * TILE_SIZE_4BPP);
}

void InitTilesetAnim_Petalburg(void)
{
    sSecondaryTilesetAnimCounter = 0;
    sSecondaryTilesetAnimCounterMax = sPrimaryTilesetAnimCounterMax;
    sSecondaryTilesetAnimCallback = NULL;
}

void InitTilesetAnim_Rustboro(void)
{
    sSecondaryTilesetAnimCounter = 0;
    sSecondaryTilesetAnimCounterMax = sPrimaryTilesetAnimCounterMax;
    sSecondaryTilesetAnimCallback = TilesetAnim_Rustboro;
}

void InitTilesetAnim_Dewford(void)
{
    sSecondaryTilesetAnimCounter = 0;
    sSecondaryTilesetAnimCounterMax = sPrimaryTilesetAnimCounterMax;
    sSecondaryTilesetAnimCallback = TilesetAnim_Dewford;
}

void InitTilesetAnim_Slateport(void)
{
    sSecondaryTilesetAnimCounter = 0;
    sSecondaryTilesetAnimCounterMax = sPrimaryTilesetAnimCounterMax;
    sSecondaryTilesetAnimCallback = TilesetAnim_Slateport;
}

void InitTilesetAnim_Mauville(void)
{
    sSecondaryTilesetAnimCounter = sPrimaryTilesetAnimCounter;
    sSecondaryTilesetAnimCounterMax = sPrimaryTilesetAnimCounterMax;
    sSecondaryTilesetAnimCallback = TilesetAnim_Mauville;
}

void InitTilesetAnim_Lavaridge(void)
{
    sSecondaryTilesetAnimCounter = 0;
    sSecondaryTilesetAnimCounterMax = sPrimaryTilesetAnimCounterMax;
    sSecondaryTilesetAnimCallback = TilesetAnim_Lavaridge;
}

void InitTilesetAnim_Silveridge(void)
{
    sSecondaryTilesetAnimCounter = 0;
    sSecondaryTilesetAnimCounterMax = sPrimaryTilesetAnimCounterMax;
    sSecondaryTilesetAnimCallback = TilesetAnim_Silveridge;
}

void InitTilesetAnim_Fallarbor(void)
{
    sSecondaryTilesetAnimCounter = 0;
    sSecondaryTilesetAnimCounterMax = sPrimaryTilesetAnimCounterMax;
    sSecondaryTilesetAnimCallback = NULL;
}

void InitTilesetAnim_Fortree(void)
{
    sSecondaryTilesetAnimCounter = 0;
    sSecondaryTilesetAnimCounterMax = sPrimaryTilesetAnimCounterMax;
    sSecondaryTilesetAnimCallback = NULL;
}

void InitTilesetAnim_Lilycove(void)
{
    sSecondaryTilesetAnimCounter = 0;
    sSecondaryTilesetAnimCounterMax = sPrimaryTilesetAnimCounterMax;
    sSecondaryTilesetAnimCallback = NULL;
}

void InitTilesetAnim_Mossdeep(void)
{
    sSecondaryTilesetAnimCounter = 0;
    sSecondaryTilesetAnimCounterMax = sPrimaryTilesetAnimCounterMax;
    sSecondaryTilesetAnimCallback = NULL;
}

void InitTilesetAnim_EverGrande(void)
{
    sSecondaryTilesetAnimCounter = 0;
    sSecondaryTilesetAnimCounterMax = sPrimaryTilesetAnimCounterMax;
    sSecondaryTilesetAnimCallback = TilesetAnim_EverGrande;
}

void InitTilesetAnim_Pacifidlog(void)
{
    sSecondaryTilesetAnimCounter = sPrimaryTilesetAnimCounter;
    sSecondaryTilesetAnimCounterMax = sPrimaryTilesetAnimCounterMax;
    sSecondaryTilesetAnimCallback = TilesetAnim_Pacifidlog;
}

void InitTilesetAnim_Sootopolis(void)
{
    sSecondaryTilesetAnimCounter = 0;
    sSecondaryTilesetAnimCounterMax = sPrimaryTilesetAnimCounterMax;
    sSecondaryTilesetAnimCallback = TilesetAnim_Sootopolis;
}

void InitTilesetAnim_BattleFrontierOutsideWest(void)
{
    sSecondaryTilesetAnimCounter = 0;
    sSecondaryTilesetAnimCounterMax = sPrimaryTilesetAnimCounterMax;
    sSecondaryTilesetAnimCallback = TilesetAnim_BattleFrontierOutsideWest;
}

void InitTilesetAnim_BattleFrontierOutsideEast(void)
{
    sSecondaryTilesetAnimCounter = 0;
    sSecondaryTilesetAnimCounterMax = sPrimaryTilesetAnimCounterMax;
    sSecondaryTilesetAnimCallback = TilesetAnim_BattleFrontierOutsideEast;
}

void InitTilesetAnim_Underwater(void)
{
    sSecondaryTilesetAnimCounter = 0;
    sSecondaryTilesetAnimCounterMax = 128;
    sSecondaryTilesetAnimCallback = TilesetAnim_Underwater;
}

void InitTilesetAnim_SootopolisGym(void)
{
    sSecondaryTilesetAnimCounter = 0;
    sSecondaryTilesetAnimCounterMax = 240;
    sSecondaryTilesetAnimCallback = TilesetAnim_SootopolisGym;
}

void InitTilesetAnim_Cave(void)
{
    sSecondaryTilesetAnimCounter = 0;
    sSecondaryTilesetAnimCounterMax = sPrimaryTilesetAnimCounterMax;
    sSecondaryTilesetAnimCallback = TilesetAnim_Cave;
}

void InitTilesetAnim_EliteFour(void)
{
    sSecondaryTilesetAnimCounter = 0;
    sSecondaryTilesetAnimCounterMax = 128;
    sSecondaryTilesetAnimCallback = TilesetAnim_EliteFour;
}

void InitTilesetAnim_MauvilleGym(void)
{
    sSecondaryTilesetAnimCounter = 0;
    sSecondaryTilesetAnimCounterMax = sPrimaryTilesetAnimCounterMax;
    sSecondaryTilesetAnimCallback = TilesetAnim_MauvilleGym;
}

void InitTilesetAnim_BikeShop(void)
{
    sSecondaryTilesetAnimCounter = 0;
    sSecondaryTilesetAnimCounterMax = sPrimaryTilesetAnimCounterMax;
    sSecondaryTilesetAnimCallback = TilesetAnim_BikeShop;
}

void InitTilesetAnim_BattlePyramid(void)
{
    sSecondaryTilesetAnimCounter = 0;
    sSecondaryTilesetAnimCounterMax = sPrimaryTilesetAnimCounterMax;
    sSecondaryTilesetAnimCallback = TilesetAnim_BattlePyramid;
}

void InitTilesetAnim_BattleDome(void)
{
    sSecondaryTilesetAnimCounter = 0;
    sSecondaryTilesetAnimCounterMax = sPrimaryTilesetAnimCounterMax;
    sSecondaryTilesetAnimCallback = TilesetAnim_BattleDome;
}

static void TilesetAnim_Rustboro(u16 timer)
{
    if (timer % 8 == 0)
    {
        QueueAnimTiles_Rustboro_WindyWater(timer / 8, 0);
        QueueAnimTiles_Rustboro_Fountain(timer / 8);
    }
    if (timer % 8 == 1)
        QueueAnimTiles_Rustboro_WindyWater(timer / 8, 1);
    if (timer % 8 == 2)
        QueueAnimTiles_Rustboro_WindyWater(timer / 8, 2);
    if (timer % 8 == 3)
        QueueAnimTiles_Rustboro_WindyWater(timer / 8, 3);
    if (timer % 8 == 4)
        QueueAnimTiles_Rustboro_WindyWater(timer / 8, 4);
    if (timer % 8 == 5)
        QueueAnimTiles_Rustboro_WindyWater(timer / 8, 5);
    if (timer % 8 == 6)
        QueueAnimTiles_Rustboro_WindyWater(timer / 8, 6);
    if (timer % 8 == 7)
        QueueAnimTiles_Rustboro_WindyWater(timer / 8, 7);
}

static void TilesetAnim_Dewford(u16 timer)
{
    if (timer % 8 == 0)
        QueueAnimTiles_Dewford_Flag(timer / 8);
}

static void TilesetAnim_Slateport(u16 timer)
{
    if (timer % 16 == 0)
        QueueAnimTiles_Slateport_Balloons(timer / 16);
}

static void TilesetAnim_Mauville(u16 timer)
{
    if (timer % 8 == 0)
        QueueAnimTiles_Mauville_Flowers(timer / 8, 0);
    if (timer % 8 == 1)
        QueueAnimTiles_Mauville_Flowers(timer / 8, 1);
    if (timer % 8 == 2)
        QueueAnimTiles_Mauville_Flowers(timer / 8, 2);
    if (timer % 8 == 3)
        QueueAnimTiles_Mauville_Flowers(timer / 8, 3);
    if (timer % 8 == 4)
        QueueAnimTiles_Mauville_Flowers(timer / 8, 4);
    if (timer % 8 == 5)
        QueueAnimTiles_Mauville_Flowers(timer / 8, 5);
    if (timer % 8 == 6)
        QueueAnimTiles_Mauville_Flowers(timer / 8, 6);
    if (timer % 8 == 7)
        QueueAnimTiles_Mauville_Flowers(timer / 8, 7);
}

static void TilesetAnim_Lavaridge(u16 timer)
{
    if (timer % 16 == 0)
        QueueAnimTiles_Lavaridge_Steam(timer / 16);
    if (timer % 16 == 1)
        QueueAnimTiles_Lavaridge_Lava(timer / 16);
}

static void TilesetAnim_Silveridge(u16 timer)
{
    if (timer % 16 == 0)
        QueueAnimTiles_Silveridge_Chimney(timer / 16);
}

static void TilesetAnim_EverGrande(u16 timer)
{
    if (timer % 8 == 0)
        QueueAnimTiles_EverGrande_Flowers(timer / 8, 0);
    if (timer % 8 == 1)
        QueueAnimTiles_EverGrande_Flowers(timer / 8, 1);
    if (timer % 8 == 2)
        QueueAnimTiles_EverGrande_Flowers(timer / 8, 2);
    if (timer % 8 == 3)
        QueueAnimTiles_EverGrande_Flowers(timer / 8, 3);
    if (timer % 8 == 4)
        QueueAnimTiles_EverGrande_Flowers(timer / 8, 4);
    if (timer % 8 == 5)
        QueueAnimTiles_EverGrande_Flowers(timer / 8, 5);
    if (timer % 8 == 6)
        QueueAnimTiles_EverGrande_Flowers(timer / 8, 6);
    if (timer % 8 == 7)
        QueueAnimTiles_EverGrande_Flowers(timer / 8, 7);
}

static void TilesetAnim_Pacifidlog(u16 timer)
{
    if (timer % 16 == 0)
        QueueAnimTiles_Pacifidlog_LogBridges(timer / 16);
    if (timer % 16 == 1)
        QueueAnimTiles_Pacifidlog_WaterCurrents(timer / 16);
}

static void TilesetAnim_Sootopolis(u16 timer)
{
    if (timer % 16 == 0)
        QueueAnimTiles_Sootopolis_StormyWater(timer / 16);
}

static void TilesetAnim_Underwater(u16 timer)
{
    if (timer % 16 == 0)
        QueueAnimTiles_Underwater_Seaweed(timer / 16);
}

static void TilesetAnim_Cave(u16 timer)
{
    if (timer % 16 == 1)
        QueueAnimTiles_Cave_Lava(timer / 16);
}

static void TilesetAnim_BattleFrontierOutsideWest(u16 timer)
{
    if (timer % 8 == 0)
        QueueAnimTiles_BattleFrontierOutsideWest_Flag(timer / 8);
}

static void TilesetAnim_BattleFrontierOutsideEast(u16 timer)
{
    if (timer % 8 == 0)
        QueueAnimTiles_BattleFrontierOutsideEast_Flag(timer / 8);
}

static void QueueAnimTiles_General_LandWaterEdge(u16 timer)
{
    u16 i = timer % ARRAY_COUNT(gTilesetAnims_General_LandWaterEdge);
    AppendTilesetAnimToBuffer(gTilesetAnims_General_LandWaterEdge[i], 480, 10 * TILE_SIZE_4BPP);
}

static void QueueAnimTiles_Lavaridge_Steam(u8 timer)
{
    u8 i = timer % ARRAY_COUNT(gTilesetAnims_Lavaridge_Steam);
    AppendTilesetAnimToBuffer(gTilesetAnims_Lavaridge_Steam[i], NUM_TILES_IN_PRIMARY + 288, 4 * TILE_SIZE_4BPP);

    i = (timer + 2) % (int)ARRAY_COUNT(gTilesetAnims_Lavaridge_Steam);
    AppendTilesetAnimToBuffer(gTilesetAnims_Lavaridge_Steam[i], NUM_TILES_IN_PRIMARY + 292, 4 * TILE_SIZE_4BPP);
}

static void QueueAnimTiles_Silveridge_Chimney(u8 timer)
{
    u8 i = timer % ARRAY_COUNT(gTilesetAnims_Silveridge_Chimney);
    AppendTilesetAnimToBuffer(gTilesetAnims_Silveridge_Chimney[i], NUM_TILES_IN_PRIMARY_TOKU + 42, 4 * TILE_SIZE_4BPP);

    // i = (timer + 2) % (int)ARRAY_COUNT(gTilesetAnims_Silveridge_Chimney);
    // AppendTilesetAnimToBuffer(gTilesetAnims_Silveridge_Chimney[i], NUM_TILES_IN_PRIMARY_TOKU + 292, 4 * TILE_SIZE_4BPP);
}

static void QueueAnimTiles_Pacifidlog_LogBridges(u8 timer)
{
    u8 i = timer % ARRAY_COUNT(gTilesetAnims_Pacifidlog_LogBridges);
    AppendTilesetAnimToBuffer(gTilesetAnims_Pacifidlog_LogBridges[i], NUM_TILES_IN_PRIMARY + 464, 30 * TILE_SIZE_4BPP);
}

static void QueueAnimTiles_Underwater_Seaweed(u8 timer)
{
    u8 i = timer % ARRAY_COUNT(gTilesetAnims_Underwater_Seaweed);
    AppendTilesetAnimToBuffer(gTilesetAnims_Underwater_Seaweed[i], NUM_TILES_IN_PRIMARY + 496, 4 * TILE_SIZE_4BPP);
}

static void QueueAnimTiles_Pacifidlog_WaterCurrents(u8 timer)
{
    u8 i = timer % ARRAY_COUNT(gTilesetAnims_Pacifidlog_WaterCurrents);
    AppendTilesetAnimToBuffer(gTilesetAnims_Pacifidlog_WaterCurrents[i], NUM_TILES_IN_PRIMARY + 496, 8 * TILE_SIZE_4BPP);
}

static void QueueAnimTiles_Mauville_Flowers(u16 timer_div, u8 timer_mod)
{
    timer_div -= timer_mod;
    if (timer_div < min(ARRAY_COUNT(gTilesetAnims_Mauville_Flower1), ARRAY_COUNT(gTilesetAnims_Mauville_Flower2)))
    {
        timer_div %= min(ARRAY_COUNT(gTilesetAnims_Mauville_Flower1), ARRAY_COUNT(gTilesetAnims_Mauville_Flower2));
        AppendTilesetAnimToBuffer(gTilesetAnims_Mauville_Flower1[timer_div], gTilesetAnims_Mauville_Flower1_VDests[timer_mod], 4 * TILE_SIZE_4BPP);
        AppendTilesetAnimToBuffer(gTilesetAnims_Mauville_Flower2[timer_div], gTilesetAnims_Mauville_Flower2_VDests[timer_mod], 4 * TILE_SIZE_4BPP);
    }
    else
    {
        timer_div %= min(ARRAY_COUNT(gTilesetAnims_Mauville_Flower1_B), ARRAY_COUNT(gTilesetAnims_Mauville_Flower2_B));
        AppendTilesetAnimToBuffer(gTilesetAnims_Mauville_Flower1_B[timer_div], gTilesetAnims_Mauville_Flower1_VDests[timer_mod], 4 * TILE_SIZE_4BPP);
        AppendTilesetAnimToBuffer(gTilesetAnims_Mauville_Flower2_B[timer_div], gTilesetAnims_Mauville_Flower2_VDests[timer_mod], 4 * TILE_SIZE_4BPP);
    }
}

static void QueueAnimTiles_Rustboro_WindyWater(u16 timer_div, u8 timer_mod)
{
    timer_div -= timer_mod;
    timer_div %= ARRAY_COUNT(gTilesetAnims_Rustboro_WindyWater);
    if (gTilesetAnims_Rustboro_WindyWater[timer_div])
        AppendTilesetAnimToBuffer(gTilesetAnims_Rustboro_WindyWater[timer_div], gTilesetAnims_Rustboro_WindyWater_VDests[timer_mod], 4 * TILE_SIZE_4BPP);
}

static void QueueAnimTiles_Rustboro_Fountain(u16 timer)
{
    u16 i = timer % ARRAY_COUNT(gTilesetAnims_Rustboro_Fountain);
    AppendTilesetAnimToBuffer(gTilesetAnims_Rustboro_Fountain[i], NUM_TILES_IN_PRIMARY + 448, 4 * TILE_SIZE_4BPP);
}

static void QueueAnimTiles_Lavaridge_Lava(u16 timer)
{
    u16 i = timer % ARRAY_COUNT(gTilesetAnims_Lavaridge_Cave_Lava);
    AppendTilesetAnimToBuffer(gTilesetAnims_Lavaridge_Cave_Lava[i], NUM_TILES_IN_PRIMARY + 160, 4 * TILE_SIZE_4BPP);
}

static void QueueAnimTiles_EverGrande_Flowers(u16 timer_div, u8 timer_mod)
{
    timer_div -= timer_mod;
    timer_div %= ARRAY_COUNT(gTilesetAnims_EverGrande_Flowers);

    AppendTilesetAnimToBuffer(gTilesetAnims_EverGrande_Flowers[timer_div], gTilesetAnims_EverGrande_VDests[timer_mod], 4 * TILE_SIZE_4BPP);
}

static void QueueAnimTiles_Cave_Lava(u16 timer)
{
    u16 i = timer % ARRAY_COUNT(gTilesetAnims_Lavaridge_Cave_Lava);
    AppendTilesetAnimToBuffer(gTilesetAnims_Lavaridge_Cave_Lava[i], NUM_TILES_IN_PRIMARY + 416, 4 * TILE_SIZE_4BPP);
}

static void QueueAnimTiles_Dewford_Flag(u16 timer)
{
    u16 i = timer % ARRAY_COUNT(gTilesetAnims_Dewford_Flag);
    AppendTilesetAnimToBuffer(gTilesetAnims_Dewford_Flag[i], NUM_TILES_IN_PRIMARY + 170, 6 * TILE_SIZE_4BPP);
}

static void QueueAnimTiles_BattleFrontierOutsideWest_Flag(u16 timer)
{
    u16 i = timer % ARRAY_COUNT(gTilesetAnims_BattleFrontierOutsideWest_Flag);
    AppendTilesetAnimToBuffer(gTilesetAnims_BattleFrontierOutsideWest_Flag[i], NUM_TILES_IN_PRIMARY + 218, 6 * TILE_SIZE_4BPP);
}

static void QueueAnimTiles_BattleFrontierOutsideEast_Flag(u16 timer)
{
    u16 i = timer % ARRAY_COUNT(gTilesetAnims_BattleFrontierOutsideEast_Flag);
    AppendTilesetAnimToBuffer(gTilesetAnims_BattleFrontierOutsideEast_Flag[i], NUM_TILES_IN_PRIMARY + 218, 6 * TILE_SIZE_4BPP);
}

static void QueueAnimTiles_Slateport_Balloons(u16 timer)
{
    u16 i = timer % ARRAY_COUNT(gTilesetAnims_Slateport_Balloons);
    AppendTilesetAnimToBuffer(gTilesetAnims_Slateport_Balloons[i], NUM_TILES_IN_PRIMARY + 224, 4 * TILE_SIZE_4BPP);
}

static void TilesetAnim_MauvilleGym(u16 timer)
{
    if (timer % 2 == 0)
        QueueAnimTiles_MauvilleGym_ElectricGates(timer / 2);
}

static void TilesetAnim_SootopolisGym(u16 timer)
{
    if (timer % 8 == 0)
        QueueAnimTiles_SootopolisGym_Waterfalls(timer / 8);
}

static void TilesetAnim_EliteFour(u16 timer)
{
    if (timer % 64 == 1)
        QueueAnimTiles_EliteFour_GroundLights(timer / 64);
    if (timer % 8 == 1)
        QueueAnimTiles_EliteFour_WallLights(timer / 8);
}

static void TilesetAnim_BikeShop(u16 timer)
{
    if (timer % 4 == 0)
        QueueAnimTiles_BikeShop_BlinkingLights(timer / 4);
}

static void TilesetAnim_BattlePyramid(u16 timer)
{
    if (timer % 8 == 0)
    {
        QueueAnimTiles_BattlePyramid_Torch(timer / 8);
        QueueAnimTiles_BattlePyramid_StatueShadow(timer / 8);
    }
}

static void TilesetAnim_BattleDome(u16 timer)
{
    if (timer % 4 == 0)
        BlendAnimPalette_BattleDome_FloorLights(timer / 4);
}

static void TilesetAnim_BattleDome2(u16 timer)
{
    if (timer % 4 == 0)
        BlendAnimPalette_BattleDome_FloorLightsNoBlend(timer / 4);
}

static void QueueAnimTiles_Building_TVTurnedOn(u16 timer)
{
    u16 i = timer % ARRAY_COUNT(gTilesetAnims_Building_TvTurnedOn);
    AppendTilesetAnimToBuffer(gTilesetAnims_Building_TvTurnedOn[i], 496, 4 * TILE_SIZE_4BPP);
}

static void QueueAnimTiles_SootopolisGym_Waterfalls(u16 timer)
{
    u16 i = timer % min(ARRAY_COUNT(gTilesetAnims_SootopolisGym_SideWaterfall), ARRAY_COUNT(gTilesetAnims_SootopolisGym_FrontWaterfall));
    AppendTilesetAnimToBuffer(gTilesetAnims_SootopolisGym_SideWaterfall[i], NUM_TILES_IN_PRIMARY + 496, 12 * TILE_SIZE_4BPP);
    AppendTilesetAnimToBuffer(gTilesetAnims_SootopolisGym_FrontWaterfall[i], NUM_TILES_IN_PRIMARY + 464, 20 * TILE_SIZE_4BPP);
}

static void QueueAnimTiles_EliteFour_WallLights(u16 timer)
{
    u16 i = timer % ARRAY_COUNT(gTilesetAnims_EliteFour_WallLights);
    AppendTilesetAnimToBuffer(gTilesetAnims_EliteFour_WallLights[i], NUM_TILES_IN_PRIMARY + 504, 1 * TILE_SIZE_4BPP);
}

static void QueueAnimTiles_EliteFour_GroundLights(u16 timer)
{
    u16 i = timer % ARRAY_COUNT(gTilesetAnims_EliteFour_FloorLight);
    AppendTilesetAnimToBuffer(gTilesetAnims_EliteFour_FloorLight[i], NUM_TILES_IN_PRIMARY + 480, 4 * TILE_SIZE_4BPP);
}

static void QueueAnimTiles_MauvilleGym_ElectricGates(u16 timer)
{
    u16 i = timer % ARRAY_COUNT(gTilesetAnims_MauvilleGym_ElectricGates);
    AppendTilesetAnimToBuffer(gTilesetAnims_MauvilleGym_ElectricGates[i], NUM_TILES_IN_PRIMARY + 144, 16 * TILE_SIZE_4BPP);
}

static void QueueAnimTiles_BikeShop_BlinkingLights(u16 timer)
{
    u16 i = timer % ARRAY_COUNT(gTilesetAnims_BikeShop_BlinkingLights);
    AppendTilesetAnimToBuffer(gTilesetAnims_BikeShop_BlinkingLights[i], NUM_TILES_IN_PRIMARY + 496, 9 * TILE_SIZE_4BPP);
}

static void QueueAnimTiles_Sootopolis_StormyWater(u16 timer)
{
    u16 i = timer % ARRAY_COUNT(gTilesetAnims_Sootopolis_StormyWater);
    AppendTilesetAnimToBuffer(gTilesetAnims_Sootopolis_StormyWater[i], NUM_TILES_IN_PRIMARY + 240, 96 * TILE_SIZE_4BPP);
}

static void QueueAnimTiles_BattlePyramid_Torch(u16 timer)
{
    u16 i = timer % ARRAY_COUNT(gTilesetAnims_BattlePyramid_Torch);
    AppendTilesetAnimToBuffer(gTilesetAnims_BattlePyramid_Torch[i], NUM_TILES_IN_PRIMARY + 151, 8 * TILE_SIZE_4BPP);
}

static void QueueAnimTiles_BattlePyramid_StatueShadow(u16 timer)
{
    u16 i = timer % ARRAY_COUNT(gTilesetAnims_BattlePyramid_StatueShadow);
    AppendTilesetAnimToBuffer(gTilesetAnims_BattlePyramid_StatueShadow[i], NUM_TILES_IN_PRIMARY + 135, 8 * TILE_SIZE_4BPP);
}

static void BlendAnimPalette_BattleDome_FloorLights(u16 timer)
{
    CpuCopy16(sTilesetAnims_BattleDomeFloorLightPals[timer % ARRAY_COUNT(sTilesetAnims_BattleDomeFloorLightPals)], &gPlttBufferUnfaded[BG_PLTT_ID(8)], PLTT_SIZE_4BPP);
    BlendPalette(BG_PLTT_ID(8), 16, gPaletteFade.y, gPaletteFade.blendColor & 0x7FFF);
    if ((u8)FindTaskIdByFunc(Task_BattleTransition_Intro) != TASK_NONE)
    {
        sSecondaryTilesetAnimCallback = TilesetAnim_BattleDome2;
        sSecondaryTilesetAnimCounterMax = 32;
    }
}

static void BlendAnimPalette_BattleDome_FloorLightsNoBlend(u16 timer)
{
    CpuCopy16(sTilesetAnims_BattleDomeFloorLightPals[timer % ARRAY_COUNT(sTilesetAnims_BattleDomeFloorLightPals)], &gPlttBufferUnfaded[BG_PLTT_ID(8)], PLTT_SIZE_4BPP);
    if ((u8)FindTaskIdByFunc(Task_BattleTransition_Intro) == TASK_NONE)
    {
        BlendPalette(BG_PLTT_ID(8), 16, gPaletteFade.y, gPaletteFade.blendColor & 0x7FFF);
        if (!--sSecondaryTilesetAnimCounterMax)
            sSecondaryTilesetAnimCallback = NULL;
    }
}

// Custom shit

const u16 gTilesetAnims_PorytilesPrimaryTutorial_Sea_Frame0[] = INCBIN_U16("data/tilesets/primary/porytiles_primary_tutorial/anim/sea/00.4bpp");
const u16 gTilesetAnims_PorytilesPrimaryTutorial_Sea_Frame1[] = INCBIN_U16("data/tilesets/primary/porytiles_primary_tutorial/anim/sea/01.4bpp");
const u16 gTilesetAnims_PorytilesPrimaryTutorial_Sea_Frame2[] = INCBIN_U16("data/tilesets/primary/porytiles_primary_tutorial/anim/sea/02.4bpp");
const u16 gTilesetAnims_PorytilesPrimaryTutorial_Sea_Frame3[] = INCBIN_U16("data/tilesets/primary/porytiles_primary_tutorial/anim/sea/03.4bpp");
const u16 gTilesetAnims_PorytilesPrimaryTutorial_Sea_Frame4[] = INCBIN_U16("data/tilesets/primary/porytiles_primary_tutorial/anim/sea/04.4bpp");
const u16 gTilesetAnims_PorytilesPrimaryTutorial_Sea_Frame5[] = INCBIN_U16("data/tilesets/primary/porytiles_primary_tutorial/anim/sea/05.4bpp");
const u16 gTilesetAnims_PorytilesPrimaryTutorial_Sea_Frame6[] = INCBIN_U16("data/tilesets/primary/porytiles_primary_tutorial/anim/sea/06.4bpp");
const u16 gTilesetAnims_PorytilesPrimaryTutorial_Sea_Frame7[] = INCBIN_U16("data/tilesets/primary/porytiles_primary_tutorial/anim/sea/07.4bpp");

const u16 gTilesetAnims_PorytilesPrimaryTutorial_SeaDark_Frame0[] = INCBIN_U16("data/tilesets/primary/porytiles_primary_tutorial/anim/sea_dark/00.4bpp");
const u16 gTilesetAnims_PorytilesPrimaryTutorial_SeaDark_Frame1[] = INCBIN_U16("data/tilesets/primary/porytiles_primary_tutorial/anim/sea_dark/01.4bpp");
const u16 gTilesetAnims_PorytilesPrimaryTutorial_SeaDark_Frame2[] = INCBIN_U16("data/tilesets/primary/porytiles_primary_tutorial/anim/sea_dark/02.4bpp");
const u16 gTilesetAnims_PorytilesPrimaryTutorial_SeaDark_Frame3[] = INCBIN_U16("data/tilesets/primary/porytiles_primary_tutorial/anim/sea_dark/03.4bpp");
const u16 gTilesetAnims_PorytilesPrimaryTutorial_SeaDark_Frame4[] = INCBIN_U16("data/tilesets/primary/porytiles_primary_tutorial/anim/sea_dark/04.4bpp");
const u16 gTilesetAnims_PorytilesPrimaryTutorial_SeaDark_Frame5[] = INCBIN_U16("data/tilesets/primary/porytiles_primary_tutorial/anim/sea_dark/05.4bpp");
const u16 gTilesetAnims_PorytilesPrimaryTutorial_SeaDark_Frame6[] = INCBIN_U16("data/tilesets/primary/porytiles_primary_tutorial/anim/sea_dark/06.4bpp");
const u16 gTilesetAnims_PorytilesPrimaryTutorial_SeaDark_Frame7[] = INCBIN_U16("data/tilesets/primary/porytiles_primary_tutorial/anim/sea_dark/07.4bpp");

const u16 gTilesetAnims_PorytilesPrimaryTutorial_SeaDarkCorner_Frame0[] = INCBIN_U16("data/tilesets/primary/porytiles_primary_tutorial/anim/sea_dark_light/00.4bpp");
const u16 gTilesetAnims_PorytilesPrimaryTutorial_SeaDarkCorner_Frame1[] = INCBIN_U16("data/tilesets/primary/porytiles_primary_tutorial/anim/sea_dark_light/01.4bpp");
const u16 gTilesetAnims_PorytilesPrimaryTutorial_SeaDarkCorner_Frame2[] = INCBIN_U16("data/tilesets/primary/porytiles_primary_tutorial/anim/sea_dark_light/02.4bpp");
const u16 gTilesetAnims_PorytilesPrimaryTutorial_SeaDarkCorner_Frame3[] = INCBIN_U16("data/tilesets/primary/porytiles_primary_tutorial/anim/sea_dark_light/03.4bpp");
const u16 gTilesetAnims_PorytilesPrimaryTutorial_SeaDarkCorner_Frame4[] = INCBIN_U16("data/tilesets/primary/porytiles_primary_tutorial/anim/sea_dark_light/04.4bpp");
const u16 gTilesetAnims_PorytilesPrimaryTutorial_SeaDarkCorner_Frame5[] = INCBIN_U16("data/tilesets/primary/porytiles_primary_tutorial/anim/sea_dark_light/05.4bpp");
const u16 gTilesetAnims_PorytilesPrimaryTutorial_SeaDarkCorner_Frame6[] = INCBIN_U16("data/tilesets/primary/porytiles_primary_tutorial/anim/sea_dark_light/06.4bpp");
const u16 gTilesetAnims_PorytilesPrimaryTutorial_SeaDarkCorner_Frame7[] = INCBIN_U16("data/tilesets/primary/porytiles_primary_tutorial/anim/sea_dark_light/07.4bpp");

const u16 gTilesetAnims_PorytilesPrimaryTutorial_Beach_Frame0[] = INCBIN_U16("data/tilesets/primary/porytiles_primary_tutorial/anim/beach/00.4bpp");
const u16 gTilesetAnims_PorytilesPrimaryTutorial_Beach_Frame1[] = INCBIN_U16("data/tilesets/primary/porytiles_primary_tutorial/anim/beach/01.4bpp");
const u16 gTilesetAnims_PorytilesPrimaryTutorial_Beach_Frame2[] = INCBIN_U16("data/tilesets/primary/porytiles_primary_tutorial/anim/beach/02.4bpp");
const u16 gTilesetAnims_PorytilesPrimaryTutorial_Beach_Frame3[] = INCBIN_U16("data/tilesets/primary/porytiles_primary_tutorial/anim/beach/03.4bpp");
const u16 gTilesetAnims_PorytilesPrimaryTutorial_Beach_Frame4[] = INCBIN_U16("data/tilesets/primary/porytiles_primary_tutorial/anim/beach/04.4bpp");
const u16 gTilesetAnims_PorytilesPrimaryTutorial_Beach_Frame5[] = INCBIN_U16("data/tilesets/primary/porytiles_primary_tutorial/anim/beach/05.4bpp");
const u16 gTilesetAnims_PorytilesPrimaryTutorial_Beach_Frame6[] = INCBIN_U16("data/tilesets/primary/porytiles_primary_tutorial/anim/beach/06.4bpp");
const u16 gTilesetAnims_PorytilesPrimaryTutorial_Beach_Frame7[] = INCBIN_U16("data/tilesets/primary/porytiles_primary_tutorial/anim/beach/07.4bpp");

const u16 gTilesetAnims_PorytilesPrimaryTutorial_SeaRock_Frame0[] = INCBIN_U16("data/tilesets/primary/porytiles_primary_tutorial/anim/sea_rock/00.4bpp");
const u16 gTilesetAnims_PorytilesPrimaryTutorial_SeaRock_Frame1[] = INCBIN_U16("data/tilesets/primary/porytiles_primary_tutorial/anim/sea_rock/01.4bpp");
const u16 gTilesetAnims_PorytilesPrimaryTutorial_SeaRock_Frame2[] = INCBIN_U16("data/tilesets/primary/porytiles_primary_tutorial/anim/sea_rock/02.4bpp");
const u16 gTilesetAnims_PorytilesPrimaryTutorial_SeaRock_Frame3[] = INCBIN_U16("data/tilesets/primary/porytiles_primary_tutorial/anim/sea_rock/03.4bpp");
const u16 gTilesetAnims_PorytilesPrimaryTutorial_SeaRock_Frame4[] = INCBIN_U16("data/tilesets/primary/porytiles_primary_tutorial/anim/sea_rock/04.4bpp");
const u16 gTilesetAnims_PorytilesPrimaryTutorial_SeaRock_Frame5[] = INCBIN_U16("data/tilesets/primary/porytiles_primary_tutorial/anim/sea_rock/05.4bpp");
const u16 gTilesetAnims_PorytilesPrimaryTutorial_SeaRock_Frame6[] = INCBIN_U16("data/tilesets/primary/porytiles_primary_tutorial/anim/sea_rock/06.4bpp");
const u16 gTilesetAnims_PorytilesPrimaryTutorial_SeaRock_Frame7[] = INCBIN_U16("data/tilesets/primary/porytiles_primary_tutorial/anim/sea_rock/07.4bpp");

const u16 gTilesetAnims_PorytilesPrimaryTutorial_FlowerDandelionWhite_Frame0[] = INCBIN_U16("data/tilesets/primary/porytiles_primary_tutorial/anim/flower_dandelion_white/00.4bpp");
const u16 gTilesetAnims_PorytilesPrimaryTutorial_FlowerDandelionWhite_Frame1[] = INCBIN_U16("data/tilesets/primary/porytiles_primary_tutorial/anim/flower_dandelion_white/01.4bpp");
const u16 gTilesetAnims_PorytilesPrimaryTutorial_FlowerDandelionWhite_Frame2[] = INCBIN_U16("data/tilesets/primary/porytiles_primary_tutorial/anim/flower_dandelion_white/02.4bpp");
const u16 gTilesetAnims_PorytilesPrimaryTutorial_FlowerDandelionWhite_Frame3[] = INCBIN_U16("data/tilesets/primary/porytiles_primary_tutorial/anim/flower_dandelion_white/03.4bpp");
const u16 gTilesetAnims_PorytilesPrimaryTutorial_FlowerDandelionWhite_Frame4[] = INCBIN_U16("data/tilesets/primary/porytiles_primary_tutorial/anim/flower_dandelion_white/04.4bpp");

const u16 gTilesetAnims_PorytilesPrimaryTutorial_FlowerDandelionYellow_Frame0[] = INCBIN_U16("data/tilesets/primary/porytiles_primary_tutorial/anim/flower_dandelion_yellow/00.4bpp");
const u16 gTilesetAnims_PorytilesPrimaryTutorial_FlowerDandelionYellow_Frame1[] = INCBIN_U16("data/tilesets/primary/porytiles_primary_tutorial/anim/flower_dandelion_yellow/01.4bpp");
const u16 gTilesetAnims_PorytilesPrimaryTutorial_FlowerDandelionYellow_Frame2[] = INCBIN_U16("data/tilesets/primary/porytiles_primary_tutorial/anim/flower_dandelion_yellow/02.4bpp");

const u16 *const gTilesetAnims_PorytilesPrimaryTutorial_Sea[] = {
    gTilesetAnims_PorytilesPrimaryTutorial_Sea_Frame0,
    gTilesetAnims_PorytilesPrimaryTutorial_Sea_Frame1,
    gTilesetAnims_PorytilesPrimaryTutorial_Sea_Frame2,
    gTilesetAnims_PorytilesPrimaryTutorial_Sea_Frame3,
    gTilesetAnims_PorytilesPrimaryTutorial_Sea_Frame4,
    gTilesetAnims_PorytilesPrimaryTutorial_Sea_Frame5,
    gTilesetAnims_PorytilesPrimaryTutorial_Sea_Frame6,
    gTilesetAnims_PorytilesPrimaryTutorial_Sea_Frame7,
};

const u16 *const gTilesetAnims_PorytilesPrimaryTutorial_SeaDark[] = {
    gTilesetAnims_PorytilesPrimaryTutorial_SeaDark_Frame0,
    gTilesetAnims_PorytilesPrimaryTutorial_SeaDark_Frame1,
    gTilesetAnims_PorytilesPrimaryTutorial_SeaDark_Frame2,
    gTilesetAnims_PorytilesPrimaryTutorial_SeaDark_Frame3,
    gTilesetAnims_PorytilesPrimaryTutorial_SeaDark_Frame4,
    gTilesetAnims_PorytilesPrimaryTutorial_SeaDark_Frame5,
    gTilesetAnims_PorytilesPrimaryTutorial_SeaDark_Frame6,
    gTilesetAnims_PorytilesPrimaryTutorial_SeaDark_Frame7,
};

const u16 *const gTilesetAnims_PorytilesPrimaryTutorial_SeaDarkCorner[] = {
    gTilesetAnims_PorytilesPrimaryTutorial_SeaDarkCorner_Frame0,
    gTilesetAnims_PorytilesPrimaryTutorial_SeaDarkCorner_Frame1,
    gTilesetAnims_PorytilesPrimaryTutorial_SeaDarkCorner_Frame2,
    gTilesetAnims_PorytilesPrimaryTutorial_SeaDarkCorner_Frame3,
    gTilesetAnims_PorytilesPrimaryTutorial_SeaDarkCorner_Frame4,
    gTilesetAnims_PorytilesPrimaryTutorial_SeaDarkCorner_Frame5,
    gTilesetAnims_PorytilesPrimaryTutorial_SeaDarkCorner_Frame6,
    gTilesetAnims_PorytilesPrimaryTutorial_SeaDarkCorner_Frame7,
};

const u16 *const gTilesetAnims_PorytilesPrimaryTutorial_Beach[] = {
    gTilesetAnims_PorytilesPrimaryTutorial_Beach_Frame0,
    gTilesetAnims_PorytilesPrimaryTutorial_Beach_Frame1,
    gTilesetAnims_PorytilesPrimaryTutorial_Beach_Frame2,
    gTilesetAnims_PorytilesPrimaryTutorial_Beach_Frame3,
    gTilesetAnims_PorytilesPrimaryTutorial_Beach_Frame4,
    gTilesetAnims_PorytilesPrimaryTutorial_Beach_Frame5,
    gTilesetAnims_PorytilesPrimaryTutorial_Beach_Frame6,
    gTilesetAnims_PorytilesPrimaryTutorial_Beach_Frame7,
};

const u16 *const gTilesetAnims_PorytilesPrimaryTutorial_SeaRock[] = {
    gTilesetAnims_PorytilesPrimaryTutorial_SeaRock_Frame0,
    gTilesetAnims_PorytilesPrimaryTutorial_SeaRock_Frame1,
    gTilesetAnims_PorytilesPrimaryTutorial_SeaRock_Frame2,
    gTilesetAnims_PorytilesPrimaryTutorial_SeaRock_Frame3,
    gTilesetAnims_PorytilesPrimaryTutorial_SeaRock_Frame4,
    gTilesetAnims_PorytilesPrimaryTutorial_SeaRock_Frame5,
    gTilesetAnims_PorytilesPrimaryTutorial_SeaRock_Frame6,
    gTilesetAnims_PorytilesPrimaryTutorial_SeaRock_Frame7,
};

const u16 *const gTilesetAnims_PorytilesPrimaryTutorial_FlowerDandelionWhite[] = {
    gTilesetAnims_PorytilesPrimaryTutorial_FlowerDandelionWhite_Frame0,
    gTilesetAnims_PorytilesPrimaryTutorial_FlowerDandelionWhite_Frame1,
    gTilesetAnims_PorytilesPrimaryTutorial_FlowerDandelionWhite_Frame0,
    gTilesetAnims_PorytilesPrimaryTutorial_FlowerDandelionWhite_Frame3,
};

const u16 *const gTilesetAnims_PorytilesPrimaryTutorial_FlowerDandelionYellow[] = {
    gTilesetAnims_PorytilesPrimaryTutorial_FlowerDandelionYellow_Frame0,
    gTilesetAnims_PorytilesPrimaryTutorial_FlowerDandelionYellow_Frame1,
    gTilesetAnims_PorytilesPrimaryTutorial_FlowerDandelionYellow_Frame0,
    gTilesetAnims_PorytilesPrimaryTutorial_FlowerDandelionYellow_Frame2,
};

#define NB_TILES_BEACH 4
#define NB_TILES_FLOWER_DANDELION_WHITE 4
#define NB_TILES_FLOWER_DANDELION_YELLOW 4
#define NB_TILES_SEA 4
#define NB_TILES_SEA_DARK 4
#define NB_TILES_SEA_DARK_CORNER 4
#define NB_TILES_SEA_ROCK 4

#define STARTING_TILE_BEACH 1
#define STARTING_TILE_FLOWER_DANDELION_WHITE (STARTING_TILE_BEACH + NB_TILES_BEACH)
#define STARTING_TILE_FLOWER_DANDELION_YELLOW (STARTING_TILE_FLOWER_DANDELION_WHITE + NB_TILES_FLOWER_DANDELION_WHITE)
#define STARTING_TILE_SEA (STARTING_TILE_FLOWER_DANDELION_YELLOW + NB_TILES_FLOWER_DANDELION_YELLOW)
#define STARTING_TILE_SEA_DARK (STARTING_TILE_SEA + NB_TILES_SEA)
#define STARTING_TILE_SEA_DARK_CORNER (STARTING_TILE_SEA_DARK + NB_TILES_SEA_DARK)
#define STARTING_TILE_SEA_ROCK (STARTING_TILE_SEA_DARK_CORNER + NB_TILES_SEA_DARK_CORNER)

static void QueueAnimTiles_ExteriorGeneric_Beach(u16 timer)
{
    u16 i = timer % ARRAY_COUNT(gTilesetAnims_PorytilesPrimaryTutorial_Beach);
    AppendTilesetAnimToBuffer(gTilesetAnims_PorytilesPrimaryTutorial_Beach[i], STARTING_TILE_BEACH, NB_TILES_BEACH * TILE_SIZE_4BPP);
}

static void QueueAnimTiles_ExteriorGeneric_FlowerDandelionWhite(u16 timer)
{
    u16 i = timer % ARRAY_COUNT(gTilesetAnims_PorytilesPrimaryTutorial_FlowerDandelionWhite);
    AppendTilesetAnimToBuffer(gTilesetAnims_PorytilesPrimaryTutorial_FlowerDandelionWhite[i], STARTING_TILE_FLOWER_DANDELION_WHITE, NB_TILES_FLOWER_DANDELION_WHITE * TILE_SIZE_4BPP);
}

static void QueueAnimTiles_ExteriorGeneric_FlowerDandelionYellow(u16 timer)
{
    u16 i = timer % ARRAY_COUNT(gTilesetAnims_PorytilesPrimaryTutorial_FlowerDandelionYellow);
    AppendTilesetAnimToBuffer(gTilesetAnims_PorytilesPrimaryTutorial_FlowerDandelionYellow[i], STARTING_TILE_FLOWER_DANDELION_YELLOW, NB_TILES_FLOWER_DANDELION_YELLOW * TILE_SIZE_4BPP);
}

static void QueueAnimTiles_ExteriorGeneric_Sea(u16 timer)
{
    u16 i = timer % ARRAY_COUNT(gTilesetAnims_PorytilesPrimaryTutorial_Sea);
    AppendTilesetAnimToBuffer(gTilesetAnims_PorytilesPrimaryTutorial_Sea[i], STARTING_TILE_SEA, NB_TILES_SEA * TILE_SIZE_4BPP);
}

static void QueueAnimTiles_ExteriorGeneric_SeaDark(u16 timer)
{
    u16 i = timer % ARRAY_COUNT(gTilesetAnims_PorytilesPrimaryTutorial_SeaDark);
    AppendTilesetAnimToBuffer(gTilesetAnims_PorytilesPrimaryTutorial_SeaDark[i], STARTING_TILE_SEA_DARK, NB_TILES_SEA_DARK * TILE_SIZE_4BPP);
}

static void QueueAnimTiles_ExteriorGeneric_SeaDarkCorner(u16 timer)
{
    u16 i = timer % ARRAY_COUNT(gTilesetAnims_PorytilesPrimaryTutorial_SeaDarkCorner);
    AppendTilesetAnimToBuffer(gTilesetAnims_PorytilesPrimaryTutorial_SeaDarkCorner[i], STARTING_TILE_SEA_DARK_CORNER, NB_TILES_SEA_DARK_CORNER * TILE_SIZE_4BPP);
}

static void QueueAnimTiles_ExteriorGeneric_SeaRock(u16 timer)
{
    u16 i = timer % ARRAY_COUNT(gTilesetAnims_PorytilesPrimaryTutorial_SeaRock);
    AppendTilesetAnimToBuffer(gTilesetAnims_PorytilesPrimaryTutorial_SeaRock[i], STARTING_TILE_SEA_ROCK, NB_TILES_SEA_ROCK * TILE_SIZE_4BPP);
}

static void TilesetAnim_ExteriorGeneric(u16 timer)
{
    if (timer % 16 == 0) {
        QueueAnimTiles_ExteriorGeneric_Sea(timer / 16);
        QueueAnimTiles_ExteriorGeneric_SeaDark(timer / 16);
        QueueAnimTiles_ExteriorGeneric_SeaDarkCorner(timer / 16);
        QueueAnimTiles_ExteriorGeneric_Beach(timer / 16);
        QueueAnimTiles_ExteriorGeneric_SeaRock(timer / 16);

        QueueAnimTiles_ExteriorGeneric_FlowerDandelionWhite(timer / 16);
        QueueAnimTiles_ExteriorGeneric_FlowerDandelionYellow(timer / 16);
    }
}

void InitTilesetAnim_ExteriorGeneric(void)
{
    sPrimaryTilesetAnimCounter = 0;
    sPrimaryTilesetAnimCounterMax = 256;
    sPrimaryTilesetAnimCallback = TilesetAnim_ExteriorGeneric;
}
