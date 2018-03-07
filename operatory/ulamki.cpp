#include <iostream>

using namespace std;

class Ulamek {
  int l, m; // licznik , mianownik
public:
    Ulamek() {
        l = 0;
        m = 1;
    }
    Ulamek(int _l, int _m)
    {
        l = _l;
        m = _m;
    }

    Ulamek& operator+=(const Ulamek &w);
    Ulamek operator+(const Ulamek &w) const;

    int getL() const { return l; }
    int getM() const { return m; }
};

Ulamek& Ulamek::operator+=(const Ulamek &w)
{
    int nl = l * w.m + w.l * m;
    int nm = m * w.m;

    l = nl;
    m = nm;

    return *this;
}

Ulamek Ulamek::operator+(const Ulamek &w) const
{
    Ulamek t(*this);
    t += w;

    return t;
}

//Ulamek operator+(const Ulamek &lewy, const Ulamek &prawy)

ostream& operator<<(ostream &os, const Ulamek &u)
{
    return os << u.getL() << "/" << u.getM() << endl;
}

int main()
{
    Ulamek a(3,8), b(1,8);


    Ulamek c = a + b;

    cout << c.getL() << "/" << c.getM() << endl;

    cout << c << endl;
}
