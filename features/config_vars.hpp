#pragma once


class c_vars {
public:
	 bool aim = false;
	 int bone = 8;
	 bool faststop = false;
	 bool esp = false;
	 bool esp_box = false;
	 bool esp_healthbar = false;
	 bool esp_skeleton = false;
	 bool esp_flags = false;
	 bool esp_removescope = false;
	 bool esp_name = false;
	 bool esp_byaw = false;
	 bool esp_noflash = false;
	 bool esp_nosmoke = false;
	 bool misc_moonwalk = false;
	 bool norecoil = false;
	 bool silent_norecoil = false;
	 bool autofire = false;
	 bool saim = false;
	 bool bhop_e = false;
	 bool airstrafe = false;
	 bool dm = false;
	 bool coloredmodels = false;
	 bool menu = false;
	 bool forcevars = false;
	 bool antiaim = false;
	 float antiaimdeg = 0;
	 float antiaimdeg2 = 0;
	 float breaker = 0.f;
	 float aimfov = 0.f;
	 float smooth = 0.f;
	 int fakelagamount = 0;
	 bool chams_self = false;
	 bool chams_invisible = false;
	 bool chams_visible = false;
	 bool chams_modifyc = false;
	 bool* m_packet;
	 bool m_packetbool;
	 vec3_t m_strafe_angles;
	 bool fakelag = false;
	 vec3_t va;

	 vec3_t actualang;

	 float hidden_color[4] = { 0.0f, 0.0f, 1.0f, 1.0f }; // Синий
	 float visible_color[4] = { 1.0f, 0.0f, 0.0f, 1.0f }; // Красный


};
extern c_vars vars;