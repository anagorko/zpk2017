#include<iostream>
#include<stdlib.h>
using namespace std;
class Stack
{
    class Element
    {
        public:
            Element* prev;
            float value;
    };

    Element* t;

public:
    Stack()
    {
        t=NULL;
    }
    ~Stack()
    {
        while(!empty()) pop();
    }

    void pop()
    {
        if(!empty())
        {
            Element* adres = t->prev;
            delete t;
            t=adres;
        }
        else return;

    }
    float top()
    {
        return t->value;
    }

    bool empty()
    {
        if(t==NULL) return true;
        else return false;
    }
    void push(float wartosc)
    {
        Element* adres = t;
        t = new Element;
        t->prev=adres;
        t->value=wartosc;
    }
};


int main()
{
    Stack s;

    while (!cin.eof()) {
        string token;
        cin >> token;

        if (token == "+") {
            float l, r;

            r = s.top(); s.pop();
            l = s.top(); s.pop();

            s.push(l + r);
        } else if (token == "*") {
            float l, r;

            r = s.top(); s.pop();
            l = s.top(); s.pop();

            s.push(l * r);
        } else if (token == "=") {
            cout << s.top() << endl;
        } else {
            s.push(atof(token.c_str()));
        }
    }
}
