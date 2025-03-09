#include "entity_structs.hpp"
#include "../dependencies/interfaces/interfaces.hpp"
bool player_t::is_bone_visible(int bone) {
	ray_t ray;
	trace_t tr;
	auto local_player = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player()));
	ray.init(local_player->eye_position(), this->get_bone_position(bone));

	trace_filter filter;
	filter.skip = local_player;

	interfaces::tracing->trace_ray(&ray, MASK_SHOT, &filter, &tr);

	if (tr.m_pEnt == this)
		return true;

	return false;
}

weapon_t* player_t::active_weapon() {
	return (weapon_t*)interfaces::entity_list->get_client_entity_handle(active_wpn());
}
