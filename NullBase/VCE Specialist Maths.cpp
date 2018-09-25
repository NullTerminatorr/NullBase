#include "VCE Specialist Maths.h"
#include <math.h>

Vector3::Vector3() {
	x = 0;
	y = 0;
	z = 0;
}

Vector3::Vector3(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

float Vector3::lengthSquare() {
	return (x*x + y * y + z * z);
}

float Vector3::length() {
	return (float)sqrt(lengthSquare());
}

bool Vector3::isNull() {
	return (x < 1 && y < 1 && z < 1);
}

Vector3 Vector3::operator+(Vector3 v) {
	Vector3 r;
	r.x = x + v.x;
	r.y = y + v.y;
	r.z = z + v.z;
	return r;
}

Vector3 Vector3::operator-(Vector3 v) {
	Vector3 r;
	r.x = x - v.x;
	r.y = y - v.y;
	r.z = z - v.z;
	return r;
}

Vector3 Vector3::operator*(float f) {
	Vector3 r;
	r.x = x * f;
	r.y = y * f;
	r.z = z * f;
	return r;
}