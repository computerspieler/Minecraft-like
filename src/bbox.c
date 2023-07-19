#include "bbox.h"

/*
    TODO: Make a more generalized version,
    for now it only works if b1 is smaller than
    b2 in every direction
*/
bool bbox_b_collide(BBox b1, BBox b2)
{
    return (
        (b1.min.x >= b2.min.x && b1.min.x <= b2.max.x) ||
        (b1.max.x >= b2.min.x && b1.max.x <= b2.max.x)
    ) && (
        (b1.min.y >= b2.min.y && b1.min.y <= b2.max.y) ||
        (b1.max.y >= b2.min.y && b1.max.y <= b2.max.y)
    );
}