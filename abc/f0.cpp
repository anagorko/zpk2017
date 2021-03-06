#include <iostream>
#include <math.h>
using namespace std;

#include "display.h"

class Shape
{
public:
    virtual void draw(Display) = 0;
};

class Figure
{
    virtual ostream& output(ostream&) const = 0;
    
public:
    virtual double area() = 0;
    
    virtual Figure* scale(double) = 0;
    virtual Figure* translate(double, double) = 0;
    virtual Figure* rotate(double) = 0;
    
    friend ostream& operator<<(ostream& os, const Figure& f);
};

ostream& operator<<(ostream& os, const Figure& f)
{
    return f.output(os);
}

class Point : public Figure, public Shape
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

    void draw(Display d)
    {
        d.drawPoint(x,y);
    }
};


class Square : public Figure, public Shape
{
    Point a,b,c,d;
    
    virtual ostream& output(ostream& os) const {
        return os << "[" << a << ";" << b << ";" << c << ";" << d << "]";
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

    void draw(Display disp)
    {
        disp.drawLine(a.getX(),a.getY(),b.getX(),b.getY());
        disp.drawLine(b.getX(),b.getY(),c.getX(),c.getY());
        disp.drawLine(c.getX(),c.getY(),d.getX(),d.getY());
        disp.drawLine(d.getX(),d.getY(),a.getX(),a.getY());
    }

};

const int n = 5;

int main(int argc, char ** argv)
{
    Square s1(Point(), 20.0);
    s1.translate(-10.0, -10.0);
 
    Square s2(Point(), 20.0);
    s2.translate(-10.0, -10.0);
    s2.scale(2.0);

    Point p1(0, 0);
    p1.translate(50.0, 0);

    Display d;
    d.init();

    while (true) {
        d.clear();
        s1.draw(d);
        s2.draw(d);
        p1.draw(d);
        d.show();

        usleep(10000);  

        s1.rotate(0.02);
        s2.rotate(-0.02);
        p1.rotate(0.02);
    }
}
