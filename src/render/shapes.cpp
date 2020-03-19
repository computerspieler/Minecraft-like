#include <GL/freeglut.h>

#include "shapes.h"

using namespace Render;

float depth;

void Shapes::Draw_Square(Vector2f v_pos, Vector2f v_size, Texture::Wrap_Format wrap_fmt){
	Vector2f v_tex_start, v_tex_end;

	switch(wrap_fmt){
		case Texture::FILL: v_tex_end = Vector2f(1, 1); break;
		case Texture::REPEAT:
			v_tex_end = Vector2f(v_size);
			break;	
	}

	glBegin(GL_QUADS);
		glTexCoord2f(v_tex_start.x, v_tex_start.y);
		glVertex3f(v_pos.x, v_pos.y, depth);
		
		glTexCoord2f(v_tex_end.x, v_tex_start.y);
		glVertex3f(v_pos.x + v_size.x, v_pos.y, depth);
		
		glTexCoord2f(v_tex_end.x, v_tex_end.y);
		glVertex3f(v_pos.x + v_size.x, v_pos.y + v_size.y, depth);
		
		glTexCoord2f(v_tex_start.x, v_tex_end.y);
		glVertex3f(v_pos.x, v_pos.y + v_size.y, depth);
	glEnd();
}

void Shapes::Go_To_Layer(Shapes::Layer layer){
	switch(layer){
		case BACKGROUND: depth = -0.1; break;
		case NORMAL    : depth =  0.0; break;
		case FOREGROUND: depth =  0.1; break;
	}
}


