#pragma once
#include "global_vars.hpp"
#include "engine_client.hpp"
#include "client_dll.hpp"
#include "entity_list.hpp"
#include "client_mode.hpp"
#include "panel.hpp"
#include "surface.hpp"
#include "player_info_manager.hpp"
#include "material_system.hpp"
#include "input.hpp"
#include "studio_render.hpp"
#include "trace.hpp"
#include "mdl_info.hpp"
#include "model_render.hpp"
#include "i_prediction.h"
#include "renderview.hpp"
#include "../../sdk/cvars.hpp"

namespace interfaces {
	extern c_global_vars* globals;
	extern i_engine_client* engine;
	extern client_dll* client;
	extern client_mode_shared* client_mode;
	extern ii_input* input;
	extern i_entity_list* entity_list;
	extern icvar* convars;
	extern i_panel* panel;
	extern i_surface* surface;
	extern iplayerinfomanager* player_mgr;
	extern i_material_system* material_system;
	extern istudio_render* studio_render;
	extern trace* tracing;
	extern iv_model_info* mdl_info;
	extern iv_model_render* mdl_render;
	extern i_prediction* prediction;
	extern i_game_movement* game_movement;
	extern IVRenderView* render_view;
	extern IDirect3DDevice9* device;
	void initialize();
	void* create_interface(const char* mod, const char* iface);
}