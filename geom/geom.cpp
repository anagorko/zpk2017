#include<iostream>
#include<math.h>
using namespace std;

// punkty
//   tworzenie
//   środek
//   odległość

// proste
//   tworzenie z równania
//   tworzenie z dwóch punktów
//   przecięcie

// okręgi
//   tworzenie z trzech punktów
//   tworzenie ze środka i promienia
//   wyznaczanie środka
//   wyznaczanie promienia
//   wyznaczanie równania

class Point
{
	float x,y;

public:
	// tworzymy punkt o zadanych współrzędnych
	Point(float x, float y) {
		setX(x);
		setY(y);
	}
	// tworzymy punkt na środku pomiędzy dwoma innymi
	Point(Point A, Point B) {
		x = (A.getX() + B.getX()) / 2;
		y = (A.getY() + B.getY()) / 2;
	}

	float dist(Point);	// obliczamy odległość od drugiego punktu

	float getX() { return x; }
	float getY() { return y; }

	void setX(float _x) { x = _x; }
	void setY(float _y) { y = _y; }
};

float Point::dist(Point B) 
{
	return sqrt((x-B.x)*(x-B.x) + (y-B.y)*(y-B.y));
}

// możliwa alternatywa:
Point mid_point(Point, Point);

class Line
{
	float A,B,C;

public:
	Line(float _A, float _B, float _C) : A(_A), B(_B), C(_C) {}
	// użyliśmy tu listy inicjalizacyjnej

	Line(Point, Point);

	Point intersection(Line l);
};

Line::Line(Point P, Point Q)
{
	float ux = P.getX() - Q.getX();
	float uy = P.getY() - Q.getY();

	A = -uy;
	B = ux;		// współczynniki tworzą wektor prostopadły do wektora PQ

	C = -(A * P.getX() + B * P.getY()); // dobieramy C tak, by punkt P leżał na prostej
}

Point Line::intersection(Line l)
{
	// wyznacznik macierzy
	// A B
	// l.A l.B

	float W = A * l.B - B * l.A;

	// wyznacznik macierzy
	// -C B
	// -l.C l.B
	float Wx = -C*l.B + l.C*B;

	// wyznacznik macierzy
	// A -C
	// l.A -l.C
	float Wy = -A*l.C + C*l.A;

	// co, gdy W == 0?
	// (zwracamy nienazwany obiekt)
	return Point(Wx/W, Wy/W);
}

class Circle
{
public:
	Circle(Point, Point, Point);
	Circle(Point, float);

	Point getCenter();
	float getRadius();
	string getEquation();
};

int main()
{
	Line k(2,-3,4);
	Line l(1,1,-10);

	Point X(0,0);
	Point Y(-1,5);
	Line m(X,Y);

	Point A = k.intersection(l);
	Point B = l.intersection(m);
	Point C = m.intersection(k);

	cout << "A("<<A.getX()<<","<<A.getY()<<")"<<endl;
	cout << "B("<<B.getX()<<","<<B.getY()<<")"<<endl;
	cout << "C("<<C.getX()<<","<<C.getY()<<")"<<endl;

	Point Bp(A,C);	// srodek boku AC
	Point Ap(B,C);

	Line sb(B,Bp);	// srodkowa z wierzcholka B
	Line sa(A,Ap);

	Point S = sa.intersection(sb);

	cout << "S(" << S.getX() << "," << S.getY() << ")" << endl;

	return 0;
}

