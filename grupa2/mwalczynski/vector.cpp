#include "vector.hpp"
#include "point.hpp"
#include <cmath>
#include <iostream>

using namespace std;

Vector::Vector(Point *p1, Point *p2) {
  p[0] = p1;
  p[1] = p2;
}

//float Vector::d() { return sqrt(pow(d0(), 2) + pow(d1(), 2)); }	// dlugosc wektora
float Vector::d() {
	//cout << d0();
  return sqrt(d0()*d0() + d1()*d1());
}	// dlugosc wektora


void Vector::plus(Vector *v) {
  p[1] = new Point(v->d0() + p[1]->x[0], p[1]->x[1] + v->d1());
}

void Vector::multiply(float z) {
	//cout << "1: as_multipl()" << to_string() << endl;
  p[1] = new Point(
    z*d0() + p[0]->x[0],
    z*d1() + p[0]->x[1]
  );
  //cout << "2: as_mmultipl()" << to_string() << endl;
  //cout << "z:" << z << "," << "d0:" << d0() << "," << "d1:" << d1() << "p0" << p[0]->to_string() << endl; 
}

//void Vector::as_versor() { multiply(1/d()); }
void Vector::as_versor() { 
	//cout << "1: as_vector()" << to_string() << endl;
  multiply(1.0);
  //cout << "2: as_vector()" << to_string() << endl;
}

string Vector::to_string() {
  return "V(" + p[0]->to_string() + "; " + p[1]->to_string() + ")";
}

float Vector::d(Point *p1, Point *p2){
  Vector* v = new Vector(p1, p2);
  return v->d();
}

float Vector::d0() {
	//cout << "p0: " + p[0]->to_string() << endl;
	//cout << "p1: " + p[1]->to_string() << endl;
	return p[1]->x[0] - p[0]->x[0];
	}
float Vector::d1() { return p[1]->x[1] - p[0]->x[1]; }

void Vector::move_vector(Vector *v) {
	float d_0 = v->d0();
	float d_1 = v->d1();
	p[0]->x[0] += d_0;
	p[0]->x[1] += d_1;
	p[1]->x[0] += d_0;
	p[1]->x[1] += d_1;
}
