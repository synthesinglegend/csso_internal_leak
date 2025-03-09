#pragma once
#include "../../dependencies/global_includes.hpp"
#include "../../sdk/matrix.hpp"

class c_aimbot {
public:
	//void aimbot(usercmd* cmd);
	void reset();
	void main(usercmd* cmd, player_t* local_player);
	bool check_visible(vec3_t& vecAbsStart, vec3_t& vecAbsEnd, player_t* Target, player_t* LocalPlayer);

	vec3_t vec_direction, vec_final_direction, temp_direction;
	vec3_t vec_corners[10];

	int target_index, temp;
	float distance;
	bool is_aimbotting;

	trace_t aim_trace;
	int bestTarget;
	float bestFov;

	struct backtrack_data_t {
		vec3_t position;   
		float simtime;     
		int tick_count;   
	};

	std::unordered_map<int, std::vector<backtrack_data_t>> backtrack_data;  //  арта дл€ хранени€ данных backtrack по индексу игрока


private:
	bool lastShot = false;
};
inline std::unique_ptr<c_aimbot> g_aimbot = std::make_unique<c_aimbot>();