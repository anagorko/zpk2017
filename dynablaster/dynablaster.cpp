#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "allegro5/allegro_image.h"

#include<iostream>
#include<vector>
#include<map>

using namespace std;

class Display;
class BitmapLoader;

// Tile - pojedynczy element na planszy (podłoga, ściana, bomba, gracz etc)
class Tile
{
	ALLEGRO_BITMAP* b = NULL;
	static BitmapLoader* tl;

public:
	static void init();
	static void destroy();

	Tile(string filename);

    	static int tile_size() { return 35; }

	void draw(Display&, int, int);
};

BitmapLoader* Tile::tl = NULL;

class BitmapLoader
{
	map<string, ALLEGRO_BITMAP*> bmaps;
	
public:
	ALLEGRO_BITMAP* getBitmap(string filename) {
		if (bmaps.find(filename) == bmaps.end()) {
			bmaps[filename] = al_load_bitmap(("tiles/"+filename).c_str());

			if (bmaps[filename] == NULL) {
				cout << "Failed to load " << filename << endl;
				return NULL;
			}

			cout << "Loaded " << filename << " " << bmaps[filename] << endl;
		}
		return bmaps[filename];
	}

	~BitmapLoader()
	{
		for (const auto &b: bmaps) {
			al_destroy_bitmap(b.second);
			cout << "Deleted " << b.first << endl;
		}
	}
};

Tile::Tile(string filename) {
	b = tl -> getBitmap(filename);
}

void Tile::init() {
	tl = new BitmapLoader();
}
void Tile::destroy() {
	delete tl;
}

class BoardElement
{
protected:
	Tile *bm;

public:
    bool getDeleteStatus();
    void setDeleteStatus(bool);

};

class Floor : BoardElement
{
public:
	Floor() {
		bm = new Tile("floor.png");
	}
};

class BonusBomb : BoardElement
{
public:
	BonusBomb() {
		bm = new Tile("bonus_bomb.png");
	}
};

class BonusRadius : BoardElement
{
public:
	BonusRadius() {
		bm = new Tile("bonus_radius.png");
	}
};

class Wall : BoardElement
{
public:
	Wall() {
		bm = new Tile("wall.png");
	}
};

class IndestructibleWall : BoardElement
{
public:
	IndestructibleWall() {
	}
};

class Display
{
    const float FPS = 60.0;

    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;

public:
    bool init(float FPS = 60.0f, int tile_x = 13, int tile_y = 13) {
        if (!al_init()) return false;
	if (!al_init_primitives_addon() || !al_init_image_addon() || !al_install_keyboard()) return false;

        event_queue = al_create_event_queue();
        if(!event_queue) return false;

        timer = al_create_timer(1.0 / FPS);
        if (!timer) return false;

        display = al_create_display(tile_x * Tile::tile_size(), tile_y * Tile::tile_size());
        if(!display) return false;

        al_register_event_source(event_queue, al_get_display_event_source(display));  
        al_register_event_source(event_queue, al_get_timer_event_source(timer));  
        al_register_event_source(event_queue, al_get_keyboard_event_source());

        al_clear_to_color(al_map_rgb(0,0,0));
  
        al_flip_display();  

        al_start_timer(timer);
	return true;
    }

    /// czeka na pojawienie się zdarzenia w kolejce
    ALLEGRO_EVENT wait_for_event() {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        return ev;
    }

    /// Czy jest zdarzenie w kolejce?
    bool has_event() {
        return al_is_event_queue_empty(event_queue);
    }

    /// czyści okno
    void clear() {
        al_clear_to_color(al_map_rgb(0,0,0));        
    }

    /// pokazuje zawartość bufora
    void flip() {
        al_flip_display();
    }
};

void Tile::draw(Display& d, int x, int y) {
	cout << "tile draw" << endl;
}

class Board
{
    vector<BoardElement*> e;

public:
    void draw(Display &d) {
        d.clear();
        d.flip();
    }

    
};


int main()
{
	// Inicjalizacja generatora liczb losowych
    	srandom( time(NULL) );

	// Inicjalizacja obiektu ładującego bitmapy
	Tile::init();

	Board b;
    
    	Display d;
    	if (!d.init()) {
		cout << "Nieudana inicjalizacja." << endl;
		return 1;
	}

    	bool wyjdz = false;
    	bool czas_rysowac = true;

	FloorTile t1,t2;

    	while (!wyjdz) {
        	ALLEGRO_EVENT ev = d.wait_for_event();

        	switch (ev.type) {
        	case ALLEGRO_EVENT_DISPLAY_CLOSE: wyjdz = true; break;
        	}

        	if(czas_rysowac && !d.has_event()) {
            		b.draw(d);
        	}
    	}

	Tile::destroy();

    	return 0;
}

