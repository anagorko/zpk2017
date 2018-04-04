#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include <iostream>
using namespace std;

class Display
{
    ALLEGRO_DISPLAY *display = NULL;

    const int w = 800;
    const int h = 600;
    
public:
    void init();    // inicjalizuje (otwiera) okienko
    void close();   // zamyka okienko
    void show();    // wyświetla zawartość okienka
    
    void drawPoint(double, double);
    void drawLine(double, double, double, double);
    void clear();   // wyciera zawartość okienka
};

void Display::clear()
{
    al_clear_to_color(al_map_rgb(0,0,0));  
}

void Display::init()
{
    if(!al_init()) {
        cerr << "Błąd podczas inicjalizacji allegro." << endl;
        assert(false);
    }
  
    if (!al_init_primitives_addon()) {
        cerr << "Błąd podczas inicjalizacji dodatku 'primitives'." << endl;
        assert(false);
    }

    display = al_create_display(w, h);

    if(!display) {
        cerr << "Błąd podczas inicjalizacji ekranu." << endl;
        assert(false);
    }
    
    clear(); show();
}

void Display::show()
{
    al_flip_display();
}

void Display::drawPoint(double x, double y)
{
    al_draw_filled_circle(x+w/2,y+h/2,2, al_map_rgb(255,255,255));
}

void Display::drawLine(double x1, double y1, double x2, double y2)
{
    al_draw_line(x1+w/2, y1+h/2, x2+w/2, y2+h/2, al_map_rgb( 255, 255, 255), 2);    
}
