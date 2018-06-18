#include "Zombie.h"

Zombie::Zombie(float x, float y, int dirX, ALLEGRO_BITMAP *image, void (*TakeLife)(void)){
    GameObject::Init(x,y,0,0,0.05,0.05,-1,0,35,35);
    Zombie::dirX = dirX;


    SetID(ENEMY);


    maxFrame = 12;
    curFrame = 0;
    frameCount = 0;
    frameDelay = 5;//im mniejsze tym szybciej animacja
    frameWidth = 33;
    frameHeight = 70;
    animationColumns = 3;
    animationDirection=-1;

/*
    if(rand()%2) //różna rotacja zombiaków
        animationDirection = 1;
    else
        animationDirection = -1;
*/
    Zombie::image = image;

    Zombie::TakeLife = TakeLife;
    // lub Comet::TakeLife=&TakeLife;
}

void Zombie::Destroy(){
    GameObject::Destroy();
}

void Zombie::Update(){
    GameObject::Update();
/*
    dirX = (survX - x) / 10;
    dirY = (survY - y) / 10;

    x += velX * dirX;
    y += velY * dirY;

*/
     if(y < 200)
        y = 200;

//trzeba ogarnąć dokładne działanie tego:
   if(++frameCount >= frameDelay){
        curFrame += animationDirection;
        if(curFrame >= maxFrame)
            curFrame = 0;
        else if(curFrame <= 0)
            curFrame = maxFrame;

        frameCount=0;
    }

    if(x+frameWidth<0)
        Collided(BORDER);

//curFrame = 1;
}
void Zombie::Render(){
    GameObject::Render();

    //int fx = (curFrame % animationColumns) * frameWidth;  //tutaj właśnie sterujemy kolumną, a poniżej wierszem - jeżeli mam w moim png jeden wiersz, to fy = 1 po prostu. jeżeli więcej to ->formuła. tutaj next wiersz to całe frameHeight trzeba dodać.
    //int fy = (curFrame / animationColumns) * frameHeight;

    //int fx = 1;
    //int fy = 71;
    int fx, fy;

   if(survX > x-150 && survX < x+150  && survY > y ){
        fx = (curFrame % animationColumns) * frameWidth;
        fy = 1;
    }
    else if(survX > x-150 && survX < x+150  && survY < y ){
        fx = (curFrame % animationColumns) * frameWidth;
        fy = 221;
    }
    else if(survX < x ){
        fx = (curFrame % animationColumns) * frameWidth;
        fy = 71;
    }
    else if (survX > x ){
        fx = (curFrame % animationColumns) * frameWidth;
        fy = 142;
    }

    al_draw_bitmap_region(image,fx,fy,frameWidth,frameHeight, x - frameWidth/2, y-frameHeight/2,0);
}


void Zombie::Collided(int objectID){
    if(objectID==BORDER){
        TakeLife();
    }

    if(objectID == BULLET) //zamiana enemy na bullet** jak się zderzy z czyms co nie jest zombie, niszczę to. tutaj raczej nie powinno się tak robić bo przeciez my musimy to ZABIĆ zeby przestalo nas jesc.
        SetAlive(false);
}
