#include <GL/gl.h>
#include <cstdlib>
#include <cstdint>

#include "texture.h"
#include "debug.h"

using namespace Render;

Texture::Texture(): width(0), height(0), raw_texture(NULL){}

Texture::Texture(std::string filename){
	// TODO: Add a way to load textures from files
}

Texture::Texture(int width, int height):
	width(width), height(height){

	raw_texture =(byte*) malloc(width * height * 4 * sizeof(byte));
	if(raw_texture == NULL)
		Debug::Error << "Unable to allocate memory for the texture" << std::endl;
}

void Texture::Generate(){
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,
		0, GL_RGBA, GL_UNSIGNED_BYTE, raw_texture);
}

Texture::~Texture(){
	if(raw_texture != NULL)
		free(raw_texture);
}

void Texture::Bind(){
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, texture_id);
}

void Texture::Pixel_Set(int x, int y, Color color){
	if(x >= width || x < 0 || y >= height || y < 0){
		Debug::Error << "Coordonates out of bounds" << std::endl;
		return;
	}

	raw_texture[(y * width + x) * 4 + 0] = color.red;
	raw_texture[(y * width + x) * 4 + 1] = color.green;
	raw_texture[(y * width + x) * 4 + 2] = color.blue;
	raw_texture[(y * width + x) * 4 + 3] = color.alpha;
}

Color Texture::Pixel_Get(int x, int y){
	if(x >= width || x < 0 || y >= height || y < 0){
		Debug::Error << "Coordonates out of bounds" << std::endl;
		return (Color){0, 0, 0, 0};
	}

	return (Color){ raw_texture[(y * width + x) * 4 + 0],
			raw_texture[(y * width + x) * 4 + 1],
			raw_texture[(y * width + x) * 4 + 2],
			raw_texture[(y * width + x) * 4 + 3]};
}
