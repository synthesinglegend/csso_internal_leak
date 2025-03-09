#pragma once
#include "studio_render.hpp"
struct model_t;

struct studiohwdata_t;
struct StudioDecalHandle_t { int unused; };
typedef unsigned short ModelInstanceHandle_t;

enum
{
	MODEL_INSTANCE_INVALID = (ModelInstanceHandle_t)~0
};

class i_clientrenderable
{
public:
	const model_t* get_model()
	{
		typedef const model_t* (__thiscall* get_model_fn)(void*);
		return vfunc< get_model_fn >(this, 9)(this); // мне лень было лень переделывать под наш вызов вфунок, поэтому метод спизжен, потом переделаю, главное это работает
	}

	
};
class iv_model_info {
public:
	model_t* get_model(int index) {
		using original_fn = model_t * (__thiscall*)(iv_model_info*, int);
		return (*(original_fn**)this)[1](this, index);
	}
	int get_model_index(const char* filename) {
		using original_fn = int(__thiscall*)(iv_model_info*, const char*);
		return (*(original_fn**)this)[2](this, filename);
	}
	const char* get_model_name(const model_t* model) noexcept
	{
		return get_vfunc<3, const char*>(this, model);
	}
	studio_hdr_t* get_studio_model(const model_t* model) {
		using original_fn = studio_hdr_t * (__thiscall*)(iv_model_info*, const model_t*);
		return (*(original_fn**)this)[28](this, model);
	}

	
};