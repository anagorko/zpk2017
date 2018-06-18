#ifndef VECTOR_H
#define VECTOR_H

#include "definitions.hpp"
#include "point.hpp"
#include <string>

using namespace std;

class Vector {
	public:
	Point* p[2];
	Vector (Point *p1, Point *p2);
	float d();
	void plus(Vector *v);
	void multiply(float z);
	void as_versor();
	string to_string();
	static float d(Point *p1, Point *p2);
	float d0();
	float d1();
	void move_vector(Vector *v);
};

#endif
