#include <iostream>
#include <GL/freeglut.h>

#include "debug.h"
#include "vector.h"
#include "render.h"

void Draw_Test(){

	glBegin(GL_QUADS);
		glColor3f(1, 1, 1);
		glVertex2f(0, 0);
		glVertex2f(1, 0);
		glVertex2f(1, 1);
		glVertex2f(0, 1);
	glEnd();
}

void Draw_Test2(){

	glBegin(GL_QUADS);
		glColor3f(1, 1, 0);
		glVertex2f(-1, -1);
		glVertex2f( 0, -1);
		glVertex2f( 0,  0);
		glVertex2f(-1,  0);
	glEnd();
}

int main(int argc, char** argv){

	Vector3f vec1 = Vector3f();
	Vector3f vec2 = Vector3f(-1, -2, -3);
	Vector3f vec3 = vec1 - vec2;

	Debug::Info << vec3 << std::endl;

	return 0;
}
