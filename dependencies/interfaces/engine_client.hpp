#pragma once
#include "../../sdk/vector3d.hpp"
#include "../../sdk/vector2d.hpp"
#include "../../sdk/view_matrix.hpp"
#include "../utils/call.hpp"
typedef struct
{
	char			name[32]; // scoreboard information
	int				user_id; // local server user ID, unique while server is running
	char			guid[33]; // global unique player identifer
	__int32			friends_id; // friends identification number
	char			friends_name[32]; // friends name
	bool			fakeplayer; // true, if player is a bot controlled by game.dll
	bool			ishltv; // true if player is the HLTV proxy
	unsigned int	custom_files[4]; // (CRC32_t) custom files CRC for this player
	unsigned char	files_downloaded; // this counter increases each time the server downloaded a new file
	char pad[200];
} player_info_t;
class i_engine_client {
public:
	
	int get_local_player() {
		using original_fn = int(__thiscall*)(i_engine_client*);
		return (*(original_fn**)this)[12](this);
	}
	int get_player_for_user_id(int user_id) {
		using original_fn = int(__thiscall*)(i_engine_client*, int);
		return (*(original_fn**)this)[9](this, user_id);
	}
	void set_view_angles(vec3_t& angles) {
		using original_fn = void(__thiscall*)(i_engine_client*, vec3_t&);
		return (*(original_fn**)this)[20](this, angles);
	}
	/*
	vec3_t get_view_angles() {
		vec3_t temp;
		using original_fn = void(__thiscall*)(i_engine_client*, vec3_t&);
		(*(original_fn**)this)[19](this, temp);
		return temp;
	}
	*/
	void get_view_angles_alternative(vec3_t& angles) {
		return call_virtual<void(__thiscall*)(void*, vec3_t&)>(this, 19)(this, angles);
	}
	void get_player_info(int index, player_info_t* info) {
		using original_fn = void(__thiscall*)(i_engine_client*, int, player_info_t*);
		return (*(original_fn**)this)[8](this, index, info);
	}
	void get_screen_size(int& width, int& height) {
		using original_fn = void(__thiscall*)(i_engine_client*, int&, int&);
		return (*(original_fn**)this)[5](this, width, height);
	}
	bool is_in_game() {
		using original_fn = bool(__thiscall*)(i_engine_client*);
		return (*(original_fn**)this)[26](this);
	}
	bool is_connected() {
		using original_fn = bool(__thiscall*)(i_engine_client*);
		return (*(original_fn**)this)[27](this);
	}
	view_matrix_t& world_to_screen_matrix() {
		view_matrix_t temp;
		using original_fn = view_matrix_t & (__thiscall*)(i_engine_client*);
		return (*(original_fn**)this)[36](this);
	}
	void execute_cmd(const char* cmd) {
		using original_fn = void(__thiscall*)(i_engine_client*, const char*);
		return (*(original_fn**)this)[106](this, cmd); // this always seems to crash whilst debugging, just feel free to continue.
	}
};