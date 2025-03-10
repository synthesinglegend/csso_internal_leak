#pragma once

#include "vector3d.hpp"

class matrix3x4_t
{
public:
	float* operator[](size_t index) noexcept
	{
		return data[index];
	}

	vec3_t Origin() noexcept
	{
		return { data[0][3], data[1][3], data[2][3] };
	}

	float data[3][4];
};

class matrix4x4_t
{
public:
	float data[4][4];
};

