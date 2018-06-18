#ifndef PLANSZA_H
#define PLANSZA_H

#include <vector>
#include <iostream>
#include <allegro5/allegro_primitives.h>
using namespace std;

class Klocek;

class Plansza
{
    static const int szer=10;
    static const int wys=20;
    bool pole[szer][wys];

public:
    int ktoryGracz;

    Plansza();

    ~Plansza(){};

    void przygotuj_plansze();

    bool czyKoniecGry();

    void set(int x, int y, bool value);

    bool get(int x, int y);

    int getSzer();

    int getWys();

    vector<int> caleWiersze(int podniesionePoziomy);

    void usunCaleWiersze(Klocek* klocek);

    //void podniesPoziom(Klocek* klocek, vector<int> &caleWiersze);

    void podniesPoziom(Klocek* klocek, int podniesionePoziomy);

    void rysujSzary(ALLEGRO_BITMAP* kolor);
};
#endif
