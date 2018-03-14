#include<iostream>
#include<math.h>
#include <sstream>
#include <cmath>

using namespace std;

// punkty
//   tworzenie
//   œrodek
//   odleg³oœæ

// proste
//   tworzenie z równania
//   tworzenie z dwóch punktów
//   przeciêcie

// okrêgi
//   tworzenie z trzech punktów
//   tworzenie ze œrodka i promienia
//   wyznaczanie œrodka
//   wyznaczanie promienia
//   wyznaczanie równania

class Point
{
	float x,y;

public:
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

// mo¿liwa alternatywa:
Point mid_point(Point, Point);

class Line
{
	float A,B,C;

public:
	Line(float _A, float _B, float _C) : A(_A), B(_B), C(_C) {}
	// u¿yliœmy tu listy inicjalizacyjnej

	Line(Point, Point);

	Point intersection(Line l);

	float getA() {return A;}
	float getB() {return B;}
	float getC() {return C;}
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

class Circle
{
    float ax, ay, bx, by, cx, cy; //wspolrzedne punktow A,B,C
    float sx, sy; //Wspolrzedne srodka okregu opisanego
    float r; //Promien

public:
	Circle(Point , Point , Point ); //Konstruktor - tworzenie okregu z 3 punktow

	Circle(Point, float); // Konstruktor - tworzenie okregu z srodka i promienia

	// wyciagniecie wspolrzednych srodka
    Point getCenter(){
        Point S(sx,sy);
        return S;
    }

	float getRadius(){
        return r;
	}

	string getEquation(){
	      string rownanie;
        string a,b,c;
        a = "(x-";  b = ")^2 + (y-";  c=")^2 = ";

        //zamiana + i - w rownaniu okregu
        if(sx<0){
            a = "(x+";
        }
        if(sy<0){
            b = ")^2 + (y+";
        }

        //pakiet sstream przechwytujacy zmienne ktore bedzie mozna zamienic na stringi przy uzyciu .str()
	      ostringstream srodekx;
	      srodekx << abs(sx);

        ostringstream srodeky;
        srodeky << abs(sy);

        ostringstream promien2;
        promien2 << r*r;

        rownanie = a+srodekx.str()+b+srodeky.str()+c+promien2.str();
        return rownanie;
	}
};

Circle::Circle(Point _A, Point _B, Point _C){
        // Wyciagniecie danych z podanych punktow A, B, C
	      ax=_A.getX();  ay=_A.getY();  bx=_B.getX();
	      by=_B.getY();  cx=_C.getX();  cy=_C.getY();
        // Utworzenie punktow A,B,C z wyciagnietych danych
        Point A(ax,ay);  Point B(bx,by);   Point C(cx,cy);
        // Punkty bedace srodkami odcinkow AB i AC
        Point ABO(A,B);  Point ACO(A,C);

        // Ax + By + C = 0 ==> (B/B)y = (A/-B)x + (C/-B) ==> y=ax+b
        // Postać kierunkowa PROSTEJ AB y=ax+b: Potrzebne tylko a
        float a1=Line(A,B).getA()/(-Line(A,B).getB()); // a stojace przy x
        //float B1=Line(A,B).getB()/(Line(A,B).getB()); // stala przy y = 1
        //float C1=Line(A,B).getC()/(-Line(A,B).getB()); // wyraz wolny b

        // Postać kierunkowa PROSTEJ AC y=ax+b: Potrzebne tylko a
        float a2=Line(A,C).getA()/(-Line(A,C).getB()); // a stojace przy x
        //float B2=Line(A,C).getB()/Line(A,C).getB(); // stala przy y = 1
        //float C2=Line(A,C).getC()/(-Line(A,C).getB()); // wyraz wolny b

        //Prosta prostopadla do AB i przechodząca przez punkt ABO
        // y=ax+c ==> ax -y + c =0 // c=-ax+y
        // warunek na prostopadlosc: a*a1=-1 //  ==> a=-1/a1
        Line Symetralna1(-1/a1, -1, 1/a1*ABO.getX()+ABO.getY()); //tworzenie symetralnej na podstawie 3 wsp: prostopadlego a, -1 oraz c obliczonego dla x,y
        Line Symetralna2(-1/a2, -1, 1/a2*ACO.getX()+ACO.getY());

        //Punkt przeciecia dwoch symetralnych
        Point S=Symetralna1.intersection(Symetralna2);

        //Przekazanie wspolrzednych srodka do zmiennych prywatnych
        sx=S.getX(); sy=S.getY();

        //Promien jako odleglosc wierzcholka A i Srodka okregu
        r=A.dist(S);
	}

Circle::Circle(Point _S, float _r){
        sx=_S.getX(); sy=_S.getY();
        r=_r;
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

	cout << "Srodek ciezkosci trojkata: " << "S(" << S.getX() << "," << S.getY() << ")" << endl;

	// DO PODPUNKTU 2

	//Tworzenie okregu z punktow
	Circle Okrag(A,B,C);

	cout << "Srodek okregu opisanego: " << "S(" << Okrag.getCenter().getX() << " , " << Okrag.getCenter().getY() << ")" << endl;
	cout << "Promien okregu opisanego: " << Okrag.getRadius() << endl;
  cout << "Rownanie opisujace okrag: " << Okrag.getEquation() <<endl;

	return 0;
}
