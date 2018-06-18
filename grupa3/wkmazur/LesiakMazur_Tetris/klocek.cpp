
#include "klocek.h"
#include <iostream>
using namespace std;

// Klasa Bazowa

bool Klocek::get(int i,int j){
    return this -> planszaKlocka.get(i,j);
}

// Sprawdzenie czy klocek doszedl do konca
bool Klocek::czyKoniecPlanszy(Plansza &plansza){
        bool wynik=false;

        for(int i=0; i< this->planszaKlocka.getSzer(); i++){
            for(int j=0; j< this->planszaKlocka.getWys()-1; j++){
                if(this->planszaKlocka.get(i,j)==true && this->planszaKlocka.get(i,j+1)==false && plansza.get(i,j+1)==true)
                    wynik=true;
                if(j+1==dolnaKrawedz && this->planszaKlocka.get(i,j+1)==true)
                    wynik=true;
            }
        }
        return wynik;
}

// PRZESUWANIE W DOL O JEDEN
void Klocek::przesun(Plansza &plansza){

        Plansza tymczasowa;

    if(!czyKoniecPlanszy(plansza)){
        for(int i=0; i< this->planszaKlocka.getSzer(); i++){
            for(int j=0; j< this->planszaKlocka.getWys(); j++){
                if(this->planszaKlocka.get(i,j)==true){
                    tymczasowa.set(i,j+1,true);
                    plansza.set(i,j,false);
                    this->planszaKlocka.set(i,j,false);
                }
            }
        }

        for(int i=0; i<plansza.getSzer(); i++){
            for(int j=0; j<plansza.getWys(); j++){
                if(tymczasowa.get(i,j)==true){
                    plansza.set(i,j,true);
                    this->planszaKlocka.set(i,j,true);
                }
            }
        }
    }
}

// RUCH W LEWO
void Klocek::lewo(Plansza &plansza){

        Plansza tymczasowa;

        // Sprawdza czy nie doszlo do lewej krawedzi
        bool lewaGranica=false;
        for(int i=0; i< this->planszaKlocka.getWys(); i++){
             if(this->planszaKlocka.get(lewaKrawedz,i)==true)
                lewaGranica=true;
        }

        // Sprawdza czy jest mozliwy ruch w lewo (czy plansza nia zawiera elementow po lewej skrajnej stronie klocka
        bool stop=false;
        for(int i=0; i< this->planszaKlocka.getSzer(); i++){
            for(int j=0; j< this->planszaKlocka.getWys(); j++){
                if(i>0 && this->planszaKlocka.get(i,j)==true && this->planszaKlocka.get(i-1,j)==false){
                    if(plansza.get(i-1,j)==true){
                        stop=true;
                    }
                }
            }
        }

    if(!lewaGranica)
        for(int i=0; i< this->planszaKlocka.getSzer(); i++){
            for(int j=0; j< this->planszaKlocka.getWys(); j++){
                if(this->planszaKlocka.get(i,j)==true){
                    //if(i>0 && plansza.get(i-1,j)==true && stop){
                    if(stop){
                        return;
                    }
                    tymczasowa.set(i-1,j,true);
                    plansza.set(i,j,false);
                    this->planszaKlocka.set(i,j,false);

                }
            }
        }

        for(int i=0; i<plansza.getSzer(); i++){
            for(int j=0; j<plansza.getWys(); j++){
                if(tymczasowa.get(i,j)==true){
                    plansza.set(i,j,true);
                    this->planszaKlocka.set(i,j,true);
                }
            }
        }
}

// RUCH W PRAWO
void Klocek::prawo(Plansza &plansza){

        Plansza tymczasowa;

        // Sprawdza czy nie doszlo do prawej krawedzi
        bool prawaGranica=false;
        for(int i=0; i< this->planszaKlocka.getWys(); i++){
             if(this->planszaKlocka.get(prawaKrawedz,i)==true)
                prawaGranica=true;
        }

        // Sprawdza czy jest mozliwy ruch w prawo (czy plansza nia zawiera elementow po prawej skrajnej stronie klocka
        bool stop=false;
        for(int i=0; i< this->planszaKlocka.getSzer(); i++){
            for(int j=0; j< this->planszaKlocka.getWys(); j++){
                if(i>0 && this->planszaKlocka.get(i,j)==true && this->planszaKlocka.get(i+1,j)==false){
                    if(plansza.get(i+1,j)==true){
                        stop=true;
                    }
                }
            }
        }

    if(!prawaGranica){
        for(int i=0; i< this->planszaKlocka.getSzer(); i++){
            for(int j=0; j< this->planszaKlocka.getWys(); j++){
                if(this->planszaKlocka.get(i,j)==true){
                    if(stop){
                        return;
                    }
                    tymczasowa.set(i+1,j,true);
                    plansza.set(i,j,false);
                    this->planszaKlocka.set(i,j,false);
                }
            }
        }

        for(int i=0; i<plansza.getSzer(); i++){
            for(int j=0; j<plansza.getWys(); j++){
                if(tymczasowa.get(i,j)==true){
                    plansza.set(i,j,true);
                    this->planszaKlocka.set(i,j,true);
                }
            }
        }
    }
}

 // PRZESUWANIE CALKOWITE W DOL
void Klocek::przesunCalkiem(Plansza &plansza){

        while(!czyKoniecPlanszy(plansza)){
            this->przesun(plansza);
        }
}

void Klocek::rysuj(Plansza &plansza){
    for(int i=0; i<planszaKlocka.getSzer(); i++){
        for(int j=0; j<planszaKlocka.getWys(); j++){
            if(planszaKlocka.get(i,j)==true){
                if(plansza.ktoryGracz == 1)
                    al_draw_bitmap(this->kolor, 141+i*30, 51+j*30, 0);
                if(plansza.ktoryGracz == 2)
                    al_draw_bitmap(this->kolor, 1061+i*30, 51+j*30, 0);
            }
        }
    }
}


void Klocek::usunCaleWiersze(vector<int> &caleWiersze, Plansza &plansza){

        int licznik=0;
        int pelnyWiersz;

        for(int z=caleWiersze.size()-1; z>=0; z--){

            pelnyWiersz=caleWiersze[z]+licznik;

            for(int j=planszaKlocka.getWys()-1; j>=0; j--){
                for(int i=0; i<planszaKlocka.getSzer(); i++){
                    if(this->planszaKlocka.get(i,j)==true){
                        if(j==pelnyWiersz){
                            this -> planszaKlocka.set(i,j,false); plansza.set(i,j,false);
                        }
                        if(j<pelnyWiersz){
                            this -> planszaKlocka.set(i,j,false); plansza.set(i,j,false);
                            this -> planszaKlocka.set(i,j+1,true); plansza.set(i,j+1,true);
                        }
                    }
                }
            }
            licznik++;
        }
}

void Klocek::podniesPoziom(vector<int> &caleWiersze,Plansza &plansza){
        int ilePoziomow=caleWiersze.size();

        for(int j=0; j<planszaKlocka.getWys(); j++){
            for(int i=0; i<planszaKlocka.getSzer(); i++){
                if(planszaKlocka.get(i,j)==true){
                    if(j-ilePoziomow < 0)
                        return;
                    this -> planszaKlocka.set(i,j,false); plansza.set(i,j,false);
                    this -> planszaKlocka.set(i,j-ilePoziomow,true); plansza.set(i,j-ilePoziomow,true);
                }
            }
        }
}

// Klocek T:
//  #
// ###
Klocek_T::Klocek_T(ALLEGRO_BITMAP* kolor){
    this->kolor=kolor;
}

void Klocek_T::dodajNaPlansze(Plansza &plansza){
    this->planszaKlocka.set(4,0,true);
    this->planszaKlocka.set(3,1,true);
    this->planszaKlocka.set(4,1,true);
    this->planszaKlocka.set(5,1,true);

    plansza.set(4,0,true);
    plansza.set(3,1,true);
    plansza.set(4,1,true);
    plansza.set(5,1,true);
}

// Obracanie klocka T
void Klocek_T::obroc(Plansza &plansza){
    /* ksztalt:  1:      2:      3:      4:
                 #      #       ###      #
                ###     ##       #      ##
                        #                #
    */
    switch(this->ksztalt){
        case 1:
            for(int i=1; i<planszaKlocka.getSzer()-1; i++){
                for(int j=1; j<planszaKlocka.getWys()-1; j++){
                    if(planszaKlocka.get(i,j)==true){
                        // Jezeli srodek ciezkosci:
                        if(planszaKlocka.get(i-1,j)==true && planszaKlocka.get(i+1,j)==true && planszaKlocka.get(i,j-1)==true){
                            // i mozliwy obrot:
                            if(plansza.get(i,j+1)==false){
                                // obracanie
                                planszaKlocka.set(i-1,j,false); plansza.set(i-1,j,false);
                                planszaKlocka.set(i,j+1,true); plansza.set(i,j+1,true);
                                ksztalt=2;
                                return;
                            }
                        }
                    }
                }
            }
            break;
        case 2:
            for(int i=1; i<planszaKlocka.getSzer()-1; i++){
                for(int j=1; j<planszaKlocka.getWys()-1; j++){
                    if(planszaKlocka.get(i,j)==true){
                        // Jezeli srodek ciezkosci:
                        if(planszaKlocka.get(i+1,j)==true && planszaKlocka.get(i,j-1)==true && planszaKlocka.get(i,j+1)==true){
                            // i mozliwy obrot:
                            if(plansza.get(i-1,j)==false){
                                // obracanie
                                planszaKlocka.set(i,j-1,false); plansza.set(i,j-1,false);
                                planszaKlocka.set(i-1,j,true); plansza.set(i-1,j,true);
                                ksztalt=3;
                                return;
                            }
                        }
                    }
                }
            }
            break;
        case 3:
            for(int i=1; i<planszaKlocka.getSzer()-1; i++){
                for(int j=1; j<planszaKlocka.getWys()-1; j++){
                    if(planszaKlocka.get(i,j)==true){
                        // Jezeli srodek ciezkosci:
                        if(planszaKlocka.get(i-1,j)==true && planszaKlocka.get(i+1,j)==true && planszaKlocka.get(i,j+1)==true){
                            // i mozliwy obrot:
                            if(plansza.get(i,j-1)==false){
                                // obracanie
                                planszaKlocka.set(i+1,j,false); plansza.set(i+1,j,false);
                                planszaKlocka.set(i,j-1,true); plansza.set(i,j-1,true);
                                ksztalt=4;
                                return;
                            }
                        }
                    }
                }
            }
            break;
        default:
            for(int i=1; i<planszaKlocka.getSzer()-1; i++){
                for(int j=1; j<planszaKlocka.getWys()-1; j++){
                    if(planszaKlocka.get(i,j)==true){
                        // Jezeli srodek ciezkosci:
                        if(planszaKlocka.get(i-1,j)==true && planszaKlocka.get(i,j-1)==true && planszaKlocka.get(i,j+1)==true){
                            // i mozliwy obrot:
                            if(plansza.get(i+1,j)==false){
                                // obracanie
                                planszaKlocka.set(i,j+1,false); plansza.set(i,j+1,false);
                                planszaKlocka.set(i+1,j,true); plansza.set(i+1,j,true);
                                ksztalt=1;
                                return;
                            }
                        }
                    }
                }
            }
    }
}

void Klocek_T::rysujPodglad(Plansza &plansza){
    if(plansza.ktoryGracz==1){
        al_draw_bitmap(this->kolor, 640, 520, 0);
        al_draw_bitmap(this->kolor, 610, 550, 0);
        al_draw_bitmap(this->kolor, 640, 550, 0);
        al_draw_bitmap(this->kolor, 670, 550, 0);
    } else if(plansza.ktoryGracz==2){
        al_draw_bitmap(this->kolor, 860, 520, 0);
        al_draw_bitmap(this->kolor, 830, 550, 0);
        al_draw_bitmap(this->kolor, 860, 550, 0);
        al_draw_bitmap(this->kolor, 890, 550, 0);
    }
}

// Klocek O
//  ##
//  ##
Klocek_O::Klocek_O(ALLEGRO_BITMAP* kolor){
    this->kolor=kolor;
}

void Klocek_O::dodajNaPlansze(Plansza &plansza){
    this->planszaKlocka.set(4,0,true);
    this->planszaKlocka.set(5,0,true);
    this->planszaKlocka.set(4,1,true);
    this->planszaKlocka.set(5,1,true);

    plansza.set(4,0,true);
    plansza.set(5,0,true);
    plansza.set(4,1,true);
    plansza.set(5,1,true);
};

void Klocek_O::rysujPodglad(Plansza &plansza){
    if(plansza.ktoryGracz==1){
        al_draw_bitmap(this->kolor, 625, 520, 0);
        al_draw_bitmap(this->kolor, 625, 550, 0);
        al_draw_bitmap(this->kolor, 655, 520, 0);
        al_draw_bitmap(this->kolor, 655, 550, 0);
    } else if (plansza.ktoryGracz==2){
        al_draw_bitmap(this->kolor, 845, 520, 0);
        al_draw_bitmap(this->kolor, 845, 550, 0);
        al_draw_bitmap(this->kolor, 875, 520, 0);
        al_draw_bitmap(this->kolor, 875, 550, 0);

    }
}


// Klocek I
//  ####
//
Klocek_I::Klocek_I(ALLEGRO_BITMAP* kolor){
    this->kolor=kolor;
}

void Klocek_I::dodajNaPlansze(Plansza &plansza){
    this->planszaKlocka.set(3,0,true);
    this->planszaKlocka.set(4,0,true);
    this->planszaKlocka.set(5,0,true);
    this->planszaKlocka.set(6,0,true);

    plansza.set(3,0,true);
    plansza.set(4,0,true);
    plansza.set(5,0,true);
    plansza.set(6,0,true);
};

// Obracanie klocka I
void Klocek_I::obroc(Plansza &plansza){
    /* ksztalt:  1:      2:      3:      4:
                          #              #
                ####      #              #
                          #     ####     #
                          #              #
    */
    switch(this->ksztalt){
        case 1:
            for(int i=2; i<planszaKlocka.getSzer()-1; i++){
                for(int j=1; j<planszaKlocka.getWys()-2; j++){
                    if(planszaKlocka.get(i,j)==true){
                        // Jezeli srodek ciezkosci:
                        if(planszaKlocka.get(i-2,j)==true && planszaKlocka.get(i-1,j)==true && planszaKlocka.get(i+1,j)==true){
                            // i mozliwy obrot:
                            if(plansza.get(i,j-1)==false && plansza.get(i,j+1)==false && plansza.get(i,j+2)==false){
                                // obracanie
                                planszaKlocka.set(i-2,j,false); plansza.set(i-2,j,false);
                                planszaKlocka.set(i-1,j,false); plansza.set(i-1,j,false);
                                planszaKlocka.set(i+1,j,false); plansza.set(i+1,j,false);

                                planszaKlocka.set(i,j-1,true); plansza.set(i,j-1,true);
                                planszaKlocka.set(i,j+1,true); plansza.set(i,j+1,true);
                                planszaKlocka.set(i,j+2,true); plansza.set(i,j+2,true);
                                ksztalt=2;
                                return;
                            }
                        }
                    }
                }
            }
            break;
        case 2:
            for(int i=2; i<planszaKlocka.getSzer()-1; i++){
                for(int j=2; j<planszaKlocka.getWys()-1; j++){
                    if(planszaKlocka.get(i,j)==true){
                        // Jezeli srodek ciezkosci:
                        if(planszaKlocka.get(i,j-2)==true && planszaKlocka.get(i,j-1)==true && planszaKlocka.get(i,j+1)==true){
                            // i mozliwy obrot:
                            if(plansza.get(i-2,j)==false && plansza.get(i-1,j)==false && plansza.get(i+1,j)==false){
                                // obracanie
                                planszaKlocka.set(i,j-1,false); plansza.set(i,j-1,false);
                                planszaKlocka.set(i,j-2,false); plansza.set(i,j-2,false);
                                planszaKlocka.set(i,j+1,false); plansza.set(i,j+1,false);

                                planszaKlocka.set(i-2,j,true); plansza.set(i-2,j,true);
                                planszaKlocka.set(i-1,j,true); plansza.set(i-1,j,true);
                                planszaKlocka.set(i+1,j,true); plansza.set(i+1,j,true);
                                ksztalt=3;
                                return;
                            }
                        }
                    }
                }
            }
            break;
        case 3:
            for(int i=1; i<planszaKlocka.getSzer()-2; i++){
                for(int j=2; j<planszaKlocka.getWys()-1; j++){
                    if(planszaKlocka.get(i,j)==true){
                        // Jezeli srodek ciezkosci:
                       if(planszaKlocka.get(i-1,j)==true && planszaKlocka.get(i+1,j)==true && planszaKlocka.get(i+2,j)==true){
                            // i mozliwy obrot:
                            if(plansza.get(i,j-2)==false && plansza.get(i,j-1)==false && plansza.get(i,j+1)==false){
                                // obracanie
                                planszaKlocka.set(i-1,j,false); plansza.set(i-1,j,false);
                                planszaKlocka.set(i+1,j,false); plansza.set(i+1,j,false);
                                planszaKlocka.set(i+2,j,false); plansza.set(i+2,j,false);

                                planszaKlocka.set(i,j-1,true); plansza.set(i,j-1,true);
                                planszaKlocka.set(i,j+1,true); plansza.set(i,j+1,true);
                                planszaKlocka.set(i,j+2,true); plansza.set(i,j+2,true);
                                ksztalt=4;
                                return;
                            }
                        }
                    }
                }
            }
            break;
        default:
            for(int i=1; i<planszaKlocka.getSzer()-2; i++){
                for(int j=1; j<planszaKlocka.getWys()-2; j++){
                    if(planszaKlocka.get(i,j)==true){
                        // Jezeli srodek ciezkosci:
                        if(planszaKlocka.get(i,j-1)==true && planszaKlocka.get(i,j+1)==true && planszaKlocka.get(i,j+2)==true){
                            // i mozliwy obrot:
                            if(plansza.get(i-1,j)==false && plansza.get(i+1,j)==false && plansza.get(i+2,j)==false){
                                // obracanie
                                planszaKlocka.set(i,j-1,false); plansza.set(i,j-1,false);
                                planszaKlocka.set(i,j+1,false); plansza.set(i,j+1,false);
                                planszaKlocka.set(i,j+2,false); plansza.set(i,j+2,false);

                                planszaKlocka.set(i-1,j,true); plansza.set(i-1,j,true);
                                planszaKlocka.set(i+1,j,true); plansza.set(i+1,j,true);
                                planszaKlocka.set(i+2,j,true); plansza.set(i+2,j,true);
                                ksztalt=1;
                                return;
                            }
                        }
                    }
                }
            }
    }
}

void Klocek_I::rysujPodglad(Plansza &plansza){
    if (plansza.ktoryGracz==1){
        al_draw_bitmap(this->kolor, 595, 535, 0);
        al_draw_bitmap(this->kolor, 625, 535, 0);
        al_draw_bitmap(this->kolor, 655, 535, 0);
        al_draw_bitmap(this->kolor, 685, 535, 0);
    } else if (plansza.ktoryGracz==2){
        al_draw_bitmap(this->kolor, 815, 535, 0);
        al_draw_bitmap(this->kolor, 845, 535, 0);
        al_draw_bitmap(this->kolor, 875, 535, 0);
        al_draw_bitmap(this->kolor, 905, 535, 0);
    }
}


// Klocek S
//   ##
//  ##
Klocek_S::Klocek_S(ALLEGRO_BITMAP* kolor){
    this->kolor=kolor;
}

void Klocek_S::dodajNaPlansze(Plansza &plansza){
    this->planszaKlocka.set(4,0,true);
    this->planszaKlocka.set(5,0,true);
    this->planszaKlocka.set(3,1,true);
    this->planszaKlocka.set(4,1,true);

    plansza.set(4,0,true);
    plansza.set(5,0,true);
    plansza.set(3,1,true);
    plansza.set(4,1,true);
};

// Obracanie klocka S
void Klocek_S::obroc(Plansza &plansza){
    /* ksztalt:  1:      2:      3:       4:
                 ##       #              #
                ##        ##     ##      ##
                           #    ##        #
    */
    switch(this->ksztalt){
        case 1:
            for(int i=1; i<planszaKlocka.getSzer()-1; i++){
                for(int j=1; j<planszaKlocka.getWys()-1; j++){
                    if(planszaKlocka.get(i,j)==true){
                        // Jezeli srodek ciezkosci:
                        if( planszaKlocka.get(i,j-1)==true ){
                            // i mozliwy obrot:
                            if(plansza.get(i+1,j)==false && plansza.get(i+1,j+1)==false){
                                // obracanie
                                planszaKlocka.set(i-1,j,false); plansza.set(i-1,j,false);
                                planszaKlocka.set(i+1,j-1,false); plansza.set(i+1,j-1,false);

                                planszaKlocka.set(i+1,j,true); plansza.set(i+1,j,true);
                                planszaKlocka.set(i+1,j+1,true); plansza.set(i+1,j+1,true);
                                ksztalt=2;
                                return;
                            }
                        }
                    }
                }
            }
            break;
        case 2:
            for(int i=1; i<planszaKlocka.getSzer()-1; i++){
                for(int j=1; j<planszaKlocka.getWys()-1; j++){
                    if(planszaKlocka.get(i,j)==true){
                        // Jezeli srodek ciezkosci:
                        if(planszaKlocka.get(i+1,j)==true){
                            // i mozliwy obrot:
                            if(plansza.get(i-1,j+1)==false && plansza.get(i,j+1)==false){
                                // obracanie
                                planszaKlocka.set(i,j-1,false); plansza.set(i,j-1,false);
                                planszaKlocka.set(i+1,j+1,false); plansza.set(i+1,j+1,false);

                                planszaKlocka.set(i-1,j+1,true); plansza.set(i-1,j+1,true);
                                planszaKlocka.set(i,j+1,true); plansza.set(i,j+1,true);
                                ksztalt=3;
                                return;
                            }
                        }
                    }
                }
            }
            break;
        case 3:
            for(int i=1; i<planszaKlocka.getSzer()-1; i++){
                for(int j=1; j<planszaKlocka.getWys()-1; j++){
                    if(planszaKlocka.get(i,j)==true){
                        // Jezeli srodek ciezkosci:
                       if(planszaKlocka.get(i,j+1)==true){
                            // i mozliwy obrot:
                            if(plansza.get(i-1,j-1)==false && plansza.get(i-1,j)==false){
                                // obracanie
                                planszaKlocka.set(i-1,j+1,false); plansza.set(i-1,j+1,false);
                                planszaKlocka.set(i+1,j,false); plansza.set(i+1,j,false);

                                planszaKlocka.set(i-1,j-1,true); plansza.set(i-1,j-1,true);
                                planszaKlocka.set(i-1,j,true); plansza.set(i-1,j,true);
                                ksztalt=4;
                                return;
                            }
                        }
                    }
                }
            }
            break;
        default:
            for(int i=1; i<planszaKlocka.getSzer()-2; i++){
                for(int j=1; j<planszaKlocka.getWys()-2; j++){
                    if(planszaKlocka.get(i,j)==true){
                        // Jezeli srodek ciezkosci:
                        if(planszaKlocka.get(i-1,j)==true){
                            // i mozliwy obrot:
                            if(plansza.get(i,j-1)==false && plansza.get(i+1,j-1)==false){
                                // obracanie
                                planszaKlocka.set(i-1,j-1,false); plansza.set(i-1,j-1,false);
                                planszaKlocka.set(i,j+1,false); plansza.set(i,j+1,false);

                                planszaKlocka.set(i,j-1,true); plansza.set(i,j-1,true);
                                planszaKlocka.set(i+1,j-1,true); plansza.set(i+1,j-1,true);
                                ksztalt=1;
                                return;
                            }
                        }
                    }
                }
            }
    }
}

void Klocek_S::rysujPodglad(Plansza &plansza){
    if (plansza.ktoryGracz==1){
        al_draw_bitmap(this->kolor, 640, 520, 0);
        al_draw_bitmap(this->kolor, 670, 520, 0);
        al_draw_bitmap(this->kolor, 610, 550, 0);
        al_draw_bitmap(this->kolor, 640, 550, 0);
    } else if(plansza.ktoryGracz==2){
        al_draw_bitmap(this->kolor, 860, 520, 0);
        al_draw_bitmap(this->kolor, 890, 520, 0);
        al_draw_bitmap(this->kolor, 830, 550, 0);
        al_draw_bitmap(this->kolor, 860, 550, 0);
    }
}


// Klocek Z
//  ##
//   ##
Klocek_Z::Klocek_Z(ALLEGRO_BITMAP* kolor){
    this->kolor=kolor;
}

void Klocek_Z::dodajNaPlansze(Plansza &plansza){
    this->planszaKlocka.set(3,0,true);
    this->planszaKlocka.set(4,0,true);
    this->planszaKlocka.set(4,1,true);
    this->planszaKlocka.set(5,1,true);

    plansza.set(3,0,true);
    plansza.set(4,0,true);
    plansza.set(4,1,true);
    plansza.set(5,1,true);
};

// Obracanie klocka Z
void Klocek_Z::obroc(Plansza &plansza){
    /* ksztalt:  1:      2:      3:      4:
                ##        #              #
                 ##      ##     ##      ##
                         #       ##     #
    */
    switch(this->ksztalt){
        case 1:
            for(int i=1; i<planszaKlocka.getSzer()-1; i++){
                for(int j=1; j<planszaKlocka.getWys()-1; j++){
                    if(planszaKlocka.get(i,j)==true){
                        // Jezeli srodek ciezkosci:
                        if( planszaKlocka.get(i,j-1)==true ){
                            // i mozliwy obrot:
                            if(plansza.get(i+1,j-1)==false && plansza.get(i,j+1)==false){
                                // obracanie
                                planszaKlocka.set(i-1,j-1,false); plansza.set(i-1,j-1,false);
                                planszaKlocka.set(i,j-1,false); plansza.set(i,j-1,false);

                                planszaKlocka.set(i+1,j-1,true); plansza.set(i+1,j-1,true);
                                planszaKlocka.set(i,j+1,true); plansza.set(i,j+1,true);
                                ksztalt=2;
                                return;
                            }
                        }
                    }
                }
            }
            break;
        case 2:
            for(int i=1; i<planszaKlocka.getSzer()-1; i++){
                for(int j=1; j<planszaKlocka.getWys()-1; j++){
                    if(planszaKlocka.get(i,j)==true){
                        // Jezeli srodek ciezkosci:
                        if(planszaKlocka.get(i+1,j)==true){
                            // i mozliwy obrot:
                            if(plansza.get(i-1,j)==false && plansza.get(i+1,j+1)==false){
                                // obracanie
                                planszaKlocka.set(i+1,j-1,false); plansza.set(i+1,j-1,false);
                                planszaKlocka.set(i+1,j,false); plansza.set(i+1,j,false);

                                planszaKlocka.set(i-1,j,true); plansza.set(i-1,j,true);
                                planszaKlocka.set(i+1,j+1,true); plansza.set(i+1,j+1,true);
                                ksztalt=3;
                                return;
                            }
                        }
                    }
                }
            }
            break;
        case 3:
            for(int i=1; i<planszaKlocka.getSzer()-1; i++){
                for(int j=1; j<planszaKlocka.getWys()-1; j++){
                    if(planszaKlocka.get(i,j)==true){
                        // Jezeli srodek ciezkosci:
                       if(planszaKlocka.get(i,j+1)==true){
                            // i mozliwy obrot:
                            if(plansza.get(i,j-1)==false && plansza.get(i-1,j+1)==false){
                                // obracanie
                                planszaKlocka.set(i,j+1,false); plansza.set(i,j+1,false);
                                planszaKlocka.set(i+1,j+1,false); plansza.set(i+1,j+1,false);

                                planszaKlocka.set(i,j-1,true); plansza.set(i,j-1,true);
                                planszaKlocka.set(i-1,j+1,true); plansza.set(i-1,j+1,true);
                                ksztalt=4;
                                return;
                            }
                        }
                    }
                }
            }
            break;
        default:
            for(int i=1; i<planszaKlocka.getSzer()-1; i++){
                for(int j=1; j<planszaKlocka.getWys()-1; j++){
                    if(planszaKlocka.get(i,j)==true){
                        // Jezeli srodek ciezkosci:
                        if(planszaKlocka.get(i-1,j)==true){
                            // i mozliwy obrót:
                            if(plansza.get(i-1,j-1)==false && plansza.get(i+1,j)==false){
                                // obracanie
                                planszaKlocka.set(i-1,j,false); plansza.set(i-1,j,false);
                                planszaKlocka.set(i-1,j+1,false); plansza.set(i-1,j+1,false);

                                planszaKlocka.set(i-1,j-1,true); plansza.set(i-1,j-1,true);
                                planszaKlocka.set(i+1,j,true); plansza.set(i+1,j,true);
                                ksztalt=1;
                                return;
                            }
                        }
                    }
                }
            }
    }
}

void Klocek_Z::rysujPodglad(Plansza &plansza){
    if(plansza.ktoryGracz==1){
        al_draw_bitmap(this->kolor, 610, 520, 0);
        al_draw_bitmap(this->kolor, 640, 520, 0);
        al_draw_bitmap(this->kolor, 640, 550, 0);
        al_draw_bitmap(this->kolor, 670, 550, 0);
    } else if(plansza.ktoryGracz==2){
        al_draw_bitmap(this->kolor, 830, 520, 0);
        al_draw_bitmap(this->kolor, 860, 520, 0);
        al_draw_bitmap(this->kolor, 860, 550, 0);
        al_draw_bitmap(this->kolor, 890, 550, 0);
    }
}

// Klocek L
//    #
//  ###
Klocek_L::Klocek_L(ALLEGRO_BITMAP* kolor){
    this->kolor=kolor;
}

void Klocek_L::dodajNaPlansze(Plansza &plansza){
    this->planszaKlocka.set(3,1,true);
    this->planszaKlocka.set(4,1,true);
    this->planszaKlocka.set(5,1,true);
    this->planszaKlocka.set(5,0,true);

    plansza.set(3,1,true);
    plansza.set(4,1,true);
    plansza.set(5,1,true);
    plansza.set(5,0,true);
};

// Obracanie klocka L
void Klocek_L::obroc(Plansza &plansza){
    /* ksztalt:  1:      2:      3:      4:
                   #      #             ##
                 ###      #     ###      #
                          ##    #        #
    */
    switch(this->ksztalt){
        case 1:
            for(int i=1; i<planszaKlocka.getSzer()-1; i++){
                for(int j=1; j<planszaKlocka.getWys()-1; j++){
                    if(planszaKlocka.get(i,j)==true){
                        // Jezeli srodek ciezkosci:
                        if(planszaKlocka.get(i-1,j)==true && planszaKlocka.get(i+1,j)==true){
                            // i mozliwy obrot:
                            if(plansza.get(i,j-1)==false && plansza.get(i,j+1)==false && plansza.get(i+1,j+1)==false){
                                // obracanie
                                planszaKlocka.set(i-1,j,false); plansza.set(i-1,j,false);
                                planszaKlocka.set(i+1,j,false); plansza.set(i+1,j,false);
                                planszaKlocka.set(i+1,j-1,false); plansza.set(i+1,j-1,false);

                                planszaKlocka.set(i,j-1,true); plansza.set(i,j-1,true);
                                planszaKlocka.set(i,j+1,true); plansza.set(i,j+1,true);
                                planszaKlocka.set(i+1,j+1,true); plansza.set(i+1,j+1,true);
                                ksztalt=2;
                                return;
                            }
                        }
                    }
                }
            }
            break;
        case 2:
            for(int i=1; i<planszaKlocka.getSzer()-1; i++){
                for(int j=1; j<planszaKlocka.getWys()-1; j++){
                    if(planszaKlocka.get(i,j)==true){
                        // Jezeli srodek ciezkosci:
                        if(planszaKlocka.get(i,j-1)==true && planszaKlocka.get(i,j+1)==true){
                            // i mozliwy obrot:
                            if(plansza.get(i-1,j)==false && plansza.get(i-1,j+1)==false && plansza.get(i+1,j)==false){
                                // obracanie
                                planszaKlocka.set(i,j-1,false); plansza.set(i,j-1,false);
                                planszaKlocka.set(i,j+1,false); plansza.set(i,j+1,false);
                                planszaKlocka.set(i+1,j+1,false); plansza.set(i+1,j+1,false);

                                planszaKlocka.set(i-1,j,true); plansza.set(i-1,j,true);
                                planszaKlocka.set(i-1,j+1,true); plansza.set(i-1,j+1,true);
                                planszaKlocka.set(i+1,j,true); plansza.set(i+1,j,true);
                                ksztalt=3;
                                return;
                            }
                        }
                    }
                }
            }
            break;
        case 3:
            for(int i=1; i<planszaKlocka.getSzer()-1; i++){
                for(int j=1; j<planszaKlocka.getWys()-1; j++){
                    if(planszaKlocka.get(i,j)==true){
                        // Jezeli srodek ciezkosci:
                       if(planszaKlocka.get(i-1,j)==true && planszaKlocka.get(i+1,j)==true){
                            // i mozliwy obrot:
                            if(plansza.get(i-1,j-1)==false && plansza.get(i,j-1)==false && plansza.get(i,j+1)==false){
                                // obracanie
                                planszaKlocka.set(i-1,j,false); plansza.set(i-1,j,false);
                                planszaKlocka.set(i-1,j+1,false); plansza.set(i-1,j+1,false);
                                planszaKlocka.set(i+1,j,false); plansza.set(i+1,j,false);

                                planszaKlocka.set(i-1,j-1,true); plansza.set(i-1,j-1,true);
                                planszaKlocka.set(i,j-1,true); plansza.set(i,j-1,true);
                                planszaKlocka.set(i,j+1,true); plansza.set(i,j+1,true);
                                ksztalt=4;
                                return;
                            }
                        }
                    }
                }
            }
            break;
        default:
            for(int i=1; i<planszaKlocka.getSzer()-1; i++){
                for(int j=1; j<planszaKlocka.getWys()-1; j++){
                    if(planszaKlocka.get(i,j)==true){
                        // Jezeli srodek ciezkosci:
                        if(planszaKlocka.get(i,j-1)==true && planszaKlocka.get(i,j+1)==true){
                            // i mozliwy obrot:
                            if(plansza.get(i-1,j)==false && plansza.get(i+1,j)==false && plansza.get(i+1,j-1)==false){
                                // obracanie
                                planszaKlocka.set(i-1,j-1,false); plansza.set(i-1,j-1,false);
                                planszaKlocka.set(i,j-1,false); plansza.set(i,j-1,false);
                                planszaKlocka.set(i,j+1,false); plansza.set(i,j+1,false);

                                planszaKlocka.set(i-1,j,true); plansza.set(i-1,j,true);
                                planszaKlocka.set(i+1,j,true); plansza.set(i+1,j,true);
                                planszaKlocka.set(i+1,j-1,true); plansza.set(i+1,j-1,true);
                                ksztalt=1;
                                return;
                            }
                        }
                    }
                }
            }
    }
}

void Klocek_L::rysujPodglad(Plansza &plansza){
    if(plansza.ktoryGracz==1){
        al_draw_bitmap(this->kolor, 610, 550, 0);
        al_draw_bitmap(this->kolor, 640, 550, 0);
        al_draw_bitmap(this->kolor, 670, 550, 0);
        al_draw_bitmap(this->kolor, 670, 520, 0);
    } else if(plansza.ktoryGracz==2){
        al_draw_bitmap(this->kolor, 830, 550, 0);
        al_draw_bitmap(this->kolor, 860, 550, 0);
        al_draw_bitmap(this->kolor, 890, 550, 0);
        al_draw_bitmap(this->kolor, 890, 520, 0);
    }
}

// Klocek J
//  #
//  ###
Klocek_J::Klocek_J(ALLEGRO_BITMAP* kolor){
    this->kolor=kolor;
}

void Klocek_J::dodajNaPlansze(Plansza &plansza){
    this->planszaKlocka.set(3,0,true);
    this->planszaKlocka.set(3,1,true);
    this->planszaKlocka.set(4,1,true);
    this->planszaKlocka.set(5,1,true);

    plansza.set(3,0,true);
    plansza.set(3,1,true);
    plansza.set(4,1,true);
    plansza.set(5,1,true);

};

// Obracanie klocka J
void Klocek_J::obroc(Plansza &plansza){
    /* ksztalt:  1:      2:      3:      4:
                #        ##              #
                ###      #      ###      #
                         #        #     ##
    */
    switch(this->ksztalt){
        case 1:
            for(int i=1; i<planszaKlocka.getSzer()-1; i++){
                for(int j=1; j<planszaKlocka.getWys()-1; j++){
                    if(planszaKlocka.get(i,j)==true){
                        // Jezeli srodek ciezkosci:
                        if(planszaKlocka.get(i-1,j)==true && planszaKlocka.get(i+1,j)==true){
                            // i mozliwy obrot:
                            if(plansza.get(i,j-1)==false && plansza.get(i,j+1)==false && plansza.get(i+1,j-1)==false){
                                // obracanie
                                planszaKlocka.set(i-1,j-1,false); plansza.set(i-1,j-1,false);
                                planszaKlocka.set(i-1,j,false); plansza.set(i-1,j,false);
                                planszaKlocka.set(i+1,j,false); plansza.set(i+1,j,false);

                                planszaKlocka.set(i,j-1,true); plansza.set(i,j-1,true);
                                planszaKlocka.set(i,j+1,true); plansza.set(i,j+1,true);
                                planszaKlocka.set(i+1,j-1,true); plansza.set(i+1,j-1,true);
                                ksztalt=2;
                                return;
                            }
                        }
                    }
                }
            }
            break;
        case 2:
            for(int i=1; i<planszaKlocka.getSzer()-1; i++){
                for(int j=1; j<planszaKlocka.getWys()-1; j++){
                    if(planszaKlocka.get(i,j)==true){
                        // Jezeli srodek ciezkosci:
                        if(planszaKlocka.get(i,j-1)==true && planszaKlocka.get(i,j+1)==true){
                            // i mozliwy obrot:
                            if(plansza.get(i-1,j)==false && plansza.get(i+1,j)==false && plansza.get(i+1,j+1)==false){
                                // obracanie
                                planszaKlocka.set(i,j-1,false); plansza.set(i,j-1,false);
                                planszaKlocka.set(i+1,j-1,false); plansza.set(i+1,j-1,false);
                                planszaKlocka.set(i,j+1,false); plansza.set(i,j+1,false);

                                planszaKlocka.set(i-1,j,true); plansza.set(i-1,j,true);
                                planszaKlocka.set(i+1,j,true); plansza.set(i+1,j,true);
                                planszaKlocka.set(i+1,j+1,true); plansza.set(i+1,j+1,true);
                                ksztalt=3;
                                return;
                            }
                        }
                    }
                }
            }
            break;
        case 3:
            for(int i=1; i<planszaKlocka.getSzer()-1; i++){
                for(int j=1; j<planszaKlocka.getWys()-1; j++){
                    if(planszaKlocka.get(i,j)==true){
                        // Jezeli srodek ciezkosci:
                       if(planszaKlocka.get(i-1,j)==true && planszaKlocka.get(i+1,j)==true){
                            // i mozliwy obrot:
                            if(plansza.get(i-1,j+1)==false && plansza.get(i,j-1)==false && plansza.get(i,j+1)==false){
                                // obracanie
                                planszaKlocka.set(i-1,j,false); plansza.set(i-1,j,false);
                                planszaKlocka.set(i+1,j,false); plansza.set(i+1,j,false);
                                planszaKlocka.set(i+1,j+1,false); plansza.set(i+1,j+1,false);

                                planszaKlocka.set(i-1,j+1,true); plansza.set(i-1,j+1,true);
                                planszaKlocka.set(i,j-1,true); plansza.set(i,j-1,true);
                                planszaKlocka.set(i,j+1,true); plansza.set(i,j+1,true);
                                ksztalt=4;
                                return;
                            }
                        }
                    }
                }
            }
            break;
        default:
            for(int i=1; i<planszaKlocka.getSzer()-1; i++){
                for(int j=1; j<planszaKlocka.getWys()-1; j++){
                    if(planszaKlocka.get(i,j)==true){
                        // Jezeli srodek ciezkosci:
                        if(planszaKlocka.get(i,j-1)==true && planszaKlocka.get(i,j+1)==true){
                            // i mozliwy obrot:
                            if(plansza.get(i-1,j-1)==false && plansza.get(i-1,j)==false && plansza.get(i+1,j)==false){
                                // obracanie
                                planszaKlocka.set(i-1,j+1,false); plansza.set(i-1,j+1,false);
                                planszaKlocka.set(i,j-1,false); plansza.set(i,j-1,false);
                                planszaKlocka.set(i,j+1,false); plansza.set(i,j+1,false);

                                planszaKlocka.set(i-1,j-1,true); plansza.set(i-1,j-1,true);
                                planszaKlocka.set(i-1,j,true); plansza.set(i-1,j,true);
                                planszaKlocka.set(i+1,j,true); plansza.set(i+1,j,true);
                                ksztalt=1;
                                return;
                            }
                        }
                    }
                }
            }
    }
}

void Klocek_J::rysujPodglad(Plansza &plansza){
    if(plansza.ktoryGracz==1){
        al_draw_bitmap(this->kolor, 610, 520, 0);
        al_draw_bitmap(this->kolor, 610, 550, 0);
        al_draw_bitmap(this->kolor, 640, 550, 0);
        al_draw_bitmap(this->kolor, 670, 550, 0);
    } else if(plansza.ktoryGracz==2){
        al_draw_bitmap(this->kolor, 830, 520, 0);
        al_draw_bitmap(this->kolor, 830, 550, 0);
        al_draw_bitmap(this->kolor, 860, 550, 0);
        al_draw_bitmap(this->kolor, 890, 550, 0);
    }
}
