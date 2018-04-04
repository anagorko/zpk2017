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
    Stack();    // inicjalizuje pusty stos
    ~Stack();   // kasuje wszystkie elementy
    
    void pop();   // kasuje gorny element stosu
    float top();  // zwraca wartosc na gorze stosu
    
    bool empty();     // true = stos jest pusty
    void push(float); // umieszcza wartosc na wierzcholku stosu
};

Stack::Stack() 
{
    t = NULL;
}

Stack::~Stack()
{
    while (!empty()) pop();
}

void Stack::pop()
{
    if (empty()) return;

    Element* p = t -> prev;
    delete t;
    t = p;
}

float Stack::top()
{
    return t -> value;
}

bool Stack::empty()
{
    return t == NULL;
}

void Stack::push(float v)
{
    Element* p = t;
    t = new Element;

    t -> value = v;
    t -> prev = p;
}

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
