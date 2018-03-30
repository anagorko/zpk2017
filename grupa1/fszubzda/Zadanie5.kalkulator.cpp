#include<stdlib.h>
#include <cstdio>
#include<iostream>
#include<vector>
using namespace std;

class Stack
{
    class Element //nowy węzeł
    {
        public:
            Element* prev; //(wskaźnik) , kolejny element w stosie
            float value;   //  wartość
    };

    Element* t; //głowa

public:
    Stack();    // inicjalizuje pusty stos (konstruktor)
    ~Stack();   // kasuje wszystkie elementy (destruktor)

    void pop();   // kasuje gorny element stosu
    float top();  // zwraca wartosc na gorze stosu

    bool empty();     // true = stos jest pusty
    void push(float); // umieszcza wartosc na wierzcholku stosu (dodaj na stos)
};

Stack::Stack(){
    t = NULL;
}

Stack::~Stack(){
    delete t;
}

void Stack::pop(){
      t = t->prev; // przeskakujemy do poprzedniego elementu ze stosu;
}

float Stack::top(){
    return t->value; //zwróć wartość wierzchołka stosu
}

bool Stack::empty(){
      if (this->top()==0) return 1;
    else return 0;
}

void Stack::push(float x){
    Element* nowy = new Element;
    nowy->value=x; 
    nowy->prev=t; 
    t=nowy;       
    delete nowy;
}

int main(){
    Stack s;
    while (!cin.eof()) {
        string token;
        cin >> token;
        if (token == "+") { //suma dwoch ostatnich (wyrzucanie dwoch ostatnich wyrazow, dodanie ich sumy)
            float l, r;

            r = s.top(); s.pop();
            l = s.top(); s.pop();

            s.push(l + r);
        } else if (token == "*") { //analogicznie tylko iloczyn
            float l, r;

            r = s.top(); s.pop();
            l = s.top(); s.pop();

            s.push(l * r);
        } else if (token == "=") { //zwroc ostatni wyraz
            cout << s.top() << endl;
        } else {
            s.push(atof(token.c_str()));
        }
    }

}
