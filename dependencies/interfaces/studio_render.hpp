#pragma once
#include <cstdint>
#include "../utils/call.hpp"

// https://gitlab.com/KittenPopo/csgo-2018-source/-/blob/main/public/istudiorender.h#L201
#define MAX_QPATH  260
using quaternion = float[4];
using rad_euler = float[3];
#define BONE_CALCULATE_MASK             0x1F
#define BONE_PHYSICALLY_SIMULATED       0x01    // bone is physically simulated when physics are active
#define BONE_PHYSICS_PROCEDURAL         0x02    // procedural when physics is active
#define BONE_ALWAYS_PROCEDURAL          0x04    // bone is always procedurally animated
#define BONE_SCREEN_ALIGN_SPHERE        0x08    // bone aligns to the screen, not constrained in motion.
#define BONE_SCREEN_ALIGN_CYLINDER      0x10    // bone aligns to the screen, constrained by it's own axis.

#define BONE_USED_MASK                  0x0007FF00
#define BONE_USED_BY_ANYTHING           0x0007FF00
#define BONE_USED_BY_HITBOX             0x00000100    // bone (or child) is used by a hit box
#define BONE_USED_BY_ATTACHMENT         0x00000200    // bone (or child) is used by an attachment point
#define BONE_USED_BY_VERTEX_MASK        0x0003FC00
#define BONE_USED_BY_VERTEX_LOD0        0x00000400    // bone (or child) is used by the toplevel model via skinned vertex
#define BONE_USED_BY_VERTEX_LOD1        0x00000800
#define BONE_USED_BY_VERTEX_LOD2        0x00001000
#define BONE_USED_BY_VERTEX_LOD3        0x00002000
#define BONE_USED_BY_VERTEX_LOD4        0x00004000
#define BONE_USED_BY_VERTEX_LOD5        0x00008000
#define BONE_USED_BY_VERTEX_LOD6        0x00010000
#define BONE_USED_BY_VERTEX_LOD7        0x00020000
#define BONE_USED_BY_BONE_MERGE         0x00040000    // bone is available for bone merge to occur against it

#define BONE_USED_BY_VERTEX_AT_LOD(lod) ( BONE_USED_BY_VERTEX_LOD0 << (lod) )
#define BONE_USED_BY_ANYTHING_AT_LOD(lod) ( ( BONE_USED_BY_ANYTHING & ~BONE_USED_BY_VERTEX_MASK ) | BONE_USED_BY_VERTEX_AT_LOD(lod) )

#define MAX_NUM_LODS 8
#define MAXSTUDIOBONES		128		// total bones actually used

#define BONE_TYPE_MASK                  0x00F00000
#define BONE_FIXED_ALIGNMENT            0x00100000    // bone can't spin 360 degrees, all interpolation is normalized around a fixed orientation

#define BONE_HAS_SAVEFRAME_POS          0x00200000    // Vector48
#define BONE_HAS_SAVEFRAME_ROT64        0x00400000    // Quaternion64
#define BONE_HAS_SAVEFRAME_ROT32        0x00800000    // Quaternion32
class cstudiohdr;
class iclient_renderable;
class cdraw_modelinfo
{
public:
	cstudiohdr* studioHdr;
	void* hardwareData;
	std::int32_t decals;
	std::int32_t skin;
	std::int32_t body;
	std::int32_t hitboxSet;
	iclient_renderable* renderable;

};

// https://gitlab.com/KittenPopo/csgo-2018-source/-/blob/main/public/istudiorender.h#L324
class i_material;
class istudio_render
{
public:
	enum
	{
		STUDIORENDER_DRAW_ENTIRE_MODEL = 0,
		STUDIORENDER_DRAW_OPAQUE_ONLY = 0x01,
		STUDIORENDER_DRAW_TRANSLUCENT_ONLY = 0x02,
		STUDIORENDER_DRAW_GROUP_MASK = 0x03,
		STUDIORENDER_DRAW_NO_FLEXES = 0x04,
		STUDIORENDER_DRAW_STATIC_LIGHTING = 0x08,
		STUDIORENDER_DRAW_ACCURATETIME = 0x10,		// Use accurate timing when drawing the model.
		STUDIORENDER_DRAW_NO_SHADOWS = 0x20,
		STUDIORENDER_DRAW_GET_PERF_STATS = 0x40,
		STUDIORENDER_DRAW_WIREFRAME = 0x80,
		STUDIORENDER_DRAW_ITEM_BLINK = 0x100,
		STUDIORENDER_SHADOWDEPTHTEXTURE = 0x200,
		STUDIORENDER_UNUSED = 0x400,
		STUDIORENDER_SKIP_DECALS = 0x800,
		STUDIORENDER_MODEL_IS_CACHEABLE = 0x1000,
		STUDIORENDER_SHADOWDEPTHTEXTURE_INCLUDE_TRANSLUCENT_MATERIALS = 0x2000,
		STUDIORENDER_NO_PRIMARY_DRAW = 0x4000,
		STUDIORENDER_SSAODEPTHTEXTURE = 0x8000,
	};

	enum EOverrideType : std::int32_t
	{
		OVERRIDE_NORMAL = 0,
		OVERRIDE_BUILD_SHADOWS,
		OVERRIDE_DEPTH_WRITE,
		OVERRIDE_SELECTIVE,
		OVERRIDE_SSAO_DEPTH_WRITE,
	};

	constexpr void SetColorModulation(const float* color) noexcept
	{
		Call<void>(this, 27, color);
	}

	void SetAlphaModulation(float flAlpha)
	{
		get_vfunc<28, void>(this, flAlpha);
	}


	void ForcedMaterialOverride(i_material* material, std::int32_t type = OVERRIDE_NORMAL, std::int32_t index = -1)
	{
		//Call<void>(this, 33, material, type, index);
		get_vfunc<33, void>(this, material, type);
	}


	constexpr bool IsForcedMaterialOverride() noexcept
	{
		return Call<bool>(this, 34);
	}
};
struct studio_box_t {
	int bone;
	int group;
	vec3_t mins;
	vec3_t maxs;
	int name_index;
	int pad01[3];
	float radius;
	int pad02[4];
};
struct studio_hitbox_set_t {
	int name_index;
	int hitbox_count;
	int hitbox_index;

	inline char* const name(void) const {
		return ((char*)this) + name_index;
	}
	inline studio_box_t* hitbox(int i) const {
		return (studio_box_t*)(((unsigned char*)this) + hitbox_index) + i;
	}
};
struct mstudiobone_t
{
	int name_index;
	inline char* const name(void) const {
		return ((char*)this) + name_index;
	}
	int parent;
	int bone_controller[6];

	vec3_t pos;
	quaternion quat;
	rad_euler rotation;

	vec3_t pos_scale;
	vec3_t rot_scale;

	matrix_t pose_to_bone;
	quaternion quat_alignement;
	int flags;
	int proc_type;
	int proc_index;
	mutable int physics_bone;

	inline void* procedure() const {
		if (proc_index == 0) return NULL;
		else return(void*)(((unsigned char*)this) + proc_index);
	};

	int surface_prop_idx;
	inline char* const surface_prop(void) const {
		return ((char*)this) + surface_prop_idx;
	}
	inline int get_surface_prop(void) const {
		return surf_prop_lookup;
	}

	int contents;
	int surf_prop_lookup;
	int unused[7];
};
class studio_hdr_t {
public:
	int id;
	int version;
	long checksum;
	char name_char_array[64];
	int length;
	vec3_t eye_pos;
	vec3_t illium_pos;
	vec3_t hull_mins;
	vec3_t hull_maxs;
	vec3_t mins;
	vec3_t maxs;
	int flags;
	int bones_count;
	int bone_index;
	int bone_controllers_count;
	int bone_controller_index;
	int hitbox_sets_count;
	int hitbox_set_index;
	int local_anim_count;
	int local_anim_index;
	int local_seq_count;
	int local_seq_index;
	int activity_list_version;
	int events_indexed;
	int textures_count;
	int texture_index;

	studio_hitbox_set_t* hitbox_set(int i) {
		if (i > hitbox_sets_count) return nullptr;
		return (studio_hitbox_set_t*)((uint8_t*)this + hitbox_set_index) + i;
	}
	

	mstudiobone_t* bone(int i) {
		if (i > bones_count) return nullptr;
		return (mstudiobone_t*)((uint8_t*)this + bone_index) + i;
	}
	
};