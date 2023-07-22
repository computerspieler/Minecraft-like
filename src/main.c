#include <stdio.h>
#include <stdlib.h>

#include <GL/glut.h>

#include "texture.h"
#include "reader.h"
#include "spritesheet.h"
#include "animation.h"
#include "perlin.h"

static SpriteSheet s;
static AnimationManager am;
static AnimationCycle ac;

float aspect_ratio;
float cpx, cpy, cpz;
float crx, cry, crz;

float noise(float x, float y)
{
    return (3. * perlin(x * .25, y * .25)
        + .5 * perlin(4. * x, 4. * y)
        + .25 * perlin(16. * x, 16. * y)
    ) / 3.75;
}

void gui_draw()
{
	int i;
	
    glPushMatrix();

	glTranslatef(-2, 1, -1);

	for(i = 0; i < 10; i ++) {
		glBegin(GL_QUADS);
			glTexCoord2f(0., 0.); glVertex3f(-.1,  0, 0);
			glTexCoord2f(1., 0.); glVertex3f( .1,  0, 0);
			glTexCoord2f(1., 1.); glVertex3f( .1, .2, 0);
			glTexCoord2f(0., 1.); glVertex3f(-.1, .2, 0);
		glEnd();

		glTranslatef(.25, 0, 0);
	}

    glPopMatrix();
}

void entities_draw()
{
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

    glTranslatef(-cpx, -cpy, -cpz);
    glRotatef(-crx, 1, 0, 0);
    glRotatef(-cry, 0, 1, 0);
    glRotatef(-crz, 0, 0, 1);

	texture_bind(animationmanager_get_current_texture(&am));
    glBegin(GL_QUADS);
        glTexCoord2f(0., 0.); glVertex3f(-1., 0, 0.);
        glTexCoord2f(1., 0.); glVertex3f( 1., 0, 0.);
        glTexCoord2f(1., 1.); glVertex3f( 1., 1, 0.);
        glTexCoord2f(0., 1.); glVertex3f(-1., 1, 0.);
    glEnd();

    glPopMatrix();
}

void display()
{
	float x, z;

    glClearColor(.4, .58, .93, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);

    glPushMatrix();

    glRotatef(crx, 1, 0, 0);
    glRotatef(cry, 0, 1, 0);
    glRotatef(crz, 0, 0, 1);
    glTranslatef(-cpx, -cpy, -cpz);

	/* World drawing */
    glBegin(GL_QUADS);
        for(x = (int) cpx-15; x < cpx+15; x ++)
            for(z = (int) cpz-15; z < cpz+15; z ++) {
                glColor3f(0., 0., .5*noise(x-.9, z-.9)+.5); glVertex3f(x,   5. * noise(x-.9, z-.9)  , z);
                glColor3f(0., 0., .5*noise(x+.1, z-.9)+.5); glVertex3f(x+1, 5. * noise(x+.1, z-.9)  , z);
                glColor3f(0., 0., .5*noise(x+.1, z+.1)+.5); glVertex3f(x+1, 5. * noise(x+.1, z+.1), z+1);
                glColor3f(0., 0., .5*noise(x-.9, z+.1)+.5); glVertex3f(x,   5. * noise(x-.9, z+.1), z+1);
            }
    glEnd();

	entities_draw();

    glPopMatrix();

	gui_draw();

    glDisable(GL_TEXTURE_2D);

    glutSwapBuffers();
}

#define SPEED .1

void Keyboard_Test(unsigned char key, int x, int y)
{
	/* Put the characters upper case */
	if(key >= 'a' && key <= 'z')
		key -= ('a' - 'A');

	switch(key){
		case 'Z': cpz -= SPEED; break;
		case 'S': cpz += SPEED; break;
		case 'Q': cpx -= SPEED; break;
		case 'D': cpx += SPEED; break;
		case ' ': cpy += SPEED; break;
		case 8  : cpy -= SPEED; break;


		case 'I': crx += 10. * SPEED; break;
		case 'K': crx -= 10. * SPEED; break;
		case 'J': cry -= 10. * SPEED; break;
		case 'L': cry += 10. * SPEED; break;

		default: break;
	}
}


void timer_func(int _)
{
    animationmanager_update(&am, .01);
    glutTimerFunc(10, timer_func, 0);
    display();
}

void reshape_func(int width, int height)
{
    glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	aspect_ratio = (float) width / (float) height;
	gluPerspective(100., aspect_ratio, .1, 10);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char* argv[])
{
    uint i;

    glutInit(&argc, argv);

    glutCreateWindow("Test");
    glutInitWindowSize(640, 480);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    glutDisplayFunc(display);

    cpx = 0;
    cpy = 1;
    cpz = 0;

	crx = 0.;
	cry = 0;
	crz = 0;
    FILE *f = fopen("resources/Grass.bmp", "r");
    s = spritesheet_create(texture_load(f), 8, 8);
    fclose(f);
    spritesheet_generate(s);

    ac = animationcycle_create(.1f);
    for(i = 0; i < s.count; i ++)
        animationcycle_add_frame(&ac, spritesheet_get_texture(s, i));

    am = animationmanager_create();
    animationmanager_enqueue(&am, &ac);
    
    glutTimerFunc(100, timer_func, 0);
    glutReshapeFunc(reshape_func);
	glutKeyboardFunc(Keyboard_Test);

    glutMainLoop();

    return EXIT_SUCCESS;
}
