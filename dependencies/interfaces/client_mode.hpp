#pragma once
class client_mode_shared
{
public:

	class CViewSetup
	{
	public:
		int      x;
		int      m_nUnscaledX;
		int      y;
		int      m_nUnscaledY;
		int      width;
		int      m_nUnscaledWidth;
		int      height;
		int      m_eStereoEye;
		int      m_nUnscaledHeight;
		bool    m_bOrtho;
		float    m_OrthoLeft;
		float    m_OrthoTop;
		float    m_OrthoRight;
		float    m_OrthoBottom;
		float    fov;
		float    fovViewmodel;
	};


};