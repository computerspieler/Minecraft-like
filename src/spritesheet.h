#ifndef _SPRITESHEET_H_
#define _SPRITESHEET_H_

#include "typedef.h"
#include "texture.h"

typedef struct SpriteSheet SpriteSheet;
struct SpriteSheet
{
    Texture *textures;
    uint count;
};

SpriteSheet spritesheet_create(Texture t, int cell_width, int cell_height);
Texture* spritesheet_get_texture(SpriteSheet s, uint i);
void spritesheet_generate(SpriteSheet s);

#endif

