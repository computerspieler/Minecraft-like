#include <GL/gl.h>

#include "camera.h"

using namespace Render;

Camera::Camera(): position(), rotation(), zoom(1.0) {}


void Camera::Projection_Set(int width, int height){
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 80, height * 80 / width, 0, -0.2, 0.2);
	glMatrixMode(GL_MODELVIEW);
}
