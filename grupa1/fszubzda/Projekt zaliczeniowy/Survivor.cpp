
#include "Survivor.h"

Survivor::Survivor(){
}
void Survivor::Destroy(){
    GameObject::Destroy();
}

void Survivor::Init(ALLEGRO_BITMAP *image){

    GameObject::Init(20,100,0,0,6,6,0,0,10,12); //arbitralne wartości startowe.

    SetID(PLAYER);
    SetAlive(true);

    lives = 3;
    score = 0;

    maxFrame = 3;
    curFrame = 0;
    frameWidth = 32;
    frameHeight = 50;
    animationColumns = 4;
    animationDirection = 1;

    animationRow = 0;

    if(image != NULL)
        Survivor::image=image;
}

void Survivor::Update(){
    GameObject::Update();

    if(x < 0)
        x = 0;
    else if(x > WIDTH)
        x = WIDTH;

    if(y < 200)
        y = 200;
    else if(y > HEIGHT)
        y = HEIGHT;
}

void Survivor::Render(){
    GameObject::Render();

    int fx = (curFrame % animationColumns) * frameWidth;
    int fy = animationRow * frameHeight;

    al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight, x -frameWidth / 2 , y - frameHeight/2,0);
}
// currentFrame, direction
void Survivor::MoveUp(){
    animationRow=3;
    dirY=-1;
}

void Survivor::MoveDown(){
    animationRow=0;
    dirY=1;
}
void Survivor::MoveLeft(){
    animationRow=1;
    curFrame = 1;
    dirX = -1;
}
void Survivor::MoveRight(){
    animationRow=2;
    curFrame=1;
    dirX=1;
}

void Survivor::ResetAnimation (int position){
    if(position==1){
        animationRow=0;
        dirY=0;
    }
    else{
        curFrame=0;
        dirX=0;
    }
}
//co gdy ktoś w nas uderzy?
void Survivor::Collide(int objectID){
    if(objectID == ENEMY)
        lives--;//tracę życie.
}
