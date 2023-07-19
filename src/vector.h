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

typedef struct Vec2i Vec2i;
struct Vec2i
{
    int x;
    int y;
};

Vec2i vec2i_add(Vec2i, Vec2i);
Vec2i vec2i_sub(Vec2i, Vec2i);
Vec2i vec2i_mul(Vec2i, Vec2i);
Vec2i vec2i_div(Vec2i, Vec2i);

int vec2i_dot_2(Vec2i, Vec2i);

#endif
