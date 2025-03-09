#pragma once
#include "../../dependencies/global_includes.hpp"

class c_misc {
public:
	std::vector<int> get_observervators(int playerid) noexcept;
	color cl_player_obs;
	void remove_flash() noexcept;
	void remove_scope() noexcept;
	void fakelag(bool& sendpacket);
	void bSendPacket();
	void force_convars();
	void norecoil(usercmd* cmd);
	void thirdperson(usercmd* cmd);
	void remove_punch(bool = false);
	void watermark() noexcept;
	void clantag_spammer() noexcept;
	void viewmodel_offset() noexcept;
	void disable_post_processing() noexcept;
	void recoil_crosshair() noexcept;
	void force_crosshair() noexcept;
private:
};

inline std::unique_ptr<c_misc> g_misc = std::make_unique<c_misc>();