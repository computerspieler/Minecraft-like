#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#ifdef _MSC_VER
#include <Windows.h>
#endif
#include <GL/gl.h>

#include "typedef.h"

typedef struct Color Color;
struct Color
{
    uchar red;
    uchar green;
    uchar blue;
    uchar alpha;
};

typedef struct Texture Texture;
struct Texture
{
    uint width;
    uint height;
    uchar* tex;
    GLuint tex_id;
    bool generated;
};

Texture texture_create(uint width, uint height);
void texture_free(Texture *tex);

void texture_put_pixel(Texture*, uint x, uint y, Color);
Color texture_get_pixel(Texture*, uint x, uint y);

void texture_generate(Texture *t);
void texture_bind(Texture *t);

#endif

