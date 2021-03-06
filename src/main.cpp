#include <iostream>
#include <GL/freeglut.h>

#include "debug.h"
#include "math/vector.h"
#include "render/shapes.h"
#include "render/texture.h"
#include "render/render.h"
#include "render/bmp_reader.h"

#define SPEED 0.5f

Render::Texture *texture, *texture_2;

void Draw_Test(){
	texture_2->Bind();
	for(int y = 0; y < 256; y++)
		for(int x = 0; x < 16*16; x++)
			Render::Shapes::Draw_Square(Vector2f(x, y), Vector2f(1, 1), Render::Texture::FILL);
	glDisable(GL_TEXTURE_2D);
}

void Draw_Test2(){

	texture->Bind();
	
	Render::Shapes::Go_To_Layer(Render::Shapes::BACKGROUND);
	Render::Shapes::Draw_Square(Vector2f(0, 0), Vector2f(80, 60), Render::Texture::REPEAT);
	
	glDisable(GL_TEXTURE_2D);
		
	//Render::Shapes::Go_To_Layer(Render::Shapes::FOREGROUND);
	//Render::Shapes::Draw_Square(Vector2f(0, 0), Vector2f(4, 60));
}

void Idle_Test(){ Render::Draw(); }

void Keyboard_Test(unsigned char key, int x, int y){
	Render::Camera* cam;

	// Put the characters upper case
	if(key >= 'a' && key <= 'z')
		key -= ('a' - 'A');

	cam = Render::Camera_Get();

	switch(key){
		case 'Z': cam->position.y += SPEED; break;
		case 'S': cam->position.y -= SPEED; break;
		case 'Q': cam->position.x += SPEED; break;
		case 'D': cam->position.x -= SPEED; break;
		case '+': cam->zoom       += SPEED; break;
		case '-': cam->zoom	  -= SPEED; break;

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
	int x, y;
	
	Render::Init(&argc, argv);

	Render::Draw_Callback_Add(Draw_Test);
	Render::GUI_Draw_Callback_Add(Draw_Test2);

	glutIdleFunc(Idle_Test);
	glutKeyboardFunc(Keyboard_Test);
	glutTimerFunc(1000, Timer_Test, 1);
	
	texture   = new Render::Texture(8, 8);
	texture_2 = Render::Image::BMP::load_Texture("resources/Grass.bmp");

	for(x = 0; x < 8; x++)
		for(y = 0; y < 8; y++){
			texture->Pixel_Set(x, y, (Render::Color){x*16, y*16, 255, 255});
		}

	texture->Generate();
	texture_2->Generate();

	glutMainLoop();
	
	return 0;
}
