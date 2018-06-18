
#include "Blood.h"

Blood::Blood(float x, float y, ALLEGRO_BITMAP *image){
    GameObject::Init(x,y,0,0,0,0,0,0,0,0);

    SetID(MISC);//miscellaneous
    SetCollidable(false);

    maxFrame = 1;
    curFrame = 0;
    frameCount = 0;
    frameDelay = 100;
    frameWidth = 33;
    frameHeight = 35;
    animationColumns = 1;
    animationDirection = 1;

    Blood::image = image;
}

void Blood::Destroy(){
    GameObject::Destroy();
}

void Blood::Update(){
    //prawie to samo co w zombie
    GameObject::Update();

    if(++frameCount>=frameDelay){
        curFrame+=animationDirection;
        if(curFrame>=maxFrame)
            SetAlive(false);

        frameCount=0;
    }
}

void Blood::Render(){
    //to samo co w zombie
    GameObject::Render();

    //int fx = (curFrame % animationColumns) * frameWidth;
    //int fy = (curFrame / animationColumns) * frameWidth;
    int fx=1;
    int fy=1;
    al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight, x -frameWidth / 2 , y - frameHeight/2,0);
}
