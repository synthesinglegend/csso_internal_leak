#include "../../dependencies/global_includes.hpp"
struct backup_variables_t {
	float			realtime;
	int				framecount;
	float			absoluteframetime;
	float			curtime;
	float			frametime;
	int				maxClients;
	int				tickcount;
	float			interval_per_tick;
	int old_tickbase;
	cmove_data* move_data;
};
class c_prediction
{
public:
	void start_predicting(usercmd* cmd);
	void stop_predicting(usercmd* cmd);
};
inline std::unique_ptr<c_prediction> g_prediction = std::make_unique<c_prediction>();
extern backup_variables_t backup_vars;