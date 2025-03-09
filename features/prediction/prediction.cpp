#include "prediction.hpp"
/*
* I dont care. Just simple saving & restoring, didnt even bother to set prediction player. 
	Do it yourself.
*/
c_prediction pred;
backup_variables_t backup_vars;
void c_prediction::start_predicting(usercmd* cmd) {
	auto local_player = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player()));
	backup_vars.curtime = interfaces::globals->curtime;
	backup_vars.frametime = interfaces::globals->frametime;
	backup_vars.tickcount = interfaces::globals->tickcount;
	backup_vars.old_tickbase = local_player->tickbase();

}

void c_prediction::stop_predicting(usercmd* cmd) {
	interfaces::globals->curtime = backup_vars.curtime;
	interfaces::globals->frametime = backup_vars.frametime;
	interfaces::globals->tickcount = backup_vars.tickcount;
}