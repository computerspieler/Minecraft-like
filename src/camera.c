#ifdef _MSC_VER
#include <Windows.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>

#include "camera.h"

void camera_update_matrix(Camera* cam)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(100., cam->aspect_ratio, .1, 100);
	glMatrixMode(GL_MODELVIEW);
}