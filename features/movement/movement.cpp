#include "movement.hpp"
#include "../config_vars.hpp"
/*
* EeXOMI strafer is good asf.
*/
class c_movement_data {
public:
	float m_flOldYaw = 0.0f;
	int m_fPrePredFlags = 0;
	int   m_bStopPlayer = 0;
	bool  m_bMinimalSpeed = false;
	bool  m_bFastStop = false;
	bool  m_bStoppedTick = false;
	bool  m_bFakeducking = false;
	bool  m_bStopOk = false;
	bool  jumped_last_tick = false;
	bool  should_fake_jump = false;
	vec3_t m_angPreviousAngles{};
	vec3_t m_angMovementAngle{};
};
inline c_movement_data movedata;


void c_movement::movement_fix(usercmd *cmd, const vec3_t& va) {
   
    
    float yaw, speed;

    vec3_t& move = *(vec3_t*)&cmd->forwardmove;

    speed = move.Length2D();

    yaw = RAD2DEG(atan2(move.y, move.x));
    yaw = DEG2RAD(cmd->viewangles.y - va.y + yaw);

    if (cmd->viewangles.x > 90.00 || cmd->viewangles.x < -90.00)
        move.x = -cos(yaw) * speed;
    else
        move.x = cos(yaw) * speed;

    move.y = sin(yaw) * speed;

}



void c_movement::bhop(usercmd* cmd, entity_t* local_player) {
	
	if (vars.aim) {
		if (!(local_player->flags() & FL_ONGROUND)) {
			cmd->buttons &= ~IN_JUMP;
		}
		return;
	}


	if (!movedata.jumped_last_tick && movedata.should_fake_jump) {
		movedata.should_fake_jump = false;
		cmd->buttons |= IN_JUMP;
	}
	else if (cmd->buttons & IN_JUMP) {
		if (local_player->flags() & FL_ONGROUND) {
			movedata.jumped_last_tick = true;
			movedata.should_fake_jump = true;
		}
		else {
			cmd->buttons &= ~IN_JUMP;
			movedata.jumped_last_tick = false;
		}
	}
	else {
		movedata.jumped_last_tick = false;
		movedata.should_fake_jump = false;
	}
  
}

__forceinline void RotateMovement(float yaw, usercmd* cmd)
{
	const float rot = DEG2RAD(cmd->viewangles.y - yaw);

	const float new_forward = (std::cos(rot) * cmd->forwardmove) - (std::sin(rot) * cmd->sidemove);
	const float new_side = (std::sin(rot) * cmd->forwardmove) + (std::cos(rot) * cmd->sidemove);

	cmd->forwardmove = new_forward;
	cmd->sidemove = new_side;
}


void c_movement::airstrafe(usercmd* cmd, entity_t* local_player) {
	if (!local_player) return;

	if ((local_player->flags() & FL_ONGROUND)) return;

	vec3_t velocity = local_player->m_vecVelocity();
	static float delta, speed = velocity.Length2D(), ideal, ideal2;

	ideal = (speed > 0.f) ? RAD2DEG(std::asin(15.f / speed)) : 90.f;
	ideal2 = (speed > 0.f) ? RAD2DEG(std::asin(30.f / speed)) : 90.f;

	std::clamp(ideal, 0.f, 90.f);
	std::clamp(ideal2, 0.f, 90.f);

	if (local_player->m_vecVelocity().Length2D() < 1.1f)
		return;

	static float yaw_add = 0.f;
	static float cl_sidespeed = 400.f;

	bool back = cmd->buttons & IN_BACK;
	bool forward = cmd->buttons & IN_FORWARD;
	bool right = cmd->buttons & IN_MOVELEFT;
	bool left = cmd->buttons & IN_MOVERIGHT;

	if (back) {
		yaw_add = -180.f;
		if (right)
			yaw_add -= 45.f;
		else if (left)
			yaw_add += 45.f;
	}
	else if (right) {
		yaw_add = 90.f;
		if (back)
			yaw_add += 45.f;
		else if (forward)
			yaw_add -= 45.f;
	}
	else if (left) {
		yaw_add = -90.f;
		if (back)
			yaw_add -= 45.f;
		else if (forward)
			yaw_add += 45.f;
	}
	else {
		yaw_add = 0.f;
	}

	vars.va.y += yaw_add;
	cmd->forwardmove = 0.f;
	cmd->sidemove = 0.f;

	delta = math.normalize_angle(vars.va.y - RAD2DEG(atan2(local_player->m_vecVelocity().y, local_player->m_vecVelocity().x)));

	cmd->sidemove = delta > 0.f ? -cl_sidespeed : cl_sidespeed;

	vars.va.y = math.normalize_angle(vars.va.y - delta);

}


void c_movement::moonwalk(usercmd* cmd, entity_t* local_player) {

	if (!local_player) return;

	if (!(local_player->flags() & FL_ONGROUND)) return;

	if (cmd->sidemove < 0.f) {
		cmd->buttons |= IN_MOVERIGHT;
		cmd->buttons &= ~IN_MOVELEFT;
	}

	if (cmd->sidemove > 0.f) {
		cmd->buttons |= IN_MOVELEFT;
		cmd->buttons &= ~IN_MOVERIGHT;
	}

	if (cmd->forwardmove > 0.f) {
		cmd->buttons |= IN_BACK;
		cmd->buttons &= ~IN_FORWARD;
	}

	if (cmd->forwardmove < 0.f) {
		cmd->buttons |= IN_FORWARD;
		cmd->buttons &= ~IN_BACK;
	}

}



void c_movement::quickstop(usercmd* cmd, entity_t* local_player) {

	if (!local_player) return;


	auto viewangle = cmd->viewangles;
	auto velo = local_player->m_vecVelocity();
	auto flags = local_player->flags();

	if (!(local_player->flags() & FL_ONGROUND)) {
		return;
	}

	if (cmd->buttons & (IN_FORWARD | IN_BACK | IN_MOVELEFT | IN_MOVERIGHT | IN_JUMP)) {
		return;
	}

	float rad_angle = (viewangle.y / 180.0f) * static_cast<float>(M_PI);
	float cos_angle = std::cos(rad_angle);
	float sin_angle = std::sin(rad_angle);

	float rx = (velo.x * cos_angle) + (velo.y * sin_angle);
	float ry = (velo.y * cos_angle) - (velo.x * sin_angle);

	if ((rx != 0.0f) || (ry != 0.0f)) {
		if (rx > 30.0f) {
			cmd->forwardmove = -450.0f;
		}
		else if (rx < -30.0f) {
			cmd->forwardmove = 450.0f;
		}
		if (ry > 30.0f) {
			cmd->sidemove = 450.0f;
		}
		else if (ry < -30.0f) {
			cmd->sidemove = -450.0f;
		}
	}
}