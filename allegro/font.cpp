//
// From Allegro5 Tutorial: http://wiki.allegro.cc/index.php?title=Allegro_5_Tutorial/Addons/Fonts
//

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <string>
#include <iostream>
using namespace std;
 
int main()
{
    if(!al_init()){
        cout << "Failed to initialize Allegro." << endl;
        return -1;
    }
 
    // inicjalizacja potrzebna, by moduł obsługujący czcionki prawidłowo działał
    al_init_font_addon();

    // używamy czcionek TTF (True Type Font)   
    al_init_ttf_addon();
 
    ALLEGRO_DISPLAY *display = al_create_display(640,480);
    if (!display) {
        // otwarcie okienka może się nie udać
        cout << "Failed to create display." << endl;
        return -1;
    }
 
    // ładowanie czcionki
    ALLEGRO_FONT *font = al_load_ttf_font("FreeMono.ttf",18,0);
 
    if (!font) {
        // może się nie udać - np. brak pliku z czcionką
        cout <<  "Could not load 'FreeMono.ttf'." << endl;
        return -1;
    }
 
    // tło okienka
    al_clear_to_color(al_map_rgb(50,10,70));

    // wyświetlenie napisu
    string s = "Czcionka FreeMono";
    al_draw_text(font, al_map_rgb(255,255,255), 640/2, (480/4),ALLEGRO_ALIGN_CENTRE, s.c_str());
 
    // można wyświetlić też liczbę
    int i = 512;
    al_draw_text(font, al_map_rgb(255,255,255), 640/2, (480*3/4),ALLEGRO_ALIGN_CENTRE, to_string(i).c_str());

    al_flip_display();
    al_rest(10.0);

    al_destroy_display(display);
 
    return 0;
}
