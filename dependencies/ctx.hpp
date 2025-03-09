#include "global_includes.hpp"

class c_ctx
{
public:
	player_t* local_player{};
};
inline std::unique_ptr<c_ctx> g_ctx = std::make_unique<c_ctx>();