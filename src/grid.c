#include <math.h>

#include "grid.h"

#ifdef _MSC_VER
#include <Windows.h>
#endif

#include <GL/glut.h>

void grid_update_cache(Grid *g)
{
    int i, x, y;

    for(i = 0; i < 4 * g->cache_width * g->cache_height; i ++)
        g->vertex_array[3 * i + 1] = g->height(
            g->vertex_array[3 * i + 0] + g->cache_center_x,
            g->vertex_array[3 * i + 2] + g->cache_center_y
        );

    for(x = 0; x < g->cache_width; x ++)
        for(y = 0; y < g->cache_height; y ++)
            g->texture_array[x + g->cache_width * y] = g->tex(
                (float) floor(x + g->cache_center_x) - g->middle_x,
                (float) floor(y + g->cache_center_y) - g->middle_y
            );
}

Grid grid_init(float (*height)(float, float), Texture* (*tex)(float, float), int cache_width, int cache_height)
{
    int x, y;
    float middle_x, middle_y;

    Grid output;

    middle_x = (float) cache_width * .5f;
    middle_y = (float) cache_height * .5f;

    output.cache_width = cache_width;
    output.cache_height = cache_height;
    output.height = height;
    output.tex = tex;
    output.cache_center_x = 0;
    output.cache_center_y = 0;
    output.middle_x = middle_x;
    output.middle_y = middle_y;

    output.texture_array = (Texture**) malloc(cache_width * cache_height * sizeof(Texture*));
    output.vertex_array = (GLfloat*) malloc(cache_width * cache_height * 4 * 3 * sizeof(GLfloat));
    output.tex_coord_array = (GLfloat*) malloc(cache_width * cache_height * 4 * 2 * sizeof(GLfloat));

    /* Initialize the vertex array */
    for(x = 0; x < cache_width; x ++) {
        for(y = 0; y < cache_height; y ++) {
            output.vertex_array[12 * (x + cache_width * y) + 3 * 0 + 0] = (float) x - middle_x;
            output.vertex_array[12 * (x + cache_width * y) + 3 * 0 + 2] = (float) y - middle_y;

            output.tex_coord_array[8 * (x + cache_width * y) + 2 * 0 + 0] = 0;
            output.tex_coord_array[8 * (x + cache_width * y) + 2 * 0 + 1] = 0;

            output.vertex_array[12 * (x + cache_width * y) + 3 * 1 + 0] = (float) x - middle_x + 1;
            output.vertex_array[12 * (x + cache_width * y) + 3 * 1 + 2] = (float) y - middle_y;

            output.tex_coord_array[8 * (x + cache_width * y) + 2 * 1 + 0] = 1;
            output.tex_coord_array[8 * (x + cache_width * y) + 2 * 1 + 1] = 0;

            output.vertex_array[12 * (x + cache_width * y) + 3 * 2 + 0] = (float) x - middle_x + 1;
            output.vertex_array[12 * (x + cache_width * y) + 3 * 2 + 2] = (float) y - middle_y + 1;

            output.tex_coord_array[8 * (x + cache_width * y) + 2 * 2 + 0] = 1;
            output.tex_coord_array[8 * (x + cache_width * y) + 2 * 2 + 1] = 1;

            output.vertex_array[12 * (x + cache_width * y) + 3 * 3 + 0] = (float) x - middle_x;
            output.vertex_array[12 * (x + cache_width * y) + 3 * 3 + 2] = (float) y - middle_y + 1;

            output.tex_coord_array[8 * (x + cache_width * y) + 2 * 3 + 0] = 0;
            output.tex_coord_array[8 * (x + cache_width * y) + 2 * 3 + 1] = 1;
        }
    }
    grid_update_cache(&output);

    return output;
}

GLfloat tex_array[] = {
    0, 0,
    1, 0,
    0, 1,
    1, 1,
};

void grid_draw(Grid* g, float offset_x, float offset_y)
{
    int i;

    if(abs((int)floor(offset_x) - g->cache_center_x) >= 1 || abs((int)floor(offset_y) - g->cache_center_y) >= 1) {
        g->cache_center_x = (int) floor(offset_x);
        g->cache_center_y = (int) floor(offset_y);
        grid_update_cache(g);
    }

    glPushMatrix();
    glTranslatef(g->cache_center_x - offset_x, 0, g->cache_center_y - offset_y);
    glVertexPointer(3, GL_FLOAT, 0, g->vertex_array);
    glTexCoordPointer(2, GL_FLOAT, 0, g->tex_coord_array);

    for(i = 0; i < g->cache_width * g->cache_height; i ++) {
	    texture_bind(g->texture_array[i]);
        glDrawArrays(GL_QUADS, 4*i, 4);
    }

    glPopMatrix();
}

