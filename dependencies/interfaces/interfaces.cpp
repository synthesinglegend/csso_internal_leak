#include "interfaces.hpp"
#include "../global_includes.hpp"
#include "../../sdk/cvars.hpp"

c_global_vars* interfaces::globals = nullptr;
i_engine_client* interfaces::engine = nullptr;
client_dll* interfaces::client = nullptr;
client_mode_shared* interfaces::client_mode = nullptr;
ii_input* interfaces::input = nullptr;
i_entity_list* interfaces::entity_list = nullptr;
i_panel* interfaces::panel = nullptr;
i_surface* interfaces::surface = nullptr;
iplayerinfomanager* interfaces::player_mgr = nullptr;
i_material_system* interfaces::material_system = nullptr;
istudio_render* interfaces::studio_render = nullptr;
trace* interfaces::tracing = nullptr;
iv_model_info* interfaces::mdl_info = nullptr;
iv_model_render* interfaces::mdl_render = nullptr;
i_prediction* interfaces::prediction = nullptr;
i_game_movement* interfaces::game_movement = nullptr;
IVRenderView* interfaces::render_view = nullptr;
IDirect3DDevice9* interfaces::device = nullptr;
icvar* interfaces::convars = nullptr;
#define INRANGE(x,a,b)  (x >= a && x <= b) 
#define getBits( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte( x )    (getBits(x[0]) << 4 | getBits(x[1]))
uintptr_t FindPattern(const char* szModule, const char* szSignature) noexcept
{
	MODULEINFO modInfo;

	GetModuleInformation(GetCurrentProcess(), GetModuleHandle(szModule), &modInfo, sizeof(MODULEINFO));

	uintptr_t startAddress = reinterpret_cast<uintptr_t>(modInfo.lpBaseOfDll);

	uintptr_t endAddress = startAddress + modInfo.SizeOfImage;

	const char* pat = szSignature;

	uintptr_t firstMatch = 0;

	for (uintptr_t pCur = startAddress; pCur < endAddress; pCur++)
	{
		if (!*pat) return firstMatch;

		if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == getByte(pat))
		{
			if (!firstMatch) firstMatch = pCur;

			if (!pat[2]) return firstMatch;

			if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?') pat += 3;

			else pat += 2;
		}
		else
		{
			pat = szSignature;

			firstMatch = 0;
		}
	}

	MessageBoxA(NULL, "Wrong signature", "Error", MB_OK);

	return NULL;
}


void* interfaces::create_interface(const char* mod, const char* iface) { 
	using fn_capture_iface_t = void* (*)(const char*, int*);
	auto fn_addr = reinterpret_cast<fn_capture_iface_t>(GetProcAddress(GetModuleHandleA(mod), "CreateInterface"));
	auto iface_addr = fn_addr(iface, nullptr);
	printf("found %s at 0x%p\n", iface, fn_addr(iface, nullptr));  

	return iface_addr;
}
void interfaces::initialize() {
	/*
	* This is the nonsense, just see below (C / C++ casts lol). It should have been C++ only.
	*/
	engine = (i_engine_client*)(interfaces::create_interface("engine.dll", "VEngineClient014"));
	client = (client_dll*)(interfaces::create_interface("client.dll", "VClient017"));
	client_mode = **(client_mode_shared***)(Memory::PatternScan("client.dll", "8B 0D ? ? ? ? 8B 01 5D FF 60 28 CC") + 2);
	input = **(ii_input***)(Memory::PatternScan("client.dll", "8B 0D ? ? ? ? 8B 01 FF 60 48") + 2);
	std::cout << "input: 0x" << std::hex << input << std::endl;
	entity_list = (i_entity_list*)(interfaces::create_interface("client.dll", "VClientEntityList003"));
	panel = (i_panel*)(interfaces::create_interface("vgui2.dll", "VGUI_Panel009"));	
	surface = (i_surface*)(interfaces::create_interface("vguimatsurface.dll", "VGUI_Surface030"));
	convars = (icvar*)(interfaces::create_interface("vstdlib.dll", "VEngineCvar004"));
	player_mgr = (iplayerinfomanager*)(interfaces::create_interface("server.dll", "PlayerInfoManager002"));
	material_system = (i_material_system*)(interfaces::create_interface("materialsystem.dll", "VMaterialSystem081"));
	studio_render = (istudio_render*)(interfaces::create_interface("studiorender.dll", "VStudioRender025"));
	tracing = (trace*)(interfaces::create_interface("engine.dll", "EngineTraceClient003"));
	mdl_info = (iv_model_info*)(interfaces::create_interface("engine.dll", "VModelInfoClient006"));
	mdl_render = (iv_model_render*)(interfaces::create_interface("engine.dll", "VEngineModel016"));
	prediction = (i_prediction*)(interfaces::create_interface("client.dll", "VClientPrediction001"));
	game_movement = (i_game_movement*)(interfaces::create_interface("client.dll", "GameMovement001"));
	render_view = (IVRenderView*)(interfaces::create_interface("engine.dll", "VEngineRenderView014"));
	device = **(IDirect3DDevice9***)(FindPattern("shaderapidx9.dll", "8B 0D ? ? ? ? 1B FF") + 2);
}