#include <vector>

#include <GL/freeglut.h>

#include "debug.h"
#include "render.h"

std::vector<void(*)()> draw_callbacks;
Render::Camera* camera;

int Render::Init(int* argc, char** argv){
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("Minehead");

	glutDisplayFunc(Draw);

	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);

	camera = new Camera();

	return 0;
}

void Render::Draw(){
	int i;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0, 0, 0, 0);

	for(i = 0; i < (int)draw_callbacks.size(); i++){
		if(draw_callbacks[i] != nullptr)
			draw_callbacks[i]();
	}

	glutSwapBuffers();
}

int Render::Draw_Callback_Add(void (*function)()){
	draw_callbacks.push_back(function);

	return draw_callbacks.size() - 1;
}

void Render::Draw_Callback_Delete(int function_id){
	if(function_id >= (int)draw_callbacks.size() || function_id < 0){
		Debug::Error << "Try to delete an out of bounds render function" << std::endl;
		Debug::Error << "The wanted render function ID: " << function_id << std::endl;		
		Debug::Error << "Number of render functions: " << draw_callbacks.size() << std::endl;		
		return;
	}

	draw_callbacks.erase(draw_callbacks.begin() + function_id);
}

void Render::Draw_Callbacks_Delete(){
	draw_callbacks.clear();
}

Render::Camera* Render::Camera_Get(){ return camera; }

