#include<iostream>
#include<math.h>
#include<vector>
using namespace std;

class Polynomial
{
    vector<double> a;  // wektor wspó³czynników

public:
    Polynomial(){} // tworzy wielomian zerowy

    double getA(int n) const;   // metoda zwracaj¹ca wspó³czynnik przy x^n
    void setA(int, double);     // metoda ustawiaj¹ca wspó³czynnik przy x^n

    int deg() const;  // zwraca stopieñ wielomianu

    Polynomial& operator+=(const Polynomial &q);
    const Polynomial operator+(const Polynomial &q) const;  // dodawanie wielomianów

    Polynomial& operator*=(const Polynomial &q);
    const Polynomial operator*(const Polynomial &q) const;  // mno¿enie wielomianów

    Polynomial& operator-=(const Polynomial &q);
    const Polynomial operator-(const Polynomial &q) const;

    bool operator==(const Polynomial &q) const;
    bool operator!=(const Polynomial &q) const;

    friend ostream& operator<<(ostream&, const Polynomial&);
};

double Polynomial::getA(int n) const
{
    return a[n];
}
void Polynomial::setA(int n, double w)
{
    if(a.size()<=n)
    {
        for(int i=a.size(); i<n; i++)
        {
            a.push_back(0);
        }
        a.push_back(w);
    }
    else a[n]=w;
}

int Polynomial::deg() const
{
    return a.size()-1;
}

Polynomial& Polynomial::operator+=(const Polynomial &q)
{
    if(deg()>=q.deg())
    {
        for(int i=0; i<=q.deg(); i++)
        {
            a[i]+=q.a[i];
        }
    }
    else
    {
        for(int i=0; i<=deg(); i++)
        {
            a[i]+=q.a[i];
        }
        for(int i=deg()+1; i<=q.deg(); i++)
        {
            a.push_back(q.a[i]);
        }
    }

    /* ALTERNATYWNIE
        for(int i=0; i<=q.deg(); i++)
    {
        if(i<=deg()) a[i]+=q.a[i];
        else a.push_back(q.a[i]);
    }
    */
    return *this;
}

const Polynomial Polynomial::operator+(const Polynomial &q) const
{
    Polynomial w=*this;
    w+=q;
    return w;
}
/*
Polynomial& Polynomial::operator*=(const Polynomial &q)
{
    Polynomial w;
    for(int i=0; i<=deg(); i++)
    {
        for(int j=0; j<=q.deg(); j++)
        {
            w[i+j]+=a[i]*q.a[j];
        }
    }
}
*/
    /*const PolynomialPolynomial::operator*(const Polynomial &q) const;  // mno¿enie wielomianów

    Polynomial& Polynomial::operator-=(const Polynomial &q);
    const PolynomialPolynomial::operator-(const Polynomial &q) const;

    bool Polynomial::operator==(const Polynomial &q) const;
    bool Polynomial::operator!=(const Polynomial &q) const;

    friend ostream& operator<<(ostream&, const Polynomial&);
*/
int main()
{
    Polynomial p, q;
    p.setA(2,3); p.setA(1,4); p.setA(0,-5);
    cout << p.getA(0) << p.getA(1) << p.getA(2) << endl;
    //cout << p << endl;                         // wypisuje 3x^2 + 4x -5

    q.setA(1,2); q.setA(0,3);
    cout << q.getA(0) << q.getA(1) << endl;
    //cout << q << endl;                         // wypisuje 2x + 3

    // wypisuje (3x^2+4x-5)*(2x+3)=6x^3 + 17x^2 + 2x - 15
    Polynomial w=q+p;
    cout << w.getA(0) << w.getA(1) << w.getA(2) << endl;

   //cout << "(" << p << ")*(" << q << ")=" << (p+q)<<endl;
    return 0;
}
