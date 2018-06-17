#include <iostream>

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
	// tworzymy punkt na œrodku pomiêdzy dwoma innymi
	Point(Point A, Point B) {
		x = (A.getX() + B.getX()) / 2;
		y = (A.getY() + B.getY()) / 2;
	}

	float getX() const { return x; }
	float getY() const { return y; }

	void setX(float _x) { x = _x; }
	void setY(float _y) { y = _y; }
};


class Line
{
	float A,B,C;

public:
    Line(){}
	Line(float _A, float _B, float _C) : A(_A), B(_B), C(_C) {}
	Point intersection(Line l);

	Point operator*(const Line &) const; // znajduje punkt przeciêcia dwóch prostych
    bool operator||(const Line &) const; // testuje równoleglosc dwóch prostych
    bool operator==(const Line &) const; // sprawdza równosc dwóch prostych
    friend ostream& operator<<(ostream&, const Point&);
};

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

Point Line::operator*(const Line &l) const
{
    Line k(*this);
    Point p=k.intersection(l);
    return p;
}
bool Line::operator||(const Line &l) const
{
    if (A*l.B==l.A*B) return true;
    else return false;
}
bool Line::operator==(const Line &l) const
{
    if(A/l.A==B/l.B && A/l.A==C/l.C) return true;
    else return false;
}

ostream& operator<<(ostream& os, const Point& p)
{
    return os << "(" << p.getX() << ", " << p.getY() << ")" << endl;
}

int main()
{
    float a,b,c;

    cout << "Podaj współczynniki pierwszego równania (ax+by=c): ";
    cin >> a >> b >> c;
    Line k(a,b,-c);


    cout << "Podaj współczynniki drugiego równania (ax+by=c): ";
    cin >> a >> b >> c;

    Line l(a,b,-c);
    if (k == l) {
      cout << "Istnieje nieskoñczenie wiele rozwiązań." << endl;
    } else if (k || l) {
      cout << "Układ jest sprzeczny." << endl;
    } else {
      cout << "Rozwiązanie układu to " << (k*l) << endl;
    }
    return 0;
}
