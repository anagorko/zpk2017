#include "Bullet.h"
#include <cmath>

//do konstruktora tutaj dodałem gunX i gunY. tak samo w mainie. w gameobject dodałem zmienne gunX i gunY
Bullet::Bullet(float x, float y, float gunX, float gunY, void(*ScorePoint)(void)){
    GameObject::Init(x,y,0,0,10,10,gunX-x,gunY-y,0,0);

    /*jeżeli strzelam w prawo to inne wsp. początkowe x i y - dopisać!*/

    SetID(BULLET);

    Bullet::ScorePoint = ScorePoint;
}

void Bullet::Destroy(){
    GameObject::Destroy();
}

void Bullet::Update(){
   /*GameObject::Update();
    x += velX * dirX;
    y += velY * dirY;
   */
    float directionx = dirX;//gunX - x;
    float directiony = dirY;//gunY - y;

    float vLength = pow( pow(directionx,2)+ pow(directiony,2) , 0.5);

    float vUnitX = directionx/vLength;
    float vUnitY = directiony/vLength;

    x += velX * vUnitX;
    y += velY * vUnitY;

    if(x>WIDTH || x<0 || y>HEIGHT || y<0)
        Collided(BORDER);
}
void Bullet::Render(){
    al_draw_filled_circle(x,y,2,al_map_rgb(255,255,255));
}

void Bullet::Collided(int objectID){
    if(objectID == ENEMY || objectID == BORDER)
        SetAlive(false);

    if(objectID==ENEMY) //gdy zderzamy z przeciwnikiem --> +1 punkt
        ScorePoint();
}
