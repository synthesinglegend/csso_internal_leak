#pragma once
enum ClientFrameStage_t {
	FRAME_UNDEFINED = -1,			// (haven't run any frames yet)
	FRAME_START,

	// A network packet is being recieved
	FRAME_NET_UPDATE_START,
	// Data has been received and we're going to start calling PostDataUpdate
	FRAME_NET_UPDATE_POSTDATAUPDATE_START,
	// Data has been received and we've called PostDataUpdate on all data recipients
	FRAME_NET_UPDATE_POSTDATAUPDATE_END,
	// We've received all packets, we can now do interpolation, prediction, etc..
	FRAME_NET_UPDATE_END,

	// We're about to start rendering the scene
	FRAME_RENDER_START,
	// We've finished rendering the scene.
	FRAME_RENDER_END
};

namespace hooked {
	
	void initialize();
	void undo();
	extern std::unique_ptr<vmt_hook> panel_hook;
	extern std::unique_ptr<vmt_hook> create_move_hook;
	extern std::unique_ptr<vmt_hook> frame_stage_notify_hook;
	extern std::unique_ptr<vmt_hook> draw_model_ex_hook;
	inline HWND window;
	inline WNDPROC wndproc_original = NULL;

	LRESULT __stdcall wndproc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

	using paint_traverse_fn = void(__thiscall*)(i_panel*, unsigned int, bool, bool);
	void __stdcall paint_traverse(unsigned int panel, bool force_repaint, bool allow_force);

	using create_move_fn = bool(__thiscall*)(client_mode_shared*, float frameTime, usercmd* cmd) noexcept;
	bool __stdcall create_move(float frameTime, usercmd* cmd) noexcept;

	using frame_stage_notify_fn = void(__thiscall*)(void*, ClientFrameStage_t);
	void __fastcall frame_stage_notify(void* ecx, void* edx, ClientFrameStage_t stage);

	using draw_model_fn = void(__thiscall*)(void*, void*, const cdraw_modelinfo&, matrix3x4_t*, float*, float*, const vec3_t&, const std::int32_t) noexcept;
	void __stdcall draw_model_ex(void* results, const cdraw_modelinfo& info, matrix3x4_t* bones, float* flexw, float* flexdw, const vec3_t& model, const std::int32_t flags) noexcept;
}

void on_createmove(usercmd* cmd);
