#ifndef _VECTOR_H_
#define _VECTOR_H_

class Vector2f{

public:
	Vector2f();
	Vector2f(float x, float y);
	Vector2f(const Vector2f& vec);

	Vector2f operator+(const Vector2f& vec);
	Vector2f operator-(const Vector2f& vec);
	Vector2f operator*(const Vector2f& vec);
	Vector2f operator/(const Vector2f& vec);

	float x, y;
};

#include <ostream>

std::ostream& operator<<(std::ostream& stream, const Vector2f& vec);

#endif

