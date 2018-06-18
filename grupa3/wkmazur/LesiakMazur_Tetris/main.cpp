/*
###########################################################
##              PROJEKT TETRIS - PLIK MAIN               ##
##  autorzy: Szymon Lesiak 348768, Wojciech Mazur 348782 ##
##                        2018 r.                        ##
###########################################################
*/

#include <memory>

#include <stdio.h>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "allegro5/allegro_image.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include <string>
#include <sstream>
#include <iostream>
#include <windows.h>
#include <vector>
#include <cstdlib>
using namespace std;

#include "plansza.h"
#include "klocek.h"

// Inicjalizacja pliku graficznego na tlo
#define BACKGROUND_FILE "img/tlo.png"
// Kafelki
#define kafelek_plik "img/zolty.png"
#define zolty "img/zolty.png"
#define zielony "img/zielony.png"
#define czerwony "img/czerwony.png"
#define pomaranczowy "img/pomaranczowy.png"
#define fioletowy "img/fioletowy.png"
#define niebieski "img/niebieski.png"
#define szary "img/szary.png"

// Funkcja pobierajaca rozdzielczosc ekranu
void GetDesktopResolution(int& horizontal, int& vertical)
{
   RECT desktop;
   const HWND hDesktop = GetDesktopWindow();
   GetWindowRect(hDesktop, &desktop);
   horizontal = desktop.right;
   vertical = desktop.bottom;
}

// Rozdzielczosc ekranu
int horizontal=0;
int vertical=0;
// Pozycja okna
int oknoLewo=0;
int oknoGora=0;

// Rozmiary kwadratow
const int k_sz = 30;	// szerokosc (piksele) kafelka
const int k_wy = 30;	// wysokosc (piksele) kafelka

// Wymiary okna
const int oknoSzer=1500;
const int oknoWys=750;
/* Wymiary okna (piksele):
        1 plansza od 141,51 dod 440,650     -> dlugosc 600, szerokosc 300
        2 plansza od 1061,51 do 1360,650    -> dlugosc 600, szerokosc 300
        przycisk 1 gracz: od 625,285 do 754,334
        przycisk 2 graczy: od 770,285 do 899,334
*/

// Aktualnie wybrany tryb gry - 1 gracz / 2 graczy
string wybranyTryb="1 gracz";

// Stop
bool stop=true;

// Wyniki graczy
long wynikGracz1=0;
long wynikGracz2=0;

//Podniesione poziomy przeciwnika - w momencie usuniecia calego wiersza
int podniesionePoziomyGracz1=0;
int podniesionePoziomyGracz2=0;

// Utworzenie elemntow odpowiedzialnych za wyswietlana grafike
ALLEGRO_DISPLAY *okno = NULL;
ALLEGRO_BITMAP *background = NULL;
ALLEGRO_BITMAP* kafelek = NULL;
ALLEGRO_BITMAP* zoltyKolor = NULL;
ALLEGRO_BITMAP* zielonyKolor = NULL;
ALLEGRO_BITMAP* czerwonyKolor = NULL;
ALLEGRO_BITMAP* pomaranczowyKolor = NULL;
ALLEGRO_BITMAP* fioletowyKolor = NULL;
ALLEGRO_BITMAP* niebieskiKolor = NULL;
ALLEGRO_BITMAP* szaryKolor = NULL;
ALLEGRO_FONT *fontWybranyTryb = NULL;
ALLEGRO_FONT *fontWynikGracza = NULL;

// Utworzenie plansz dla graczy
Plansza planszaGracz1;
Plansza planszaGracz2;

// Wektory zawierajacy wszystkie klocki (osobne dla obu graczy ze wzgledu na dokonywane na nich akcje)
vector<Klocek*> wektorKlockowGracz1;
vector<Klocek*> wektorKlockowGracz2;

// Iteracje graczy 1 i 2
int iteracjaGracz1=0;
int iteracjaGracz2=0;

// Zamiana w string
    template<typename T>
    std::string to_string(const T& obj)
    {
        std::stringstream ss;
        ss << obj;
        return ss.str();
    }

// Funkcja odswiezajaca ekran
    void Aktualizuj_ekran(){

        // Ustawienie obrazka na tlo
        al_draw_bitmap(background,0,0,0);

        //Rysowanie szarych kafelkow
        planszaGracz1.rysujSzary(szaryKolor);
        if(wybranyTryb=="2 graczy")
            planszaGracz2.rysujSzary(szaryKolor);

        // Rysowanie podgladu nastepnego klocka - GRACZ 1
        if(wektorKlockowGracz1.size()>1)
            wektorKlockowGracz1[iteracjaGracz1+1]->rysujPodglad(planszaGracz1);
        else if (wektorKlockowGracz1.size()==1)
            wektorKlockowGracz1[iteracjaGracz1]->rysujPodglad(planszaGracz1);
        // Rysowanie podgladu nastepnego klocka - GRACZ 2
        if(wektorKlockowGracz2.size()>1 && wybranyTryb=="2 graczy")
            wektorKlockowGracz2[iteracjaGracz2+1]->rysujPodglad(planszaGracz2);
        else if (wektorKlockowGracz2.size()==1 && wybranyTryb=="2 graczy")
            wektorKlockowGracz2[iteracjaGracz2]->rysujPodglad(planszaGracz2);

        // Rysowanie klockow bez ostatniego - GRACZ 1
        if(wektorKlockowGracz1.size()>1)
            for(int i=0; i<=iteracjaGracz1; i++){
                wektorKlockowGracz1[i]->rysuj(planszaGracz1);
            }
        // Rysowanie klockow bez ostatniego - GRACZ 2
        if(wektorKlockowGracz2.size()>1)
            for(int i=0; i<=iteracjaGracz2; i++){
                wektorKlockowGracz2[i]->rysuj(planszaGracz2);
            }

        //Napis dotyczacy wybranego trybu
        al_draw_text(fontWybranyTryb, al_map_rgb(255,255,255), 796, 628, ALLEGRO_ALIGN_LEFT, wybranyTryb.c_str()); //815 407
        //Napisy z wynikami graczy
        al_draw_text(fontWynikGracza, al_map_rgb(0,0,0), 370, 672, ALLEGRO_ALIGN_LEFT, to_string(wynikGracz1).c_str());
        al_draw_text(fontWynikGracza, al_map_rgb(0,0,0), 1295, 672, ALLEGRO_ALIGN_LEFT, to_string(wynikGracz2).c_str());

        //Odswiez
        al_flip_display();
    }

    // Losowanie koloru
    ALLEGRO_BITMAP* wylosujKolor(){
        ALLEGRO_BITMAP* wynik = NULL;
        int losujKolor = (rand() % 6 ) + 1;
        switch(losujKolor)
        {
            case 1:
                wynik=zoltyKolor;
                break;
            case 2:
                wynik=zielonyKolor;
                break;
            case 3:
                wynik=czerwonyKolor;
                break;
            case 4:
                wynik=pomaranczowyKolor;
                break;
            case 5:
                wynik=fioletowyKolor;
                break;
            default:
                wynik=niebieskiKolor;
        }
        return wynik;
    }

    // Tworzenie nowego klocka
    void nowyKlocek(){
        ALLEGRO_BITMAP* wylosowanyKolor=wylosujKolor();
        int losujKsztalt = (rand() % 7 ) + 1;
        switch(losujKsztalt)
                {
                    case 1:
                        wektorKlockowGracz1.push_back(new Klocek_T(wylosowanyKolor));
                        wektorKlockowGracz2.push_back(new Klocek_T(wylosowanyKolor));
                        break;
                    case 2:
                        wektorKlockowGracz1.push_back(new Klocek_O(wylosowanyKolor));
                        wektorKlockowGracz2.push_back(new Klocek_O(wylosowanyKolor));
                        break;
                    case 3:
                        wektorKlockowGracz1.push_back(new Klocek_I(wylosowanyKolor));
                        wektorKlockowGracz2.push_back(new Klocek_I(wylosowanyKolor));
                        break;
                    case 4:
                        wektorKlockowGracz1.push_back(new Klocek_S(wylosowanyKolor));
                        wektorKlockowGracz2.push_back(new Klocek_S(wylosowanyKolor));
                        break;
                    case 5:
                        wektorKlockowGracz1.push_back(new Klocek_Z(wylosowanyKolor));
                        wektorKlockowGracz2.push_back(new Klocek_Z(wylosowanyKolor));
                        break;
                    case 6:
                        wektorKlockowGracz1.push_back(new Klocek_L(wylosowanyKolor));
                        wektorKlockowGracz2.push_back(new Klocek_L(wylosowanyKolor));
                        break;
                    default:
                        wektorKlockowGracz1.push_back(new Klocek_J(wylosowanyKolor));
                        wektorKlockowGracz2.push_back(new Klocek_J(wylosowanyKolor));
                }
    }

    void dodajNaPlansze(Plansza &plansza){
        if (wektorKlockowGracz1.size()>1){
            if (plansza.ktoryGracz==1)
                wektorKlockowGracz1[iteracjaGracz1]->dodajNaPlansze(planszaGracz1);
            if (plansza.ktoryGracz==2)
                wektorKlockowGracz2[iteracjaGracz2]->dodajNaPlansze(planszaGracz2);
        }
    }

// ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! !
// ============ MAIN ================

int main()
{
    planszaGracz1.ktoryGracz=1;
    planszaGracz2.ktoryGracz=2;

    // pseudolosowosc liczb
    srand( time( NULL ) );

    // Obsluga bledu przy inicjalizacji
    if (!al_init()) {
        cout << "Inicjalizacja nie powiodla sie." << endl; return -1;
    }

    // Okno
    GetDesktopResolution(horizontal, vertical);
    oknoLewo = (horizontal-oknoSzer)/2;
    // Utworzenie okna o wymiarach
    okno = al_create_display(oknoSzer, oknoWys);
    al_set_window_title( okno, "Tetris - Lesiak&Mazur");
    al_set_window_position( okno, oknoLewo, oknoGora);

    // Potrzebne addony i instalacje
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    // Zaladowanie obrazkow
    // tlo
    background = al_load_bitmap(BACKGROUND_FILE);
    // czcionki
    fontWybranyTryb = al_load_ttf_font("FreeMonoBold.ttf",21,0);
    fontWynikGracza = al_load_ttf_font("FreeMonoBold.ttf",40,0);
    // kafelki
    kafelek = al_load_bitmap(kafelek_plik);
    zoltyKolor = al_load_bitmap(zolty);
    zielonyKolor = al_load_bitmap(zielony);
    czerwonyKolor = al_load_bitmap(czerwony);
    pomaranczowyKolor = al_load_bitmap(pomaranczowy);
    fioletowyKolor = al_load_bitmap(fioletowy);
    niebieskiKolor = al_load_bitmap(niebieski);
    szaryKolor = al_load_bitmap(szary);

    // Kolejka zdarzen
    ALLEGRO_EVENT_QUEUE *zdarzenie = NULL;
    // Utworzenie kolejki zdarzen
    zdarzenie = al_create_event_queue();

    // Obsluga bledu przy inicjalizacji
    if (!okno || !zdarzenie) {
        cout << "Inicjalizacja nie powiodla sie." << endl; return -1;
    }

    // Zrodla kolejki zdarzen
    // przyciski okna
    al_register_event_source(zdarzenie, al_get_display_event_source(okno));
    // przyciski myszy
    al_install_mouse();
    al_register_event_source(zdarzenie, al_get_mouse_event_source());
    // przyciski klawiatury
    al_install_keyboard();
    al_register_event_source(zdarzenie, al_get_keyboard_event_source());

    // Dodanie 1 klocka
    nowyKlocek();

    // Aktualizuj plansze
    Aktualizuj_ekran();

    // Zegar
    clock_t teraz;
    clock_t teraz2;


// ================================================
// ================== CIALO GRY ===================
// ================================================
    while (true) {

        //Aktualizuj_ekran();

        // Nastepne zdarzenie bez czekania
        ALLEGRO_EVENT ev;
        al_get_next_event(zdarzenie, &ev);

        //Jezeli wcisnieto "Stop"
        if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && ev.mouse.x>=768 && ev.mouse.x<=1000 && ev.mouse.y>=350 && ev.mouse.y<=400) {
            stop=true;
            wektorKlockowGracz1.clear();
            wektorKlockowGracz2.clear();
            planszaGracz1.przygotuj_plansze();
            planszaGracz2.przygotuj_plansze();
            wynikGracz1=0;
            wynikGracz2=0;
            iteracjaGracz1=0;
            iteracjaGracz2=0;
            podniesionePoziomyGracz1=0;
            podniesionePoziomyGracz2=0;
            nowyKlocek();
            Aktualizuj_ekran();
        }

    // ---------   STOP   ---------
        while(stop){
                al_get_next_event(zdarzenie, &ev);

                // Jezeli wcisnieto start
                if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && ev.mouse.x>=522 && ev.mouse.x<=755 && ev.mouse.y>=350 && ev.mouse.y<=400) {
                    stop=false;
                    if (wektorKlockowGracz1.size()==1){
                        nowyKlocek();

                        if(wybranyTryb=="1 gracz")
                            dodajNaPlansze(planszaGracz1);
                        if(wybranyTryb=="2 graczy"){
                            dodajNaPlansze(planszaGracz1);
                            dodajNaPlansze(planszaGracz2);
                        }

                        Aktualizuj_ekran();
                        teraz=clock();
                        teraz2=clock();
                    }
                }
                //Jezeli wcisnieto "2 graczy" podczas stopu
                if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && ev.mouse.x>=770 && ev.mouse.x<=899 && ev.mouse.y>=285 && ev.mouse.y<=334) {
                    wybranyTryb="2 graczy";
                    iteracjaGracz1=0;
                    iteracjaGracz2=0;
                    Aktualizuj_ekran();
                }
                //Jezeli wcisnieto "1 gracz"
                if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && ev.mouse.x>=625 && ev.mouse.x<=754 && ev.mouse.y>=285 && ev.mouse.y<=334) {
                    wybranyTryb="1 gracz";
                    iteracjaGracz1=0;
                    Aktualizuj_ekran();
                }
                // Jesli wcisnieto przycisk X to zamknij zamknij aplikacje
                if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                    break;
                }
        }
    // --------- KONIEC STOPU ---------

    //GRACZ 1 - OBSLUGA KLAWIATURY (STRZALKI)
        // Jezeli wcisnieto strzalke w dol to opusc
        if (ev.type==ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode==ALLEGRO_KEY_DOWN){
            wektorKlockowGracz1[iteracjaGracz1] -> przesun(planszaGracz1);
            Aktualizuj_ekran();
        }

        // Jezeli wcisnieto strzalke w lewo to porusz w lewo
        if (ev.type==ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode==ALLEGRO_KEY_LEFT){
            wektorKlockowGracz1[iteracjaGracz1] -> lewo(planszaGracz1);
            Aktualizuj_ekran();
        }

        // Jezeli wcisnieto strzalke w prawo to porusz w prawo
        if (ev.type==ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode==ALLEGRO_KEY_RIGHT){
            wektorKlockowGracz1[iteracjaGracz1] -> prawo(planszaGracz1);
            Aktualizuj_ekran();
        }

        // Jezeli wcisnieto spacje to opusc w dol
        if (ev.type==ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode==ALLEGRO_KEY_SPACE){
            wektorKlockowGracz1[iteracjaGracz1] -> przesunCalkiem(planszaGracz1);
            Aktualizuj_ekran();
        }

        // Jezeli wcisnieto strzalke w gore to obroc
        if (ev.type==ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode==ALLEGRO_KEY_UP){
            wektorKlockowGracz1[iteracjaGracz1] -> obroc(planszaGracz1);
            Aktualizuj_ekran();
        }

    //GRACZ 2 - OBSLUGA KLAWIATURY  (WASD)
        // Jezeli wcisnieto S to opusc
        if (ev.type==ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode==ALLEGRO_KEY_S){
            wektorKlockowGracz2[iteracjaGracz2] -> przesun(planszaGracz2);
            Aktualizuj_ekran();
        }

        // Jezeli wcisnieto A to porusz w lewo
        if (ev.type==ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode==ALLEGRO_KEY_A){
            wektorKlockowGracz2[iteracjaGracz2] -> lewo(planszaGracz2);
            Aktualizuj_ekran();
        }

        // Jezeli wcisnieto D to porusz w prawo
        if (ev.type==ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode==ALLEGRO_KEY_D){
            wektorKlockowGracz2[iteracjaGracz2] -> prawo(planszaGracz2);
            Aktualizuj_ekran();
        }

        // Jezeli wcisnieto Shift to opusc calkiem w dol
        if (ev.type==ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode==ALLEGRO_KEY_TAB){
            wektorKlockowGracz2[iteracjaGracz2] -> przesunCalkiem(planszaGracz2);
            Aktualizuj_ekran();
        }

        // Jezeli wcisnieto strzalke W to obroc
        if (ev.type==ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode==ALLEGRO_KEY_W){
            wektorKlockowGracz2[iteracjaGracz2] -> obroc(planszaGracz2);
            Aktualizuj_ekran();
        }

    //WYJSCIE Z APLIKACJI
        // Jesli wcisnieto przycisk X to zamknij zamknij aplikacje
        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            cout << "Odebrano zdarzenie ALLEGRO_EVENT_DISPLAY_CLOSE - zamkniecie aplikacji" << endl;
            break;
        }


    //----------- PETLA CO POL SEKUNDY - GRACZ 1 -----------
                // Nowa petla co pol sekundy lub po wcisnieciu spacji (opuszczenie calkowite klocka w dol)
                if( (clock()-teraz)/(CLOCKS_PER_SEC/1000)>=500 || (ev.type==ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode==ALLEGRO_KEY_SPACE)){


                    // Jesli ostatnio dodany klocek doszedl do konca to:
                    if( wektorKlockowGracz1[iteracjaGracz1] -> czyKoniecPlanszy(planszaGracz1)){

                            // Jesli ten klocek zatrzymal sie na samej gorze - KONIEC GRY
                            if(wektorKlockowGracz1[iteracjaGracz1]->get(3,1)==true || wektorKlockowGracz1[iteracjaGracz1]->get(4,1)==true || wektorKlockowGracz1[iteracjaGracz1]->get(5,1)==true || wektorKlockowGracz1[iteracjaGracz1]->get(6,1)==true
                               || wektorKlockowGracz1[iteracjaGracz1]->get(3,0)==true || wektorKlockowGracz1[iteracjaGracz1]->get(4,0)==true || wektorKlockowGracz1[iteracjaGracz1]->get(5,0)==true || wektorKlockowGracz1[iteracjaGracz1]->get(6,0)==true){

                                stop=true;
                                wektorKlockowGracz1.clear();
                                wektorKlockowGracz2.clear();
                                planszaGracz1.przygotuj_plansze();
                                planszaGracz2.przygotuj_plansze();
                                podniesionePoziomyGracz1=0;
                                podniesionePoziomyGracz2=0;

                                if (wybranyTryb=="1 gracz")
                                    al_show_native_message_box(okno, "Koniec gry", "Gra dobiegla konca, twoj wynik to:", to_string(wynikGracz1).c_str(), NULL, ALLEGRO_MESSAGEBOX_OK_CANCEL);
                                if(wybranyTryb=="2 graczy"){
                                    string tekst1="Wynik Gracza 2 to: "; string tekst2=to_string(wynikGracz2); string tekst3="\nWynik Gracza 1 to: "; string tekst4=to_string(wynikGracz1);
                                    string tekst5=tekst1+tekst2+tekst3+tekst4;
                                    al_show_native_message_box(okno, "Koniec gry", "Wygral Gracz 2 !!!", tekst5.c_str(), NULL, ALLEGRO_MESSAGEBOX_OK_CANCEL);
                                }
                                wynikGracz1=0;
                                wynikGracz2=0;
                                nowyKlocek();
                                iteracjaGracz1=0;
                                iteracjaGracz2=0;
                                continue;
                            }

                            // Spisanie calych wierszy
                            vector<int> caleWiersze = planszaGracz1.caleWiersze(podniesionePoziomyGracz1);
                            if(caleWiersze.size()>0){
                                // Jesli istnieja cale wiersze to:
                                podniesionePoziomyGracz2+=caleWiersze.size();

                                for (int i=0; i<wektorKlockowGracz1.size()-1; i++){
                                    // usun wiersze i opusc klocki
                                    wektorKlockowGracz1[i]->usunCaleWiersze(caleWiersze, planszaGracz1);
                                    if(wybranyTryb=="2 graczy")
                                        wektorKlockowGracz2[i]->podniesPoziom(caleWiersze,planszaGracz2);
                                }
                                for (int i=0; i<wektorKlockowGracz1.size()-1; i++){
                                    // usun wiersze i opusc klocki
                                    planszaGracz1.usunCaleWiersze(wektorKlockowGracz1[i]);
                                    if(wybranyTryb=="2 graczy")
                                        planszaGracz2.podniesPoziom(wektorKlockowGracz2[i],podniesionePoziomyGracz2);
                                }

                                wynikGracz1+=caleWiersze.size()*100;
                            }

                            iteracjaGracz1++;
                            nowyKlocek();
                            dodajNaPlansze(planszaGracz1);
                            Aktualizuj_ekran();
                    }
                    else{
                            wektorKlockowGracz1[iteracjaGracz1] -> przesun(planszaGracz1);
                            Aktualizuj_ekran();
                            teraz=clock();
                    }
                }
    //----------- KONIEC PETLI -----------

        //----------- PETLA CO POL SEKUNDY - GRACZ 2 -----------
                // Nowa petla co pol sekundy lub po wcisnieciu spacji (opuszczenie calkowite klocka w dol)
                if( (clock()-teraz2)/(CLOCKS_PER_SEC/1000)>=500 || (ev.type==ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode==ALLEGRO_KEY_TAB)){

                    // Jesli ostatnio dodany klocek doszedl do konca to:
                    if( wektorKlockowGracz2[iteracjaGracz2] -> czyKoniecPlanszy(planszaGracz2)){

                            // Jesli ten klocek zatrzymal sie na samej gorze - KONIEC GRY
                            if(wektorKlockowGracz2[iteracjaGracz2]->get(3,1)==true || wektorKlockowGracz2[iteracjaGracz2]->get(4,1)==true || wektorKlockowGracz2[iteracjaGracz2]->get(5,1)==true || wektorKlockowGracz2[iteracjaGracz2]->get(6,1)==true
                                || wektorKlockowGracz2[iteracjaGracz2]->get(3,0)==true || wektorKlockowGracz2[iteracjaGracz2]->get(4,0)==true || wektorKlockowGracz2[iteracjaGracz2]->get(5,0)==true || wektorKlockowGracz2[iteracjaGracz2]->get(6,0)==true){

                                stop=true;
                                wektorKlockowGracz1.clear();
                                wektorKlockowGracz2.clear();
                                planszaGracz1.przygotuj_plansze();
                                planszaGracz2.przygotuj_plansze();
                                podniesionePoziomyGracz1=0;
                                podniesionePoziomyGracz2=0;

                                string tekst1="Wynik Gracza 1 to: "; string tekst2=to_string(wynikGracz1); string tekst3="\nWynik Gracza 2 to: "; string tekst4=to_string(wynikGracz2);
                                string tekst5=tekst1+tekst2+tekst3+tekst4;
                                al_show_native_message_box(okno, "Koniec gry", "Wygral Gracz 1 !!!", tekst5.c_str(), NULL, ALLEGRO_MESSAGEBOX_OK_CANCEL);

                                wynikGracz1=0;
                                wynikGracz2=0;
                                nowyKlocek();
                                iteracjaGracz1=0;
                                iteracjaGracz2=0;
                                continue;
                            }

                            // Spisanie calych wierszy
                            vector<int> caleWiersze = planszaGracz2.caleWiersze(podniesionePoziomyGracz2);
                            if(caleWiersze.size()>0){

                                podniesionePoziomyGracz1+=caleWiersze.size();
                                // Jesli istnieja cale wiersze to:
                                for (int i=0; i<wektorKlockowGracz2.size()-1; i++){
                                    // usun wiersze i opusc klocki
                                    wektorKlockowGracz2[i]->usunCaleWiersze(caleWiersze, planszaGracz2);
                                    wektorKlockowGracz1[i]->podniesPoziom(caleWiersze,planszaGracz1);
                                }
                                for (int i=0; i<wektorKlockowGracz2.size()-1; i++){
                                    // usun wiersze i opusc klocki
                                    planszaGracz2.usunCaleWiersze(wektorKlockowGracz2[i]);
                                    planszaGracz1.podniesPoziom(wektorKlockowGracz1[i],podniesionePoziomyGracz1);
                                }

                                wynikGracz2+=caleWiersze.size()*100;
                            }

                            iteracjaGracz2++;
                            nowyKlocek();
                            dodajNaPlansze(planszaGracz2);
                            Aktualizuj_ekran();
                    }
                    else{
                            wektorKlockowGracz2[iteracjaGracz2] -> przesun(planszaGracz2);
                            Aktualizuj_ekran();
                            teraz2=clock();
                    }
                }
    //----------- KONIEC PETLI -----------

    }
// ================================================
// ============== KONIEC CIALA GRY ================
// ================================================

    cout << "Koniec aplikacji." << endl;

    // Zamkniecie okna
    al_destroy_display(okno);
    al_destroy_event_queue(zdarzenie);

    return 0;
}

