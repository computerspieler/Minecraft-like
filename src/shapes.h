#ifndef _SHAPES_H_
#define _SHAPES_H_

#include "vector.h"
#include "texture.h"

namespace Render{
	namespace Shapes{
		enum Layer{
			BACKGROUND, NORMAL, FOREGROUND
		};
		typedef enum Layer Layer;
		
		void Go_To_Layer(Layer layer);

		void Draw_Square(Vector2f v_pos, Vector2f v_size, Texture::Wrap_Format wrap_fmt);
	};
};

#endif
