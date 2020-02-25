#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <string>

#include "typedef.h"
#include "color.h"

namespace Render{
	class Texture{
	public:
		Texture();
		Texture(std::string filename);
		Texture(int width, int height);

		~Texture();

		void Bind();
		void Generate();

		void Pixel_Set(int x, int y, Color color);
		Color Pixel_Get(int x, int y);	
	private:
		int  width, height;
		uint texture_id;
		byte* raw_texture;
	};
};

#endif
