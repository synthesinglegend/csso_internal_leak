#pragma once
#include "recv_prop.hpp"
class i_client_unknown;
class client_class;
class i_client_networkable;

typedef i_client_networkable* (*create_client_class_fn)(int ent_number, int serial_number);
typedef i_client_networkable* (*create_event_fn)();
enum class_ids {
    CTestTraceline = 194,
    CTEWorldDecal = 195,
    CTESpriteSpray = 192,
    CTESprite = 191,
    CTESparks = 190,
    CTESmoke = 189,
    CTEShowLine = 187,
    CTEProjectedDecal = 184,
    CTEPlayerDecal = 183,
    CTEPhysicsProp = 180,
    CTEParticleSystem = 179,
    CTEMuzzleFlash = 178,
    CTELargeFunnel = 176,
    CTEKillPlayerAttachments = 175,
    CTEImpact = 174,
    CTEGlowSprite = 173,
    CTEShatterSurface = 186,
    CTEFootprintDecal = 171,
    CTEFizz = 170,
    CTEExplosion = 168,
    CTEEnergySplash = 167,
    CTEEffectDispatch = 166,
    CTEDynamicLight = 165,
    CTEDecal = 163,
    CTEClientProjectile = 162,
    CTEBubbleTrail = 161,
    CTEBubbles = 160,
    CTEBSPDecal = 159,
    CTEBreakModel = 158,
    CTEBloodStream = 157,
    CTEBloodSprite = 156,
    CTEBeamSpline = 155,
    CTEBeamRingPoint = 154,
    CTEBeamRing = 153,
    CTEBeamPoints = 152,
    CTEBeamLaser = 151,
    CTEBeamFollow = 150,
    CTEBeamEnts = 149,
    CTEBeamEntPoint = 148,
    CTEBaseBeam = 147,
    CTEArmorRicochet = 146,
    CTEMetalSparks = 177,
    CSteamJet = 142,
    CSmokeStack = 137,
    DustTrail = 240,
    CFireTrail = 54,
    SporeTrail = 247,
    SporeExplosion = 246,
    RocketTrail = 244,
    SmokeTrail = 245,
    CPropVehicleDriveable = 127,
    ParticleSmokeGrenade = 243,
    CParticleFire = 107,
    MovieExplosion = 241,
    CTEGaussExplosion = 172,
    CEnvQuadraticBeam = 47,
    CEmbers = 39,
    CEnvWind = 51,
    CPrecipitation = 122,
    CPrecipitationBlocker = 123,
    CBaseTempEntity = 17,
    CWeaponXM1014 = 238,
    CWeaponUSP = 237,
    CWeaponUMP45 = 236,
    CWeaponTec9 = 235,
    CWeaponTaser = 234,
    CWeaponSSG08 = 233,
    CSmokeGrenade = 135,
    CWeaponSG556 = 232,
    CWeaponSCAR20 = 231,
    CWeaponSawedOff = 230,
    CWeaponRevolver = 229,
    CWeaponP90 = 228,
    CWeaponP250 = 227,
    CWeaponNova = 226,
    CWeaponNegev = 225,
    CWeaponMP9 = 224,
    CWeaponMP7 = 223,
    CWeaponMP5SD = 222,
    CIncendiaryGrenade = 75,
    CMolotovGrenade = 105,
    CWeaponMAG7 = 221,
    CWeaponMAC10 = 220,
    CWeaponM4A4 = 219,
    CWeaponM4A1 = 218,
    CWeaponM249 = 217,
    CKnifePush = 95,
    CKnifeWidowmaker = 102,
    CKnifeUrsus = 101,
    CKnifeStiletto = 97,
    CKnifeSkeleton = 96,
    CKnifeOutdoor = 94,
    CKnifeGypsy = 91,
    CKnifeCord = 85,
    CKnifeCanis = 84,
    CKnifeSurvivalBowie = 98,
    CKnifeFalchion = 87,
    CKnifeTactical = 100,
    CKnifeGut = 90,
    CKnifeButterfly = 83,
    CKnifeM9Bayonet = 93,
    CKnifeBayonet = 82,
    CKnifeFlip = 88,
    CKnifeKarambit = 92,
    CKnifeCSS = 86,
    CKnifeT = 99,
    CKnifeGG = 89,
    CKnife = 81,
    CWeaponHKP2000 = 216,
    CHEGrenade = 72,
    CWeaponGlock = 215,
    CWeaponGalilAR = 214,
    CWeaponG3SG1 = 213,
    CFlashbang = 56,
    CWeaponFiveSeven = 212,
    CWeaponFAMAS = 211,
    CWeaponElite = 210,
    CDecoyGrenade = 35,
    CWeaponDeagle = 209,
    CWeaponCZ75A = 208,
    CWeaponCSBaseGun = 206,
    CWeaponCSBase = 205,
    CC4 = 26,
    CWeaponBizon = 204,
    CWeaponBaseItem = 203,
    CBaseCSGrenade = 6,
    CBaseCSGloves = 5,
    CWeaponAWP = 202,
    CWeaponAUG = 201,
    CWeaponAK47 = 200,
    CItem_Healthshot = 80,
    NextBotCombatCharacter = 242,
    CSmokeGrenadeProjectile = 136,
    CMolotovProjectile = 106,
    CDecoyProjectile = 36,
    CFootstepControl = 58,
    CCSGameRulesProxy = 30,
    CWeaponCubemap = 0,
    CWeaponCycler = 207,
    CFireCrackerBlast = 52,
    CInferno = 76,
    CTEPlantBomb = 181,
    CTEFireBullets = 169,
    CTERadioIcon = 185,
    CPlantedC4 = 115,
    CCSTeam = 34,
    CCSPlayerResource = 32,
    CCSPlayer = 31,
    CCSRagdoll = 33,
    CTEPlayerAnimEvent = 182,
    CHostage = 73,
    CHostageCarriableProp = 74,
    CChicken = 27,
    CBaseCSGrenadeProjectile = 7,
    CHandleTest = 71,
    CTeamplayRoundBasedRulesProxy = 145,
    CSpriteTrail = 141,
    CSpriteOriented = 140,
    CSprite = 139,
    CRagdollPropAttached = 130,
    CRagdollProp = 129,
    CPredictedViewModel = 124,
    CPoseController = 120,
    CGameRulesProxy = 70,
    CInfoLadderDismount = 77,
    CFuncLadder = 63,
    CEnvDetailController = 43,
    CWorld = 239,
    CWaterLODControl = 199,
    CWaterBullet = 198,
    CVoteController = 197,
    CVGuiScreen = 196,
    CPropJeep = 126,
    CPropVehicleChoreoGeneric = 0,
    CTest_ProxyToggle_Networkable = 193,
    CTesla = 188,
    CTeamTrainWatcher = 0,
    CBaseTeamObjectiveResource = 16,
    CTeam = 144,
    CSun = 143,
    CParticlePerformanceMonitor = 108,
    CSpotlightEnd = 138,
    CSlideshowDisplay = 134,
    CShadowControl = 133,
    CSceneEntity = 132,
    CRopeKeyframe = 131,
    CRagdollManager = 128,
    CPhysicsPropMultiplayer = 113,
    CPhysBoxMultiplayer = 111,
    CPropDoorRotating = 125,
    CBasePropDoor = 15,
    CDynamicProp = 38,
    CPostProcessController = 121,
    CPointCommentaryNode = 119,
    CPointCamera = 118,
    CPlayerResource = 117,
    CPlasma = 116,
    CPhysMagnet = 114,
    CPhysicsProp = 112,
    CPhysBox = 110,
    CParticleSystem = 109,
    CMaterialModifyControl = 104,
    CLightGlow = 103,
    CInfoOverlayAccessor = 79,
    CFuncTrackTrain = 69,
    CFuncSmokeVolume = 68,
    CFuncRotating = 67,
    CFuncReflectiveGlass = 66,
    CFuncOccluder = 65,
    CFuncMonitor = 64,
    CFunc_LOD = 60,
    CTEDust = 164,
    CFunc_Dust = 59,
    CFuncConveyor = 62,
    CBreakableSurface = 25,
    CFuncAreaPortalWindow = 61,
    CFish = 55,
    CEntityFlame = 41,
    CFireSmoke = 53,
    CEnvTonemapController = 50,
    CEnvScreenEffect = 48,
    CEnvScreenOverlay = 49,
    CEnvProjectedTexture = 46,
    CEnvParticleScript = 45,
    CFogController = 57,
    CEnvDOFController = 44,
    CEntityParticleTrail = 42,
    CEntityDissolve = 40,
    CDynamicLight = 37,
    CColorCorrectionVolume = 29,
    CColorCorrection = 28,
    CBreakableProp = 24,
    CBeamSpotlight = 22,
    CBaseToggle = 18,
    CBasePlayer = 13,
    CBaseFlex = 10,
    CBaseEntity = 9,
    CBaseDoor = 8,
    CBaseCombatCharacter = 3,
    CBaseAnimatingOverlay = 2,
    CBoneFollower = 23,
    CBaseAnimating = 1,
    CInfoLightingRelative = 78,
    CAI_BaseNPC = 0,
    CBeam = 21,
    CBaseViewModel = 19,
    CBaseProjectile = 14,
    CBaseParticleEntity = 12,
    CBaseGrenade = 11,
    CBaseCombatWeapon = 4,
    CBaseWeaponWorldModel = 20,
};

class c_client_class {
public:
    create_client_class_fn create_fn;
    create_event_fn create_event_fn;
    char* network_name;
    recv_table* recvtable_ptr;
    c_client_class* next_ptr;
    class_ids class_id;
};