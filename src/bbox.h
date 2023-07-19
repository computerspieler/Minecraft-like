#ifndef _BBOX_H_
#define _BBOX_H_

#include "vector.h"
#include "typedef.h"

typedef struct BBox BBox;
struct BBox
{
    Vec2f min;
    Vec2f max;
};

bool bbox_b_collide(BBox, BBox);

#endif
