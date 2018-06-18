#include "vector.hpp"
#include "point.hpp"
#include <cmath>

using namespace std;

Point::Point (float x1, float x2) {
  x[0] = x1;
  x[1] = x2;
}

/*
void Point::add_vector(Vector *v){
  x[0] += v->d0();
  x[1] += v->d1();
}
*/

string Point::to_string() {
  return "P(" + std::to_string(x[0]) + ", " + std::to_string(x[1]) + ")";
}

