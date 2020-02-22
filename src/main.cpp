#include <iostream>
#include <GL/freeglut.h>

#include "debug.h"
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

	int first_render_func_id;

	Debug::Info    << "Test" << std::endl;
	Debug::Warning << "Test" << std::endl;
	Debug::Error   << "Test" << std::endl;

	Render::Init(&argc, argv);

	first_render_func_id = Render::Add_Render_Function(Draw_Test);
	std::cout << first_render_func_id << std::endl;
	std::cout << Render::Add_Render_Function(Draw_Test2) << std::endl;
	Render::Delete_Render_Funtion(-1);

	glutMainLoop();

	return 0;
}
