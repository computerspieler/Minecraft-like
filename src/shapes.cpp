#include <GL/freeglut.h>

#include "shapes.h"

using namespace Render;

void Shapes::Draw_Square(Vector2f v_pos, Vector2f v_size){
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex2f(v_pos.x           , v_pos.y);
		glTexCoord2f(1.0, 0.0); glVertex2f(v_pos.x + v_size.x, v_pos.y);
		glTexCoord2f(1.0, 1.0); glVertex2f(v_pos.x + v_size.x, v_pos.y + v_size.y);
		glTexCoord2f(0.0, 1.0); glVertex2f(v_pos.x           , v_pos.y + v_size.y);
	glEnd();
}

void Shapes::Draw_Quad(Vector2f v0, Vector2f v1, Vector2f v2, Vector2f v3){
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex2f(v0.x, v0.y);
		glTexCoord2f(1.0, 0.0); glVertex2f(v1.x, v1.y);
		glTexCoord2f(1.0, 1.0); glVertex2f(v2.x, v2.y);
		glTexCoord2f(0.0, 1.0); glVertex2f(v3.x, v3.y);
	glEnd();
}

void Shapes::Draw_Triangle(Vector2f v0, Vector2f v1, Vector2f v2){}
