#include "vector.h"

Vector3f::Vector3f(): x(0), y(0), z(0) {}
Vector3f::Vector3f(float x, float y, float z): x(x), y(y), z(z) {}
Vector3f::Vector3f(const Vector3f& vec): x(vec.x), y(vec.y), z(vec.z) {}

Vector3f Vector3f::operator+(const Vector3f& vec){
	return Vector3f(x + vec.x, y + vec.y, z + vec.z);
}
Vector3f Vector3f::operator-(const Vector3f& vec){
	return Vector3f(x - vec.x, y - vec.y, z - vec.z);
}
Vector3f Vector3f::operator*(const Vector3f& vec){
	return Vector3f(x * vec.x, y * vec.y, z * vec.z);
}
Vector3f Vector3f::operator/(const Vector3f& vec){
	return Vector3f(x / vec.x, y / vec.y, z / vec.z);
}

std::ostream& operator<<(std::ostream& stream, const Vector3f& vec){
	return stream << "{" << vec.x << ";" << vec.y << ";" << vec.z << "}";
}

