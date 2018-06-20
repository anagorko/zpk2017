#pragma once

#include "GameObject.h"

class Survivor : public GameObject{
    float lives;
    int score;
    int animationRow;

public:
    Survivor();
    void Destroy();

    void Init(ALLEGRO_BITMAP *image = NULL); //jest obrazek to jest, jak nie ma to nic się nie stanie dzięki =NULL
    void Update();
    void Render();

    void MoveUp();
    void MoveDown();
    void MoveLeft();
    void MoveRight();

    void ResetAnimation (int position);

    int GetLives() {return lives;}
    int GetScore() {return score;}

    void LoseLife() {lives-=1;}
    void AddPoint() {score++;}

    void Collided(int objectID);
};
