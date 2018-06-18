#pragma once

#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "Globals.h"

class GameObject{
    int ID;
    bool alive;
    bool collidable;

protected:
    float x;
    float y;

    float survX;
    float survY;

    float velX; //velocity - prędkość
    float velY;

    float gunX;
    float gunY;

    int dirX;
    int dirY;

    int boundX;
    int boundY;

    int maxFrame;
    int curFrame;
    int frameCount;
    int frameDelay;
    int frameWidth;
    int frameHeight;
    int animationColumns;
    int animationDirection;

    ALLEGRO_BITMAP *image;

public:
    GameObject(); //konstruktor
    void virtual Destroy(); //destruktor - nie do końca

    void Init(float x, float y, float survX, float survY, float velX, float velY, int dirX, int dirY, int boundX, int boundY);
    void virtual Update();
    void virtual Render();

    float GetX(){return x;}
    float GetY(){return y;}

    void SetX(float x){GameObject::x = x;} // zadziała jak float _x {x=_x;}
    void SetY(float y){GameObject::y = y;}

    float SetSurvX(float survX){GameObject::survX=survX;}
    float SetSurvY(float survY){GameObject::survY=survY;}

    float SetGunX(float gunX){GameObject::gunX=gunX;}
    float SetGunY(float gunY){GameObject::gunY=gunY;}

    int GetBoundX() {return boundX;}
    int GetBoundY() {return boundY;}

    int GetID() {return ID;}
    void SetID(int ID){GameObject::ID = ID;}

    bool GetAlive() {return alive;}
    void SetAlive(bool alive) {GameObject::alive = alive;}

    bool GetCollidable(){return collidable;}
    void SetCollidable(bool collidable) {GameObject::collidable = collidable;}

    bool CheckCollisions(GameObject *otherObject); //sprawdza czy obiekty ze sobą kolidują
    void virtual Collided(int objectID); // sprawdzamy z czym koliduje -> żeby wiedzieć jak zadziałać w konkretnym przypadku
    bool Collidable(); //połączenie getalive, getcollidable -> sprawdza tez czy obiekt w ogóle żyje(a nie tylko na podstawie 'collidable'

};
