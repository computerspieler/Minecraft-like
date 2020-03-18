#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <string>

#include "typedef.h"
#include "color.h"

namespace Render{
	class Texture{
	public:
		enum Wrap_Format{
			FILL, REPEAT
		};
		typedef enum Wrap_Format Wrap_Format;

		Texture();
		Texture(int width, int height);

		~Texture();

		void Bind();
		void Generate();

		void Pixel_Set(int x, int y, Color color);
		Color Pixel_Get(int x, int y);	
	private:
		int  width, height;
		uint texture_id;
		uchar* raw_texture;
	};
};

#endif
