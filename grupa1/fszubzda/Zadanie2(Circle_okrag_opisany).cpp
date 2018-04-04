#include<iostream>
#include<math.h>
#include<string>
#include<sstream>


using namespace std;

/* patch - kod zapożyczony ze strony stackoverflow. Błąd przy uzyciu funkcji to_string ("to_string is not a member of std")
   Wygląda na to, że funkcja wywołuje błąd na niektórych wersjach programu; rozwiązaniem jest poniżej napisany patch tworzący funkcję to_string:
*/
namespace patch{
    template < typename T > std::string to_string (const T& n){
        std::ostringstream stm;
        stm<<n;
        return stm.str();
    }
}

/*2. Wyznacz środek i promień okręgu opisanego na tym trójkącie.*/


class Point
{
    float x,y;

public:
	Point(float x, float y){
		setX(x);
		setY(y);
	};	// tworzymy punkt o zadanych wspó³rzêdnych
	Point(Point A, Point B){
		x = (A.getX() + B.getX()) / 2;
		y = (A.getY() + B.getY()) / 2;
	};	// tworzymy punkt na œrodku pomiêdzy dwoma innymi

	float dist(Point);	// obliczamy odleg³oœæ od drugiego punktu

	float getX() { return x; }
	float getY() { return y; }

	void setX(float _x) { x = _x; }
	void setY(float _y) { y = _y; }
};

float Point::dist(Point B){
    return  sqrt((x-B.x)*(x-B.x) + (y-B.y)*(y-B.y));
}


class Line
{
    float A,B,C;
public:
	Line(float _A, float _B, float _C) : A(_A), B(_B), C(_C) {}

    Line(Point,Line);

	Line(Point, Point);

	Point intersection(Line l);
};

//konstruktor tworzący prostą prostopadłą do zadanej prostej l w punkcie S
Line::Line(Point S, Line l){
    float a1= l.A/(-l.B);
    float a2 = (-1)/ a1;
    float b2 = S.getY() - a2 * S.getX();

    A = a2;
    B = -1;
    C = b2;
}

Line::Line(Point P, Point Q){
	float ux = P.getX() - Q.getX();
	float uy = P.getY() - Q.getY();

	A = -uy;
	B = ux;		// wspó³czynniki tworz¹ wektor prostopad³y do wektora PQ
    C = -(A * P.getX() + B * P.getY()); // dobieramy C tak, by punkt P le¿a³ na prostej
}

Point Line::intersection(Line l){
    float W = A * l.B - B * l.A;
    float Wx = -C*l.B + l.C*B;
    float Wy = -A*l.C + C*l.A;

    return Point(Wx/W, Wy/W);
}


class Circle
{
    float sx,sy, r; // srodek, promien
    float ax,ay,bx,by,cx,cy;

public:
	Circle(Point, Point, Point); //tu mamy wierzcholki abc i z tego robimy
	Circle(Point, float);        // tu mamy punkt srodkowy i promien okregu

	Point getCenter();
	float getRadius();
	string getEquation();
};

//konstruktor tworzący środek okręgu opisanego na trójkącie _A_B_C i promień r:
Circle::Circle(Point _A, Point _B, Point _C){
    ax = _A.getX(); ay = _A.getY();
    bx = _B.getX(); by = _B.getY();
    cx = _C.getX(); cy = _C.getY();

    Point A(ax, ay);//                          -- Point(float, float)
    Point B(bx, by);
    Point C(cx, cy);

    Point ACp(A,C); // srodek boku AC           -- Point(Point, Point)
    Point BCp(B,C); // srodek boku BC

    Line ACl(A,C);  //prosta opisujaca bok AC   -- Line(Point,Point)
    Line BCl(B,C);  //prosta opisujaca bok BC

    Line sym1(ACp, ACl);//prosta prostopadła do AC w punkcie ACp (symetralna) -- Line(Point,Line)
    Line sym2(BCp, BCl);//prosta prostopadła do BC w punkcie BCp (symetralna) -- Line(Point,Line)

    Point S = sym1.intersection(sym2);
    sx = S.getX(); sy=S.getY();

    r = S.dist(A);
}

//konstruktor z danym Środkiem okręgu oraz promieniem:
Circle::Circle(Point S, float R){
    sx = S.getX();
    sy = S.getY();
    r = R;
}

Point Circle::getCenter(){
    return Point(sx,sy);
}

float Circle::getRadius(){
    return r;
}

//funkcja uzywająca funkcji to_string opisanej na początku do stworzenia równania okręgu:
string Circle::getEquation(){

    string SX, SY;
    string rownanie;
    string R  = patch::to_string(r*r);

    if(sx>0)
    SX = patch::to_string(sx);
    else
    SX = patch::to_string(sx*(-1));

    if(sy>0)
    SY = patch::to_string(sy);
    else
    SY = patch::to_string(sy*(-1));

//brakuje warunków gdy sx lub sy == 0
    if (sx > 0 && sy>0)
     rownanie ="Rownanie okregu to: (x - " + SX + ") + (y - " + SY + ") = " + R;
    else if (sx > 0 && sy < 0)
     rownanie ="Rownanie okregu to: (x - " + SX + ") + (y + " + SY +") = " + R;
    else if (sx < 0 && sy < 0)
     rownanie ="Rownanie okregu to: (x + " + SX + ") + (y + " + SY +") = " + R;
    else
     rownanie ="Rownanie okregu to: (x + " + SX + ") + (y - " + SY +") = " + R;

    return rownanie;
}



int main(){
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


	Line sa(A,Ap);
	Line sb(B,Bp);	// srodkowa z wierzcholka B

	Point S = sa.intersection(sb);

	cout << "S(" << S.getX() << "," << S.getY() << ")" << endl<<endl;


// konstruktor z wierzcholkami trojkata
    Circle srod(A,B,C);
	cout <<"Srodek:"<<"("<< srod.getCenter().getX() << " , " << srod.getCenter().getY() << ")" <<endl;
    cout <<"Promien: "<<srod.getRadius()<<endl;

    cout<<srod.getEquation()<<endl<<endl;


// Konstruktor ze srodkiem i promieniem:
    Point Sr(-0.23, 7.06);
    Circle srod1(Sr, 5.888);
    cout <<"Srodek:"<<"("<< srod1.getCenter().getX() << " , " << srod1.getCenter().getY() << ")" <<endl;
    cout <<"Promien: "<<srod1.getRadius()<<endl;

    cout<<srod1.getEquation()<<endl<<endl;

	return 0;
}
