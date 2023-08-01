#ifndef _VECTOR_H_
#define _VECTOR_H_

typedef struct Vec2f Vec2f;
struct Vec2f
{
    float x;
    float y;
};

Vec2f vec2f_add(Vec2f, Vec2f);
Vec2f vec2f_sub(Vec2f, Vec2f);
Vec2f vec2f_mul(Vec2f, Vec2f);
Vec2f vec2f_div(Vec2f, Vec2f);

float vec2f_dot_2(Vec2f, Vec2f);


typedef struct Vec3f Vec3f;
struct Vec3f
{
    float x;
    float y;
    float z;
};

Vec3f vec3f_add(Vec3f, Vec3f);
Vec3f vec3f_sub(Vec3f, Vec3f);
Vec3f vec3f_mul(Vec3f, Vec3f);
Vec3f vec3f_div(Vec3f, Vec3f);

float vec3f_dot_2(Vec3f, Vec3f);

#endif
