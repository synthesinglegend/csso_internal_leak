#pragma once
#include "client_classes.hpp"
#include "../dependencies/math/math.hpp"
#include "../dependencies/netvar_manager/netvar_mgr.hpp"
#include "collideable.hpp"
#include "../dependencies/interfaces/mdl_info.hpp"
typedef unsigned long CBaseHandle;
enum move_type {
	movetype_none = 0,
	movetype_isometric,
	movetype_walk,
	movetype_step,
	movetype_fly,
	movetype_flygravity,
	movetype_vphysics,
	movetype_push,
	movetype_noclip,
	movetype_ladder,
	movetype_observer,
	movetype_custom,
	movetype_last = movetype_custom,
	movetype_max_bits = 4,
	max_movetype
};

enum entity_flags {
	fl_onground = (1 << 0),
	fl_ducking = (1 << 1),
	fl_waterjump = (1 << 2),
	fl_ontrain = (1 << 3),
	fl_inrain = (1 << 4),
	fl_frozen = (1 << 5),
	fl_atcontrols = (1 << 6),
	fl_client = (1 << 7),
	fl_fakeclient = (1 << 8),
	fl_inwater = (1 << 9),
	fl_fly = (1 << 10),
	fl_swim = (1 << 11),
	fl_conveyor = (1 << 12),
	fl_npc = (1 << 13),
	fl_godmode = (1 << 14),
	fl_notarget = (1 << 15),
	fl_aimtarget = (1 << 16),
	fl_partialground = (1 << 17),
	fl_staticprop = (1 << 18),
	fl_graphed = (1 << 19),
	fl_grenade = (1 << 20),
	fl_stepmovement = (1 << 21),
	fl_donttouch = (1 << 22),
	fl_basevelocity = (1 << 23),
	fl_worldbrush = (1 << 24),
	fl_object = (1 << 25),
	fl_killme = (1 << 26),
	fl_onfire = (1 << 27),
	fl_dissolving = (1 << 28),
	fl_transragdoll = (1 << 29),
	fl_unblockable_by_player = (1 << 30)
};

enum item_definition_indexes {
	WEAPON_DEAGLE = 1,
	WEAPON_ELITE = 2,
	WEAPON_FIVESEVEN = 3,
	WEAPON_GLOCK = 4,
	WEAPON_AK47 = 7,
	WEAPON_AUG = 8,
	WEAPON_AWP = 9,
	WEAPON_FAMAS = 10,
	WEAPON_G3SG1 = 11,
	WEAPON_GALILAR = 13,
	WEAPON_M249 = 14,
	WEAPON_M4A1 = 16,
	WEAPON_MAC10 = 17,
	WEAPON_P90 = 19,
	WEAPON_MP5SD = 23,
	WEAPON_UMP45 = 24,
	WEAPON_XM1014 = 25,
	WEAPON_BIZON = 26,
	WEAPON_MAG7 = 27,
	WEAPON_NEGEV = 28,
	WEAPON_SAWEDOFF = 29,
	WEAPON_TEC9 = 30,
	WEAPON_TASER = 31,
	WEAPON_HKP2000 = 32,
	WEAPON_MP7 = 33,
	WEAPON_MP9 = 34,
	WEAPON_NOVA = 35,
	WEAPON_P250 = 36,
	WEAPON_SHIELD = 37,
	WEAPON_SCAR20 = 38,
	WEAPON_SG556 = 39,
	WEAPON_SSG08 = 40,
	WEAPON_KNIFEGG = 41,
	WEAPON_KNIFE = 42,
	WEAPON_FLASHBANG = 43,
	WEAPON_HEGRENADE = 44,
	WEAPON_SMOKEGRENADE = 45,
	WEAPON_MOLOTOV = 46,
	WEAPON_DECOY = 47,
	WEAPON_INCGRENADE = 48,
	WEAPON_C4 = 49,
	WEAPON_HEALTHSHOT = 57,
	WEAPON_KNIFE_T = 59,
	WEAPON_M4A1_SILENCER = 60,
	WEAPON_USP_SILENCER = 61,
	WEAPON_CZ75A = 63,
	WEAPON_REVOLVER = 64,
	WEAPON_TAGRENADE = 68,
	WEAPON_FISTS = 69,
	WEAPON_BREACHCHARGE = 70,
	WEAPON_TABLET = 72,
	WEAPON_MELEE = 74,
	WEAPON_AXE = 75,
	WEAPON_HAMMER = 76,
	WEAPON_SPANNER = 78,
	WEAPON_KNIFE_GHOST = 80,
	WEAPON_FIREBOMB = 81,
	WEAPON_DIVERSION = 82,
	WEAPON_FRAG_GRENADE = 83,
	WEAPON_SNOWBALL = 84,
	WEAPON_BUMPMINE = 85,
	WEAPON_BAYONET = 500,
	WEAPON_KNIFE_FLIP = 505,
	WEAPON_KNIFE_GUT = 506,
	WEAPON_KNIFE_KARAMBIT = 507,
	WEAPON_KNIFE_M9_BAYONET = 508,
	WEAPON_KNIFE_TACTICAL = 509,
	WEAPON_KNIFE_FALCHION = 512,
	WEAPON_KNIFE_SURVIVAL_BOWIE = 514,
	WEAPON_KNIFE_BUTTERFLY = 515,
	WEAPON_KNIFE_PUSH = 516,
	WEAPON_KNIFE_URSUS = 519,
	WEAPON_KNIFE_GYPSY_JACKKNIFE = 520,
	WEAPON_KNIFE_STILETTO = 522,
	WEAPON_KNIFE_WIDOWMAKER = 523,
	STUDDED_BLOODHOUND_GLOVES = 5027,
	T_GLOVES = 5028,
	CT_GLOVES = 5029,
	SPORTY_GLOVES = 5030,
	SLICK_GLOVES = 5031,
	LEATHER_HANDWRAPS = 5032,
	MOTORCYCLE_GLOVES = 5033,
	SPECIALIST_GLOVES = 5034,
	STUDDED_HYDRA_GLOVES = 5035,
};

enum e_hitboxes {
	HITBOX_INVALID = -1,
	HITBOX_HEAD,
	HITBOX_NECK,
	HITBOX_PELVIS,
	HITBOX_STOMACH,
	HITBOX_LOWER_CHEST,
	HITBOX_CHEST,
	HITBOX_UPPER_CHEST,
	HITBOX_RIGHT_THIGH,
	HITBOX_LEFT_THIGH,
	HITBOX_RIGHT_CALF,
	HITBOX_LEFT_CALF,
	HITBOX_RIGHT_FOOT,
	HITBOX_LEFT_FOOT,
	HITBOX_RIGHT_HAND,
	HITBOX_LEFT_HAND,
	HITBOX_RIGHT_UPPER_ARM,
	HITBOX_RIGHT_FOREARM,
	HITBOX_LEFT_UPPER_ARM,
	HITBOX_LEFT_FOREARM,
	HITBOX_MAX
};
enum weapon_type : int
{
	WT_Invalid,
	WT_Grenade,
	WT_Knife,
	WT_Misc,
	WT_Pistol,
	WT_Submg,
	WT_Rifle,
	WT_Sniper,
	WT_Shotgun,
	WT_Machinegun,
	WT_Max
};

class entity_t {
public:
	PVOID animating() { // мне почему то нравится заменять обычные плюсовые (и не только плюсовые, так же и в си) воидпоинтеры на их эквивалент в винапи
		return (PVOID)(uintptr_t(this) + 0x4);
	}
	PVOID networkable() {
		return (PVOID)(uintptr_t(this) + 0x8);
	}
	collideable_t* collideable() {
		using original_fn = collideable_t * (__thiscall*)(void*);
		return (*(original_fn**)this)[3](this);
	}
	c_client_class* client_class() {
		using original_fn = c_client_class * (__thiscall*)(void*);
		return (*(original_fn**)networkable())[2](networkable());
	}
	model_t* model() {
		using original_fn = model_t * (__thiscall*)(void*);
		return (*(original_fn**)animating())[8](animating());
	}

	int DrawModel(int flags)
	{
		const auto renderable = this->get_renderable();
		if (!renderable) return false;
		return get_vfunc<10, int>(renderable, flags);
	}

	int get_id() // epic way to get entity index with assembly
	{
		int id;

		PVOID entity = (PVOID)this;

		__asm
		{
			MOV ECX, entity
			MOV EAX, DWORD PTR DS : [ECX + 0x8]
			MOV EDX, DWORD PTR DS : [EAX + 0x24]
			LEA ESI, DWORD PTR DS : [ECX + 0x8]
			MOV ECX, ESI
			CALL EDX
			MOV id, EAX
		}

		return id;
	}
	bool is_player() {
		return client_class()->class_id == 31;
	}

	NETVAR("DT_BasePlayer", "m_vecViewOffset[0]", m_viewoffset_x, float); // idk ?
	NETVAR("DT_BasePlayer", "m_vecViewOffset[1]", m_viewoffset_y, float);
	NETVAR("DT_BasePlayer", "m_vecViewOffset[2]", m_viewoffset_z, float);
	NETVAR("DT_BasePlayer", "m_vecOrigin", origin, vec3_t);
	NETVAR("DT_BasePlayer", "m_vecViewOffset", viewoffset, vec3_t);
	NETVAR("DT_BasePlayer", "m_vecVelocity", velocity, vec3_t);
	NETVAR("DT_BaseCombatCharacter", "m_hActiveWeapon", active_wpn, uint32_t);
	NETVAR("DT_CSPlayer", "m_iTeamNum", team, int);
	NETVAR("DT_CSPlayer", "m_fFlags", flags, int);
	const vec3_t& get_abs_origin() // interwebz solutions 
	{
		typedef const vec3_t& (__thiscall* GetAbsOrg_t)(PVOID);
		return ((GetAbsOrg_t)(*(PDWORD)(*(PDWORD)(this) + 0x24)))(this);
	}

	vec3_t& m_vecVelocity()
	{
		return *(vec3_t*)((DWORD)this + 0x100);
	}

	bool setup_bones(matrix_t* out, int max_bones, int mask, float time) {
		if (!this) {
			return false;
		}

		using original_fn = bool(__thiscall*)(void*, matrix_t*, int, int, float);
		return (*(original_fn**)animating())[16](animating(), out, max_bones, mask, time);
	}

	i_clientrenderable* get_renderable() { return (i_clientrenderable*)((DWORD)this + 0x4); }

	const model_t* get_model()
	{
		const auto renderable = this->get_renderable();
		if (!renderable) return nullptr;

		return renderable->get_model();
	}

};
class base_view_model : public entity_t {
public:
	NETVAR("DT_BaseViewModel", "m_nModelIndex", model_index, int);
	NETVAR("DT_BaseViewModel", "m_nViewModelIndex", view_model_index, int);
	NETVAR("DT_BaseViewModel", "m_hWeapon", m_hweapon, int);
	NETVAR("DT_BaseViewModel", "m_hOwner", m_howner, int);
};

class attributable_item_t : public entity_t {
public:
	NETVAR("DT_BaseAttributableItem", "m_iItemDefinitionIndex", item_definition_index, short);
	base_view_model* get_view_model() {
		return (base_view_model*)(DWORD)this;
	}
};

class weapon_t : public entity_t {
public:
	NETVAR("DT_BaseCombatWeapon", "m_flNextPrimaryAttack", next_primary_attack, float);
	NETVAR("DT_BaseCombatWeapon", "m_flNextSecondaryAttack", next_secondary_attack, float);
	NETVAR("DT_BaseCombatWeapon", "m_iClip1", clip1_count, int);
	NETVAR("DT_BaseCombatWeapon", "m_iClip2", clip2_count, int);
	NETVAR("DT_BaseCombatWeapon", "m_iPrimaryReserveAmmoCount", primary_reserve_ammo_acount, int);
	NETVAR("DT_WeaponCSBase", "m_flRecoilIndex", recoil_index, float);
	NETVAR("DT_WeaponCSBaseGun", "m_zoomLevel", zoom_level, float);
	NETVAR("DT_BaseAttributableItem", "m_iItemDefinitionIndex", item_definition_index, short);

	NETVAR("DT_BaseCombatWeapon", "m_iEntityQuality", entity_quality, int);

	float get_innacuracy() {
		using original_fn = float(__thiscall*)(void*);
		return (*(original_fn**)this)[399](this);
	}
	
	float get_spread() {
		using original_fn = float(__thiscall*)(void*);
		return (*(original_fn**)this)[400](this);
	}
	short get_weapon_id() {
		using original_fn = short(__thiscall*)(void*);
		return(*(original_fn**)this)[382](this);
	}
	void update_accuracy_penalty() {
		using original_fn = void(__thiscall*)(void*);
		(*(original_fn**)this)[402](this);
	}

	std::string weapon_name_definition() {
		if (!this)
			return ("");
		int id = this->item_definition_index();
		switch (id) {
		case WEAPON_DEAGLE:
			return ("deagle");
		case WEAPON_AUG:
			return ("aug");
		case WEAPON_G3SG1:
			return ("g3sg1");
		case WEAPON_MAC10:
			return ("mac10");
		case WEAPON_P90:
			return ("p90");
		case WEAPON_SSG08:
			return ("ssg08");
		case WEAPON_SCAR20:
			return ("scar20");
		case WEAPON_UMP45:
			return ("ump45");
		case WEAPON_ELITE:
			return ("elite");
		case WEAPON_FAMAS:
			return ("famas");
		case WEAPON_FIVESEVEN:
			return ("fiveseven");
		case WEAPON_GALILAR:
			return ("galilar");
		case WEAPON_M4A1_SILENCER:
			return ("m4a1_s");
		case WEAPON_M4A1:
			return ("m4a4");
		case WEAPON_P250:
			return ("p250");
		case WEAPON_M249:
			return ("m249");
		case WEAPON_XM1014:
			return ("xm1014");
		case WEAPON_GLOCK:
			return ("glock");
		case WEAPON_USP_SILENCER:
			return ("usp_s");
		case WEAPON_HKP2000:
			return ("p2000");
		case WEAPON_AK47:
			return ("ak47");
		case WEAPON_AWP:
			return ("awp");
		case WEAPON_BIZON:
			return ("bizon");
		case WEAPON_MAG7:
			return ("mag7");
		case WEAPON_NEGEV:
			return ("negev");
		case WEAPON_SAWEDOFF:
			return ("sawedoff");
		case WEAPON_TEC9:
			return ("tec9");
		case WEAPON_TASER:
			return ("zeus");
		case WEAPON_NOVA:
			return ("nova");
		case WEAPON_CZ75A:
			return ("cz75");
		case WEAPON_SG556:
			return ("sg553");
		case WEAPON_REVOLVER:
			return ("revolver");
		case WEAPON_MP7:
			return ("mp7");
		case WEAPON_MP9:
			return ("mp9");
		case WEAPON_MP5SD:  //same icon as ump
			return ("mp5");
		case WEAPON_C4:
			return ("c4");
		case WEAPON_MOLOTOV:
			return ("fire_molo");
		case WEAPON_INCGRENADE:
			return ("fire_inc");
		case WEAPON_FLASHBANG:
			return ("flash");
		case WEAPON_DECOY:
			return ("decoy");
		default:
			return ("error");
		}
		return ("");
	}


	std::string weapon_icon_definition() {
		if (!this)
			return ("");
		int id = this->item_definition_index();
		switch (id) {
		case WEAPON_KNIFE_T:
			return ("[");
		case WEAPON_DEAGLE:
			return ("A");
		case WEAPON_AUG:
			return ("U");
		case WEAPON_G3SG1:
			return ("X");
		case WEAPON_MAC10:
			return ("K");
		case WEAPON_P90:
			return ("P");
		case WEAPON_SSG08:
			return ("a");
		case WEAPON_SCAR20:
			return ("Y");
		case WEAPON_UMP45:
			return ("L");
		case WEAPON_ELITE:
			return ("B");
		case WEAPON_FAMAS:
			return ("R");
		case WEAPON_FIVESEVEN:
			return ("C");
		case WEAPON_GALILAR:
			return ("Q");
		case WEAPON_M4A1_SILENCER:
			return ("T");
		case WEAPON_M4A1:
			return ("S");
		case WEAPON_P250:
			return ("F");
		case WEAPON_M249:
			return ("g");
		case WEAPON_XM1014:
			return ("b");
		case WEAPON_GLOCK:
			return ("D");
		case WEAPON_USP_SILENCER:
			return ("G");
		case WEAPON_HKP2000:
			return ("E");
		case WEAPON_AK47:
			return ("W");
		case WEAPON_AWP:
			return ("Z");
		case WEAPON_BIZON:
			return ("M");
		case WEAPON_MAG7:
			return ("d");
		case WEAPON_NEGEV:
			return ("f");
		case WEAPON_SAWEDOFF:
			return ("c");
		case WEAPON_TEC9:
			return ("H");
		case WEAPON_TASER:
			return ("h");
		case WEAPON_NOVA:
			return ("e");
		case WEAPON_CZ75A:
			return ("I");
		case WEAPON_SG556:
			return ("V");
		case WEAPON_REVOLVER:
			return ("J");
		case WEAPON_MP7:
			return ("N");
		case WEAPON_MP9:
			return ("O");
		case WEAPON_MP5SD:  //same icon as ump
			return ("L");
		case WEAPON_C4:
			return ("o");
		case WEAPON_SMOKEGRENADE:
			return ("k");
		case WEAPON_MOLOTOV:
			return ("l");
		case WEAPON_INCGRENADE:
			return ("n");
		case WEAPON_FLASHBANG:
			return ("i");
		case WEAPON_DECOY:
			return ("m");
		default:
			return ("]");
		}
		return ("");
	}

	int get_type() {
		if (!this) return WT_Invalid;
		int ID = this->item_definition_index();
		switch (ID) {
		case WEAPON_DEAGLE:
		case WEAPON_P250:
		case WEAPON_USP_SILENCER:
		case WEAPON_HKP2000:
		case WEAPON_GLOCK:
		case WEAPON_FIVESEVEN:
		case WEAPON_TEC9:
		case WEAPON_ELITE:
		case WEAPON_REVOLVER:
		case WEAPON_CZ75A:
			return WT_Pistol;
			break;
		case WEAPON_MP9:
		case WEAPON_MP7:
		case WEAPON_UMP45:
		case WEAPON_BIZON:
		case WEAPON_P90:
		case WEAPON_MAC10:
			return WT_Submg;
			break;
		case WEAPON_BAYONET:
		case WEAPON_KNIFE_SURVIVAL_BOWIE:
		case WEAPON_KNIFE_BUTTERFLY:
		case WEAPON_KNIFE:
		case WEAPON_KNIFE_FALCHION:
		case WEAPON_KNIFE_FLIP:
		case WEAPON_KNIFE_GUT:
		case WEAPON_KNIFE_KARAMBIT:
		case WEAPON_KNIFE_M9_BAYONET:
		case WEAPON_KNIFE_PUSH:
		case WEAPON_KNIFE_TACTICAL:
		case WEAPON_KNIFE_T:
			return WT_Knife;
			break;
		case WEAPON_SAWEDOFF:
		case WEAPON_XM1014:
		case WEAPON_MAG7:
		case WEAPON_NOVA:
			return WT_Shotgun;
		case WEAPON_M249:
		case WEAPON_NEGEV:
			return WT_Machinegun;
		case WEAPON_TASER:
		case WEAPON_C4:
			return WT_Misc;
			break;
		case WEAPON_HEGRENADE:
		case WEAPON_FLASHBANG:
		case WEAPON_DECOY:
		case WEAPON_SMOKEGRENADE:
		case WEAPON_INCGRENADE:
		case WEAPON_MOLOTOV:
			return WT_Grenade;
			break;
		case WEAPON_AK47:
		case WEAPON_M4A1:
		case WEAPON_M4A1_SILENCER:
		case WEAPON_GALILAR:
		case WEAPON_FAMAS:
		case WEAPON_AUG:
		case WEAPON_SG556:
			return WT_Rifle;
			break;
		case WEAPON_SCAR20:
		case WEAPON_G3SG1:
		case WEAPON_SSG08:
		case WEAPON_AWP:
			return WT_Sniper;
			break;
		default:
			return WT_Knife;
		}
		return WT_Invalid;
	}
};
class player_t : public entity_t {
private:
	template <typename T>
	T& read(uintptr_t offset) {
		return *reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(this) + offset);
	}

	template <typename T>
	void write(uintptr_t offset, T data) {
		*reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(this) + offset) = data;
	}

public:
	NETVAR("DT_CSPlayer", "m_bIsScoped", is_scoped, bool);
	NETVAR("DT_CSPlayer", "m_iHealth", health, int);
	NETVAR("DT_CSPlayer", "m_lifeState", life_state, int);
	NETVAR("DT_CSPlayer", "m_fFlags", flags, int);
	NETVAR("DT_CSPlayer", "m_flFlashDuration", flash_duration, float);
	NETVAR("DT_CSPlayer", "m_iTeamNum", team, int);	
	NETVAR("DT_CSPlayer", "m_ArmorValue", armor, int);
	NETVAR("DT_CSPlayer", "m_bHasHelmet", has_helmet, bool);
	NETVAR("DT_CSPlayer", "m_iAccount", money, int);
	NETVAR("DT_CSPlayer", "m_iShotsFired", shotsfired, int);
	NETVAR("DT_CSPlayer", "m_flLowerBodyYawTarget", lower_body_yaw, float);
	NETVAR("DT_BaseEntity", "m_flSimulationTime", simtime, int);
	NETVAR("DT_CSPlayer", "m_nTickBase", tickbase, int);
	NETVAR("DT_CSPlayer", "m_aimPunchAngle", aimpunchangle, vec3_t);
	NETVAR("DT_CSPlayer", "m_vecPunchAngle", punchangle, vec3_t);
	NETVAR("DT_BaseCombatCharacter", "m_hActiveWeapon", activeweaponhandle, CBaseHandle);
	NETVAR("DT_BasePlayer", "m_flNextAttack", next_attack, float);

	bool is_alive() {
		return life_state() == 0;
	}
	weapon_t* active_weapon();
	bool is_dormant() {
		bool dormant;

		PVOID entity = (PVOID)this;

		__asm
		{
			MOV ECX, entity
			MOV EAX, DWORD PTR DS : [ECX + 0x8]
			MOV EDX, DWORD PTR DS : [EAX + 0x20]
			LEA ESI, DWORD PTR DS : [ECX + 0x8]
			MOV ECX, ESI
			CALL EDX
			MOV dormant, AL
		}

		return dormant;
	}
	
	vec3_t eye_position() {
		return origin() + viewoffset();
	}

	vec3_t& v_angle()
	{
		return *(vec3_t*)((DWORD)this + 0x2EC4 + 0x4);
	}

	bool is_bone_visible(int bone);

	bool IsVisible() {
		for (int i = 0; i < 8; ++i) {
			if (this->is_bone_visible(i))
				return true;
		}
		return false;
	}

	vec3_t get_bone_position(int bone) {
		matrix_t bone_matrices[128];
		if (setup_bones(bone_matrices, 128, 256, 0.0f))
			return vec3_t{ bone_matrices[bone][0][3], bone_matrices[bone][1][3], bone_matrices[bone][2][3] };
		else
			return vec3_t{ };
	}
	
};
