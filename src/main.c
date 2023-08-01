#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>

#include <GL/glut.h>

#include "texture.h"
#include "reader.h"
#include "spritesheet.h"
#include "animation.h"
#include "perlin.h"
#include "vector.h"
#include "billboard.h"
#include "camera.h"

static SpriteSheet s1;
static SpriteSheet sp;
static AnimationManager am;
static AnimationCycle ac;

Camera cam;
Vec3f player_pos;
Vec2f player_dir;

int cam_max_x, cam_min_x;
int cam_max_z, cam_min_z;
float fog_color[] = {.4, .58, .93, 1};

float noise(float x, float y)
{
	x += 1./32.f;
	y += 1./32.f;

	return (3.  * perlin(x / 8. , y / 8.)
		+.5  * perlin(4. * x , 4. * y)
		+.25 * perlin(16. * x, 16. * y)
	) / 3.75;
}

float noise_middle(float x, float y)
{
	float fx = floor(x);
	float fy = floor(y);

	return (noise(fx + 1, fy) + noise(fx, fy + 1)) * .5;
}

float noise_floor(float x, float y)
{
	float p1, p2, p3;
	float fx, fy;
	float dx, dy;

	fx = floor(x);
	fy = floor(y);
	
	dx = x - fx;
	dy = y - fy;

	p1 = noise(fx, fy + 1);
	p2 = noise(fx + 1, fy);

	if(dx + dy < 1) {
		p3 = noise(fx, fy);
		return (1. - dx - dy) * p3 + dx * p2 + dy * p1;
	} else {
		p3 = noise(fx + 1, fy + 1);
		dx = 1. - dx;
		dy = 1. - dy;
		return (1. - dx - dy) * p3 + dx * p1 + dy * p2;
	}
}

long long get_current_time()
{
	struct timeval te;
	gettimeofday(&te, NULL);
	return te.tv_sec * 1000LL + te.tv_usec / 1000;
}

void gui_draw()
{
	int i;

	glDisable(GL_DEPTH_TEST);
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
	float x, y, z;

	texture_bind(spritesheet_get_texture(s1, 4));
	for(x = (int) cam.pos.x + cam_min_x; x < cam.pos.x + cam_max_x; x ++) {
		for(z = (int) cam.pos.z + cam_min_z; z < cam.pos.z + cam_max_z; z ++) {
			y = 5. * noise_middle(x, z);

			if(y > 4 || y < 2)
				continue;

			glTranslatef(x, y, z);
			glRotatef(-cam.rot.y, 0, 1, 0);

			glBegin(GL_QUADS);
				glTexCoord2f(0., 0.); glVertex3f(0, 0, 0.5);
				glTexCoord2f(1., 0.); glVertex3f(1, 0, 0.5);
				glTexCoord2f(1., 1.); glVertex3f(1, 1, 0.5);
				glTexCoord2f(0., 1.); glVertex3f(0, 1, 0.5);
			glEnd();

			glRotatef(cam.rot.y, 0, 1, 0);
			glTranslatef(-x, -y, -z);
		}
	}

	/* Player drawing */
	Billboard b;
	b.pos = player_pos;
	b.tex = spritesheet_get_texture(sp, 0);
	billboard_draw(&b);
}

void display()
{
	int x, z;

	glClearColor(.4, .58, .93, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_FOG);
	glEnable(GL_DEPTH_TEST);

	glPushMatrix();

	glRotatef(cam.rot.x, 1, 0, 0);
	glRotatef(cam.rot.y, 0, 1, 0);
	glRotatef(cam.rot.z, 0, 0, 1);
	glTranslatef(-cam.pos.x, -cam.pos.y, -cam.pos.z);

	glEnable(GL_TEXTURE_2D);

	/* World drawing */
	/* TODO: Clipping */
	cam_min_x = -25;
	cam_max_x =  25;
	cam_min_z = -25;
	cam_max_z =  25;

	for(x = floor(cam.pos.x) + cam_min_x; x <= floor(cam.pos.x) + cam_max_x; x ++) {
		for(z = floor(cam.pos.z) + cam_min_z; z <= floor(cam.pos.z) + cam_max_z; z ++) {
			texture_bind(spritesheet_get_texture(s1, (int)(x+z) & 3));

			glBegin(GL_QUADS);
				glTexCoord2f(0., 0.); glVertex3f(x,   5. * noise(x,   z),   z);
				glTexCoord2f(1., 0.); glVertex3f(x+1, 5. * noise(x+1, z),   z);
				glTexCoord2f(1., 1.); glVertex3f(x+1, 5. * noise(x+1, z+1), z+1);
				glTexCoord2f(0., 1.); glVertex3f(x,   5. * noise(x,   z+1), z+1);
			glEnd();
		}
	}

	entities_draw();

	glPopMatrix();

	gui_draw();

	glDisable(GL_TEXTURE_2D);

	glutSwapBuffers();
}

#define SPEED .25
#ifndef M_PI
#define M_PI 3.141592653589793238463
#endif

void update_camera_position()
{
	cam.pos.x = player_pos.x + 3. * sin(-cam.rot.y * M_PI / 180.);
	cam.pos.z = player_pos.z + 3. * cos(-cam.rot.y * M_PI / 180.);
	cam.pos.y = player_pos.y + 3;
}

void Keyboard_Test(unsigned char key, int x, int y)
{
	/* Put the characters upper case */
	if(key >= 'a' && key <= 'z')
		key -= ('a' - 'A');

	switch(key){
		case 'Z':
			player_pos.z += SPEED * player_dir.y;
			player_pos.x += SPEED * player_dir.x;
			break;
		case 'S':
			player_pos.z -= SPEED * player_dir.y;
			player_pos.x -= SPEED * player_dir.x;
			break;
		case 'Q':
			player_pos.z -= SPEED * player_dir.x;
			player_pos.x += SPEED * player_dir.y;
			break;
		case 'D':
			player_pos.z += SPEED * player_dir.x;
			player_pos.x -= SPEED * player_dir.y;
			break;
		case ' ': cam.pos.y += SPEED; break;
		case 8  : cam.pos.y -= SPEED; break;


		case 'I': cam.rot.x += 10. * SPEED; break;
		case 'K': cam.rot.x -= 10. * SPEED; break;
		case 'J': cam.rot.y += 10. * SPEED; break;
		case 'L': cam.rot.y -= 10. * SPEED; break;

		default: break;
	}

	while(cam.rot.y < 0)
		cam.rot.y += 360.;

	while(cam.rot.y >= 360.)
		cam.rot.y -= 360.;

	player_pos.y = 5. * noise_floor(player_pos.x, player_pos.z);

	player_dir.x =  sin(cam.rot.y * M_PI / 180.);
	player_dir.y = -cos(cam.rot.y * M_PI / 180.);

	update_camera_position();
}


void timer_func(int _)
{
	animationmanager_update(&am, .01);
	glutTimerFunc(10, timer_func, 0);

	long long start = get_current_time();
	display();
	long long end = get_current_time();
	printf("Time per frame: %lld ms\n", end - start);
}

void reshape_func(int width, int height)
{
	glViewport(0, 0, width, height);
	cam.aspect_ratio = (float) width / (float) height;
	camera_update_matrix(&cam);
}

int main(int argc, char* argv[])
{
	uint i;

	glutInit(&argc, argv);

	glutCreateWindow("Test");
	glutInitWindowSize(640, 480);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	glutDisplayFunc(display);

	player_pos.x = 0;
	player_pos.y = 0;
	player_pos.z = 0;

	player_dir.x = 0;
	player_dir.y = -1;

	cam.rot.x = 30;
	cam.rot.y = 0;
	cam.rot.z = 0;

	update_camera_position();

	FILE *f = fopen("resources/Grass.bmp", "r");
	s1 = spritesheet_create(texture_load(f), 8, 8);
	fclose(f);
	spritesheet_generate(s1);

	f = fopen("resources/Player.bmp", "r");
	sp = spritesheet_create(texture_load(f), 8, 8);
	fclose(f);
	spritesheet_generate(sp);

	ac = animationcycle_create(.1f);
	for(i = 0; i < s1.count; i ++)
		animationcycle_add_frame(&ac, spritesheet_get_texture(s1, i));

	am = animationmanager_create();
	animationmanager_enqueue(&am, &ac);
	
	glutTimerFunc(100, timer_func, 0);
	glutReshapeFunc(reshape_func);
	glutKeyboardFunc(Keyboard_Test);

	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogf(GL_FOG_END, 17);
	glFogfv(GL_FOG_COLOR, fog_color);

	glutMainLoop();

	return EXIT_SUCCESS;
}
