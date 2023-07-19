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


Vec2i vec2i_add(Vec2i v1, Vec2i v2)
{
    Vec2i output;

    output.x = v1.x + v2.x;
    output.y = v1.y + v2.y;

    return output;
}

Vec2i vec2i_sub(Vec2i v1, Vec2i v2)
{
    Vec2i output;

    output.x = v1.x - v2.x;
    output.y = v1.y - v2.y;

    return output;
}

Vec2i vec2i_mul(Vec2i v1, Vec2i v2)
{
    Vec2i output;

    output.x = v1.x * v2.x;
    output.y = v1.y * v2.y;

    return output;
}

Vec2i vec2i_div(Vec2i v1, Vec2i v2)
{
    Vec2i output;

    output.x = v1.x / v2.x;
    output.y = v1.y / v2.y;

    return output;
}

int vec2i_dot_2(Vec2i v1, Vec2i v2)
{ return v1.x * v2.x + v1.y * v2.y; }
