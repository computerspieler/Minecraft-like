#ifndef _GRID_H_
#define _GRID_H_

#ifdef _MSC_VER
#include <Windows.h>
#endif

#include <GL/gl.h>

#include "texture.h"

typedef struct Grid Grid;
struct Grid
{
    float (*height)(float, float);
    Texture* (*tex)(float, float);

    GLfloat *vertex_array;
    Texture* *texture_array;
    GLfloat *tex_coord_array;

    int cache_width;
    int cache_height;
    int cache_center_x;
    int cache_center_y;

    float middle_x;
    float middle_y;
};

Grid grid_init(float (*height)(float, float), Texture* (*tex)(float, float), int cache_width, int cache_height);
void grid_draw(Grid*, float offset_x, float offset_y);

#endif
