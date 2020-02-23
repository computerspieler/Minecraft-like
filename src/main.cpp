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
		glVertex2f( 0,  0);
		glVertex2f(-1,  0);
		glVertex2f(-1, -1);
		glVertex2f( 0, -1);
	glEnd();
}

void Idle_Test(){}

void Keyboard_Test(unsigned char key, int x, int y){
	// Put the characters upper case
	if(key >= 'a' && key <= 'z')
		key -= ('a' - 'A');

	switch(key){
		default:
			Debug::Info << "Key Pressed : " << key << " (" << (int)key << ")" << std::endl;
	}
}

void Timer_Test(int value){

	Debug::Info << "Time passed since the beginning : " << value << " seconds" << std::endl;
	glutTimerFunc(1000, Timer_Test, value + 1);
}

int main(int argc, char** argv){

	Render::Init(&argc, argv);

	Render::Draw_Callback_Add(Draw_Test);
	Render::Draw_Callback_Add(Draw_Test2);

	glutIdleFunc(Idle_Test);
	glutKeyboardFunc(Keyboard_Test);
	Timer_Test(0);

	glutMainLoop();

	return 0;
}
