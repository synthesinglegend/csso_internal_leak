#pragma once
#include "../../sdk/vector3d.hpp"
#include "../math/math.hpp"
#include "../utils/call.hpp"
#include "../../sdk/entity_structs.hpp"
#define DISPSURF_FLAG_SURFACE		(1<<0)
#define DISPSURF_FLAG_WALKABLE		(1<<1)
#define DISPSURF_FLAG_BUILDABLE		(1<<2)
#define DISPSURF_FLAG_SURFPROP1		(1<<3)
#define DISPSURF_FLAG_SURFPROP2		(1<<4)
enum Contents_t {
    CONTENTS_EMPTY = 0,
    CONTENTS_SOLID = 0x1,
    CONTENTS_WINDOW = 0x2,
    CONTENTS_AUX = 0x4,
    CONTENTS_GRATE = 0x8,
    CONTENTS_SLIME = 0x10,
    CONTENTS_WATER = 0x20,
    CONTENTS_BLOCKLOS = 0x40,
    CONTENTS_OPAQUE = 0x80,
    CONTENTS_TESTFOGVOLUME = 0x100,
    CONTENTS_UNUSED = 0x200,
    CONTENTS_BLOCKLIGHT = 0x400,
    CONTENTS_TEAM1 = 0x800,
    CONTENTS_TEAM2 = 0x1000,
    CONTENTS_IGNORE_NODRAW_OPAQUE = 0x2000,
    CONTENTS_MOVEABLE = 0x4000,
    CONTENTS_AREAPORTAL = 0x8000,
    CONTENTS_PLAYERCLIP = 0x10000,
    CONTENTS_MONSTERCLIP = 0x20000,
    CONTENTS_CURRENT_0 = 0x40000,
    CONTENTS_CURRENT_90 = 0x80000,
    CONTENTS_CURRENT_180 = 0x100000,
    CONTENTS_CURRENT_270 = 0x200000,
    CONTENTS_CURRENT_UP = 0x400000,
    CONTENTS_CURRENT_DOWN = 0x800000,
    CONTENTS_ORIGIN = 0x1000000,
    CONTENTS_MONSTER = 0x2000000,
    CONTENTS_DEBRIS = 0x4000000,
    CONTENTS_DETAIL = 0x8000000,
    CONTENTS_TRANSLUCENT = 0x10000000,
    CONTENTS_LADDER = 0x20000000,
    CONTENTS_HITBOX = 0x40000000,
};

enum Masks_t {
    MASK_ALL = 0xFFFFFFFF,
    MASK_SOLID = CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_WINDOW | CONTENTS_MONSTER | CONTENTS_GRATE,
    MASK_PLAYERSOLID = CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_PLAYERCLIP | CONTENTS_WINDOW | CONTENTS_MONSTER | CONTENTS_GRATE,
    MASK_NPCSOLID = CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_MONSTERCLIP | CONTENTS_WINDOW | CONTENTS_MONSTER | CONTENTS_GRATE,
    MASK_NPCFLUID = CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_MONSTERCLIP | CONTENTS_WINDOW | CONTENTS_MONSTER | CONTENTS_GRATE,
    MASK_WATER = CONTENTS_WATER | CONTENTS_MOVEABLE | CONTENTS_SLIME,
    MASK_OPAQUE = CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_OPAQUE,
    MASK_OPAQUE_AND_NPCS = MASK_OPAQUE | CONTENTS_MONSTER,
    MASK_BLOCKLOS = CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_BLOCKLOS,
    MASK_BLOCKLOS_AND_NPCS = MASK_BLOCKLOS | CONTENTS_MONSTER,
    MASK_VISIBLE = MASK_OPAQUE | CONTENTS_IGNORE_NODRAW_OPAQUE,
    MASK_VISIBLE_AND_NPCS = MASK_OPAQUE_AND_NPCS | CONTENTS_IGNORE_NODRAW_OPAQUE,
    MASK_SHOT = CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_MONSTER | CONTENTS_WINDOW | CONTENTS_DEBRIS | CONTENTS_GRATE | CONTENTS_HITBOX,
    MASK_SHOT_BRUSHONLY = CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_WINDOW | CONTENTS_DEBRIS,
    MASK_SHOT_HULL = CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_MONSTER | CONTENTS_WINDOW | CONTENTS_DEBRIS | CONTENTS_GRATE,
    MASK_SHOT_PORTAL = CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_WINDOW | CONTENTS_MONSTER,
    MASK_SOLID_BRUSHONLY = CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_WINDOW | CONTENTS_GRATE,
    MASK_PLAYERSOLID_BRUSHONLY = CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_WINDOW | CONTENTS_PLAYERCLIP | CONTENTS_GRATE,
    MASK_NPCSOLID_BRUSHONLY = CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_WINDOW | CONTENTS_MONSTERCLIP | CONTENTS_GRATE,
    MASK_NPCWORLDSTATIC = CONTENTS_SOLID | CONTENTS_WINDOW | CONTENTS_MONSTERCLIP | CONTENTS_GRATE,
    MASK_NPCWORLDSTATIC_FLUID = CONTENTS_SOLID | CONTENTS_WINDOW | CONTENTS_MONSTERCLIP,
    MASK_SPLITAREPORTAL = CONTENTS_WATER | CONTENTS_SLIME,
    MASK_CURRENT = CONTENTS_CURRENT_0 | CONTENTS_CURRENT_90 | CONTENTS_CURRENT_180 | CONTENTS_CURRENT_270 | CONTENTS_CURRENT_UP | CONTENTS_CURRENT_DOWN,
    MASK_DEADSOLID = CONTENTS_SOLID | CONTENTS_PLAYERCLIP | CONTENTS_WINDOW | CONTENTS_GRATE,
    CS_MASK_SHOOT = MASK_SOLID | CONTENTS_DEBRIS
};

class IHandleEntity;
class ray_t {

public:

    vec_aligned_t  m_Start;    // starting point, centered within the extents
    vec_aligned_t  m_Delta;    // direction + length of the ray
    vec_aligned_t  m_StartOffset;    // Add this to m_Start to get the actual ray start
    vec_aligned_t  m_Extents;    // Describes an axis aligned box extruded along a ray

    //const matrix3x4_t* m_world_axis_transform;

    bool    m_IsRay;    // are the extents zero?
    bool    m_IsSwept;    // is delta != 0?


    //ray_t() : m_world_axis_transform(NULL) { }
    ray_t() {}

    void init(vec3_t const& start, vec3_t const& end)
    {
        //(&end);
        math.vec_sub(end, start, m_Delta);

        m_IsSwept = (m_Delta.length_sqr() != 0);

        m_Extents.init();
        m_IsRay = true;

        // Offset m_Start to be in the center of the box...
        m_StartOffset.init();
        math.vector_copy(start, m_Start);
    }

    void init(vec3_t const& start, vec3_t const& end, vec3_t const& mins, vec3_t const& maxs)
    {
        //Assert(&end);
        math.vector_subtract_(end, start, m_Delta);

        m_IsSwept = (m_Delta.length_sqr() != 0);

        math.vector_subtract_(maxs, mins, m_Extents);
        m_Extents *= 0.5f;
        m_IsRay = (m_Extents.length_sqr() < 1e-6);

        // Offset m_Start to be in the center of the box...
        math.vec_add(mins, maxs, m_StartOffset);
        m_StartOffset *= 0.5f;
        math.vec_add(start, m_StartOffset, m_Start);
        m_StartOffset *= -1.0f;
    }

    // compute inverse delta
    vec3_t InvDelta() const
    {
        vec3_t vecInvDelta;
        for (int iAxis = 0; iAxis < 3; ++iAxis)
        {
            if (m_Delta[iAxis] != 0.0f)
            {
                vecInvDelta[iAxis] = 1.0f / m_Delta[iAxis];
            }
            else
            {
                vecInvDelta[iAxis] = FLT_MAX;
            }
        }
        return vecInvDelta;
    }

};

struct csurface_t
{
    const char* name;
    short            surfaceProps;
    uint16_t     flags;
};

struct cplane_t
{
    vec3_t  normal;
    float   dist;
    unsigned char  type;
    unsigned char signbits;
    unsigned char pad[2];
   
};

class trace_t {
public:

    // Displacement flags tests.
    bool IsDispSurface(void) { return ((m_displacement_flags & DISPSURF_FLAG_SURFACE) != 0); }
    bool IsDispSurfaceWalkable(void) { return ((m_displacement_flags & DISPSURF_FLAG_WALKABLE) != 0); }
    bool IsDispSurfaceBuildable(void) { return ((m_displacement_flags & DISPSURF_FLAG_BUILDABLE) != 0); }
    bool IsDispSurfaceProp1(void) { return ((m_displacement_flags & DISPSURF_FLAG_SURFPROP1) != 0); }
    bool IsDispSurfaceProp2(void) { return ((m_displacement_flags & DISPSURF_FLAG_SURFPROP2) != 0); }

public:

    vec3_t   m_startpos;
    vec3_t   m_endpos;
    cplane_t m_plane;
    float    m_fraction;
    int      m_contents;
    uint16_t m_displacement_flags;
    bool     m_allsolid;
    bool     m_startsolid;

    float            fractionleftsolid;
    csurface_t        surface;
    int                hitgroup;
    short            physicsbone;
    player_t* m_pEnt;
    int                hitbox;
    trace_t() {}
};



enum TraceType_t
{
    TRACE_EVERYTHING = 0,
    TRACE_WORLD_ONLY,                // NOTE: This does *not* test static props!!!
    TRACE_ENTITIES_ONLY,            // NOTE: This version will *not* test static props
    TRACE_EVERYTHING_FILTER_PROPS,    // NOTE: This version will pass the IHandleEntity for props through the filter, unlike all other filters
};
class i_trace_filter {
public:
    virtual bool ShouldHitEntity(void* pEntity, int contentsMask) = 0;
    virtual TraceType_t GetTraceType() const = 0;
};

class trace_filter : public i_trace_filter {
public:
    bool ShouldHitEntity(void* pEntityHandle, int contentsMask) {
        return (pEntityHandle != skip);
    }

    TraceType_t GetTraceType() const {
        return TRACE_EVERYTHING;
    }

    void* skip;
};

class trace_filter_skip_one_entity : public i_trace_filter {
public:
    trace_filter_skip_one_entity(void* pPassEnt1) {
        passentity1 = pPassEnt1;
        ent1 = 0;
        ent2 = 0;
    }

    virtual bool ShouldHitEntity(void* pEntityHandle, int contentsMask) {
        return (pEntityHandle != passentity1);
    }

    virtual TraceType_t GetTraceType() const {
        return TRACE_EVERYTHING;
    }
    void* passentity1;
private:
    PVOID ent1;
    PVOID ent2;
};
class trace_filter_one_entity2 : public i_trace_filter {
public:
    bool ShouldHitEntity(void* pEntityHandle, int contentsMask) {
        return (pEntityHandle == pEntity);
    }

    TraceType_t GetTraceType() const {
        return TRACE_ENTITIES_ONLY;
    }

    void* pEntity;
};

class trace_filter_skip_two_entities : public i_trace_filter {
public:
    trace_filter_skip_two_entities(void* pPassEnt1, void* pPassEnt2) {
        passentity1 = pPassEnt1;
        passentity2 = pPassEnt2;
    }

    virtual bool ShouldHitEntity(void* pEntityHandle, int contentsMask) {
        return !(pEntityHandle == passentity1 || pEntityHandle == passentity2);
    }

    virtual TraceType_t GetTraceType() const {
        return TRACE_EVERYTHING;
    }

    void* passentity1;
    void* passentity2;
};



class trace_entity : public i_trace_filter {
public:
    bool ShouldHitEntity(void* pEntityHandle, int contentsMask) {
        return !(pEntityHandle == pSkip1);
    }

    TraceType_t GetTraceType() const {
        return TRACE_ENTITIES_ONLY;
    }

    void* pSkip1;
};

class trace_world_only : public i_trace_filter {
public:
    bool ShouldHitEntity(void* pEntityHandle, int contentsMask) {
        return false;
    }

    TraceType_t GetTraceType() const {
        return TRACE_EVERYTHING;
    }

    void* pSkip1;
};

class collideable_t;
class trace {
public:
    virtual int get_point_contents(const vec3_t& pos, int mask = MASK_ALL,
        IHandleEntity** ent = nullptr) = 0;
    virtual int get_point_contents_collideable(collideable_t* collide, const vec3_t& pos) = 0;
    virtual int       GetPointContents_WorldOnly(const vec3_t& vecAbsPosition, int contentsMask = MASK_ALL) = 0;
    virtual void clip_ray_to_entity(const ray_t& ray, unsigned int mask, player_t* ent, trace_t* trace) = 0;
    virtual void clip_ray_to_collideable(const ray_t& ray, unsigned int mask, collideable_t* collide, trace_t* trace) =
        0;
    virtual void trace_ray(const ray_t* ray, unsigned int mask, i_trace_filter* filter, trace_t* trace) = 0;
};