#ifndef KLOCEK_H
#define KLOCEK_H

#include "plansza.h"
#include <allegro5/allegro_primitives.h>
#include <iostream>
using namespace std;

// Klasa Bazowa
class Klocek
{
protected:
    //string kolor;

    ALLEGRO_BITMAP* kolor = NULL;
    int ksztalt=1;

    Plansza planszaKlocka;
    int dolnaKrawedz=19;
    int lewaKrawedz=0;
    int prawaKrawedz=9;

public:
    bool get(int i,int j);

    virtual void dodajNaPlansze(Plansza &plansza)=0;

    bool czyKoniecPlanszy(Plansza &plansza);

    void przesun(Plansza &plansza);

    void lewo(Plansza &plansza);

    void prawo(Plansza &plansza);

    void przesunCalkiem(Plansza &plansza);

    virtual void obroc(Plansza &plansza)=0;

    void rysuj(Plansza &plansza);

    virtual void rysujPodglad(Plansza &plansza)=0;

    void usunCaleWiersze(vector<int> &caleWiersze, Plansza &plansza);

    void podniesPoziom(vector<int> &caleWiersze, Plansza &plansza);
};

// =========== Klasy dziedziczace ===========

// Klocek T
//  #
// ###
class Klocek_T: public Klocek
{

public:
    Klocek_T(ALLEGRO_BITMAP* kolor);

    ~Klocek_T(){};

    void dodajNaPlansze(Plansza &plansza);

    void obroc(Plansza &plansza);

    void rysujPodglad(Plansza &plansza);
};


// Klocek O
//  ##
//  ##
class Klocek_O: public Klocek
{

public:
    Klocek_O(ALLEGRO_BITMAP* kolor);

    ~Klocek_O(){};

    void dodajNaPlansze(Plansza &plansza);

    void obroc(Plansza &plansza){};

    void rysujPodglad(Plansza &plansza);
};


// Klocek I
//  ####
//
class Klocek_I: public Klocek
{

public:
    Klocek_I(ALLEGRO_BITMAP* kolor);

    ~Klocek_I(){};

    void dodajNaPlansze(Plansza &plansza);

    void obroc(Plansza &plansza);

    void rysujPodglad(Plansza &plansza);
};


// Klocek S
//    ##
//   ##
class Klocek_S: public Klocek
{

public:
    Klocek_S(ALLEGRO_BITMAP* kolor);

    ~Klocek_S(){};

    void dodajNaPlansze(Plansza &plansza);

    void obroc(Plansza &plansza);

    void rysujPodglad(Plansza &plansza);
};


// Klocek Z
//   ##
//    ##
class Klocek_Z: public Klocek
{

public:
    Klocek_Z(ALLEGRO_BITMAP* kolor);

    ~Klocek_Z(){};

    void dodajNaPlansze(Plansza &plansza);

    void obroc(Plansza &plansza);

    void rysujPodglad(Plansza &plansza);
};


// Klocek L
//     #
//   ###
class Klocek_L: public Klocek
{

public:
    Klocek_L(ALLEGRO_BITMAP* kolor);

    ~Klocek_L(){};

    void dodajNaPlansze(Plansza &plansza);

    void obroc(Plansza &plansza);

    void rysujPodglad(Plansza &plansza);
};


// Klocek J
//   #
//   ###
class Klocek_J: public Klocek
{

public:
    Klocek_J(ALLEGRO_BITMAP* kolor);

    ~Klocek_J(){};

    void dodajNaPlansze(Plansza &plansza);

    void obroc(Plansza &plansza);

    void rysujPodglad(Plansza &plansza);
};

#endif

