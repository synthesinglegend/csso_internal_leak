#include "../../dependencies/global_includes.hpp"
#include "../../dependencies/interfaces/engine_client.hpp"
#include "visuals.hpp"
#include "../../dependencies/utils/renderer.hpp"
#include "../config_vars.hpp"
#include  "../../dependencies/ctx.hpp"
/*
* I like these visuals.
*/

void c_visuals::box_esp(player_t* ent) noexcept {
	if (!vars.esp_box) return;
	auto local_player = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player()));
	player_info_t info;
	interfaces::engine->get_player_info(ent->get_id(), &info);

	box bbox;
	if (!get_playerbox(ent, bbox))
		return;
	auto red = 255;
	auto green = 255;
	auto blue = 255;

	std::string print{ info.name };
	std::transform(print.begin(), print.end(), print.begin(), [](UCHAR c) { return std::tolower(c); });

	if (vars.esp_name) {
		g_renderer->draw_text(bbox.x + (bbox.w / 2), bbox.y - 15, 200, print, true, color(red, green, blue, ent->is_dormant() ? 120 : 255));
	}
	


	g_renderer->draw_outline(bbox.x - 1, bbox.y - 1, bbox.w + 2, bbox.h + 2, color(0, 0, 0, ent->is_dormant() ? 50 : 255));
	g_renderer->draw_rect(bbox.x, bbox.y, bbox.w, bbox.h, color(red, green, blue, ent->is_dormant() ? 50 : 255));
	g_renderer->draw_outline(bbox.x + 1, bbox.y + 1, bbox.w - 2, bbox.h - 2, color(0, 0, 0, ent->is_dormant() ? 50 : 255));
}


void c_visuals::health_bar(player_t* ent) noexcept {
	if (!vars.esp_healthbar) return;
	box bbox;
	if (!get_playerbox(ent, bbox))
		return;
	auto red = 255;
	auto green = 255;
	auto blue = 255;

	box temp(bbox.x - 5, bbox.y + (bbox.h - bbox.h * (math.int_clamp(ent->health(), 0.f, 100.f) / 100.f)), 1, bbox.h * (math.int_clamp(ent->health(), 0.f, 100) / 100.f) - (ent->health() >= 100 ? 0 : -1));
	box temp_bg(bbox.x - 5, bbox.y, 1, bbox.h);


	auto health_color = color((255 - ent->health() * 2.55), (ent->health() * 2.55), 0, alpha[ent->get_id()]);

	if (ent->health() > 100)
		health_color = color(0, 255, 0);

	int h_index = 0;
	g_renderer->draw_filled_rect(temp_bg.x - 1, temp_bg.y - 1, temp_bg.w + 2, temp_bg.h + 2, color(0, 0, 0, 100 + alpha[ent->get_id()]));
	g_renderer->draw_filled_rect(temp.x, temp.y, temp.w, temp.h, color(health_color));
	//auto weapon = ent->active_weapon();
	//if (!weapon)
	//	return;

	//g_renderer->draw_text(bbox.x + (bbox.w / 2), bbox.h + (10 * h_index) + bbox.y + 2, 65, weapon->weapon_name_definition().c_str(), true, color(red, green, blue, 255));
}

void c_visuals::skeleton(player_t* entity) noexcept {
	if (!vars.esp_skeleton) return;

	auto studiohdr = interfaces::mdl_info->get_studio_model(entity->get_model());
	if (!studiohdr)
		return;

	vec3_t v_parent, v_child, s_parent, s_child;

	for (int i = 0; i < studiohdr->bones_count; i++) {
		mstudiobone_t* bone = studiohdr->bone(i);
		if (!bone)
			return;

		if (bone && (bone->flags & BONE_USED_BY_HITBOX) && (bone->parent != -1)) {
			v_child = entity->get_bone_position(i);
			v_parent = entity->get_bone_position(bone->parent);

			if (math.world_to_screen(v_parent, s_parent) && math.world_to_screen(v_child, s_child))
				g_renderer->draw_line(s_parent[0], s_parent[1], s_child[0], s_child[1], color(255, 255, 255, entity->is_dormant() ? 120 : 255));
		}
	}
}


void c_visuals::player_flags(player_t* ent) noexcept {
	if (!vars.esp_flags) return;
	box bbox;
	if (!get_playerbox(ent, bbox))
		return;
	std::vector<std::pair<std::string, color>> flags;
	if (ent->has_helmet() && ent->armor() > 0)
		flags.emplace_back(std::pair<std::string, color>("HK", color(255, 255, 255, ent->is_dormant() ? 120 : 255)));
	else if (!ent->has_helmet() && ent->armor() > 0)
		flags.emplace_back(std::pair<std::string, color>("K", color(255, 255, 255, ent->is_dormant() ? 120 : 255)));

	if (ent->money())
		flags.emplace_back(std::pair<std::string, color>(std::string("$").append(std::to_string(ent->money())), color(120, 180, 10, ent->is_dormant() ? 120 : 255)));

	if (ent->is_scoped())
		flags.emplace_back(std::pair<std::string, color>(std::string("SCOPED"), color(80, 160, 200, ent->is_dormant() ? 120 : 255)));

	if (vars.esp_byaw) {
		flags.emplace_back(std::pair<std::string, color>(std::to_string(ent->lower_body_yaw()), color(255, 230, 0, ent->is_dormant() ? 120 : 255)));
	}
	
	auto position = 0;
	for (auto text : flags) {
		g_renderer->draw_text(bbox.x + bbox.w + 3, bbox.y + position - 2, 200, text.first, false, text.second);
		position += 12;
	}
}

void c_visuals::nosmoke() noexcept
{
	std::vector<const char*> gay_mats =
	{
		"particle/particle_smokegrenade1",
		"particle/particle_smokegrenade2",
		"particle/particle_smokegrenade3",
	};

	for (auto matName : gay_mats)
	{
		i_material* mat = interfaces::material_system->find_material(matName, "Other textures");
		mat->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, true);
	}
}


/* Всё что ниже может сильно жрать фпс, тебе следует посидеть с профилировщиком производительности, если такая проблема есть*/

void c_visuals::run() noexcept {
	if (!vars.esp) return;
	if (!g_ctx->local_player)
		return;
	if (vars.esp_nosmoke) 
	{
		nosmoke();
	}

	for (int i = 1; i < interfaces::globals->maxClients; i++) {
		auto entity = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(i));

		if (!entity || entity == g_ctx->local_player || entity->health() <= 1)
			continue;
		if (entity->team() == g_ctx->local_player->team())
			continue;
		const int fade = (int)((6.66666666667f * interfaces::globals->frametime) * 255);

		alpha[i] = 255;

		if (vars.esp) {
			box_esp(entity);
			health_bar(entity);
			skeleton(entity);
			player_flags(entity);
		}
	}
}

void c_visuals::dm_run() noexcept {

	if (!g_ctx->local_player)
		return;

	for (int i = 1; i < interfaces::globals->maxClients; i++) {
		auto entity = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(i));

		if (!entity || entity == g_ctx->local_player || entity->health() <= 1)
			continue;

		const int fade = (int)((6.66666666667f * interfaces::globals->frametime) * 255);

		auto new_alpha = alpha[i];
		new_alpha += entity->is_dormant() ? -fade : fade;

		alpha[i] = 255;

		box_esp(entity);
		health_bar(entity);
		skeleton(entity);
		player_flags(entity);
	

	}
}

