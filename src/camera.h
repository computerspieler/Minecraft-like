#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "vector.h"

namespace Render{
	class Camera{
	public:
		Camera();

		void Projection_Set(int width, int height);

		Vector2f position, rotation;
		float zoom;
	};
};

#endif
