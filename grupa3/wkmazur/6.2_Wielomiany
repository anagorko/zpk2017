#include <iostream>
#include <vector>
#include<cmath>

using namespace std;

class Polynomial
{
    vector<double> a;  // wektor wspó³czynników

public:
    // tworzy wielomian zerowy
    Polynomial(){
        a.push_back(0);
    }

    // metoda zwracaj¹ca wspó³czynnik przy x^n
    double getA(int n) const{
        return a[n];
    }

    // metoda ustawiaj¹ca wspó³czynnik przy x^n
    void setA(int n, double _A){
        if (n>a.size()) {
            for(int i=a.size(); i<n; i++){
                a.push_back(0);
            }
          a.push_back(_A);
        }
        else if(n==a.size()) a.push_back(_A);
        else a[n]=_A;
    }

    // zwraca stopieñ wielomianu
    int deg() const{
        return a.size()-1;
    }

    // dodawanie wielomianów 1
    Polynomial& operator+=(const Polynomial &q){
        int len;
        if (a.size()>=q.deg()+1) len=a.size(); //jesli wielomian zrodlowy dluzszy
        else len=q.deg()+1; //jesli wielomian zrodlowy krotszy

        for(int i=0; i<len; i++){
            if(i>deg()) a.push_back(0); //jesli i wykracza poza stopien wielomianu zrodlowego wstaw 0
            if(i<=q.deg()) a[i]+=q.getA(i); //dopoki i nie wykracza poza stopien wielomianu q to dodaj, jesli wykracza to nic nie sumujemy
        }
    }
    // dodawanie wielomianów 2
    const Polynomial operator+(const Polynomial &q) const{
        Polynomial a=*this;
        a+=q;
        return a;
    }

    // mnozenie wielomianów 1
    Polynomial& operator*=(const Polynomial &q){
        int len=deg()+q.deg(); //suma dlugosci
        int lenThis=deg();
        int lenQ=q.deg();

        Polynomial X=*this; //kopia oryginalu

        for(int z=deg()+1;z<=len;z++) {a.push_back(0);}

            for(int i=lenThis; i>=0; i--){
               for(int j=lenQ; j>=0; j--){
                    if(i+j>deg()); //cout << i << " " << j << endl;
                    a[i+j]+=a[i]*q.getA(j);
                    //cout <<endl<< q.getA(j) << " * " << a[i] ;
                }
            }
        for(int i=0; i<=X.deg(); i++)
            if (X.getA(i)!=0) a[i]-=X.getA(i);
        }

    // mnozenie wielomianów 2
    const Polynomial operator*(const Polynomial &q) const{
        Polynomial a=*this;
        a*=q;
        return a;
    }

    // odejmowanie wielomianow 1
    Polynomial& operator-=(const Polynomial &q){
        int len;
        if (a.size()>=q.deg()+1) len=a.size(); //jesli wielomian zrodlowy dluzszy
        else len=q.deg()+1; //jesli wielomian zrodlowy krotszy

        for(int i=0; i<len; i++){
            if(i>deg()) a.push_back(0); //jesli i wykracza poza stopien wielomianu zrodlowego wstaw 0
            if(i<=q.deg()) a[i]-=q.getA(i); //dopoki i nie wykracza poza stopien wielomianu q to dodaj, jesli wykracza to nic nie sumujemy
        }
    }

    // odejmowanie wielomianow 2
    const Polynomial operator-(const Polynomial &q) const{
        Polynomial a=*this;
        a-=q;
        return a;
    }

    // operator porownania
    bool operator==(const Polynomial &q) const{
        int countTrue=0;
        if (a.size()!=q.deg()+1) return false;
        else {
            for(int i=0; i<=deg(); i++){
                if (a[i]==q.getA(i))
                    countTrue++;
            }
          return countTrue==a.size();
        }
    }

    bool operator!=(const Polynomial &q) const{
        bool a=*this==q;
        return !a;
    }

    //strumien wyjscia
    friend ostream& operator<<(ostream& os, const Polynomial& W);
};

// wyswietlanie wielomianu
ostream& operator<<(ostream& os, const Polynomial& W){
        string rownanie;
        for(int i=W.deg(); i>1; i--){
            if(W.getA(i)!=0){

                if(W.getA(i)>0) rownanie+=" + ";
                else if(W.getA(i)<0) rownanie+=" - ";
                rownanie+=to_string(abs(W.getA(i)));
                rownanie+="x^";
                rownanie+=to_string(i);
            }
        }
        if(W.getA(1)!=0){
            if(W.getA(1)>0) rownanie+=" + ";
            else rownanie+=" - ";
            rownanie+=to_string(abs(W.getA(1)));
            rownanie+="x";
        }
        if(W.getA(0)!=0){
            if(W.getA(0)>0) rownanie+=" + ";
            else rownanie+=" - ";
            rownanie+=to_string(abs(W.getA(0)));
        }

        if (rownanie[1]=='+') rownanie.erase(0,3);

        return os << rownanie;
    }

int main()
{
    Polynomial p, q;

    p.setA(12,5); p.setA(5,4); p.setA(0,-5);
    cout << "p: " << p << endl;

    q.setA(4,3); q.setA(1,7); q.setA(2,3);

    cout << "q: " << q << endl;

    cout << "p+q: " << p+q << endl;
    cout << "p-q: " << p-q << endl;
    cout << "p*q: " << p*q << endl;

    bool test= p!=q;
    cout << "Czy p!=q: " << test << endl;

}

