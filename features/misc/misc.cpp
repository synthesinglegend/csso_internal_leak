#include <vector>
#include "misc.hpp"
#include "../config_vars.hpp"

void c_misc::remove_scope() noexcept {

	if (!interfaces::engine->is_connected() && !interfaces::engine->is_in_game())
		return;

	auto local_player = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player()));
	if (!local_player)
		return;

	if (local_player && !local_player->is_scoped())
		return;

	int w, h;
	interfaces::engine->get_screen_size(w, h);
	interfaces::surface->set_drawing_color(0, 0, 0, 255);
	interfaces::surface->draw_line(0, h / 2, w, h / 2);
	interfaces::surface->draw_line(w / 2, 0, w / 2, h);


}

void c_misc::remove_flash() noexcept {

	if (!interfaces::engine->is_connected() && !interfaces::engine->is_in_game())
		return;

	auto local_player = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player()));
	if (!local_player)
		return;

	local_player->flash_duration() = 0.f;


}

DWORD bSendPacketPTR;
BYTE* bSendPacketBYTE;
DWORD dwBack;

void c_misc::bSendPacket()
{
	if (!bSendPacketPTR)
	{
		bSendPacketPTR = (DWORD)GetModuleHandleA("engine.dll") + 0xF5800 + 0x03;
		bSendPacketBYTE = (BYTE*)((DWORD)bSendPacketPTR);
		VirtualProtect((PVOID)bSendPacketPTR, 2, PAGE_EXECUTE_READWRITE, &dwBack);
		printf("%X -> sendpacket\n", bSendPacketPTR);

	}
	vars.m_packet = (bool*)&bSendPacketBYTE[0];

	vars.m_packetbool = *(bool*)&bSendPacketBYTE[0];
}

void c_misc::fakelag(bool& sendpacket) {
	static int choke = 0;

	if (choke == 0)
	{
		choke = vars.fakelagamount;
		if (!sendpacket)
		sendpacket = true;
	}
	else
	{
		choke--;
		if (sendpacket)
		sendpacket = false;
	}

}

void c_misc::force_convars()
{
	auto pSvCheats = interfaces::convars->FindVar("sv_cheats");

	pSvCheats->SetValue(1);
}

void c_misc::thirdperson(usercmd* cmd) {

	// Получение локального игрока
	auto local_player = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player()));
	if (!local_player)  // Проверка на nullptr
		return;

	static bool bToggled = false;
	if (GetAsyncKeyState(VK_MBUTTON) & 1)
		bToggled = !bToggled;

	if (bToggled)
	{
		interfaces::input->m_fCameraInThirdPerson = true;
		interfaces::input->m_vecCameraOffset.z = 60.f;
		local_player->v_angle().x = vars.actualang.x;
		local_player->v_angle().y = vars.actualang.y;
	}
	else
	{
		interfaces::input->m_fCameraInThirdPerson = false;
		interfaces::input->m_vecCameraOffset.z = 0.f;
	}
}

void c_misc::norecoil(usercmd* cmd) {

	// Получение локального игрока
	auto local_player = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player()));
	if (!local_player)  // Проверка на nullptr
		return;

	auto weapon = local_player->active_weapon();
	if (!weapon)  // Проверка на наличие оружия
		return;

	// Получение угла отдачи
	vec3_t innac = local_player->aimpunchangle();


	// Применение углов
	cmd->viewangles.x -= innac.x * 2.f;
	cmd->viewangles.y -= innac.y * 2.f;

	auto view_recoil = interfaces::convars->FindVar("view_recoil_tracking");
	auto weapon_recoil = interfaces::convars->FindVar("weapon_recoil_view_punch_extra");

	view_recoil->SetValue(0.f);
	weapon_recoil->SetValue(0.f);

};