#include "aimbot.hpp"
#include "../../dependencies/global_includes.hpp"
#include "../config_vars.hpp"

__forceinline void VectorAngles(const vec3_t& forward, vec3_t& angles)
{
    double tmp, yaw, pitch;
    double fx = forward[0], fy = forward[1], fz = forward.z;
    if (fy == 0.0 && fx == 0.0)
    {
        yaw = 0.0;
        pitch = 0.0;
    }
    else
    {
        yaw = (atan2(fy, fx) * 180.0 / M_PI);
        if (yaw < 0.0)
            yaw += 360.0;

        tmp = sqrt(fx * fx + fy * fy);
        pitch = (atan2(-fz, tmp) * 180.0 / M_PI);
    }

    angles[0] = pitch;
    angles[1] = yaw;
    angles[2] = 0;
}

inline void VectorSubtract(const vec3_t& a, const vec3_t& b, vec3_t& c)
{
    c.x = a.x - b.x;
    c.y = a.y - b.y;
    c.z = a.z - b.z;
}

inline float VectorNormalize(vec3_t& vec)
{
    float sqrlen = vec.length_sqr() + 1.0e-10f, invlen;
    invlen = 1.f / sqrt(sqrlen);
    vec.x *= invlen;
    vec.y *= invlen;
    vec.z *= invlen;
    return sqrlen * invlen;
}

inline void VectorNormalizeFast(vec3_t& vec)
{
    VectorNormalize(vec);
}

bool c_aimbot::check_visible(vec3_t& vecAbsStart, vec3_t& vecAbsEnd, player_t* Target, player_t* LocalPlayer)
{
    auto local_player = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player()));

    ray_t ray;
    ray.init(vecAbsStart, vecAbsEnd);

    trace_filter_skip_one_entity filter{ Target };

    trace_t trace;
    interfaces::tracing->trace_ray(&ray, MASK_SOLID, &filter, &aim_trace);

    return (aim_trace.m_fraction == 1.0f);
}

bool IsReadyToShoot(player_t* LocalPlayer, weapon_t* Weapon)
{
    if (!LocalPlayer) return false;
    if (!Weapon) return false;

    int WeaponID = Weapon->get_weapon_id();
    float curtime = interfaces::globals->interval_per_tick * LocalPlayer->tickbase();

    return Weapon->next_primary_attack() <= curtime && LocalPlayer->next_attack() <= curtime && Weapon->clip1_count() > 0;
}

float NormalizeAngle(float angle)
{
    while (angle < -180.0f) angle += 360.0f;
    while (angle > 180.0f) angle -= 360.0f;
    return angle;
}

float GetFov(const vec3_t& viewAngle, const vec3_t& aimAngle)
{
    vec3_t delta = aimAngle - viewAngle;
    delta.x = NormalizeAngle(delta.x);
    delta.y = NormalizeAngle(delta.y);
    return sqrt(delta.x * delta.x + delta.y * delta.y);
}

int Rate(player_t* LocalPlayer, player_t* Ent)
{
    int rate = 0;
    rate = LocalPlayer->get_abs_origin().distance(Ent->get_abs_origin());
    return rate;
}

void c_aimbot::reset()
{
    distance = FLT_MAX;
    temp = INT_MAX;
    target_index = -1;
    is_aimbotting = false;
}


int TimeToTicks(float dt) {
    return static_cast<int>(0.5f + dt / interfaces::globals->interval_per_tick);
}

void c_aimbot::main(usercmd* cmd, player_t* local_player)
{
    reset();

    for (auto i = 64; i >= 1; --i)
    {
        if (i == interfaces::engine->get_local_player()) continue;
        player_t* p = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(i));
        if (p == 0) continue;
        if (p->is_dormant()) continue;

        int bone_id = vars.bone;

        vec3_t start = vec3_t(local_player->eye_position().x, local_player->eye_position().y, local_player->get_bone_position(8).z);
        vec3_t end = p->get_bone_position(bone_id);

        bool visible = check_visible(start, end, p, local_player);

        if (!p || p == local_player || p->health() <= 0 || p->team() == local_player->team() || !p->team() || p->team() == 0 || p->life_state() == 258 || p->life_state() == 257 || !visible) {
            continue;
        }

        vec3_t eyepos = local_player->get_bone_position(8);
        vec3_t enemy = p->get_bone_position(bone_id);

        auto newAngles = start.calc_angle(p->get_bone_position(bone_id));
        vec3_t original_angles;
        interfaces::engine->get_view_angles_alternative(original_angles);
        float currentFov = GetFov(original_angles, newAngles);
        if (currentFov > vars.aimfov) continue;

        int rate = Rate(local_player, p);
        if (rate > temp) continue;

        if (visible)
        {
            if (!local_player->active_weapon())
                return;
            auto weaponID = local_player->active_weapon()->get_weapon_id();
            if (!weaponID)
                return;

            if (local_player && weaponID != 49 && IsReadyToShoot(local_player, local_player->active_weapon()))
            {
                if (!vars.autofire)
                {
                    if (cmd->buttons & IN_ATTACK)
                    {
                        //cmd->tick_count = TimeToTicks(p->simtime());

                        if (vars.smooth > 0)
                        {
                            float smooth_factor = vars.smooth / 100.0f;
                            float sin_factor = sin(smooth_factor * M_PI * 0.5);

                            newAngles.x = original_angles.x + (newAngles.x - original_angles.x) * sin_factor;
                            newAngles.y = original_angles.y + (newAngles.y - original_angles.y) * sin_factor;
                        }

                        if (vars.saim)
                        {
                            cmd->viewangles = newAngles;
                        }
                        else
                        {
                            interfaces::engine->set_view_angles(newAngles);
                        }

                        is_aimbotting = true;
                    }
                }
                else if (vars.autofire)
                {
                    if (vars.smooth > 0)
                    {
                        float smooth_factor = vars.smooth / 100.0f;
                        float sin_factor = sin(smooth_factor * M_PI * 0.5);

                        newAngles.x = original_angles.x + (newAngles.x - original_angles.x) * sin_factor;
                        newAngles.y = original_angles.y + (newAngles.y - original_angles.y) * sin_factor;
                    }

                    if (vars.saim)
                    {
                        cmd->viewangles = newAngles;
                    }
                    else
                    {
                        interfaces::engine->set_view_angles(newAngles);
                    }

                    is_aimbotting = true;
                }
            }

            target_index = i;
            temp = rate;
        }
    }

    if (is_aimbotting && target_index != -1 && vars.autofire)
    {
        auto weapon_id = local_player->active_weapon()->get_weapon_id();
        if (weapon_id == 29 || weapon_id == 21)
        {
            cmd->buttons |= IN_ATTACK;
            return;
        }
        else if (weapon_id == 49)
            return;

        if (IsReadyToShoot(local_player, local_player->active_weapon()))
        {
            if (lastShot)
            {
                cmd->buttons &= ~IN_ATTACK;
                lastShot = false;
            }
            else
            {
                cmd->buttons |= IN_ATTACK;
                lastShot = true;
            }
        }
    }
}





