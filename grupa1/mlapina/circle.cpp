#include<iostream>
#include<math.h>
#include <string>
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

	Point intersection(Line l); // ?

	Line ort(Line, Point);
};

Line::Line(Point P, Point Q)
{
	float ux = P.getX() - Q.getX();
	float uy = P.getY() - Q.getY();

	A = -uy;
	B = ux;		// współczynniki tworzą wektor prostopadły do wektora PQ

	C = -(A * P.getX() + B * P.getY()); // dobieramy C tak, by punkt P leżał na prostej
}

Line Line::ort(Line l, Point R) // prostopadłe przechodzące przez środek strony
{
    float A1 = -1/l.A;
    float B1 = l.B;
   float  C1 = -(A1 * R.getX() + B1 * R.getY());
  return Line(A1,B1,C1);
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
    float K;

public:

	//Circle(Point _A, Point _B, Point _C): A(_A), B(_B), C(_C) {} // opisany na trójkącie
	//Circle(Point, float); // środek i promień

	Point getCenter(Line,Line);
	float getRadius(Point,Point,Point);
	string getEquation(Line,Line,Point,Point,Point);
};

Point Circle::getCenter(Line orta, Line ortb){
   Point Center = orta.intersection(ortb);
   return Point(Center.getX(),Center.getY());
}
float Circle::getRadius(Point A, Point B, Point C)
{
float Radius=A.dist(B)*A.dist(B)*B.dist(C)/(4*(A.dist(B)+A.dist(B)+B.dist(C)));
return(Radius);
}

string Circle::getEquation(Line orta, Line ortb, Point A,Point B, Point C)
{ Point S = orta.intersection(ortb);
//   return(Center.getX(),Center.getY());
cout << "(x-"<< S.getX() << ")+(y-" << S.getY()<< ")=" << (Circle.getRadius(A,B,C))*2<< endl;
}


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

	Line ortb(k,Bp);
	Line orta(m,Ap);

	Point R = orta.intersection(ortb);

	float P = getRadius(A,B,C);

	string Q = getEquation(orta, ortb, A,B,C);

	// radius
	// równanie okręgu

	cout << "S(" << S.getX() << "," << S.getY() << ")" << endl;
	cout << "Srodek okregu R(" << R.getX() << "," << R.getY() << endl;
    cout << "Promień = " << P << endl;
    cout << "Rownanie okregu:" << Q << endl;

	return 0;
}

