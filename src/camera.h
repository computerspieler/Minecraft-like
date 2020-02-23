#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "vector.h"

namespace Render{
	class Camera{
	public:
		Camera();

		Vector2f position, rotation;
	};
};

#endif
