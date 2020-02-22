#include <vector>

#include <GL/freeglut.h>

#include "render.h"

std::vector<void(*)()> display_functions;

int Render::Init(int* argc, char** argv){
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("Minehead");

	glutDisplayFunc(Draw);

	return 0;
}

void Render::Draw(){
	int i;

	glClearColor(0, 0, 0, 0);

	for(i = 0; i < display_functions.size(); i++){
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
	if(function_id >= display_functions.size()){
		
		return;
	}

	display_functions.erase(display_functions.begin() + function_id);
}
