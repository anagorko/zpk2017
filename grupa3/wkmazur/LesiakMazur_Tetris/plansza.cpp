
#include "plansza.h"
#include "klocek.h"
#include <iostream>
using namespace std;

Plansza::Plansza(){
        this->przygotuj_plansze();
    }

void Plansza::przygotuj_plansze(){
        for(int i=0; i<this->getSzer(); i++){
            for(int j=0; j<this->getWys(); j++){
                this->set(i,j,false);
            }
        }
    }

bool Plansza::czyKoniecGry(){
        int licznik=0;
        for(int j=this->getWys()-1; j>=0; j--){
            for(int i=0; i<this->getSzer(); i++){
                if(this->pole[i][j]==true){
                    licznik++;
                    break;
                }
            }
        }
        cout << licznik;
        if(licznik>=20 && (get(3,2)==true || get(4,2)==true || get(5,2)==true || get(6,2)==true))
            return true;
        else
            return false;
}

void Plansza::set(int x, int y, bool value){
        this->pole[x][y]=value;
    }

bool Plansza::get(int x, int y){
        return this -> pole[x][y];
    }

int Plansza::getSzer(){
        return this -> szer;
    }

int Plansza::getWys(){
        return this -> wys;
    }

vector<int> Plansza::caleWiersze(int podniesionePoziomy){
        vector<int> caleWiersze;
        for(int j=0; j< this->wys-podniesionePoziomy; j++){
            for(int i=0; i< this->szer; i++){
                if(this -> get(i,j)==false){
                    break;
                }
                if(i==9 && this -> get(i,j)==true)
                    caleWiersze.push_back(j);
            }
        }
        return caleWiersze;
}

void Plansza::usunCaleWiersze(Klocek* klocek){
        for(int i=0; i < szer; i++){
            for(int j=0; j< wys; j++){
                if(klocek->get(i,j)==true){
                    this->set(i,j,true);
                }
            }
        }
}

void Plansza::podniesPoziom(Klocek* klocek, int podniesionePoziomy){
        for(int i=0; i < szer; i++){
            for(int j=0; j< wys; j++){
                if(klocek->get(i,j)==true){
                    this->set(i,j,true);
                }
            }
        }

        int ilePoziomow=podniesionePoziomy;
        for(int j=wys-1; j > wys-1-ilePoziomow; j--){
            for(int i=0; i < szer; i++){
                this->set(i,j,true);
            }
        }
}

void Plansza::rysujSzary(ALLEGRO_BITMAP* kolor){
        for(int i=0; i<szer;i++){
            for(int j=0; j<wys; j++){
                if(this->get(i,j)==true){
                    if(ktoryGracz==1)
                        al_draw_bitmap(kolor, 141+i*30, 51+j*30, 0);
                    if(ktoryGracz==2)
                        al_draw_bitmap(kolor, 1061+i*30, 51+j*30, 0);
                }
            }
        }
}
