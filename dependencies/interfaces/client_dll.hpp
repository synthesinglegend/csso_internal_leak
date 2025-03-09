#pragma once
#include "../../sdk/client_classes.hpp"
class client_dll {
public:
	c_client_class* get_client_classes() {
		using original_fn = c_client_class * (__thiscall*)(client_dll*);
		return (*(original_fn**)this)[8](this);
	}


};