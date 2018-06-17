#include <iostream>
#include <math.h>
using namespace std;

class Figure
{
    virtual ostream& output(ostream&) const = 0;

public:
    virtual double area() = 0;

    virtual Figure* scale(double) = 0;
    virtual Figure* translate(double, double) = 0;
    virtual Figure* rotate(double) = 0;

    friend ostream& operator<<(ostream& os, const Figure* f);
};

ostream& operator<<(ostream& os, const Figure* f)
{
    return f -> output(os);
}

class Point : public Figure
{
    double x, y;
    virtual ostream& output(ostream& os) const
    {
        return os << "(" <<  x << "," << y << ")";
    }

public:
    Point(double _x, double _y) {
        x = _x; y = _y;
    }

    Point() : Point(0.0, 0.0) {
    }

    virtual double area()
    {
        return 0;
    }
    virtual Figure* scale(double k)
    {
        x*=k;
        y*=k;

        return this;
    }
    virtual Figure* translate(double dx, double dy)
    {
        x+=dx;
        y+=dy;

        return this;
    }
    virtual Figure* rotate(double alpha)
    {
        x=x*cos(alpha)-y*sin(alpha);
        y=x*sin(alpha)+y*cos(alpha);

        return this;
    }

    double distanceTo(Point P)
    {
        double dx = x - P.x;
        double dy = y - P.y;

        return sqrt(dx*dx + dy*dy);
    }

    double getX() const { return x; }
    double getY() const { return y; }

};

class Square : public Figure
{
    Point A, B, C, D;

    virtual ostream& output(ostream& os) const
    {
        return os << "[" << &A << ";" << &B << ";" << &C << ";" << &D << "]";
    }
public:
    Square(Point P, double x) {
        A = B = D = P;

        B.translate(x,0);
        C = B;
        C.translate(0,x);
        D.translate(0,x);
    }

    virtual double area()
    {
        return A.distanceTo(B)*A.distanceTo(B);
    }

    virtual Figure* scale(double k)
    {
        A.scale(k);
        B.scale(k);
        C.scale(k);
        D.scale(k);

        return this;
    }
    virtual Figure* translate(double dx, double dy)
    {
        A.translate(dx, dy);
        B.translate(dx, dy);
        C.translate(dx, dy);
        D.translate(dx, dy);

        return this;
    }
    virtual Figure* rotate(double alpha)
    {
        A.rotate(alpha);
        B.rotate(alpha);
        C.rotate(alpha);
        D.rotate(alpha);

        return this;
    }
};
class Circle : public Figure
{
    Point S;
    float r;

    virtual ostream& output(ostream& os) const
    {
        return os << "Srodek=" << &S << "; Promien=" << r;
    }

public:
    Circle() : Circle(Point(0.0, 0.0), 1){}

    Circle(Point _S, float _r)
    {
        S=_S;
        r=_r;
    }

    virtual double area()
    {
        return 3.14*r*r;
    }

    virtual Figure* scale(double k)
    {
        S.scale(k);
        r*=k;

        return this;
    }

    virtual Figure* translate(double dx, double dy)
    {
        S.translate(dx, dy);

        return this;
    }

    virtual Figure* rotate(double alpha)
    {
        S.rotate(alpha);

        return this;
    }
};

class Line : public Figure
{
    Point A, B;

    virtual ostream& output(ostream& os) const
    {
        double dx = A.getX() - B.getX();
        double dy = A.getY() - B.getY();
        double a, b, c;
        a = -dy;
        b = dx;
        c = -(a * A.getX() + b * A.getY());

        return os << "A=" << &A << ", B=" << &B << " o wzorze: " << a << "x+" << b << "y+" << c << "=0";
    }

public:
    Line() : Line(Point(0.0, 0.0), Point(1.0, 1.0)){}

    Line(Point _A, Point _B)
    {
        A=_A;
        B=_B;
    }
    virtual double area()
    {
        return 0;
    }

    virtual Figure* scale(double k)
    {
        A.scale(k);
        B.scale(k);

        return this;
    }

    virtual Figure* translate(double dx, double dy)
    {
        A.translate(dx,dy);
        B.translate(dx,dy);

        return this;
    }

    virtual Figure* rotate(double alpha)
    {
        A.rotate(alpha);
        B.rotate(alpha);

        return this;
    }
};
/*
int main()
{
    Figure* f = new Square(Point(10.0, 20.0), 30.0);
    Figure* g = new Point(-5.0, 15.0);

    cout << f << " ma pole " << f -> area() << endl;
    cout << g << " ma pole " << g -> area() << endl;

    Figure* linia = new Line(Point(0.0,0.0), Point(1.0, 1.0));
    cout << linia <<  endl;

}
*/
int main(int argc, char ** argv)
{
    Figure* f = new Square(Point(10.0, 20.0), 30.0);
    Figure* g = new Point(-5.0, 15.0);

    cout << f << " ma pole " << f -> area() << endl;
    cout << g << " ma pole " << g -> area() << endl;

    // Napisz klasy Circle i Line powy¿ej tak, by poni¿szy kod siê kompilowa³

    Figure* c = new Circle(Point(40.0, 50.0), 5.0);
    c -> translate(10.0, 5.0);
    c -> rotate(0.5);
    cout << c << " ma pole " << c -> area() << endl;

    Figure* l = new Line(Point(5.0, 7.0), Point(3.0, 2.0));
    l -> rotate(-0.2);
    l -> translate(3.0, 5.0);
    cout << l << " ma pole " << l -> area() << endl;
}
