#include "vector.h"

Vector2f::Vector2f(): x(0), y(0) {}
Vector2f::Vector2f(float x, float y): x(x), y(y) {}
Vector2f::Vector2f(const Vector2f& vec): x(vec.x), y(vec.y) {}

Vector2f Vector2f::operator+(const Vector2f& vec){
	return Vector2f(x + vec.x, y + vec.y);
}
Vector2f Vector2f::operator-(const Vector2f& vec){
	return Vector2f(x - vec.x, y - vec.y);
}
Vector2f Vector2f::operator*(const Vector2f& vec){
	return Vector2f(x * vec.x, y * vec.y);
}
Vector2f Vector2f::operator/(const Vector2f& vec){
	return Vector2f(x / vec.x, y / vec.y);
}

std::ostream& operator<<(std::ostream& stream, const Vector2f& vec){
	return stream << "{" << vec.x << ";" << vec.y << "}";
}
