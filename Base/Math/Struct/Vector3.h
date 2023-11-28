#pragma once
struct Vector3 final{
	float x;
	float y;
	float z;
	Vector3* operator +(Vector3 other) {
		this->x = this->x + other.x;
		this->y = this->y + other.y;
		this->z = this->z + other.z;
			return this;
	}
	Vector3* operator =(Vector3* other) {
		this->x = other->x;
		this->y = other->y;
		this->z = other->z;
		return this;
	}
	Vector3* operator +=(Vector3 other) {
		this->x = this->x + other.x;
		this->y = this->y + other.y;
		this->z = this->z + other.z;
			return this;
	}
	Vector3* operator +=(Vector3* other) {
		this->x = this->x + other->x;
		this->y = this->y + other->y;
		this->z = this->z + other->z;
			return this;
	}
	Vector3* operator *(float other) {
		this->x = this->x * other;
		this->y = this->y * other;
		this->z = this->z * other;
		return this;
	}
};

