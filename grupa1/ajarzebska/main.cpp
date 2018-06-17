
/*******************************************/
/***                                     ***/
/***              LEMMINGS               ***/
/***                                     ***/
/***         Agnieszka Jarzębska         ***/
/***                348781               ***/
/*******************************************/

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "allegro5/allegro_image.h"
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

#include <iostream>
using namespace std;

/********************************/
/*** PODSTAWOWE PARAMETRY GRY ***/
/********************************/

/* PARAMETRY DLA CALEJ GRY */
const int sz = 40; // szerokosc planszy
const int wy = 20; // wysokosc planszy

const int k_sz = 30; // szerokosc (piksele) kafelka
const int k_wy = 30; // wysokosc (piksele) kafelka

const float FPS = 60; // Frames Per Second

const int screen_w = sz*k_sz; // szerokosc ekranu (screen width)
const int screen_h = wy*k_wy; // wysokosc ekranu (screen height)

const int wymagana_energia = 50; // energia wymagana do rozpoczecia ruchu przez lemminga

/* PARAMETRY DLA POZIOMU */
int x_start, y_start, x_meta, y_meta; // polozenie startu i mety
int ile_ocalonych=0; // ile lemmingow zostalo juz ocalonych
int poziom=1;
int ile_lemmingow; // ile lemmingow utworzyc
int ile_uratowac; // ile lemmingow do uratowania
bool koniec_gry=false;
int x; int y; // polozenie kursora

/************************/
/*** STRUKTURY DANYCH ***/
/************************/

enum typ_kafelka
{
    pusty = 0,
    tlo,
    ziemia,
    niezniszczalna,
    start,
    meta,
    lemmingKafelek,
    menu,
    numerki,
    liczba_kafelkow
};

class kafelek
{
public:
    enum typ_kafelka typ;
    int wariant;
};

const string plik_z_kafelkiem[liczba_kafelkow] =
{
    "grafika/pusty.png", // pusty
    "grafika/tlo.png", // tlo
    "grafika/ziemia.png", // ziemia (ktora da sie kopac)
    "grafika/ziemia niezniszczalna.png", // ziemia niezniszczalna
    "grafika/start.png", // start
    "grafika/meta.png", // meta
    "grafika/lemmingi.png", // lemmingi
    "grafika/menu.png", //menu
    "grafika/numerki.png" // numerki
};

/******************************/
/***   KLASY - DEKLARACJA   ***/
/******************************/

class plansza;
class Lemming;
class LemmingZwykly;
class LemmingBloker;
class LemmingKopacz;

/****************************************************/
/***   FUNKCJE POMOCNICZE DLA KLAS - DEKLARACJA   ***/
/****************************************************/

bool czy_jest_bloker(int, int);
bool czy_ziemia(int, int);
bool czy_pusto(int, int);
bool czy_blokada(int, int);
bool czy_blokada_dla_kopacza(int, int);
bool czy_meta(int, int);

/****************/
/***   KLASY  ***/
/****************/
class plansza
{
public:
    class kafelek tlo[sz][wy];
    class kafelek ziemia[sz][wy];

    vector<Lemming*> g;
};

class plansza p;

class Lemming {
private:
    int n;
    int x, y; // pozycja na planszy
    int czekaj;
    int kierunek;
    int odwrocony;
    int spadanie;
    bool zyje;
    bool ocalony;

public:
    int typ;

    void setN(int _n) {n=_n;}
    void setX(int _x) {x=_x;}
    void setY(int _y) {y=_y;}
    void setCzekaj(int w) {czekaj=w;}
    void setKierunek(int k) {kierunek=k;}
    void setOdwrocony(int t) {odwrocony=t;}
    void setSpadanie(int s) {spadanie=s;}
    void setOcalony(bool o) {ocalony=o;}
    void setZyje(bool z) {zyje=z;}

    int getN() {return n;}
    int getX() {return x;}
    int getY() {return y;}
    int getCzekaj() {return czekaj;}
    int getKierunek() {return kierunek;}
    int getOdwrocony() {return odwrocony;}
    int getSpadanie() {return spadanie;}
    bool getOcalony() {return ocalony;}
    bool getZyje() {return zyje;}
    int getTyp() {return typ;}

    void spadaj(){
        setY(getY()+1);
        setSpadanie(getSpadanie()+1);
    }

public:
    virtual void ruch_lemmingow()=0;
};

class LemmingZwykly : public Lemming {
public:
    LemmingZwykly(int _n){
        setN(_n);
        typ = 0;
    }
    LemmingZwykly(Lemming* l){
        setN(l -> getN());
        setX(l -> getX());
        setY(l -> getY());
        setCzekaj(l -> getCzekaj());
        setKierunek(l -> getKierunek());
        setOdwrocony(l -> getOdwrocony());
        setSpadanie(l -> getSpadanie());
        setOcalony(l -> getOcalony());
        setZyje(l -> getZyje());
        typ = 0;
    }

    void ruch_lemmingow(){
        if(getCzekaj()==0){
            if(czy_ziemia(getX(),getY()+1)){
                if(getSpadanie()<4){
                    setSpadanie(0);
                    if(czy_pusto(getX()+getKierunek(), getY()) && !czy_jest_bloker(getX(), getY())){
                        setX(getX() + getKierunek());
                    }
                    else if(czy_jest_bloker(getX(), getY())){
                        setKierunek(getKierunek()*-1);
                        setOdwrocony(getOdwrocony()-getKierunek());
                        setX(getX() + getKierunek());
                    }
                    else if(czy_blokada(getX()+getKierunek(), getY())){
                        setKierunek(getKierunek()*-1);
                        setOdwrocony(getOdwrocony()-getKierunek());
                    }
                    else if(czy_meta(getX()+getKierunek(), getY())){
                        setOcalony(true);
                        ile_ocalonych++;
                        setX(getX() + getKierunek());
                    }
                }
                else setZyje(false);
            }
            else if(czy_meta(getX(), getY()+1)){
                setOcalony(true);
                ile_ocalonych++;
                setX(getX() + getKierunek());
            }
            else spadaj();
        }
        else setCzekaj(getCzekaj()-1);
    }
};

class LemmingBloker : public Lemming {
public:
    LemmingBloker(int _n){
        setN(_n);
        typ = 1;
    }
    LemmingBloker(Lemming* l){
        setN(l -> getN());
        setX(l -> getX());
        setY(l -> getY());
        setCzekaj(l -> getCzekaj());
        setKierunek(l -> getKierunek());
        setOdwrocony(l -> getOdwrocony());
        setSpadanie(l -> getSpadanie());
        setOcalony(l -> getOcalony());
        setZyje(l -> getZyje());
        typ = 1;
    }

    void ruch_lemmingow(){
        if(czy_ziemia(getX(),getY()+1)){
            if(getSpadanie()<4) setSpadanie(0);
            else setZyje(false);
        }
        else if(czy_meta(getX(),getY()+1)){
            setOcalony(true);
            ile_ocalonych++;
            setX(getX() + getKierunek());
        }
        else{
            spadaj();
            int numer=this -> getN();
            Lemming* tmp = new LemmingZwykly(p.g[numer]);
            delete p.g[numer];
            p.g[numer] = tmp;
        }
    }
};

class LemmingKopacz : public Lemming
{
private:
    int energia_kopania=0;
    bool koniec_kopania=false;
public:
    LemmingKopacz(int _n){
        setN(_n);
        typ = 2;
    }
    LemmingKopacz(Lemming* l){
        setN(l -> getN());
        setX(l -> getX());
        setY(l -> getY());
        setCzekaj(l -> getCzekaj());
        setKierunek(l -> getKierunek());
        setOdwrocony(l -> getOdwrocony());
        setSpadanie(l -> getSpadanie());
        setOcalony(l -> getOcalony());
        setZyje(l -> getZyje());
        typ = 2;
    }

    void setEnergiaKopania(int e) {energia_kopania=e;}
    void setKoniecKopania(int k) {koniec_kopania=k;}

    int getEnergiaKopania() {return energia_kopania;}
    bool getKoniecKopania() {return koniec_kopania;}

    void ruch_lemmingow(){
        if(getCzekaj()==0){
            if(czy_ziemia(getX(),getY()+1)){
                if(getSpadanie()<4){
                    setSpadanie(0);
                    if(czy_pusto(getX()+getKierunek(), getY()) && !czy_jest_bloker(getX(), getY())){
                        if(getKoniecKopania()==true){
                            int numer=this -> getN();
                            Lemming* tmp = new LemmingZwykly(p.g[numer]);
                            delete p.g[numer];
                            p.g[numer] = tmp;
                        }
                        setX(getX() + getKierunek());
                    }
                    else if(czy_jest_bloker(getX(), getY())){
                        setKierunek(getKierunek()*-1);
                        setOdwrocony(getOdwrocony()-getKierunek());
                        setX(getX() + getKierunek());
                    }
                    else if(czy_blokada_dla_kopacza(getX()+getKierunek(), getY())){
                        setKierunek(getKierunek()*-1);
                        setOdwrocony(getOdwrocony()-getKierunek());
                    }
                    else if(p.ziemia[getX()+getKierunek()][getY()].typ == ziemia){
                        if(p.ziemia[getX()+2*getKierunek()][getY()].typ == pusty) setKoniecKopania(true);
                        if(getEnergiaKopania()>=3){
                            p.ziemia[getX()+getKierunek()][getY()].typ = pusty;
                            setEnergiaKopania(0);
                        }
                        energia_kopania++;
                    }
                    else if(czy_meta(getX()+ getKierunek(), getY())){
                        setOcalony(true);
                        ile_ocalonych++;
                        setX(getX() + getKierunek());
                    }
                }
                else setZyje(false);
            }
            else if(p.ziemia[getX()][getY()+1].typ == meta){
                setOcalony(true);
                ile_ocalonych++;
                setX(getX() + getKierunek());
            }
            else{
                spadaj();
                int numer=this -> getN();
                Lemming* tmp = new LemmingZwykly(p.g[numer]);
                delete p.g[numer];
                p.g[numer] = tmp;
            }
        }
        else setCzekaj(getCzekaj()-1);
    }
};

/***************************************/
/***   FUNKCJE POMOCNICZE DLA KLAS   ***/
/***************************************/

bool czy_jest_bloker(int a, int b)
{
    for (auto &l: p.g){
        if((l -> getTyp() == 1) and l -> getX()==a and l -> getY()==b) return true;
    }
    return false;
};

bool czy_ziemia(int a, int b)
{
    if(p.ziemia[a][b].typ == ziemia ||
       p.ziemia[a][b].typ == niezniszczalna) {
        return true;
    }
    return false;
};

bool czy_pusto(int a, int b)
{
    if((p.ziemia[a][b].typ == pusty ||
       p.ziemia[a][b].typ == start) &&
       !czy_jest_bloker(a, b)){
        return true;
    }
    return false;
};

bool czy_blokada(int a, int b)
{
    if(czy_ziemia(a, b) ||
       czy_jest_bloker(a, b)){
        return true;
    }
    return false;
};

bool czy_blokada_dla_kopacza(int a, int b)
{
    if(p.ziemia[a][b].typ == niezniszczalna ||
       czy_jest_bloker(a, b)){
        return true;
    }
    return false;
}

bool czy_meta(int a, int b)
{
    if(p.ziemia[a][b].typ == meta) {
        return true;
    }
    return false;
};


/*******************/
/***   BITMAPY   ***/
/*******************/

ALLEGRO_BITMAP* bitmapa[liczba_kafelkow];

bool przygotuj_bitmapy()
{
    for (int i = 0; i < liczba_kafelkow; i++){
        bitmapa[i] = al_load_bitmap(plik_z_kafelkiem[i].c_str());
        if (!bitmapa[i]){
            cerr << "Błąd podczas wczytywania bitmapy " << plik_z_kafelkiem[i] << "." << endl;
            return false;
        }
    }
    return true;
}

bool zaladuj_bitmape(string nazwa_pliku)
{
    ALLEGRO_BITMAP  *obrazek = NULL;

    obrazek = al_load_bitmap(nazwa_pliku.c_str());

    if(!obrazek) {
        cerr << "Blad podczas wczytania bitmapy" << endl;
        return false;
    }
    al_draw_bitmap(obrazek,0,0,0);

    return true;
}

int wyswietlaj_bitmape(ALLEGRO_EVENT_QUEUE *event_queue, bool &wyjdz)
{
    bool klinkniecie=false;
    al_flip_display();
    while(!klinkniecie){
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
            klinkniecie=true;
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                wyjdz=true;
                return 0;
            }
        }
    }
}
/*******************/
/***   FUNKCJE   ***/
/*******************/

int wczytaj_plansze(int poziom, int &n, int &u, bool &k)
{
    // cala plansza wypelniona tlem i pusta ziemia
    for (int i = 0; i < sz; i++){
        for (int j = 0; j < wy; j++){
            p.tlo[i][j].typ = tlo;
            p.tlo[i][j].wariant = 0;
            p.ziemia[i][j].typ = pusty;
            p.ziemia[i][j].wariant = 0;
        }
    }
    // utworzenie stringa z nazwa pliku
    fstream f;
    std::stringstream sstm;
    sstm << "poziom " << poziom << ".txt";
    string nazwa = sstm.str();

    // otworz plik
    f.open(nazwa, ios::in);

    char ch;

    if (!f.is_open()){
        cout << "Brak kolejnego poziomu - gra ukonczona" << endl;
        k=true; // koniec gry
        return -1;
    }
    f >> n; // wczytaj liczbe lemmingow
    f >> u; // wczytaj liczbe lemmingow do uratowania
    f.get(ch); // wczytaj znak konca linii

    // Wczytywanie mapy
    int i=0; //kolumna
    int j=0; //wiersz
    while (!f.eof()){
        f.get(ch);
        if(ch=='%'){
            p.ziemia[i][j].typ = ziemia;
            p.ziemia[i][j].wariant = rand() % 4;
        }
        else if(ch=='#'){
            p.ziemia[i][j].typ = niezniszczalna;
            p.ziemia[i][j].wariant = rand() % 4;
        }
        else if(ch=='\n'){
            i=-1;
            j++;
        }
        else if(ch=='S'){
            p.ziemia[i][j].typ = start;
            p.ziemia[i][j].wariant = 0;
            x_start=i;
            y_start=j;
        }
        else if(ch=='M'){
            p.ziemia[i][j].typ = meta;
            p.ziemia[i][j].wariant = 0;
            x_meta=i;
            y_meta=j;
        }
        i++;
    }
    f.close();

    // staly element - menu (wybor typu lemminga i stan planszy)
    p.ziemia[sz/2-1][wy-1].typ = menu;
    p.ziemia[sz/2-1][wy-1].wariant = 0;

    p.ziemia[sz/2][wy-1].typ = menu;
    p.ziemia[sz/2][wy-1].wariant = 2;

    p.ziemia[sz/2+2][wy-1].typ = numerki;
    p.ziemia[sz/2+2][wy-1].wariant = (ile_ocalonych-ile_ocalonych%10)/10;
    p.ziemia[sz/2+3][wy-1].typ = numerki;
    p.ziemia[sz/2+3][wy-1].wariant = ile_ocalonych%10;

    p.ziemia[sz/2+4][wy-1].typ = numerki;
    p.ziemia[sz/2+4][wy-1].wariant = 10;

    p.ziemia[sz/2+5][wy-1].typ = numerki;
    p.ziemia[sz/2+5][wy-1].wariant = (u-u%10)/10;
    p.ziemia[sz/2+6][wy-1].typ = numerki;
    p.ziemia[sz/2+6][wy-1].wariant = u%10;

    return 0;
}

void parametry_poziomu(int p, int n, int u)
{
    if(p>=10) al_draw_bitmap_region(bitmapa[numerki], (p-(p%10))/10* k_sz, 0, k_sz, k_wy, 4*k_sz, 0*k_wy, 0); //który poziom, cyfra dziesiątek
    al_draw_bitmap_region(bitmapa[numerki], p%10* k_sz, 0, k_sz, k_wy, 5*k_sz, 0*k_wy, 0); //który poziom, cyfra jedności
    if(n>=10) al_draw_bitmap_region(bitmapa[numerki], (n-(n%10))/10* k_sz, 0, k_sz, k_wy, 20*k_sz, 4*k_wy, 0); //liczba lemmingów, cyfra dziesiątek
    al_draw_bitmap_region(bitmapa[numerki], n%10*k_sz, 0, k_sz, k_wy, 21*k_sz, 4*k_wy, 0); //liczba lemmingów, cyfra jedności
    if(u>=10) al_draw_bitmap_region(bitmapa[numerki], (u-(u%10))/10* k_sz, 0, k_sz, k_wy, 20*k_sz, 6*k_wy, 0); //liczba do uratowania, cyfra dziesiątek
    al_draw_bitmap_region(bitmapa[numerki], u%10* k_sz, 0, k_sz, k_wy, 21*k_sz, 6*k_wy, 0); //liczba do uratowania, cyfra jedności
}

void utworz_lemmingi(int n)
{
    for(int i=0; i<n; i++){
        p.g.push_back(new LemmingZwykly(i));

        p.g[i] -> setX(x_start);
        p.g[i] -> setY(y_start);
        p.g[i] -> setN(i);
        p.g[i] -> setCzekaj(2*i+2);
        p.g[i] -> setKierunek(1);
        p.g[i] -> setOdwrocony(0);
        p.g[i] -> setSpadanie(0);
        p.g[i] -> setOcalony(false);
        p.g[i] -> setZyje(true);
    }
}

void aktualizuj()
{
    p.ziemia[sz/2+2][wy-1].wariant = (ile_ocalonych-ile_ocalonych%10)/10;
    p.ziemia[sz/2+3][wy-1].wariant = ile_ocalonych%10;
}

void rysuj_plansze()
{
    al_clear_to_color(al_map_rgb(0,0,0));

    for (int i = 0; i < sz; i++){
        for (int j = 0; j < wy; j++){
            // tlo
            al_draw_bitmap_region(bitmapa[p.tlo[i][j].typ], p.tlo[i][j].wariant*k_sz,
                                  0, k_sz, k_wy, i*k_sz, j*k_sz, 0);
            // ziemia
            al_draw_bitmap_region(bitmapa[p.ziemia[i][j].typ], p.ziemia[i][j].wariant*k_sz,
                                  0, k_sz, k_wy, i*k_sz, j*k_sz, 0);
            // lemmingi
            for (auto &l: p.g){
                if (l -> getZyje() == true && l -> getOcalony() == false && l -> getX() == i && l -> getY() == j){
                    al_draw_bitmap_region(bitmapa[lemmingKafelek], ((l -> getTyp())*2 + l -> getOdwrocony()) * k_sz,
                                          0, k_sz, k_wy, i*k_sz, j*k_sz, 0);
                }
            }
        }
    }
}

/**********************/
/*** INICJALIZACJA  ***/
/**********************/

ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *timer = NULL;

int init()
{
    srand( time(NULL) );

    if(!al_init()) {
        cerr << "Blad podczas inicjalizacji allegro." << endl;
        return -1;
    }

    if (!al_init_primitives_addon()) {
        cerr << "Blad podczas inicjalizacji dodatku 'primitives'." << endl;
        return -1;
    }

    if(!al_init_image_addon()){
        cerr << "Blad podczas inicjalizacji dodatku 'image'." << endl;
        return -1;
    }

    if(!al_install_keyboard()){
        cerr << "Blad podczas inicjalizacji klawiatury." << endl;
        return -1;
    }
    if(!al_install_mouse()){
        cerr << "Blad podczas inicjalizacji myszy." << endl;
        return -1;
    }

    timer = al_create_timer(1.0 / FPS);
    if(!timer){
        cerr << "Blad podczas inicjalizacji zegara." << endl;
        return -1;
    }

    display = al_create_display(screen_w, screen_h);
    if(!display){
        cerr << "Blad podczas inicjalizacji ekranu." << endl;
        al_destroy_timer(timer);
        return -1;
    }

    event_queue = al_create_event_queue();
    if(!event_queue){
        cerr << "Blad podczas inicjalizacji kolejki zdarzeń." << endl;
        al_destroy_display(display);
        al_destroy_timer(timer);
        return -1;
    }

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_clear_to_color(al_map_rgb(0,0,0));

    al_flip_display();
    al_start_timer(timer);

    return 0;
}

int main(int argc, char ** argv)
{
    if (init() != 0) {
        cerr << "Inicjalizacja nie powiodła się." << endl;
        return -1;
    }

    if (!przygotuj_bitmapy()) {
        return -1;
    }

    ALLEGRO_COLOR kolor = al_map_rgb(44,117,255); // kolor potrzebny do ramki przy zmianie typu lemminga

    bool wyjdz=false;

    /* EKRAN STARTOWY */
    bool zacznij_gre=false;
    zaladuj_bitmape("start gry.bmp");
    wyswietlaj_bitmape(event_queue, wyjdz);
    if(wyjdz) return 0;

    /* INSTRUKCJA */
    bool instrukcja=false;
    zaladuj_bitmape("instrukcja.bmp");
    wyswietlaj_bitmape(event_queue, wyjdz);
    if(wyjdz) return 0;

    /* GRA - KOLEJNE POZIOMY*/
    while(!koniec_gry) {
        ile_ocalonych=0;
        wczytaj_plansze(poziom, ile_lemmingow, ile_uratowac, koniec_gry);
        if(koniec_gry==true) break; // brak planszy do wczytania - koniec gry
        /* EKRAN WYMAGAŃ POZIOMU */
        bool zacznij_poziom=false;
        zaladuj_bitmape("start poziomu.bmp");
        parametry_poziomu(poziom, ile_lemmingow, ile_uratowac); // druga część ładowania bitmapy - wymagania konkretnego poziomu
        wyswietlaj_bitmape(event_queue, wyjdz);


        int aktualna_energia=30;
        int zmiana_bloker=1;
        int zmiana_kopacz=1;
        bool przerysuj = true;

        utworz_lemmingi(ile_lemmingow);
        aktualizuj();
        rysuj_plansze();
        al_flip_display();
        przerysuj = true;
        while(ile_ocalonych<ile_uratowac){
            ALLEGRO_EVENT ev;
            al_wait_for_event(event_queue, &ev);

            if(ev.type == ALLEGRO_EVENT_TIMER) {
                aktualna_energia++;
                if(aktualna_energia>=wymagana_energia) {
                    for (auto &l: p.g) {
                        if(l -> getZyje()==true && l -> getOcalony()==false) {
                            l -> ruch_lemmingow();
                        }
                    }
                    aktualna_energia=0;
                }
                przerysuj=true;
            }
            else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES){
                x=ev.mouse.x;
                y=ev.mouse.y;
            }
            else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
                if(x/30==sz/2-1 && y/30==wy-1){
                    p.ziemia[sz/2][wy-1].wariant = 2; // odznaczenie kopacza jeśli był
                    zmiana_kopacz=1;
                    p.ziemia[sz/2-1][wy-1].wariant += zmiana_bloker;
                    zmiana_bloker *= -1;
                }
                else if(x/30==sz/2 && y/30==wy-1){
                    p.ziemia[sz/2-1][wy-1].wariant = 0; // odznaczenie blokera jeśli był
                    zmiana_bloker=1;
                    p.ziemia[sz/2][wy-1].wariant += zmiana_kopacz;
                    zmiana_kopacz *= -1;
                }
                for(auto &l: p.g){
                    if(x/30==l -> getX() && y/30==l -> getY() && l -> getTyp()==0) {
                        if(zmiana_bloker==-1){
                            Lemming* tmp = new LemmingBloker(l);
                            delete l;
                            l = tmp;
                            break;
                        }
                        else if(zmiana_kopacz==-1){
                            Lemming* tmp = new LemmingKopacz(l);
                            delete l;
                            l = tmp;
                            break;
                        }
                    }
                }
            }
            else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
                if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                    poziom--;
                    break;
                }
            }

            if(przerysuj && al_is_event_queue_empty(event_queue)) {
                przerysuj = false;
                aktualizuj();
                rysuj_plansze();
                if(zmiana_bloker==-1 || zmiana_kopacz==-1) {
                    al_draw_rectangle(x-10, y-5, x+20, y+25, kolor, 1); // kwadrat wokół kursora
                }
                al_flip_display();
            }
        }
        poziom++;
        p.g.clear();
    }
    zaladuj_bitmape("koniec gry.bmp");
    wyswietlaj_bitmape(event_queue, wyjdz);
    return 0;
}
