#pragma once
struct Vector3 final{
	float x;
	float y;
	float z;
	Vector3 operator +(Vector3 other) {
		Vector3 me;
		me.x = this->x + other.x;
		me.y = this->y + other.y;
		me.z = this->z + other.z;
			return me;
	}
	Vector3 operator *(float other) {
		Vector3 me;
		me.x = this->x * other;
		me.y = this->y * other;
		me.z = this->z * other;
			return me;
	}
};

