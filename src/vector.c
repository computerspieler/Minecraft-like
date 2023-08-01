#include "vector.h"

Vec2f vec2f_add(Vec2f v1, Vec2f v2)
{
    Vec2f out;

    out.x = v1.x + v2.x;
    out.y = v1.y + v2.y;

    return out;
}
Vec2f vec2f_sub(Vec2f v1, Vec2f v2)
{
    Vec2f out;

    out.x = v1.x - v2.x;
    out.y = v1.y - v2.y;

    return out;
}
Vec2f vec2f_mul(Vec2f v1, Vec2f v2)
{
    Vec2f out;

    out.x = v1.x * v2.x;
    out.y = v1.y * v2.y;

    return out;
}
Vec2f vec2f_div(Vec2f v1, Vec2f v2)
{
    Vec2f out;

    out.x = v1.x / v2.x;
    out.y = v1.y / v2.y;

    return out;
}

float vec2f_dot_2(Vec2f v1, Vec2f v2)
{ return v1.x * v2.x + v1.y * v2.y; }


Vec3f vec3f_add(Vec3f v1, Vec3f v2)
{
	Vec3f out;

	out.x = v1.x + v2.x;
	out.y = v1.y + v2.y;
	out.z = v1.z + v2.z;

	return out;
}
Vec3f vec3f_sub(Vec3f v1, Vec3f v2)
{
	Vec3f out;

	out.x = v1.x - v2.x;
	out.y = v1.y - v2.y;
	out.z = v1.z - v2.z;

	return out;
}
Vec3f vec3f_mul(Vec3f v1, Vec3f v2)
{
	Vec3f out;

	out.x = v1.x * v2.x;
	out.y = v1.y * v2.y;
	out.z = v1.z * v2.z;

	return out;
}
Vec3f vec3f_div(Vec3f v1, Vec3f v2)
{
	Vec3f out;

	out.x = v1.x / v2.x;
	out.y = v1.y / v2.y;
	out.z = v1.z / v2.z;

	return out;
}

float vec3f_dot_2(Vec3f v1, Vec3f v2)
{ return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z; }

