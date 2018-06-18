#ifndef POINT_H
#define POINT_H

#include "definitions.hpp"
#include "vector.hpp"
#include <string>

using namespace std;

class Point {
	public:
	float x[2];
	Point (float x1, float x2);
	//void add_vector(Vector *v);
	string to_string();
};

#endif
