#include<iostream>
#include<math.h>
using namespace std;

class Point
{
	float x,y;

public:
	Point(){}

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

	Line(Line, Point); // DODANE - tworzy prostą równoległą do danej i przechodzącą przez dany punkt
	Line(Point, Point);

	Point intersection(Line l);


};

Line::Line(Line l, Point P) // DODANE
{
	A = -l.B;
	B = l.A;	// kierunek prostopadły


	C = -(A*P.getX()+B*P.getY()); // punkt P leży na prostej
}

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
	Point S; // DODANE - środek
	float r; // DODANE - promień

public:
	Circle(Point, Point, Point);
	Circle(Point, float);

	Point getCenter();
	float getRadius();
	string getEquation();
};

// DODANE - implementacja metod klasy Circle
Circle::Circle(Point A, Point B, Point C)
{
	Point Cp = Point(A,B);
	Point Ap = Point(B,C); // srodki bokow

	Line SAB = Line(Line(A,B),Cp); // symetralna boku AB
	Line SBC = Line(Line(B,C),Ap); // symetralna boku BC

	S = SAB.intersection(SBC); // srodek - punkt przeciecia symetralnych

	r = S.dist(A); // promien - odleglosc srodka od wierzcholka
}

Circle::Circle(Point _S, float _r)
{
	S=_S; r=_r;
}
Point Circle::getCenter()
{
	return S;
}
float Circle::getRadius()
{
	return r;
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

	cout << "S(" << S.getX() << "," << S.getY() << ")" << endl;

	return 0;
}

