#include <iostream>
using namespace std;

#include <allegro5/allegro.h>

int main(int, char**)
{
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;

    if (!al_init()) {
        cout << "Inicjalizacja nie powiodła się." << endl; return -1;
    }
    
    display = al_create_display(800, 600);
    event_queue = al_create_event_queue();
    
    if (!display || !event_queue) {
        cout << "Inicjalizacja nie powiodła się." << endl; return -1;
    }

    al_register_event_source(event_queue, al_get_display_event_source(display));

    while (true) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
        
        // https://www.allegro.cc/manual/5/ALLEGRO_EVENT

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            cout << "Odebrałem zdarzenie ALLEGRO_EVENT_DISPLAY_CLOSE" << endl;
            break;
        }
    }

    cout << "Jestem poza pętlą." << endl;
        
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
}

