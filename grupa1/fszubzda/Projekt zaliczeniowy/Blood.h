#pragma once

#include "GameObject.h"

class Blood: public GameObject{

public:
    Blood(float x, float y, ALLEGRO_BITMAP *image);
    void Destroy();

    void Update();
    void Render();
};
