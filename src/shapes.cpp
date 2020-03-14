#include <GL/freeglut.h>

#include "shapes.h"

using namespace Render;

float depth;

void Shapes::Draw_Square(Vector2f v_pos, Vector2f v_size){
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex3f(v_pos.x,
						   v_pos.y,
						   depth);
		glTexCoord2f(1.0, 0.0); glVertex3f(v_pos.x + v_size.x,
						   v_pos.y,
						   depth);
		glTexCoord2f(1.0, 1.0); glVertex3f(v_pos.x + v_size.x,
						   v_pos.y + v_size.y,
						   depth);
		glTexCoord2f(0.0, 1.0); glVertex3f(v_pos.x,
						   v_pos.y + v_size.y,
						   depth);
	glEnd();
}

void Shapes::Draw_Quad(Vector2f v0, Vector2f v1, Vector2f v2, Vector2f v3){
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex3f(v0.x, v0.y, depth);
		glTexCoord2f(1.0, 0.0); glVertex3f(v1.x, v1.y, depth);
		glTexCoord2f(1.0, 1.0); glVertex3f(v2.x, v2.y, depth);
		glTexCoord2f(0.0, 1.0); glVertex3f(v3.x, v3.y, depth);
	glEnd();
}

void Shapes::Draw_Triangle(Vector2f v0, Vector2f v1, Vector2f v2){}

void Shapes::Go_To_Layer(Shapes::Layer layer){
	switch(layer){
		case BACKGROUND: depth = -0.1; break;
		case NORMAL    : depth =  0.0; break;
		case FOREGROUND: depth =  0.1; break;
	}
}


