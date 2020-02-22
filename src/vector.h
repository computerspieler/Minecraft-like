#ifndef _VECTOR_H_
#define _VECTOR_H_

class Vector3f{

public:
	Vector3f();
	Vector3f(float x, float y, float z);
	Vector3f(const Vector3f& vec);

	Vector3f operator+(const Vector3f& vec);
	Vector3f operator-(const Vector3f& vec);
	Vector3f operator*(const Vector3f& vec);
	Vector3f operator/(const Vector3f& vec);

	float x, y, z;
};

std::ostream& operator<<(std::ostream& stream, const Vector3f& vec);

#endif

