#pragma once
class bf_write;
class bf_read;
class C_BaseCombatWeapon;
struct kbutton_t;
class usercmd;

	enum ButtonCode_t
	{
		
	};

	struct CameraThirdData_t
	{
		float	m_flPitch;
		float	m_flYaw;
		float	m_flDist;
		float	m_flLag;
		vec3_t	m_vecHullMin;
		vec3_t	m_vecHullMax;
	};


	enum indices : size_t {
		CREATEMOVE = 3,
		WRITEUSERCMDDELTATOBUFFER = 5,
		ENCODEUSERCMDTOBUFFER = 6,
		GETUSERCMD = 8,
		CAMISTHIRDPERSON = 32,
		CAMTOTHIRDPERSON = 35,
		CAMTOFIRSTPERSON = 36,
	};

	class ii_input
	{
	public:
		char konoplya[0x8D];
		bool m_fCameraInThirdPerson;
		char weed[0x02];
		vec3_t m_vecCameraOffset;
	};
	