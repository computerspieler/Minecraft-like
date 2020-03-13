#ifndef _SHAPES_H_
#define _SHAPES_H_

#include "vector.h"

namespace Render{
	namespace Shapes{
		void Draw_Square(Vector2f v_pos, Vector2f v_size);
		void Draw_Quad  (Vector2f v0, Vector2f v1, Vector2f v2, Vector2f v3);

		void Draw_Triangle(Vector2f v0, Vector2f v1, Vector2f v2);
	};
};

#endif
