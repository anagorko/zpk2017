#include <iostream>

using namespace std;


#include <math.h>
#include <string>
#include <sstream>

class Point
{
	float x,y;

public:
    //Point(){}
	// tworzymy punkt o zadanych wspó³rzêdnych
	Point(float x, float y) {
		setX(x);
		setY(y);
	}
	// tworzymy punkt na œrodku pomiêdzy dwoma innymi
	Point(Point A, Point B) {
		x = (A.getX() + B.getX()) / 2;
		y = (A.getY() + B.getY()) / 2;
	}

	float dist(Point);	// obliczamy odleg³oœæ od drugiego punktu

	float getX() { return x; }
	float getY() { return y; }

	void setX(float _x) { x = _x; }
	void setY(float _y) { y = _y; }
};

float Point::dist(Point B)
{
	return sqrt((x-B.x)*(x-B.x) + (y-B.y)*(y-B.y));
}

class Line
{
	float A,B,C;

public:
	Line(float _A, float _B, float _C) : A(_A), B(_B), C(_C) {}
	// u¿yliœmy tu listy inicjalizacyjnej

	Line(Point, Point);
    Line(Line, Point);
	Point intersection(Line l);
};

Line::Line(Point P, Point Q)
{
	float ux = P.getX() - Q.getX();
	float uy = P.getY() - Q.getY();

	A = -uy;
	B = ux;		// wspó³czynniki tworz¹ wektor prostopad³y do wektora PQ

	C = -(A * P.getX() + B * P.getY()); // dobieramy C tak, by punkt P le¿a³ na prostej
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

Line::Line(Line linia, Point Punkt) //prosta prostopadla
{
    A=-1/linia.A;//parametr przy x liczba odwrotna z odwrotnym znakiem - prosta prostopadła
    B=1/linia.B;//parametr przy y liczba odwrotna
    C=-A*Punkt.getX()-B*Punkt.getY();
}

class Circle
{
    Point srodek_kola;
    float promien;

public:
	Circle(Point, Point, Point);
	Circle(Point, float);

	Point getCenter();
	float getRadius();
	string getEquation();
};

Circle::Circle(Point X, Point Y, Point Z)
{
    Point srodek_XY=Point(X,Y); //punkt na srodku boku XY
    Line linia_XY=Line(X,Y); //linia zawierająca odcinek XY
    Line sym_XY=Line(linia_XY,srodek_XY);//symetralna

    Point srodek_XZ=Point(X,Z); //punkt na srodku boku XZ
    Line linia_XZ=Line(X,Z); //linia zawierająca odcinek XZ
    Line sym_XZ=Line(linia_XZ,srodek_XZ);//symetralna

    Point srodek_kola=sym_XY.intersection(sym_XZ);
    promien=srodek_kola.dist(X);
}

Circle::Circle(Point X, float r)
{
    srodek_kola=X;
    promien=r;
}

Point Circle::getCenter()
{
    return srodek_kola;
}

float Circle::getRadius()
{
    return promien;
}

string Circle::getEquation()
{
    string a;
    ostringstream convert1;
    convert1 << srodek_kola.getX();
    a=convert1.str();
    string b;
    ostringstream convert2;
    convert2 << srodek_kola.getY();
    b=convert2.str();
    string c;
    ostringstream convert3;
    convert3 << getRadius();
    c=convert3.str();
    string rownanie = "(x+" + a + ")^2+(y+" + b + ")^2=" + c + "^2" ;
    return rownanie;
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

	//Point Bp(A,C);	// srodek boku AC
	//Point Ap(B,C);

	//Line sb(B,Bp);	// srodkowa z wierzcholka B
	//Line sa(A,Ap);

	//Point S = sa.intersection(sb);

	//cout << "S(" << S.getX() << "," << S.getY() << ")" << endl;

	Circle Kolo(A,B,C);
	cout << Kolo.getRadius;

	return 0;
}
