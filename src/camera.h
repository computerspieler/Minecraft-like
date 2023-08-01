#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "vector.h"

typedef struct Camera Camera;
struct Camera
{
	float aspect_ratio;
	Vec3f pos, rot;
};

void camera_update_matrix(Camera*);

#endif
