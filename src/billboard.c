#include "billboard.h"
#include "vector.h"
#include "texture.h"
#include "camera.h"

void billboard_init()
{

}

extern Camera cam;

void billboard_draw(Billboard* b)
{
	glPushMatrix();

	glTranslatef(b->pos.x, b->pos.y, b->pos.z);
	glRotatef(-cam.rot.x, 1, 0, 0);

	texture_bind(b->tex);
	glBegin(GL_QUADS);
		glTexCoord2f(0., 0.); glVertex3f(-.5, 0, 0);
		glTexCoord2f(1., 0.); glVertex3f( .5, 0, 0);
		glTexCoord2f(1., 1.); glVertex3f( .5, 1, 0);
		glTexCoord2f(0., 1.); glVertex3f(-.5, 1, 0);
	glEnd();

	glPopMatrix();
}
