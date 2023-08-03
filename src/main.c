#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef _MSC_VER
#include <sys/time.h>
#endif

#ifdef _MSC_VER
#include <Windows.h>
#endif

#include <GL/glut.h>

#include "texture.h"
#include "reader.h"
#include "spritesheet.h"
#include "animation.h"
#include "perlin.h"
#include "vector.h"
#include "camera.h"
#include "biome.h"
#include "grid.h"

SpriteSheet s1;
static SpriteSheet sp;
static AnimationManager am;
static AnimationCycle ac;

Camera cam;
Vec3f player_pos;
Vec2f player_dir;
Grid g;

float fog_color[] = {.4, .58, .93, 1};

BiomeType biome_noise(float x, float y)
{
	float perlin_noise;

	x += 1./32.f;
	y += 1./32.f;
	
	perlin_noise = perlin(x / 128. , y / 128.);

	if(perlin_noise < .1f) return SEA;
	if(perlin_noise < .125f) return BEACH;
	if(perlin_noise < .25f) return DEFAULT;
	return MOUNTAIN;
}

Texture* get_ground_texture(float x, float y)
{
	switch(biome_noise(x + .5, y + .5)) {
	case SEA: return spritesheet_get_texture(s1, 1);
	case BEACH: return spritesheet_get_texture(s1, 3);
	case DEFAULT: return spritesheet_get_texture(s1, 0);
	case MOUNTAIN: return spritesheet_get_texture(s1, 2);
	}
	return NULL;
}


float noise(float x, float y)
{
	float p1, p2, p3;
	BiomeType b;

	b = biome_noise(x, y);

	x += 1./32.f;
	y += 1./32.f;

	p1 = perlin(x / 128. , y / 128.);
	p2 = perlin( 4. * x,  4. * y);
	p3 = perlin(16. * x, 16. * y);

	switch(b) {
	case SEA: return .1f;
	case BEACH: return 15. * (p1 - .1) + 0.0625 * p2 + .1f; 
	case DEFAULT: return 15. * (p1 - .125) + .125 * p2 + .0625 * p3;
	case MOUNTAIN: return 15. * (p1 - .25) + .5 + 2.5 * p2 + .125 * p3 + 1.25;
	}

	return -1;
}

float noise_middle(float x, float y)
{
	float fx, fy;

	fx = floor(x);
	fy = floor(y);

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
#ifndef _MSC_VER
	struct timeval te;
	gettimeofday(&te, NULL);
	return te.tv_sec * 1000LL + te.tv_usec / 1000;
#else
	SYSTEMTIME t;
	GetSystemTime(&t);
	return t.wSecond * 1000LL + t.wMilliseconds;
#endif
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
	for(x = (int) cam.pos.x - 25; x < cam.pos.x + 25; x ++) {
		for(z = (int) cam.pos.z - 25; z < cam.pos.z + 25; z ++) {
			y = noise_middle(x, z);

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
	texture_bind(spritesheet_get_texture(sp, 0));
	glPushMatrix();

	glTranslatef(player_pos.x, player_pos.y, player_pos.z);
	glRotatef(-cam.rot.y, 0, 1, 0);

	glBegin(GL_QUADS);
		glTexCoord2f(0., 0.); glVertex3f(-.25,  0, 0);
		glTexCoord2f(1., 0.); glVertex3f( .25,  0, 0);
		glTexCoord2f(1., 1.); glVertex3f( .25, .5, 0);
		glTexCoord2f(0., 1.); glVertex3f(-.25, .5, 0);
	glEnd();

	glPopMatrix();

}

void display()
{
	int x, z;

	glClearColor(.4, .58, .93, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_FOG);
	glEnable(GL_DEPTH_TEST);
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glPushMatrix();

	glEnable(GL_TEXTURE_2D);

	glRotatef(cam.rot.x, 1, 0, 0);
	glRotatef(cam.rot.y, 0, 1, 0);
	glRotatef(cam.rot.z, 0, 0, 1);

	/* World drawing */
	glPushMatrix();
	glTranslatef(player_pos.x-cam.pos.x, -cam.pos.y, player_pos.z-cam.pos.z);
	grid_draw(&g, player_pos.x, player_pos.z);
	glPopMatrix();

	glTranslatef(-cam.pos.x, -cam.pos.y, -cam.pos.z);

	entities_draw();

	glPopMatrix();

	gui_draw();

	glDisable(GL_TEXTURE_2D);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glutSwapBuffers();
}

#define SPEED .25
#ifndef M_PI
#define M_PI 3.141592653589793238463
#endif

void update_camera_position()
{
	cam.pos.x = player_pos.x + 2. * sin(-cam.rot.y * M_PI / 180.);
	cam.pos.z = player_pos.z + 2. * cos(-cam.rot.y * M_PI / 180.);
	cam.pos.y = player_pos.y + 2;
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

	player_pos.y = noise_floor(player_pos.x, player_pos.z);

	player_dir.x =  sin(cam.rot.y * M_PI / 180.);
	player_dir.y = -cos(cam.rot.y * M_PI / 180.);

	update_camera_position();
}


void timer_func(int _)
{
	long long start, end;

	animationmanager_update(&am, .01);
	glutTimerFunc(10, timer_func, 0);

	start = get_current_time();
	display();
	end = get_current_time();
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
	FILE *f;

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

	cam.rot.x = 0;
	cam.rot.y = 0;
	cam.rot.z = 0;

	update_camera_position();

	f = fopen("resources/Grass.bmp", "rb");
	s1 = spritesheet_create(texture_load(f), 8, 8);
	fclose(f);
	spritesheet_generate(s1);

	f = fopen("resources/Player.bmp", "rb");
	sp = spritesheet_create(texture_load(f), 8, 8);
	fclose(f);
	spritesheet_generate(sp);

	ac = animationcycle_create(.1f);
	for(i = 0; i < s1.count; i ++)
		animationcycle_add_frame(&ac, spritesheet_get_texture(s1, i));

	am = animationmanager_create();
	animationmanager_enqueue(&am, &ac);

	g = grid_init(noise, get_ground_texture, 20, 20);

	
	glutTimerFunc(100, timer_func, 0);
	glutReshapeFunc(reshape_func);
	glutKeyboardFunc(Keyboard_Test);

	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogf(GL_FOG_END, 10);
	glFogfv(GL_FOG_COLOR, fog_color);

	glutMainLoop();

	return EXIT_SUCCESS;
}
