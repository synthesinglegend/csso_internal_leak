#include "../dependencies/global_includes.hpp"
#include "../dependencies/utils/fnv.hpp"
#include "../features/misc/misc.hpp"
#include "../features/visuals/visuals.hpp"
#include "../features/aimbot/aimbot.hpp"
#include "../dependencies/input_handler/input_handler.hpp"
#include "../features/movement/movement.hpp"
#include <sstream>
#include "../features/anti-aimbot/antiaim.hpp"
#include "../features/config_vars.hpp"
#include "../features/prediction/prediction.hpp"
#include <Windows.h>
#include <tlhelp32.h>
#include "../features/menu/menu.hpp"
#include "../dependencies/imgui/dx9/imgui_impl_dx9.h"
#include "../dependencies/imgui/dx9/imgui_impl_dx9.cpp"
#include "../sdk/cvars.hpp"
#include "../sdk/checksum_md5.h"
#include "../dependencies/ctx.hpp"
hooked::paint_traverse_fn paint_orig = nullptr;
hooked::create_move_fn createmove_orig = nullptr;
std::unique_ptr<vmt_hook> hooked::panel_hook;

std::unique_ptr<vmt_hook> hooked::create_move_hook;

std::unique_ptr<vmt_hook> hooked::frame_stage_notify_hook;

std::unique_ptr<vmt_hook> hooked::draw_model_ex_hook;

std::unique_ptr<vmt_hook> renderview_hook;

std::unique_ptr<vmt_hook> endscene_hook;
c_renderer render;

/*
* This was my first experience of using VMT Hooks.
* Very, very messy code.
* If you any 'good-looking' code - it was written by (nightmare__)
* See nonsense - it was twod1e.
* Crash on unload btw due to p100 endscene hook.
*/
const std::wstring csso_int = L"csso_internal";

void __stdcall hooked::paint_traverse(unsigned int panel, bool force_repaint, bool allow_force) {
	if (!strcmp(interfaces::panel->get_name(panel), "HudZoom"))
	{
		return;
	}

	reinterpret_cast<paint_traverse_fn>(panel_hook->get_original(41))(interfaces::panel, panel, force_repaint, allow_force);

	const char* pszPanelName = interfaces::panel->get_name(panel);

	if (pszPanelName && pszPanelName[0] == 'F' && pszPanelName[5] == 'O') {

		if (GetAsyncKeyState(VK_INSERT) & 1)
		{
			vars.menu = !vars.menu;
		}
		std::stringstream ss;


		int width, height;
		interfaces::engine->get_screen_size(width, height);
		ss << "*removed* - " __DATE__ << " " << "| mess cleaned";



		render.draw_filled_rect(width - 275, 4, 269, 20, color(33, 35, 47, 255));
		render.draw_outline(width - 275, 4, 269, 20, color(30, 30, 41, 255));
		render.draw_text(width - 270, 7, render.name_font_big, ss.str().c_str(), false, color(255, 255, 255, 255));
		if (interfaces::engine->is_in_game() && interfaces::engine->is_connected())
		{

			g_visuals->run();

			if (vars.esp_noflash) {
				g_misc->remove_flash();
			}

			g_misc->remove_scope();

			if (vars.dm) {
				g_visuals->dm_run();
			}	

		}
	}
}

void __fastcall hooked::frame_stage_notify(void* ecx, void* edx, ClientFrameStage_t stage)
{

	switch (stage)
	{
	case FRAME_RENDER_START:
	{
		auto local_player = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player()));

		g_ctx->local_player->punchangle().vec3_t::vec3_t();

		break;
	}
	case FRAME_RENDER_END:
	{

		break;
	}
	case FRAME_NET_UPDATE_START:
	{

		break;
	}
	case FRAME_NET_UPDATE_END:
	{

		break;
	}
	case FRAME_NET_UPDATE_POSTDATAUPDATE_START:
	{

		break;
	}
	case FRAME_NET_UPDATE_POSTDATAUPDATE_END:
	{

		break;
	}
	}


	return reinterpret_cast<frame_stage_notify_fn>(frame_stage_notify_hook->get_original(35))(interfaces::client, stage);

}



void on_createmove(usercmd* cmd)
{
	vars.va = cmd->viewangles;

	antiaim_(cmd);

	g_prediction->start_predicting(cmd);

	if (vars.bhop_e)
	{
		g_movement->bhop(cmd, g_ctx->local_player);
		
	}

	vars.m_strafe_angles = cmd->viewangles;

	if (vars.airstrafe) {
		g_movement->airstrafe(cmd, g_ctx->local_player);
	}

	if (vars.aim)
	{
		g_aimbot->main(cmd, g_ctx->local_player);
	}
	

	g_prediction->stop_predicting(cmd);
	g_movement->movement_fix(cmd, vars.va);
	g_misc->thirdperson(cmd);

	g_misc->bSendPacket();

	if (vars.fakelag) {
		g_misc->fakelag(*vars.m_packet);
	}
	else {
		*vars.m_packet = true;
	}
	
	if (vars.m_packetbool) {
		vars.actualang.x = cmd->viewangles.x;
		vars.actualang.y = cmd->viewangles.y;
	}

	if (vars.norecoil) {
		g_misc->norecoil(cmd);
	} 

	if (vars.misc_moonwalk) { 
		g_movement->moonwalk(cmd, g_ctx->local_player);
	}

	if (vars.faststop) {
		g_movement->quickstop(cmd, g_ctx->local_player);
	} 
	
	if (vars.forcevars) {
		g_misc->force_convars();
	}
	
}

bool __stdcall hooked::create_move(float frameTime, usercmd* cmd) noexcept
{
	if (!cmd || !cmd->command_number)
		reinterpret_cast<create_move_fn>(create_move_hook->get_original(21))(interfaces::client_mode, frameTime, cmd);

	g_ctx->local_player = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player()));

	if (interfaces::engine->is_in_game() && interfaces::engine->is_connected())
	{
		on_createmove(cmd);
	}
	return false;


}

float colorz[3] = { 0.f, 1.0f, 0.f };
float alphaz[1] = { 150.f };

void __stdcall hooked::draw_model_ex(void* results, const cdraw_modelinfo& info, matrix3x4_t* bones, float* flexw, float* flexdw, const vec3_t& model, const std::int32_t flags) noexcept
{
	reinterpret_cast<draw_model_fn>(draw_model_ex_hook->get_original(29))(interfaces::studio_render, results, info, bones, flexw, flexdw, model, flags);
}


LRESULT __stdcall hooked::wndproc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) {
	static bool pressed = false;

	if (!pressed && GetAsyncKeyState(VK_INSERT)) {
		pressed = true;
	}
	else if (pressed && !GetAsyncKeyState(VK_INSERT)) {
		pressed = false;

		g_menu->menu_opened = !g_menu->menu_opened;
	}

	if (g_menu->menu_opened) {

		//interfaces::inputsystem->enable_input(false);

	}
	else if (!g_menu->menu_opened) {

		//interfaces::inputsystem->enable_input(true);
	}

	if (g_menu->menu_opened && ImGui_ImplDX9_WndProcHandler(hwnd, message, wparam, lparam))
		return true;

	return CallWindowProcA(hooked::wndproc_original, hwnd, message, wparam, lparam);
}


void __stdcall hooked_sceneend() {
	using scene_end_fn = void(__thiscall*)(void*);
	static auto original_fn = reinterpret_cast<scene_end_fn>(renderview_hook->get_original(9));
	// просто хук сценэнда, для чего нибудь может понадобиться 
	original_fn(interfaces::render_view);

	if (interfaces::engine->is_in_game() && interfaces::engine->is_connected()) {
		auto localplayer = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player()));


		for (int i = 1; i < interfaces::globals->maxClients; ++i) {
			auto entity = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(i));

			if (!entity || entity == localplayer || entity->health() <= 1)
				continue;


			bool isEnemy = entity->is_player() && (entity->team() != localplayer->team());

			const char* materialName = "debug/debugambientcube";
			i_material* material = interfaces::material_system->FindMaterial(materialName);

			if (isEnemy) {

				if (entity->is_player() && entity->is_alive() && entity->health() > 0)
					continue;

				if (vars.chams_invisible)
				{

					material->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
					material->SetMaterialVarFlag(MATERIAL_VAR_NOCULL, true);
					material->SetMaterialVarFlag(MATERIAL_VAR_NOFOG, true);
					material->SetMaterialVarFlag(MATERIAL_VAR_HALFLAMBERT, true);
					material->SetMaterialVarFlag(MATERIAL_VAR_FLAT, true);
					interfaces::render_view->SetColorModulation(vars.hidden_color);
					interfaces::render_view->SetBlend(vars.hidden_color[3]);
					interfaces::mdl_render->ForceMaterialOverride(material);
					entity->DrawModel(0x1);

				}

				if (vars.chams_visible)
				{


					material->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
					material->SetMaterialVarFlag(MATERIAL_VAR_FLAT, true);
					interfaces::render_view->SetColorModulation(vars.visible_color);
					interfaces::render_view->SetBlend(vars.visible_color[3]);
					interfaces::mdl_render->ForceMaterialOverride(material);
					entity->DrawModel(0x1);

				}

				interfaces::mdl_render->ForceMaterialOverride(nullptr);
			}

		}
	}
}

static bool initialized = false;
HRESULT WINAPI end_of_scene(IDirect3DDevice9* m_pDevice)
{
	typedef HRESULT(WINAPI* _EndScene)(IDirect3DDevice9*);
	_EndScene oEndScene;
	oEndScene = (_EndScene)(endscene_hook->get_original(42));

	if (!initialized)
	{
		g_menu->ImGui_fontcreation();
		g_menu->ImGui_stylesetup(m_pDevice);
		initialized = true;
	}

	if (initialized) {
		g_menu->pre_render(m_pDevice);
		g_menu->post_render();

		g_menu->draw_menu();

		g_menu->end_present(m_pDevice);
	}
	return oEndScene(m_pDevice);
}

void hooked::initialize() {


	panel_hook = std::make_unique<vmt_hook>();

	panel_hook->setup(interfaces::panel);

	panel_hook->hook_index(41, reinterpret_cast<void*>(paint_traverse));

	render.setup_fonts();
	std::cout << "hooked paint_traverse\n";
	interfaces::globals = interfaces::player_mgr->get_globalvars();
	printf("player_mgr -> global_vars, 0x%p\n", interfaces::globals);

	create_move_hook = std::make_unique<vmt_hook>();
	create_move_hook->setup(interfaces::client_mode);
	create_move_hook->hook_index(21, reinterpret_cast<void*>(create_move));
	std::cout << "hooked create_move\n";

	frame_stage_notify_hook = std::make_unique<vmt_hook>();
	frame_stage_notify_hook->setup(interfaces::client);
	frame_stage_notify_hook->hook_index(35, reinterpret_cast<void*>(frame_stage_notify));
	std::cout << "hooked frame_stage_notify\n";

	draw_model_ex_hook = std::make_unique<vmt_hook>();
	draw_model_ex_hook->setup(interfaces::studio_render);
	draw_model_ex_hook->hook_index(29, reinterpret_cast<void*>(draw_model_ex));
	std::cout << "hooked draw_model_ex\n";


	renderview_hook = std::make_unique<vmt_hook>();
	renderview_hook->setup(interfaces::render_view);
	renderview_hook->hook_index(9, reinterpret_cast<void*>(hooked_sceneend));
	std::cout << "hooked scene_end\n";

	endscene_hook = std::make_unique<vmt_hook>();
	endscene_hook->setup(interfaces::device);
	endscene_hook->hook_index(42, end_of_scene);

	std::cout << "hooked end_scene\n";

	hooked::window = FindWindowA("Source001", NULL);
	hooked::wndproc_original = reinterpret_cast<WNDPROC>(SetWindowLongW(hooked::window, GWL_WNDPROC, reinterpret_cast<LONG>(wndproc)));


	std::ofstream("csso/materials/textured.vmt") << R"#("VertexLitGeneric" {
			"$basetexture" "vgui/white_additive"
			"$ignorez"      "1"
			"$envmap"       ""
			"$nofog"        "1"
			"$model"        "1"
			"$nocull"       "0"
			"$selfillum"    "1"
			"$halflambert"  "1"
			"$znearer"      "0"
			"$flat"         "1"
        })#";

	std::ofstream("csso/materials/reflective.vmt") << R"#("VertexLitGeneric" {
			"$basetexture" "vgui/white_additive"
			"$ignorez" "0"
			"$envmap" "env_cubemap"
			"$normalmapalphaenvmapmask" "1"
			"$envmapcontrast"  "1"
			"$nofog" "1"
			"$model" "1"
			"$nocull" "0"
			"$selfillum" "1"
			"$halflambert" "1"
			"$znearer" "0"
			"$flat" "1"
		})#";
}