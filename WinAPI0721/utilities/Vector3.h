#pragma once
#include "stdafx.h"

class Vector3
{
public:
	Vector3() : x(0), y(0), z(0) {}

	template<typename T, typename U, typename V>
	Vector3(T x, U y, V z)
	{
		this->x = (int)x;
		this->y = (int)y;
		this->z = (int)z;
	}

	Vector3 operator-(const Vector3& other)
	{

		return Vector3(x - other.x, y - other.y, z - other.z);
	}

	Vector3 operator+(const Vector3& other)
	{

		return Vector3(x + other.x, y + other.y, z + other.z);
	}

	bool operator==(const Vector3& other)
	{

		if (this->x == other.x && this->y == other.y && this->z == other.z) return true;
	    return false;
	}

	int x, y, z;

};