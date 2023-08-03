#include <assert.h>
#include <stdlib.h>

#ifdef _MSC_VER
#include <Windows.h>
#endif
#include <GL/gl.h>

#include "texture.h"

Texture texture_create(uint width, uint height)
{
    Texture output;

    output.tex_id = (GLuint) -1;
    output.width = width;
    output.height = height;
    output.generated = false;

    if(width != 0 && height != 0) {
        output.tex = malloc(width * height * 4 * sizeof(uchar));
        assert(output.tex != NULL);
    } else
        output.tex = NULL;

    return output;
}

void texture_free(Texture *tex)
{
    if(tex->tex != NULL)
        free(tex->tex);

    tex->tex = NULL;
    tex->width = 0;
    tex->height = 0;
}

void texture_put_pixel(Texture *t, uint x, uint y, Color c)
{
    assert(x < t->width);
    assert(y < t->height);
    assert(!t->generated);

    t->tex[4 * (x + t->width * y) + 0] = c.red;
    t->tex[4 * (x + t->width * y) + 1] = c.green;
    t->tex[4 * (x + t->width * y) + 2] = c.blue;
    t->tex[4 * (x + t->width * y) + 3] = c.alpha;
}

Color texture_get_pixel(Texture *t, uint x, uint y)
{
    Color output;

    assert(x < t->width);
    assert(y < t->height);

    output.red = t->tex[4 * (x + t->width * y) + 0];
    output.green = t->tex[4 * (x + t->width * y) + 1];
    output.blue = t->tex[4 * (x + t->width * y) + 2];
    output.alpha = t->tex[4 * (x + t->width * y) + 3];

    return output;
}

void texture_generate(Texture *t)
{
    assert(!t->generated);

    glGenTextures(1, &t->tex_id);
    glBindTexture(GL_TEXTURE_2D, t->tex_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, t->width, t->height,
        0, GL_RGBA, GL_UNSIGNED_BYTE, t->tex);

    t->generated = true;
}

void texture_bind(Texture *t)
{
    assert(t->generated);

    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, t->tex_id);
}

