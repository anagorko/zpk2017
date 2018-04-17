#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

using namespace std; 

const float FPS = 60;
 
int main(int argc, char **argv)
{
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;

    if(!al_init() || !al_init_primitives_addon()) {
        cout << "failed to initialize allegro!" << endl;
        return -1;
    }
 
    if(!al_install_mouse()) {
        cout << "failed to initialize the mouse!" << endl;
        return -1;
    }
 
    display = al_create_display(800, 600);
    if(!display) {
        cout << "failed to create display!" << endl;
        return -1;
    }
 
    event_queue = al_create_event_queue();
    if (!event_queue) {
        cout << "failed to create event_queue!" << endl;
        return -1;
    }
 
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_mouse_event_source());
 
    al_clear_to_color(al_map_rgb(0,0,0));
    al_flip_display();

    int bouncer_x = 400;
    int bouncer_y = 300;

    while(1)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
 
        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) 
        {
            break;
        } else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES || ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {
            bouncer_x = ev.mouse.x;
            bouncer_y = ev.mouse.y;
        } else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
            break;
        }
 
        if(al_is_event_queue_empty(event_queue)) {
            al_clear_to_color(al_map_rgb(0,0,0));
            al_draw_rectangle(bouncer_x, bouncer_y, bouncer_x + 32, bouncer_y + 32, al_map_rgba(255,255,0,128),2);
            al_flip_display();
        }
    }
 
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
 
    return 0;
}
