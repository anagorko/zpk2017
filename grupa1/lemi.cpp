#include <iostream>
#include<vector>

using namespace std;

class L {
public:
    int n;

public:
    virtual void f() { cout << "L"; }
};

class A : public L {
public:
    A(int _n) { n = _n; }
    A(L* l) { n = l -> n; }
    void f() { cout << "A" << n; }
};

class B : public L {
public:
    B(int _n) { n = _n; }
    B(L* l) { n = l -> n; }

    void f() { cout << "B" << n; }
};

int main()
{
    vector<L*> v;

    v.push_back(new A(1));
    v.push_back(new B(2));
    v.push_back(new A(3));

    for (auto &l: v) {
        l -> f();
    }

    L* tmp = new A(v[1]);
    delete v[1];
    v[1] = tmp;

    cout << endl;

    for (auto &l: v) {
        l -> f();
    }

    return 0;
}
