#pragma once

#include "GameObject.h"

class Zombie : public GameObject{ //dziedziczę z GameObject;
        void (*TakeLife)(void);
public:
        Zombie(float x, float y, int dirX, ALLEGRO_BITMAP *image, void (*TakeLife)(void)); // i ostatni element bedzie czytany z maina
        void Destroy();

        void Update();
        void Render();

        void Collided(int objectID);
};
