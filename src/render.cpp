#include <vector>

#include <GL/freeglut.h>

#include "debug.h"
#include "render.h"

std::vector<void(*)()> draw_callbacks;
std::vector<void(*)()> gui_draw_callbacks;
Render::Camera* camera;

int Render::Init(int* argc, char** argv){
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("Minehead");

	glutDisplayFunc(Draw);
	glutReshapeFunc(Resize);

	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);

	camera = new Camera();

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	return 0;
}

void Render::Draw(){
	int i;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0, 0, 0, 0);

	glPushMatrix();
	glTranslatef(camera->position.x, camera->position.y, 0);

	for(i = 0; i < (int)draw_callbacks.size(); i++){
		if(draw_callbacks[i] != nullptr)
			draw_callbacks[i]();
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 0.1);

	for(i = 0; i < (int)gui_draw_callbacks.size(); i++){
		if(gui_draw_callbacks[i] != nullptr)
			gui_draw_callbacks[i]();
	}
	glPopMatrix();

	glutSwapBuffers();
}

void Render::Resize(int width, int height){
	camera->Projection_Set(width, height);	
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

int Render::GUI_Draw_Callback_Add(void (*function)()){
        gui_draw_callbacks.push_back(function);

        return gui_draw_callbacks.size() - 1;
}

void Render::GUI_Draw_Callback_Delete(int function_id){
        if(function_id >= (int)gui_draw_callbacks.size() || function_id < 0){
                Debug::Error << "Try to delete an out of bounds render function" << std::endl;
                Debug::Error << "The wanted render function ID: " << function_id << std::endl;
                Debug::Error << "Number of render functions: " << gui_draw_callbacks.size() << std::endl;
                return;
        }

        gui_draw_callbacks.erase(gui_draw_callbacks.begin() + function_id);
}


void Render::Draw_Callbacks_Delete(){
	draw_callbacks.clear();
}

Render::Camera* Render::Camera_Get(){ return camera; }

