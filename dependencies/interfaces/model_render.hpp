#pragma once
#include "../../sdk/sdk_includes.hpp"
struct draw_model_state_t {
	studio_hdr_t* m_pStudioHdr;
	studiohwdata_t* m_pStudioHWData;
	iclient_renderable* m_pRenderable;
	const matrix3x4_t* m_pModelToWorld;
	void*     m_decals;
	int                     m_drawFlags;
	int                     m_lod;
};

class iv_model_render {
public:
	i_material* ForceMaterialOverride(i_material* pMaterial, int nOverrideType = 0)
	{
		return get_vfunc<1, i_material*>(this, pMaterial, nOverrideType);
	}
};