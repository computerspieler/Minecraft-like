#include <vector>

#include <GL/freeglut.h>

#include "debug.h"
#include "render.h"

std::vector<void(*)()> display_functions;
Render::Camera* camera;

int Render::Init(int* argc, char** argv){
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("Minehead");

	glutDisplayFunc(Draw);

	camera = new Camera();

	return 0;
}

void Render::Draw(){
	int i;

	glClearColor(0, 0, 0, 0);

	for(i = 0; i < (int)display_functions.size(); i++){
		if(display_functions[i] != nullptr)
			display_functions[i]();
	}

	glutSwapBuffers();
}

int Render::Add_Render_Function(void (*function)()){
	display_functions.push_back(function);

	return display_functions.size() - 1;
}

void Render::Delete_Render_Funtion(int function_id){
	if(function_id >= (int)display_functions.size() || function_id < 0){
		Debug::Error << "Try to delete an out of bounds render function" << std::endl;
		Debug::Error << "The wanted render function ID: " << function_id << std::endl;		
		Debug::Error << "Number of render functions: " << display_functions.size() << std::endl;		
		return;
	}

	display_functions.erase(display_functions.begin() + function_id);
}

void Render::Clear_Render_Funtions(){
	display_functions.clear();
}

Render::Camera* Render::get_Camera(){ return camera; }
