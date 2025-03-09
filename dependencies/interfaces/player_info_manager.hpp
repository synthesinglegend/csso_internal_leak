#pragma once
class iplayerinfomanager
{
public:
	virtual void** somefunc(void** idk) = 0;//virtual IPlayerInfo* GetPlayerInfo(edict_t* pEdict) = 0;
	virtual c_global_vars* get_globalvars() = 0;
};