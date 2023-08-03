#include <assert.h>
#include <stdlib.h>

#include "spritesheet.h"
#include "texture.h"

SpriteSheet spritesheet_create(Texture t, int cell_width, int cell_height)
{
    int i, j;
    int x, y;
    SpriteSheet output;
    int texture_per_col, texture_per_row;

    assert(t.width % cell_width == 0);
    assert(t.height % cell_height == 0);

    texture_per_col = t.width / cell_width;
    texture_per_row = t.height / cell_height;

    output.count = texture_per_row * texture_per_col;
    output.textures = (Texture*) malloc(output.count * sizeof(Texture));

    assert(output.textures != NULL);

    for(j = 0; j < texture_per_row; j ++) {
        for(i = 0; i < texture_per_col; i ++) {
            output.textures[i + texture_per_col * j] =
                texture_create(cell_width, cell_height);

            for(y = 0; y < cell_height; y ++)
                for(x = 0; x < cell_width; x ++)
                    texture_put_pixel(
                        &output.textures[i + texture_per_col * j],
                        x, y,
                        texture_get_pixel(
                            &t,
                            x + cell_width  * i,
                            y + cell_height * j
                        )
                    );
        }
    }

    texture_free(&t);

    return output;
}

Texture* spritesheet_get_texture(SpriteSheet s, uint i)
{
    assert(i < s.count);
    return &s.textures[i];
}

void spritesheet_generate(SpriteSheet s)
{
    uint i;

    for(i = 0; i < s.count; i ++)
        texture_generate(&s.textures[i]);
}

