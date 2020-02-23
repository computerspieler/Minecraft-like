#include <iostream>
#include <GL/freeglut.h>

#include "debug.h"
#include "vector.h"
#include "render.h"

#define SPEED 0.1f

void Draw_Test(){

	glBegin(GL_QUADS);
		glColor3f(1, 1, 1);
		glVertex2f(1, 1);
		glVertex2f(2, 1);
		glVertex2f(2, 2);
		glVertex2f(1, 2);
	glEnd();
}

void Draw_Test2(){

	glBegin(GL_QUADS);
		glColor3f(0.5, 0.5, 0.5);
		glVertex3f(20, 15, -0.1);
		glVertex3f( 0, 15, -0.1);
		glVertex3f( 0,  0, -0.1);
		glVertex3f(20,  0, -0.1);

		glColor3f(0.75, 0.75, 0.75);
		glVertex3f(0, 15, 0.1);
		glVertex3f(1, 15, 0.1);
		glVertex3f(1,  0, 0.1);
		glVertex3f(0,  0, 0.1);
	glEnd();
}

void Idle_Test(){ Render::Draw(); }

void Keyboard_Test(unsigned char key, int x, int y){
	Render::Camera* cam;

	// Put the characters upper case
	if(key >= 'a' && key <= 'z')
		key -= ('a' - 'A');

	cam = Render::Camera_Get();

	switch(key){
		case 'Z': cam->position.y -= SPEED; break;
		case 'S': cam->position.y += SPEED; break;
		case 'Q': cam->position.x += SPEED; break;
		case 'D': cam->position.x -= SPEED; break;

		default:
			Debug::Info << "Key Pressed : " << key << " (" << (int)key << ")" << std::endl;
	}

	Debug::Info << "Camera's position " << cam->position << std::endl;
}

void Timer_Test(int value){

	Debug::Info << "Time passed since the beginning : " << value << " seconds" << std::endl;
	glutTimerFunc(1000, Timer_Test, value + 1);
}

int main(int argc, char** argv){

	Render::Init(&argc, argv);

	Render::Draw_Callback_Add(Draw_Test);
	Render::GUI_Draw_Callback_Add(Draw_Test2);

	glutIdleFunc(Idle_Test);
	glutKeyboardFunc(Keyboard_Test);
	glutTimerFunc(1000, Timer_Test, 1);

	glutMainLoop();

	return 0;
}
