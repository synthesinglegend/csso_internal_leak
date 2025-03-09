#pragma once
#include "../../sdk/sdk_includes.hpp"
#include "../../dependencies/interfaces/trace.hpp"
struct fire_bullet_data_t {
	vec3_t		 m_position = {};
	vec3_t		 m_direction = {};
	trace_t m_enter_trace = {};
	float		 m_current_damage = 0.f;
	int			 m_penetrate_count = 0;

	fire_bullet_data_t() {
		reset();
	}

	fire_bullet_data_t(vec3_t position, vec3_t direction) {
		m_position = position;
		m_direction = direction;
	}

	void reset() {
		m_position = {};
		m_direction = {};
		m_enter_trace = {};
		m_current_damage = 0.f;
		m_penetrate_count = 0;
	}
};