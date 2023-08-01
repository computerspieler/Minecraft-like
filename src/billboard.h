#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "texture.h"
#include "vector.h"

typedef struct Billboard Billboard;
struct Billboard
{
	Vec3f pos;
	Texture *tex;
};

void billboard_init();
void billboard_draw(Billboard*);

#endif
