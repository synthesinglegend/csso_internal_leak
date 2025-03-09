#pragma once
#include "../../sdk/vector3d.hpp"
#include "../../sdk/vector2d.hpp"
constexpr double pi = 3.14159265358979323846;

#define deg_to_rad( x )  ( (float)(x) * (float)( pi / 180.f ) )
#define rad_to_deg( x )  ( (float)(x) * (float)( 180.f / pi ) )

class c_math {
public:

	//float distance_based_fov(float distance, vec3_t angle, c_usercmd* cmd);
	vec3_t calculate_angle(const vec3_t& source, const vec3_t& destination, const vec3_t& viewAngles);
	vec3_t calculate_angle_se(const vec3_t& vec_source, const vec3_t& vec_destination);
	void sin_cos(float r, float* s, float* c);
	float flt_clamp(float val, float min, float max);
	int int_clamp(int val, int min, int max);
	vec3_t angle_vector(vec3_t angle);
	float point_to_line(vec3_t point, vec3_t line_origin, vec3_t dir);
	void transform_vector(vec3_t&, matrix_t&, vec3_t&);
	void vector_angles(vec3_t&, vec3_t&);
	void angle_vectors(vec3_t&, vec3_t&);
	void anglevectors(const vec3_t& angles, vec3_t* forward, vec3_t* right, vec3_t* up);
	vec3_t calculate_angle_alternative(vec3_t& a, vec3_t& b);
	vec3_t vector_add(vec3_t&, vec3_t&);
	vec3_t vector_subtract(vec3_t&, vec3_t&);
	vec3_t vector_subtract_(const vec3_t&, const vec3_t&, vec_aligned_t&);
	vec3_t vector_copy(const vec3_t&, vec3_t&);
	vec3_t vector_multiply(vec3_t&, vec3_t&);
	vec3_t vector_divide(vec3_t&, vec3_t&);
	void vec_add(const vec3_t& a, const vec3_t& b, vec3_t& c);
	void vec_sub(const vec3_t& a, const vec3_t& b, vec3_t& c);
	void vec_mul(const vec3_t& a, float b, vec3_t& c);
	void vec_cpy(const vec3_t& src, vec3_t& dst);
	bool screen_transform(const vec3_t& point, vec3_t& screen);
	bool world_to_screen(const vec3_t& origin, vec3_t& screen);
	float distance_to_ray(vec3_t& pos, vec3_t& ray_start, vec3_t& ray_end, float* along = nullptr, vec3_t* point_on_ray = nullptr);
	float normalize_angle(float angle);
};

extern c_math math;