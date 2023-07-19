#include <stdio.h>
#include <stdlib.h>

#include <GL/glut.h>

#include "texture.h"
#include "reader.h"
#include "spritesheet.h"
#include "animation.h"

static SpriteSheet s;
static AnimationManager am;
static AnimationCycle ac;

void display()
{
    glClearColor(.4, .58, .93, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    texture_bind(animationmanager_get_current_texture(&am));

    glPushMatrix();

    glTranslatef(.1, 0, 0);

    glBegin(GL_QUADS);
        glTexCoord2f(0., 0.); glVertex3f(0., 0., 0.);
        glTexCoord2f(1., 0.); glVertex3f(1., 0., 0.);
        glTexCoord2f(1., 1.); glVertex3f(1., 1., 0.);
        glTexCoord2f(0., 1.); glVertex3f(0., 1., 0.);
    glEnd();

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    glutSwapBuffers();
}

void timer_func(int)
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
	glOrtho(0, 40, height * 40 / width, 0, -0.2, 0.2);
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

    glutMainLoop();

    return EXIT_SUCCESS;
}
