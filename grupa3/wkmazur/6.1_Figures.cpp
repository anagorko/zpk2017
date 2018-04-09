#include <iostream>
#undef __STRICT_ANSI__
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

    virtual ostream& output(ostream& os) const {
        return os << "(" <<  x << "," << y << ")";
    }

public:
    Point() : Point(0.0, 0.0) {
    }
    Point(double _x, double _y) {
        x = _x; y = _y;
    }

    virtual double area() {
        return 0;
    }

    virtual Figure* scale(double k) {
        x = k * x;
        y = k * y;

        return this;
    };

    virtual Figure* translate(double dx, double dy) {
        x = x + dx;
        y = y + dy;

        return this;
    }

    virtual Figure* rotate(double alpha) {
        double nx = cos(alpha) * x - sin(alpha) * y;
        double ny = sin(alpha) * x + cos(alpha) * y;

        x = nx;
        y = ny;

        return this;
    }

    double distanceTo(Point p)
    {
        double dx = x - p.x;
        double dy = y - p.y;

        return sqrt(dx*dx + dy*dy);
    }

    double getX() const { return x; }
    double getY() const { return y; }
};


class Square : public Figure
{
    Point a,b,c,d;

    virtual ostream& output(ostream& os) const {
        return os << "[" << &a << ";" << &b << ";" << &c << ";" << &d << "]";
    }

public:
    Square(Point p, double x) {
        a = b = c = d = p;

        b.translate(x,0);
        c.translate(x,x);
        d.translate(0,x);
    }

    virtual double area() {
        return a.distanceTo(b) * a.distanceTo(b);
    }

    virtual Figure* scale(double k) {
        a.scale(k);
        b.scale(k);
        c.scale(k);
        d.scale(k);

        return this;
    }

    virtual Figure* translate(double dx, double dy) {
        a.translate(dx, dy);
        b.translate(dx, dy);
        c.translate(dx, dy);
        d.translate(dx, dy);

        return this;
    }

    virtual Figure* rotate(double alpha) {
        a.rotate(alpha);
        b.rotate(alpha);
        c.rotate(alpha);
        d.rotate(alpha);

        return this;
    }
};

class Circle : public Figure
{
    Point S;
    double r;

    virtual ostream& output(ostream& os) const {
        return os << "S" << &S << "; Promien: " << r;
    }

public:
    Circle(Point P, double _r){
        S=P;
        r=_r;
    }

    virtual double area() {
        return M_PI*r*r;
    }

    virtual Figure* scale(double k) {
        S.scale(k);
        r*=k;
        return this;
    }

    virtual Figure* translate(double dx, double dy) {
        S.translate(dx, dy);
        return this;
    }

    virtual Figure* rotate(double alpha) {
        S.rotate(alpha);
        return this;
    }

};

class Line : public Figure
{
    Point A,B;

    virtual ostream& output(ostream& os) const {
        //wzor funkcji y=ax+b
        float a,b,c;
        float ux = A.getX() - B.getX();
        float uy = A.getY() - B.getY();
        a = -uy;
        b = ux;
        c = -(a * A.getX() + b * A.getY());

        if (c/-b<0)
        return os << "Prosta przechodzaca przez punkty A" << &A << " i B" << &B << " o rownaniu: y = " << a/-b << "x " << c/-b;
        else
        return os << "Prosta przechodzaca przez punkty A" << &A << " i B" << &B << " o rownaniu: y = " << a/-b << "x +" << c/-b;
    }

public:
    Line(Point _A, Point _B){
        A=_A;
        B=_B;
    }

    virtual double area() {
        return 0;
    }

    virtual Figure* scale(double k) {
        A.scale(k);
        B.scale(k);
        return this;
    }

    virtual Figure* translate(double dx, double dy) {
        A.translate(dx, dy);
        B.translate(dx, dy);
        return this;
    }

    virtual Figure* rotate(double alpha) {
        A.rotate(alpha);
        B.rotate(alpha);
        return this;
    }

};

int main(int argc, char ** argv)
{
    Figure* f = new Square(Point(10.0, 20.0), 30.0);
    Figure* g = new Point(-5.0, 15.0);

    cout << f << " ma pole " << f -> area() << endl;
    cout << g << " ma pole " << g -> area() << endl;

    // Napisz klasy Circle i Line powyżej tak, by poniższy kod się kompilował


    Figure* c = new Circle(Point(40.0, 50.0), 5.0);
    c -> translate(10.0, 5.0);
    c -> rotate(0.5);
    cout << c << endl;

    Figure* l = new Line(Point(5.0, 7.0), Point(3.0, 2.0));
    cout << l << endl;
    l -> rotate(-0.2);
    l -> translate(3.0, 5.0);
    cout << l << endl;

}
