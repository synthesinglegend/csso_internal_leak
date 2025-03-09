#pragma once
#include "../../dependencies/global_includes.hpp"
class c_movement {
public:
	void bhop(usercmd* cmd, entity_t* local_player);
	void movement_fix(usercmd* cmd, const vec3_t& va);
	void moonwalk(usercmd* cmd, entity_t* local_player);
	void quickstop(usercmd* cmd, entity_t* local_player);
	void airstrafe(usercmd* cmd, entity_t* local_player);
};
inline std::unique_ptr<c_movement> g_movement = std::make_unique<c_movement>();