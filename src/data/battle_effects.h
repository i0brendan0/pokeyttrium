#include "battle_scripts.h"

const struct MoveBattleEffect gMoveBattleEffects[NUM_BATTLE_MOVE_EFFECTS] =
{
    [EFFECT_HIT]                        = { BattleScript_EffectHit },
    [EFFECT_SLEEP]                      = { BattleScript_EffectSleep },
    [EFFECT_ABSORB]                     = { BattleScript_EffectAbsorb },
    [EFFECT_EXPLOSION]                  = { BattleScript_EffectExplosion },
    [EFFECT_DREAM_EATER]                = { BattleScript_EffectDreamEater },
    [EFFECT_MIRROR_MOVE]                = { BattleScript_EffectMirrorMove },
    [EFFECT_ATTACK_UP]                  = { BattleScript_EffectAttackUp },
    [EFFECT_DEFENSE_UP]                 = { BattleScript_EffectDefenseUp },
    [EFFECT_SPEED_UP]                   = { BattleScript_EffectSpeedUp },
    [EFFECT_SPECIAL_ATTACK_UP]          = { BattleScript_EffectSpecialAttackUp },
    [EFFECT_SPECIAL_DEFENSE_UP]         = { BattleScript_EffectSpecialDefenseUp },
    [EFFECT_ACCURACY_UP]                = { BattleScript_EffectAccuracyUp },
    [EFFECT_EVASION_UP]                 = { BattleScript_EffectEvasionUp },
    [EFFECT_SPECIAL_ATTACK_UP_3]        = { BattleScript_EffectSpecialAttackUp3 },
    [EFFECT_ATTACK_DOWN]                = { BattleScript_EffectAttackDown },
    [EFFECT_DEFENSE_DOWN]               = { BattleScript_EffectDefenseDown },
    [EFFECT_SPEED_DOWN]                 = { BattleScript_EffectSpeedDown },
    [EFFECT_SPECIAL_ATTACK_DOWN]        = { BattleScript_EffectSpecialAttackDown },
    [EFFECT_SPECIAL_DEFENSE_DOWN]       = { BattleScript_EffectSpecialDefenseDown },
    [EFFECT_ACCURACY_DOWN]              = { BattleScript_EffectAccuracyDown },
    [EFFECT_EVASION_DOWN]               = { BattleScript_EffectEvasionDown },
    [EFFECT_HAZE]                       = { BattleScript_EffectHaze },
    [EFFECT_BIDE]                       = { BattleScript_EffectBide },
    [EFFECT_ROAR]                       = { BattleScript_EffectRoar },
    [EFFECT_MULTI_HIT]                  = { BattleScript_EffectHit },
    [EFFECT_CONVERSION]                 = { BattleScript_EffectConversion },
    [EFFECT_RESTORE_HP]                 = { BattleScript_EffectRestoreHp },
    [EFFECT_TOXIC]                      = { BattleScript_EffectToxic },
    [EFFECT_LIGHT_SCREEN]               = { BattleScript_EffectLightScreen },
    [EFFECT_REST]                       = { BattleScript_EffectRest },
    [EFFECT_OHKO]                       = { BattleScript_EffectOHKO },
    [EFFECT_FUSION_COMBO]               = { BattleScript_EffectHit },
    [EFFECT_SUPER_FANG]                 = { BattleScript_EffectSuperFang },
    [EFFECT_FIXED_DAMAGE_ARG]           = { BattleScript_EffectFixedDamageArg },
    [EFFECT_HEAL_BLOCK]                 = { BattleScript_EffectHealBlock },
    [EFFECT_RECOIL_IF_MISS]             = { BattleScript_EffectRecoilIfMiss },
    [EFFECT_MIST]                       = { BattleScript_EffectMist },
    [EFFECT_FOCUS_ENERGY]               = { BattleScript_EffectFocusEnergy },
    [EFFECT_CONFUSE]                    = { BattleScript_EffectConfuse },
    [EFFECT_ATTACK_UP_2]                = { BattleScript_EffectAttackUp2 },
    [EFFECT_DEFENSE_UP_2]               = { BattleScript_EffectDefenseUp2 },
    [EFFECT_SPEED_UP_2]                 = { BattleScript_EffectSpeedUp2 },
    [EFFECT_SPECIAL_ATTACK_UP_2]        = { BattleScript_EffectSpecialAttackUp2 },
    [EFFECT_SPECIAL_DEFENSE_UP_2]       = { BattleScript_EffectSpecialDefenseUp2 },
    [EFFECT_ACCURACY_UP_2]              = { BattleScript_EffectAccuracyUp2 },
    [EFFECT_EVASION_UP_2]               = { BattleScript_EffectEvasionUp2 },
    [EFFECT_TRANSFORM]                  = { BattleScript_EffectTransform },
    [EFFECT_ATTACK_DOWN_2]              = { BattleScript_EffectAttackDown2 },
    [EFFECT_DEFENSE_DOWN_2]             = { BattleScript_EffectDefenseDown2 },
    [EFFECT_SPEED_DOWN_2]               = { BattleScript_EffectSpeedDown2 },
    [EFFECT_SPECIAL_ATTACK_DOWN_2]      = { BattleScript_EffectSpecialAttackDown2 },
    [EFFECT_SPECIAL_DEFENSE_DOWN_2]     = { BattleScript_EffectSpecialDefenseDown2 },
    [EFFECT_ACCURACY_DOWN_2]            = { BattleScript_EffectAccuracyDown2 },
    [EFFECT_EVASION_DOWN_2]             = { BattleScript_EffectEvasionDown2 },
    [EFFECT_REFLECT]                    = { BattleScript_EffectReflect },
    [EFFECT_POISON]                     = { BattleScript_EffectPoison },
    [EFFECT_PARALYZE]                   = { BattleScript_EffectParalyze },
    [EFFECT_TWO_TURNS_ATTACK]           = { BattleScript_EffectTwoTurnsAttack },
    [EFFECT_SUBSTITUTE]                 = { BattleScript_EffectSubstitute },
    [EFFECT_RAGE]                       = { BattleScript_EffectRage },
    [EFFECT_MIMIC]                      = { BattleScript_EffectMimic },
    [EFFECT_METRONOME]                  = { BattleScript_EffectMetronome },
    [EFFECT_LEECH_SEED]                 = { BattleScript_EffectLeechSeed },
    [EFFECT_DO_NOTHING]                 = { BattleScript_EffectDoNothing },
    [EFFECT_DISABLE]                    = { BattleScript_EffectDisable },
    [EFFECT_LEVEL_DAMAGE]               = { BattleScript_EffectLevelDamage },
    [EFFECT_PSYWAVE]                    = { BattleScript_EffectPsywave },
    [EFFECT_COUNTER]                    = { BattleScript_EffectCounter },
    [EFFECT_ENCORE]                     = { BattleScript_EffectEncore },
    [EFFECT_PAIN_SPLIT]                 = { BattleScript_EffectPainSplit },
    [EFFECT_SNORE]                      = { BattleScript_EffectSnore },
    [EFFECT_CONVERSION_2]               = { BattleScript_EffectConversion2 },
    [EFFECT_LOCK_ON]                    = { BattleScript_EffectLockOn },
    [EFFECT_SKETCH]                     = { BattleScript_EffectSketch },
    [EFFECT_SLEEP_TALK]                 = { BattleScript_EffectSleepTalk },
    [EFFECT_DESTINY_BOND]               = { BattleScript_EffectDestinyBond },
    [EFFECT_FLAIL]                      = { BattleScript_EffectHit },
    [EFFECT_SPITE]                      = { BattleScript_EffectSpite },
    [EFFECT_FALSE_SWIPE]                = { BattleScript_EffectHit },
    [EFFECT_HEAL_BELL]                  = { BattleScript_EffectHealBell },
    [EFFECT_TRIPLE_KICK]                = { BattleScript_EffectTripleKick },
    [EFFECT_MEAN_LOOK]                  = { BattleScript_EffectMeanLook },
    [EFFECT_NIGHTMARE]                  = { BattleScript_EffectNightmare },
    [EFFECT_MINIMIZE]                   = { BattleScript_EffectMinimize },
    [EFFECT_CURSE]                      = { BattleScript_EffectCurse },
    [EFFECT_HEALING_WISH]               = { BattleScript_EffectHealingWish },
    [EFFECT_PROTECT]                    = { BattleScript_EffectProtect },
    [EFFECT_SPIKES]                     = { BattleScript_EffectSpikes },
    [EFFECT_FORESIGHT]                  = { BattleScript_EffectForesight },
    [EFFECT_PERISH_SONG]                = { BattleScript_EffectPerishSong },
    [EFFECT_SANDSTORM]                  = { BattleScript_EffectSandstorm },
    [EFFECT_ENDURE]                     = { BattleScript_EffectEndure },
    [EFFECT_ROLLOUT]                    = { BattleScript_EffectRollout },
    [EFFECT_SWAGGER]                    = { BattleScript_EffectSwagger },
    [EFFECT_FURY_CUTTER]                = { BattleScript_EffectFuryCutter },
    [EFFECT_ATTRACT]                    = { BattleScript_EffectAttract },
    [EFFECT_RETURN]                     = { BattleScript_EffectHit },
    [EFFECT_PRESENT]                    = { BattleScript_EffectPresent },
    [EFFECT_FRUSTRATION]                = { BattleScript_EffectHit },
    [EFFECT_SAFEGUARD]                  = { BattleScript_EffectSafeguard },
    [EFFECT_MAGNITUDE]                  = { BattleScript_EffectMagnitude },
    [EFFECT_BATON_PASS]                 = { BattleScript_EffectBatonPass },
    [EFFECT_PURSUIT]                    = { BattleScript_EffectHit },
    [EFFECT_CAPTIVATE]                  = { BattleScript_EffectCaptivate },
    [EFFECT_MORNING_SUN]                = { BattleScript_EffectMorningSun },
    [EFFECT_SYNTHESIS]                  = { BattleScript_EffectSynthesis },
    [EFFECT_MOONLIGHT]                  = { BattleScript_EffectMoonlight },
    [EFFECT_HIDDEN_POWER]               = { BattleScript_EffectHit },
    [EFFECT_RAIN_DANCE]                 = { BattleScript_EffectRainDance },
    [EFFECT_SUNNY_DAY]                  = { BattleScript_EffectSunnyDay },
    [EFFECT_FELL_STINGER]               = { BattleScript_EffectHit },
    [EFFECT_BELLY_DRUM]                 = { BattleScript_EffectBellyDrum },
    [EFFECT_PSYCH_UP]                   = { BattleScript_EffectPsychUp },
    [EFFECT_MIRROR_COAT]                = { BattleScript_EffectMirrorCoat },
    [EFFECT_SKULL_BASH]                 = { BattleScript_EffectSkullBash },
    [EFFECT_EARTHQUAKE]                 = { BattleScript_EffectHit },
    [EFFECT_FUTURE_SIGHT]               = { BattleScript_EffectFutureSight },
    [EFFECT_GUST]                       = { BattleScript_EffectGust },
    [EFFECT_SOLAR_BEAM]                 = { BattleScript_EffectSolarBeam },
    [EFFECT_THUNDER]                    = { BattleScript_EffectHit },
    [EFFECT_TELEPORT]                   = { BattleScript_EffectTeleport },
    [EFFECT_BEAT_UP]                    = { BattleScript_EffectBeatUp },
    [EFFECT_SEMI_INVULNERABLE]          = { BattleScript_EffectSemiInvulnerable },
    [EFFECT_DEFENSE_CURL]               = { BattleScript_EffectDefenseCurl },
    [EFFECT_SOFTBOILED]                 = { BattleScript_EffectSoftboiled },
    [EFFECT_FAKE_OUT]                   = { BattleScript_EffectFakeOut },
    [EFFECT_UPROAR]                     = { BattleScript_EffectUproar },
    [EFFECT_STOCKPILE]                  = { BattleScript_EffectStockpile },
    [EFFECT_SPIT_UP]                    = { BattleScript_EffectSpitUp },
    [EFFECT_SWALLOW]                    = { BattleScript_EffectSwallow },
    [EFFECT_WORRY_SEED]                 = { BattleScript_EffectWorrySeed },
    [EFFECT_HAIL]                       = { BattleScript_EffectHail },
    [EFFECT_TORMENT]                    = { BattleScript_EffectTorment },
    [EFFECT_FLATTER]                    = { BattleScript_EffectFlatter },
    [EFFECT_WILL_O_WISP]                = { BattleScript_EffectWillOWisp },
    [EFFECT_MEMENTO]                    = { BattleScript_EffectMemento },
    [EFFECT_FACADE]                     = { BattleScript_EffectHit },
    [EFFECT_FOCUS_PUNCH]                = { BattleScript_EffectFocusPunch },
    [EFFECT_DOUBLE_POWER_ON_ARG_STATUS] = { BattleScript_EffectHit },
    [EFFECT_FOLLOW_ME]                  = { BattleScript_EffectFollowMe },
    [EFFECT_NATURE_POWER]               = { BattleScript_EffectNaturePower },
    [EFFECT_CHARGE]                     = { BattleScript_EffectCharge },
    [EFFECT_TAUNT]                      = { BattleScript_EffectTaunt },
    [EFFECT_HELPING_HAND]               = { BattleScript_EffectHelpingHand },
    [EFFECT_TRICK]                      = { BattleScript_EffectTrick },
    [EFFECT_ROLE_PLAY]                  = { BattleScript_EffectRolePlay },
    [EFFECT_WISH]                       = { BattleScript_EffectWish },
    [EFFECT_ASSIST]                     = { BattleScript_EffectAssist },
    [EFFECT_INGRAIN]                    = { BattleScript_EffectIngrain },
    [EFFECT_MAGIC_COAT]                 = { BattleScript_EffectMagicCoat },
    [EFFECT_RECYCLE]                    = { BattleScript_EffectRecycle },
    [EFFECT_REVENGE]                    = { BattleScript_EffectHit },
    [EFFECT_BRICK_BREAK]                = { BattleScript_EffectBrickBreak },
    [EFFECT_YAWN]                       = { BattleScript_EffectYawn },
    [EFFECT_KNOCK_OFF]                  = { BattleScript_EffectHit },
    [EFFECT_ENDEAVOR]                   = { BattleScript_EffectEndeavor },
    [EFFECT_ERUPTION]                   = { BattleScript_EffectHit },
    [EFFECT_SKILL_SWAP]                 = { BattleScript_EffectSkillSwap },
    [EFFECT_IMPRISON]                   = { BattleScript_EffectImprison },
    [EFFECT_REFRESH]                    = { BattleScript_EffectRefresh },
    [EFFECT_GRUDGE]                     = { BattleScript_EffectGrudge },
    [EFFECT_SNATCH]                     = { BattleScript_EffectSnatch },
    [EFFECT_LOW_KICK]                   = { BattleScript_EffectHit },
    [EFFECT_TEETER_DANCE]               = { BattleScript_EffectTeeterDance },
    [EFFECT_HIT_ESCAPE]                 = { BattleScript_EffectHitEscape },
    [EFFECT_MUD_SPORT]                  = { BattleScript_EffectMudSport },
    [EFFECT_WEATHER_BALL]               = { BattleScript_EffectHit },
    [EFFECT_TICKLE]                     = { BattleScript_EffectTickle },
    [EFFECT_COSMIC_POWER]               = { BattleScript_EffectCosmicPower },
    [EFFECT_SKY_UPPERCUT]               = { BattleScript_EffectSkyUppercut },
    [EFFECT_BULK_UP]                    = { BattleScript_EffectBulkUp },
    [EFFECT_PLACEHOLDER]                = { BattleScript_EffectPlaceholder },
    [EFFECT_WATER_SPORT]                = { BattleScript_EffectWaterSport },
    [EFFECT_CALM_MIND]                  = { BattleScript_EffectCalmMind },
    [EFFECT_DRAGON_DANCE]               = { BattleScript_EffectDragonDance },
    [EFFECT_CAMOUFLAGE]                 = { BattleScript_EffectCamouflage },
    [EFFECT_PLEDGE]                     = { BattleScript_EffectPledge },
    [EFFECT_FLING]                      = { BattleScript_EffectFling },
    [EFFECT_NATURAL_GIFT]               = { BattleScript_EffectNaturalGift },
    [EFFECT_WRING_OUT]                  = { BattleScript_EffectHit },
    [EFFECT_ASSURANCE]                  = { BattleScript_EffectHit },
    [EFFECT_TRUMP_CARD]                 = { BattleScript_EffectHit },
    [EFFECT_ACROBATICS]                 = { BattleScript_EffectHit },
    [EFFECT_HEAT_CRASH]                 = { BattleScript_EffectHit },
    [EFFECT_PUNISHMENT]                 = { BattleScript_EffectHit },
    [EFFECT_STORED_POWER]               = { BattleScript_EffectHit },
    [EFFECT_ELECTRO_BALL]               = { BattleScript_EffectHit },
    [EFFECT_GYRO_BALL]                  = { BattleScript_EffectHit },
    [EFFECT_ECHOED_VOICE]               = { BattleScript_EffectHit },
    [EFFECT_PAYBACK]                    = { BattleScript_EffectHit },
    [EFFECT_ROUND]                      = { BattleScript_EffectHit },
    [EFFECT_BRINE]                      = { BattleScript_EffectHit },
    [EFFECT_RETALIATE]                  = { BattleScript_EffectHit },
    [EFFECT_BULLDOZE]                   = { BattleScript_EffectHit },
    [EFFECT_FOUL_PLAY]                  = { BattleScript_EffectHit },
    [EFFECT_PSYSHOCK]                   = { BattleScript_EffectHit },
    [EFFECT_ROOST]                      = { BattleScript_EffectRoost },
    [EFFECT_GRAVITY]                    = { BattleScript_EffectGravity },
    [EFFECT_MIRACLE_EYE]                = { BattleScript_EffectMircleEye },
    [EFFECT_TAILWIND]                   = { BattleScript_EffectTailwind },
    [EFFECT_EMBARGO]                    = { BattleScript_EffectEmbargo },
    [EFFECT_AQUA_RING]                  = { BattleScript_EffectAquaRing },
    [EFFECT_TRICK_ROOM]                 = { BattleScript_EffectTrickRoom },
    [EFFECT_WONDER_ROOM]                = { BattleScript_EffectWonderRoom },
    [EFFECT_MAGIC_ROOM]                 = { BattleScript_EffectMagicRoom },
    [EFFECT_MAGNET_RISE]                = { BattleScript_EffectMagnetRise },
    [EFFECT_TOXIC_SPIKES]               = { BattleScript_EffectToxicSpikes },
    [EFFECT_GASTRO_ACID]                = { BattleScript_EffectGastroAcid },
    [EFFECT_STEALTH_ROCK]               = { BattleScript_EffectStealthRock },
    [EFFECT_TELEKINESIS]                = { BattleScript_EffectTelekinesis },
    [EFFECT_POWER_SWAP]                 = { BattleScript_EffectPowerSwap },
    [EFFECT_GUARD_SWAP]                 = { BattleScript_EffectGuardSwap },
    [EFFECT_HEART_SWAP]                 = { BattleScript_EffectHeartSwap },
    [EFFECT_POWER_SPLIT]                = { BattleScript_EffectPowerSplit },
    [EFFECT_GUARD_SPLIT]                = { BattleScript_EffectGuardSplit },
    [EFFECT_STICKY_WEB]                 = { BattleScript_EffectStickyWeb },
    [EFFECT_METAL_BURST]                = { BattleScript_EffectMetalBurst },
    [EFFECT_LUCKY_CHANT]                = { BattleScript_EffectLuckyChant },
    [EFFECT_SUCKER_PUNCH]               = { BattleScript_EffectSuckerPunch },
    [EFFECT_SIMPLE_BEAM]                = { BattleScript_EffectSimpleBeam },
    [EFFECT_ENTRAINMENT]                = { BattleScript_EffectEntrainment },
    [EFFECT_HEAL_PULSE]                 = { BattleScript_EffectHealPulse },
    [EFFECT_QUASH]                      = { BattleScript_EffectQuash },
    [EFFECT_ION_DELUGE]                 = { BattleScript_EffectIonDeluge },
    [EFFECT_FREEZE_DRY]                 = { BattleScript_EffectHit },
    [EFFECT_TOPSY_TURVY]                = { BattleScript_EffectTopsyTurvy },
    [EFFECT_MISTY_TERRAIN]              = { BattleScript_EffectMistyTerrain },
    [EFFECT_GRASSY_TERRAIN]             = { BattleScript_EffectGrassyTerrain },
    [EFFECT_ELECTRIC_TERRAIN]           = { BattleScript_EffectElectricTerrain },
    [EFFECT_PSYCHIC_TERRAIN]            = { BattleScript_EffectPsychicTerrain },
    [EFFECT_ATTACK_ACCURACY_UP]         = { BattleScript_EffectAttackAccUp },
    [EFFECT_ATTACK_SPATK_UP]            = { BattleScript_EffectAttackSpAttackUp },
    [EFFECT_TWO_TYPED_MOVE]             = { BattleScript_EffectHit },
    [EFFECT_ME_FIRST]                   = { BattleScript_EffectMeFirst },
    [EFFECT_QUIVER_DANCE]               = { BattleScript_EffectQuiverDance },
    [EFFECT_COIL]                       = { BattleScript_EffectCoil },
    [EFFECT_ELECTRIFY]                  = { BattleScript_EffectElectrify },
    [EFFECT_REFLECT_TYPE]               = { BattleScript_EffectReflectType },
    [EFFECT_SOAK]                       = { BattleScript_EffectSoak },
    [EFFECT_GROWTH]                     = { BattleScript_EffectGrowth },
    [EFFECT_LAST_RESORT]                = { BattleScript_EffectLastResort },
    [EFFECT_SHELL_SMASH]                = { BattleScript_EffectShellSmash },
    [EFFECT_SHIFT_GEAR]                 = { BattleScript_EffectShiftGear },
    [EFFECT_DEFENSE_UP_3]               = { BattleScript_EffectDefenseUp3 },
    [EFFECT_NOBLE_ROAR]                 = { BattleScript_EffectNobleRoar },
    [EFFECT_VENOM_DRENCH]               = { BattleScript_EffectVenomDrench },
    [EFFECT_TOXIC_THREAD]               = { BattleScript_EffectToxicThread },
    [EFFECT_HIT_SWITCH_TARGET]          = { BattleScript_EffectHitSwitchTarget },
    [EFFECT_FINAL_GAMBIT]               = { BattleScript_EffectFinalGambit },
    [EFFECT_CHANGE_TYPE_ON_ITEM]        = { BattleScript_EffectHit },
    [EFFECT_AUTOTOMIZE]                 = { BattleScript_EffectAutotomize },
    [EFFECT_COPYCAT]                    = { BattleScript_EffectCopycat },
    [EFFECT_DEFOG]                      = { BattleScript_EffectDefog },
    [EFFECT_HIT_ENEMY_HEAL_ALLY]        = { BattleScript_EffectHitEnemyHealAlly },
    [EFFECT_SYNCHRONOISE]               = { BattleScript_EffectSynchronoise },
    [EFFECT_PSYCHO_SHIFT]               = { BattleScript_EffectPsychoShift },
    [EFFECT_POWER_TRICK]                = { BattleScript_EffectPowerTrick },
    [EFFECT_AFTER_YOU]                  = { BattleScript_EffectAfterYou },
    [EFFECT_BESTOW]                     = { BattleScript_EffectBestow },
    [EFFECT_ROTOTILLER]                 = { BattleScript_EffectRototiller },
    [EFFECT_FLOWER_SHIELD]              = { BattleScript_EffectFlowerShield },
    [EFFECT_SPEED_SWAP]                 = { BattleScript_EffectSpeedSwap },
    [EFFECT_REVELATION_DANCE]           = { BattleScript_EffectHit },
    [EFFECT_AURORA_VEIL]                = { BattleScript_EffectAuroraVeil },
    [EFFECT_THIRD_TYPE]                 = { BattleScript_EffectThirdType },
    [EFFECT_ACUPRESSURE]                = { BattleScript_EffectAcupressure },
    [EFFECT_AROMATIC_MIST]              = { BattleScript_EffectAromaticMist },
    [EFFECT_POWDER]                     = { BattleScript_EffectPowder },
    [EFFECT_BELCH]                      = { BattleScript_EffectHit },
    [EFFECT_PARTING_SHOT]               = { BattleScript_EffectPartingShot },
    [EFFECT_MAT_BLOCK]                  = { BattleScript_EffectMatBlock },
    [EFFECT_STOMPING_TANTRUM]           = { BattleScript_EffectHit },
    [EFFECT_INSTRUCT]                   = { BattleScript_EffectInstruct },
    [EFFECT_LASER_FOCUS]                = { BattleScript_EffectLaserFocus },
    [EFFECT_MAGNETIC_FLUX]              = { BattleScript_EffectMagneticFlux },
    [EFFECT_GEAR_UP]                    = { BattleScript_EffectGearUp },
    [EFFECT_STRENGTH_SAP]               = { BattleScript_EffectStrengthSap },
    [EFFECT_MIND_BLOWN]                 = { BattleScript_EffectMindBlown },
    [EFFECT_PURIFY]                     = { BattleScript_EffectPurify },
    [EFFECT_FAIL_IF_NOT_ARG_TYPE]       = { BattleScript_FailIfNotArgType },
    [EFFECT_SHORE_UP]                   = { BattleScript_EffectShoreUp },
    [EFFECT_GEOMANCY]                   = { BattleScript_EffectGeomancy },
    [EFFECT_FAIRY_LOCK]                 = { BattleScript_EffectFairyLock },
    [EFFECT_ALLY_SWITCH]                = { BattleScript_EffectAllySwitch },
    [EFFECT_RELIC_SONG]                 = { BattleScript_EffectRelicSong },
    [EFFECT_BODY_PRESS]                 = { BattleScript_EffectHit },
    [EFFECT_EERIE_SPELL]                = { BattleScript_EffectEerieSpell },
    [EFFECT_JUNGLE_HEALING]             = { BattleScript_EffectJungleHealing },
    [EFFECT_COACHING]                   = { BattleScript_EffectCoaching },
    [EFFECT_LASH_OUT]                   = { BattleScript_EffectHit },
    [EFFECT_GRASSY_GLIDE]               = { BattleScript_EffectHit },
    [EFFECT_DYNAMAX_DOUBLE_DMG]         = { BattleScript_EffectHit },
    [EFFECT_DECORATE]                   = { BattleScript_EffectDecorate },
    [EFFECT_SNIPE_SHOT]                 = { BattleScript_EffectHit },
    [EFFECT_RECOIL_HP_25]               = { BattleScript_EffectRecoilHP25 },
    [EFFECT_STUFF_CHEEKS]               = { BattleScript_EffectStuffCheeks },
    [EFFECT_GRAV_APPLE]                 = { BattleScript_EffectHit },
    [EFFECT_GLITZY_GLOW]                = { BattleScript_EffectGlitzyGlow },
    [EFFECT_BADDY_BAD]                  = { BattleScript_EffectBaddyBad },
    [EFFECT_SAPPY_SEED]                 = { BattleScript_EffectSappySeed },
    [EFFECT_FREEZY_FROST]               = { BattleScript_EffectFreezyFrost },
    [EFFECT_SPARKLY_SWIRL]              = { BattleScript_EffectSparklySwirl },
    [EFFECT_PLASMA_FISTS]               = { BattleScript_EffectPlasmaFists },
    [EFFECT_HYPERSPACE_FURY]            = { BattleScript_EffectHyperspaceFury },
    [EFFECT_AURA_WHEEL]                 = { BattleScript_EffectAuraWheel },
    [EFFECT_PHOTON_GEYSER]              = { BattleScript_EffectPhotonGeyser },
    [EFFECT_SHELL_SIDE_ARM]             = { BattleScript_EffectShellSideArm },
    [EFFECT_TERRAIN_PULSE]              = { BattleScript_EffectHit },
    [EFFECT_NO_RETREAT]                 = { BattleScript_EffectNoRetreat },
    [EFFECT_TAR_SHOT]                   = { BattleScript_EffectTarShot },
    [EFFECT_POLTERGEIST]                = { BattleScript_EffectPoltergeist },
    [EFFECT_OCTOLOCK]                   = { BattleScript_EffectOctolock },
    [EFFECT_CLANGOROUS_SOUL]            = { BattleScript_EffectClangorousSoul },
    [EFFECT_BOLT_BEAK]                  = { BattleScript_EffectHit },
    [EFFECT_SKY_DROP]                   = { BattleScript_EffectSkyDrop },
    [EFFECT_EXPANDING_FORCE]            = { BattleScript_EffectHit },
    [EFFECT_METEOR_BEAM]                = { BattleScript_EffectMeteorBeam },
    [EFFECT_RISING_VOLTAGE]             = { BattleScript_EffectHit },
    [EFFECT_BEAK_BLAST]                 = { BattleScript_EffectHit },
    [EFFECT_COURT_CHANGE]               = { BattleScript_EffectCourtChange },
    [EFFECT_STEEL_BEAM]                 = { BattleScript_EffectSteelBeam },
    [EFFECT_EXTREME_EVOBOOST]           = { BattleScript_EffectExtremeEvoboost },
    [EFFECT_HIT_SET_REMOVE_TERRAIN]     = { BattleScript_EffectHitSetRemoveTerrain },
    [EFFECT_DARK_VOID]                  = { BattleScript_EffectDarkVoid },
    [EFFECT_VICTORY_DANCE]              = { BattleScript_EffectVictoryDance },
    [EFFECT_TEATIME]                    = { BattleScript_EffectTeatime },
    [EFFECT_ATTACK_UP_USER_ALLY]        = { BattleScript_EffectAttackUpUserAlly },
    [EFFECT_SHELL_TRAP]                 = { BattleScript_EffectShellTrap },
    [EFFECT_PSYBLADE]                   = { BattleScript_EffectHit },
    [EFFECT_HYDRO_STEAM]                = { BattleScript_EffectHit },
    [EFFECT_REVIVAL_BLESSING]           = { BattleScript_EffectRevivalBlessing },
    [EFFECT_SNOWSCAPE]                  = { BattleScript_EffectSnow },
    [EFFECT_TAKE_HEART]                 = { BattleScript_EffectTakeHeart },
    [EFFECT_COLLISION_COURSE]           = { BattleScript_EffectHit },
    [EFFECT_CORROSIVE_GAS]              = { BattleScript_EffectCorrosiveGas },
    [EFFECT_POPULATION_BOMB]            = { BattleScript_EffectHit },
    [EFFECT_SALT_CURE]                  = { BattleScript_EffectSaltCure },
    [EFFECT_CHILLY_RECEPTION]           = { BattleScript_EffectChillyReception },
    [EFFECT_MAX_MOVE]                   = { BattleScript_EffectMaxMove },
    [EFFECT_GLAIVE_RUSH]                = { BattleScript_EffectGlaiveRush },
    [EFFECT_RAGING_BULL]                = { BattleScript_EffectBrickBreak },
    [EFFECT_RAGE_FIST]                  = { BattleScript_EffectHit },
    [EFFECT_DOODLE]                     = { BattleScript_EffectDoodle },
    [EFFECT_FILLET_AWAY]                = { BattleScript_EffectFilletAway },
    [EFFECT_IVY_CUDGEL]                 = { BattleScript_EffectHit },
    [EFFECT_FICKLE_BEAM]                = { BattleScript_EffectHit },
    [EFFECT_BLIZZARD]                   = { BattleScript_EffectHit },
    [EFFECT_RAIN_ALWAYS_HIT]            = { BattleScript_EffectHit },
};