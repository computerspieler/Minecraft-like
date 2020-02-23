#include <GL/gl.h>

#include "camera.h"

using namespace Render;

Camera::Camera(): position(), rotation() {}

void Camera::Projection_Set(int width, int height){
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 20, height * 20 / width, 0, -0.2, 0.2);
	glMatrixMode(GL_MODELVIEW);
}
