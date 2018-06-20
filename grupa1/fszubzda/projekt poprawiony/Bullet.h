#pragma once

#include "GameObject.h"

class Bullet : public GameObject{
    void (*ScorePoint)(void);
public:
    Bullet(float x, float y, float gunX, float gunY, void(*ScorePoint)(void));
    void Destroy();

    void Update();
    void Render();

    void Collided(int objectID);
};
