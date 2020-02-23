#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "vector.h"

namespace Render{
	class Camera{
	public:
		Camera();

		Vector3f position, rotation;
	};
};

#endif
