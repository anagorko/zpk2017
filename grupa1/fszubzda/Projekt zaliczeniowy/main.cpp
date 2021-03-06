
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <list>

#include "GameObject.h"
#include "Survivor.h"
#include "Bullet.h"
#include "Zombie.h"
#include "Globals.h"
#include "Blood.h"
#include "Background.h"

using namespace std;

bool keys[] = {false,false,false,false,false};
enum KEYS{UP, DOWN, LEFT, RIGHT, SPACE};

//globals - tu można globalne wrzucac, ale charakterystyczne dla maina.
Survivor *survivor;
std::list<GameObject *> objects;
std::list<GameObject *>::iterator iter; //one będą iterować przez tę wielką listę/vector  z obiektami wszystkimi z gry
std::list<GameObject *>::iterator iter2;


// GunPoint nie dostał oddzielnej klasy, jest to tylko jedna funkcja która rysuje, a Update pochodzi bezpośrednio z myszki.
int pos_x, pos_y;
void DrawGunpoint(int pos_x, int pos_y){
    al_draw_circle(pos_x,pos_y,10,al_map_rgb(0,0,0), 2);
    al_draw_filled_rectangle(pos_x+1,pos_y-10,pos_x-1,pos_y+10, al_map_rgb(0,0,0));
    al_draw_filled_rectangle(pos_x+10,pos_y-1,pos_x-10,pos_y+1, al_map_rgb(0,0,0));
}
//prototypes
void __cdecl TakeLife();//pt 6 ma początku
//void TakeLife() __attribute__((cdecl));
void ScorePoint();

int main(){


    bool done=false;
    bool render = true;
    const int FPS = 60;

    float gameTime=0;
    int frames=0;
    int gameFPS=0;

    /*
    Project variables
    */
    survivor = new Survivor();


    /*ALLEGRO VARIABLES*/
    ALLEGRO_BITMAP *survivorImage = NULL;
    ALLEGRO_BITMAP *zombieImage = NULL;
    ALLEGRO_BITMAP *bloodImage = NULL;
    ALLEGRO_BITMAP *bgImage = NULL;
    ALLEGRO_BITMAP *mgImage = NULL;
    ALLEGRO_BITMAP *fgImage = NULL;


    //allegro variables
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue=NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_FONT *font18;

    if(!al_init())
        return -1;

    display= al_create_display(WIDTH,HEIGHT);

    if(!display)
        return -1;

    /*
    INSTALL ADDON

    */
    al_init_primitives_addon();
    al_install_keyboard(); //działanie klawiatury
    al_init_image_addon();
    al_init_font_addon();//czcionka
    al_init_ttf_addon();//czcionka
    al_install_mouse();//myszka
    /*
    PROJECT INIT
    */
    font18 = al_load_font("arial.ttf",18,0);

    /*background musi być przed wszystkimi na liście*/
    bgImage = al_load_bitmap("bg.png");
    mgImage = al_load_bitmap("mg.png");
    al_convert_mask_to_alpha(mgImage, al_map_rgb(255,255,255));
    fgImage = al_load_bitmap("fg.png");
    al_convert_mask_to_alpha(fgImage, al_map_rgb(255,255,255));

    Background *bg = new Background(bgImage, 0.5);
    objects.push_back(bg);

    bg = new Background(mgImage, 1);
    objects.push_back(bg);

    bg = new Background(fgImage, 1);
    objects.push_back(bg);


    survivorImage = al_load_bitmap("modernguy02.png");
    al_convert_mask_to_alpha(survivorImage, al_map_rgb(255,255,255));
    survivor ->Init(survivorImage);

    objects.push_back(survivor);

    zombieImage = al_load_bitmap("zombie_small.png");
    al_convert_mask_to_alpha(zombieImage , al_map_rgb(255,255,255));

    bloodImage = al_load_bitmap("blood.png");
    al_convert_mask_to_alpha(bloodImage, al_map_rgb(255,255,255));

    /*
    TIMER AND STARTUP
    */
    event_queue = al_create_event_queue();
    timer = al_create_timer(1.0/FPS);

    al_register_event_source(event_queue,al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer)); // fps
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_start_timer(timer);
    gameTime = al_current_time();
    al_hide_mouse_cursor(display);

    while(!done){
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);


         if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
            switch(ev.keyboard.keycode){
            case ALLEGRO_KEY_ESCAPE:
                done=true;
                break;
            case ALLEGRO_KEY_UP:
                keys[UP]=true;
                break;
            case ALLEGRO_KEY_DOWN:
                keys[DOWN]=true;
                break;
            case ALLEGRO_KEY_LEFT:
                keys[LEFT]=true;
                break;
            case ALLEGRO_KEY_RIGHT:
                keys[RIGHT]=true;
                break;
            case ALLEGRO_KEY_SPACE:
                keys[SPACE]=true;
                Bullet *bullet = new Bullet(survivor->GetX() + 17, survivor->GetY(), pos_x, pos_y, &ScorePoint); //inicjujemy nową kulę9
                objects.push_back(bullet);
                break;
            }
        }
        else if (ev.type==ALLEGRO_EVENT_KEY_UP){
            switch(ev.keyboard.keycode){
            case ALLEGRO_KEY_ESCAPE:
                done=true;
                break;
            case ALLEGRO_KEY_UP:
                keys[UP]=false;
                break;
            case ALLEGRO_KEY_DOWN:
                keys[DOWN]=false;
                break;
            case ALLEGRO_KEY_LEFT:
                keys[LEFT]=false;
                break;
            case ALLEGRO_KEY_RIGHT:
                keys[RIGHT]=false;
                break;
            case ALLEGRO_KEY_SPACE:
                keys[SPACE]=false;
                break;
            }
        }
        else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES){
            pos_x = ev.mouse.x;
            pos_y = ev.mouse.y;
        }
          else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
            if(ev.mouse.button & 1){
            pos_x = ev.mouse.x;
            pos_y = ev.mouse.y;
            Bullet *bullet = new Bullet(survivor->GetX() + 17, survivor->GetY(), pos_x, pos_y, &ScorePoint); //inicjujemy nową kulę9
            objects.push_back(bullet);
            }
        }
        else if(ev.type == ALLEGRO_EVENT_TIMER){
                render = true;

                //FPS UPDATE
                frames++;
                if(al_current_time()-gameTime>=1){
                    gameTime = al_current_time();
                    gameFPS = frames;
                    frames = 0;
                }

                if(keys[UP])
                    survivor->MoveUp();//poza klasą trzeba odwoływać się tak
                else if(keys[DOWN])
                    survivor->MoveDown();
                else
                    survivor->ResetAnimation(1);

                if(keys[LEFT])
                    survivor->MoveLeft();
                else if (keys[RIGHT])
                    survivor->MoveRight();
                else
                    survivor->ResetAnimation(0);

                if(rand() % 100 == 0){
                    Zombie *zombie= new Zombie(WIDTH, 30 + rand() % (HEIGHT - 60), -1, zombieImage, &TakeLife);
                    Zombie *zombie1= new Zombie(1, 30 + rand() % (HEIGHT - 60), 1, zombieImage, &TakeLife);

                    objects.push_back(zombie);
                    objects.push_back(zombie1);
                }

                /*UPDATE SECTION*/
                for(iter = objects.begin() ; iter!=objects.end(); ++iter){
                    /*Opis co przed (*iter)-> Update: Nie jestem w stanie zamieścić w klasie Zombie kodu w Render, który zmieniałby, w zależności od pozycji gracza, stronę w którą skierowane są zombie, ponieważ musiałbym zrobić wielokrotne dziedziczenie, które jest, przynajmniej na ten moment, skomplikowane. Zamiast tego dopisałem do GameObject zmienne survX i survY - czyli zmienne które mówią nam gdzie znajduje się nasz bohater i tutaj są aktualizowane  tylko dla zombiaków. Zmienna może się też przydać gdy chciałbym dokładać inne stworki (klasy). Gdyby nad tym popracować to oczywiście lepiej byłoby zrobić podwójne dziedziczenie i Update miałby miejsce w pliku (klasie) Zombie.*/

                    float survX = survivor->GetX();
                    float survY = survivor->GetY();

                   (*iter)->SetSurvX(survX);
                   (*iter)->SetSurvY(survY);

                   (*iter)-> Update();   //tak zapisane (*iter) - to staje się tym obiektem którego szukamy
              }

              //collisions
                for(iter = objects.begin() ; iter != objects.end(); ++iter){
                    if(! (*iter)->Collidable()) continue; //jesli nie mozna go collide'owac to po prostu idziemy do nastepnego

                    for(iter2 = iter; iter2!=objects.end();++iter2){
                        if(!(*iter2)->Collidable()) continue;
                        if( (*iter)->GetID()==(*iter2)->GetID()) continue; // stworki nie będą kolidować ze stworkami

                        if((*iter)->CheckCollisions( (*iter2))  ){ //dodanie GetID!=Player - teraz nie niszczę stworków przez nachodzenie.
                            (*iter)->Collided( (*iter2)->GetID()); //np iter to my, kolidujemy ze stworkiem
                            (*iter2)->Collided( (*iter)->GetID()); //a tu stwoerek koliduje z nami

                            if((*iter)->GetID() == BULLET || (*iter2)->GetID()== BULLET ){ //jeżeli Bullet z kimś kolidował to tylko wtedy pojawi się krew
                            Blood *blood = new Blood ( ((*iter)->GetX() + (*iter2)->GetX())/2, ((*iter)->GetY() + (*iter2)->GetY())/2 , bloodImage);
                            objects.push_back(blood);
                            }
                        }
                    }
                }
              //pozbycie się niepotrzebnych obiektów (np. wystrzelona kula poza obramowaniem) film part 4. 15 minuta.
              for(iter = objects.begin() ; iter != objects.end(); ){
                    if (!(*iter)->GetAlive()) {//gdy nie jest alive
                        delete (*iter);
                        iter=objects.erase(iter);
              }
              else
                iter++;
              }

         }

        if(render && al_is_event_queue_empty(event_queue)){

            render=false;
            al_draw_textf(font18,al_map_rgb(255,0,255), 5, 5, 0, "%i lives left. %i objects has been destroyed.",survivor->GetLives(), survivor->GetScore());
            /*begin project render*/

            for(iter = objects.begin(); iter != objects.end(); ++iter){
                (*iter)->Render();
                DrawGunpoint(pos_x,pos_y);
            }

            /*FLIP*/
            al_flip_display();
            al_clear_to_color(al_map_rgb(202,202,202));


        }
    }

    /*czyszczenie*/
    for(iter = objects.begin(); iter != objects.end(); ){
        (*iter)->Destroy();
        delete (*iter);
        iter = objects.erase(iter); //to jest ++iter
    }

    al_destroy_bitmap(bloodImage);
    al_destroy_bitmap(bgImage);
    al_destroy_bitmap(mgImage);
    al_destroy_bitmap(fgImage);
    //
    al_destroy_font(font18);
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);
    al_destroy_display(display);

    return 0;
}


void __cdecl TakeLife(){
survivor->LoseLife();
}

void __cdecl ScorePoint(){
survivor->AddPoint();
}

