#include "GameObject.h"

//konstruktor - domyślnie ustawiam 0 bo to na razie bez różnicy.
GameObject::GameObject(){
    x=0;
    y=0;

    survX=0;
    survY=0;

    velX=0;
    velY=0;

    dirX=0;
    dirY=0;

    gunX = 0;
    gunY = 0;

    boundX=0;
    boundY=0;


    maxFrame=0;
    curFrame=0;
    frameCount=0;
    frameDelay=0;
    frameWidth=0;
    animationColumns=0;
    animationDirection=0;

    image=NULL;

    alive=true;
    collidable=true;
}

//(jakby destruktor) jeżeli jest obrazek -> zniszcz. każdy obiekt będzie mógł sam po sobie sprzątać.
void GameObject::Destroy(){
    if(!image)
       al_destroy_bitmap(image);

    image=NULL;// setting image to NULL afterwards isn't even needed, but it's good practice﻿
}

void GameObject::Init(float x, float y, float survX, float survY, float velX, float velY, int dirX, int dirY, int boundX, int boundY){
    GameObject::x = x;
    GameObject::y = y;

    GameObject::velX=velX;
    GameObject::velY=velY;

    GameObject::dirX=dirX;
    GameObject::dirY=dirY;

    GameObject::boundX=boundX;
    GameObject::boundY=boundY;
}

//
void GameObject::Update(){
    x += velX * dirX;
    y += velY * dirY;
}

// na razie nie uzupełniam bo każdy obiekt będzie to robić inaczej. virtual się chyba przyda wlasnie tu;
void GameObject::Render(){
}

bool GameObject::CheckCollisions(GameObject *otherObject){
    float oX = otherObject->GetX();
    float oY = otherObject->GetY();

    int obX = otherObject->GetBoundX();
    int obY = otherObject->GetBoundY();

    if( x + boundX > oX - obX &&
        x - boundX < oX + obX &&
        y + boundY > oY - obY &&
        y - boundY < oY + obY)
        return true;
    else
        return false;
}

//na razie zostawiam, kolizje z różnymi obiektami mają być różne dla obiektów; istnieje zeby być virtual funkcją.
void GameObject::Collided(int objectID){
}

bool GameObject::Collidable(){
    return alive && collidable; //true tylko gdy jest alive i collidable  (obie=true)
}









