// Kolorowe Game Of Life
// wzajemna interakcja komorek jest zalezna od ich kolorow

// Interfejs zostal wykonany za pomoca bibliotek SDL2 i SDL2_ttf, ktore trzeba zainstalowac
// aby skompilowac program. Dokladna instrukcja instalacyjna:
// http://lazyfoo.net/tutorials/SDL/01_hello_SDL/index.php (SDL2)
// http://lazyfoo.net/SDL_tutorials/lesson03/index.php (SDL2_ttf)
// Rowniez zalaczony plik Arial.ttf powinien znajdowac sie w tym samym katalogu co plik .cpp
// Ponizszy plik mozna kompilowac z terminala komenda g++ game_of_life.cpp -w -lSDL2 -lSDL2_ttf
// Program nastepnie nalezy uruchomic komenda ./a.out

// Robert Soczewica - interfejs, Marek Sztyk - algorytm


#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <cstdlib>

using namespace std;

SDL_Renderer* renderowanie = NULL;
SDL_Window* okno = NULL;

/* Deklaracje klas */
class Przycisk {
    public:
        int x1;
        int y1;
        int x2;
        int y2;
};

class Komorka {
    public:
        int stan;
        int kolor[3];
        int counter[3];
};

/* Zmienne globalne */
const int MARTWA_KOMORKA = 0;
const int SIATKA_ROZMIAR = 20;  /* rozmiar siatki rozdielającej pola (piksele) */
const int OKNO_ROZMIAR = 500;   /* rozmiar okna gry (piksele) */
const int KOMORKA_ROZMIAR = OKNO_ROZMIAR / SIATKA_ROZMIAR;  /* rozmiar pojedynczej komorki (piksele) */
const int V_ANIMACJA = 250; /* predkosc animiacji (milisekundy) */

/* Funkcje */
int zywi_sasiedzi( int siatka[][SIATKA_ROZMIAR], int rozmiar, int x, int y );

bool zaladuj_okno( );
bool animacja = false;
bool koniec_gry = false;

int kolor[] = {255, 255, 0};
int reprodukcja[] = {3, 8, 3, 5}; /* liczba sasiadow przy ktorej zachodzi reprodukcja */
int przeludnienie[] = {3, 2, 3, 5}; /* powyzej tej liczby sasiadow komorki umieraja z przeludnienia */
int izolacja[] = {2, 1, 2, 2}; /* ponizej tej wartosci komorki umieraja z samotnosci */

void zaladuj_siatke( Komorka siatka[][SIATKA_ROZMIAR], int rozmiar );
void stan_komorki( Komorka siatka[][SIATKA_ROZMIAR], int rozmiar, int x, int y, int liczba_sasiadow );
void zaladuj_komorke( Komorka siatka[][SIATKA_ROZMIAR], int rozmiar, int x, int y, int wartosc, int kolor[]);
void krok( Komorka siatka[][SIATKA_ROZMIAR], int rozmiar );
void tekst( );
void rysuj_przycisk( int x1, int y1, int x2, int y2 );
void pokaz_menu( );
void pokaz_siatke( Komorka siatka[][SIATKA_ROZMIAR], int rozmiar );
void interakcja( Komorka siatka[][SIATKA_ROZMIAR], int rozmiar );
void zakoncz_wyswietlanie( );

/* Definicje danych obiektow */
Przycisk start = {OKNO_ROZMIAR + 20, 20, OKNO_ROZMIAR + 180, 120};
Przycisk kolor1 = {OKNO_ROZMIAR + 20, 260, OKNO_ROZMIAR + 180, 300};
Przycisk kolor2 = {OKNO_ROZMIAR + 20, 330, OKNO_ROZMIAR + 180, 370};
Przycisk kolor3 = {OKNO_ROZMIAR + 20, 400, OKNO_ROZMIAR + 180, 440};
Przycisk wymaz = {OKNO_ROZMIAR + 20, 140, OKNO_ROZMIAR + 180, 200};

/***********************************************************************************************************/

int main(int argv, char** args) {
    Uint32 ticks;

    Komorka siatka[SIATKA_ROZMIAR][SIATKA_ROZMIAR]; /* siatka gry */

    if( !zaladuj_okno() ) {
        return 1;
    }

    if( TTF_Init() < 0 ) { }

    zaladuj_siatke( siatka, SIATKA_ROZMIAR );
    ticks = SDL_GetTicks( );
    SDL_SetWindowTitle( okno, "Game Of Life" );

    while( !koniec_gry ) {
        interakcja( siatka, SIATKA_ROZMIAR );
        pokaz_siatke( siatka, SIATKA_ROZMIAR );

        if( animacja && (SDL_GetTicks() - ticks) > V_ANIMACJA ) {
            krok( siatka, SIATKA_ROZMIAR );
            ticks = SDL_GetTicks( );
        }
    }
    TTF_Quit( );
    zakoncz_wyswietlanie( );
    return 0;
}

/***********************************************************************************************************/

/* funkcja zwraca ilosc zywych sasiadow kazdego rodzaju */
int zywi_sasiedzi( Komorka siatka[][SIATKA_ROZMIAR], int rozmiar, int x, int y ) {

    int i, j, ile = 0;

    siatka[y][x].counter[0]=0;
    siatka[y][x].counter[1]=0;
    siatka[y][x].counter[2]=0;

    for( i = y-1; i <= y+1; i++ ) {
        for( j = x-1; j <= x+1; j++ ) {
            if( i >= 0 && j >= 0 && i < rozmiar && j < rozmiar) {
                if( siatka[i][j].stan > MARTWA_KOMORKA ) {
                    ile++;
                    switch( siatka[i][j].stan )
                    {
                    case 0:
                        break;
                    case 1:
                        siatka[y][x].counter[0] = siatka[y][x].counter[0]+1;
                        break;
                    case 2:
                        siatka[y][x].counter[1] = siatka[y][x].counter[1]+1;
                        break;
                    case 3:
                        siatka[y][x].counter[2] = siatka[y][x].counter[2]+1;
                        break;
                    }
                }
            }
        }
    }

    if( siatka[y][x].stan != MARTWA_KOMORKA ) {
        ile--;
    }

    return ile;
}

/* funkcja ladujaca i rendurujaca okno gry */
bool zaladuj_okno( ) {
    if( SDL_Init( SDL_INIT_VIDEO ) != 0 ) {
        SDL_LogError( SDL_LOG_CATEGORY_APPLICATION, "Nie mozna zainicializowac SDL: %s\n", SDL_GetError( ) );
        return 0;
    }

    if( SDL_CreateWindowAndRenderer(700, OKNO_ROZMIAR, 0, &okno, &renderowanie ) < 0) {
        SDL_LogError( SDL_LOG_CATEGORY_APPLICATION, "Nie mozna zaladowac okna i renderowac - %s\n", SDL_GetError( ) );
        return 0;
    }
    return 1;
}

/* funkcja laduje siatke, ktorej wszystkie komorki sa martwe */
void zaladuj_siatke( Komorka siatka[][SIATKA_ROZMIAR], int rozmiar ) {
    int x, y;
    for( y = 0; y < rozmiar; y++ ) {
        for( x = 0; x < rozmiar; x++ ) {
            siatka[y][x].stan = MARTWA_KOMORKA;
        }
    }
}

/* funkcja okreslajaca na bazie sasiadow czy dana komorka jest zywa czy martwa */
void stan_komorki( Komorka siatka[][SIATKA_ROZMIAR], int rozmiar, int x, int y, int liczba_sasiadow ) {

    int nowy_stan = 1;

    for( int i = 1; i < 3; i++ ) {
        if( siatka[y][x].counter[i]>siatka[y][x].counter[i-1] ) {
            nowy_stan = i + 1;
        }
    }

    if( liczba_sasiadow == reprodukcja[nowy_stan] ) {

        siatka[y][x].stan = nowy_stan;
        switch( siatka[y][x].stan )
                    {
                    case 1:
                        siatka[y][x].kolor[0] = 255;
                        siatka[y][x].kolor[1] = 255;
                        siatka[y][x].kolor[2] = 0;
                        break;
                    case 2:
                        siatka[y][x].kolor[0] = 0;
                        siatka[y][x].kolor[1] = 0;
                        siatka[y][x].kolor[2] = 255;
                        break;
                    case 3:
                        siatka[y][x].kolor[0] = 255;
                        siatka[y][x].kolor[1] = 165;
                        siatka[y][x].kolor[2] = 0;
                        break;
                    }



    } else if ( liczba_sasiadow > przeludnienie[nowy_stan] || liczba_sasiadow < izolacja[nowy_stan] ) {
        siatka[y][x].stan = MARTWA_KOMORKA;
    }
}

/* funkcja laduje podana przez argument wartosc komorki */
void zaladuj_komorke( Komorka siatka[][SIATKA_ROZMIAR], int rozmiar, int x, int y, int wartosc, int kolor[]) {
    if ( x >= 0 && x < rozmiar && y >= 0 && y < rozmiar ) {
        siatka[y][x].stan = wartosc;
        siatka[y][x].kolor[0] = kolor[0];
        siatka[y][x].kolor[1] = kolor[1];
        siatka[y][x].kolor[2] = kolor[2];
    }
}

/* funkcja najpierw liczy sasiadow dla kazdej komorki, a pozniej odswieza na podstawie tego wyniku jej stan */
void krok( Komorka siatka[][SIATKA_ROZMIAR], int rozmiar ) {
    int x, y, licz[SIATKA_ROZMIAR][SIATKA_ROZMIAR];
    for( y = 0; y < rozmiar; y++ ) {
        for(x = 0; x < rozmiar; x++) {
            licz[y][x] = zywi_sasiedzi(siatka, rozmiar, x, y);
        }
    }

    for( y = 0; y < SIATKA_ROZMIAR; y++ ) {
        for( x = 0; x < SIATKA_ROZMIAR; x++ ) {
            stan_komorki( siatka, rozmiar, x, y, licz[y][x] );
        }
    }
}

/* funkcja rysujaca tekst na przyciskach */
void tekst( ){
    int x, y;
    TTF_Font * f = TTF_OpenFont( "Arial.ttf", 30 );
    SDL_Color czarny = {0, 0, 0};
    SDL_Surface * surface1 = TTF_RenderText_Solid( f, "START / PAUZA", czarny );
    SDL_Surface * surface2 = TTF_RenderText_Solid( f, "WYMAZ", czarny );
    if( surface1 == NULL || surface2 == NULL ) {
        printf( "Nie mozna renderowac: %s", TTF_GetError() );
    } else {
        SDL_Texture * napis1 = SDL_CreateTextureFromSurface( renderowanie, surface1 );
        SDL_Texture * napis2 = SDL_CreateTextureFromSurface( renderowanie, surface2 );
        if( napis1 == NULL || napis2 == NULL ) {
            printf( "Nie mozna utworzyc tekstury: %s", SDL_GetError() );
            SDL_DestroyTexture( napis1 );
            SDL_DestroyTexture( napis2 );
        } else {
            SDL_Rect r1 = {start.x1 + 10, start.y1 + 35, 140, 40};
            SDL_RenderCopy( renderowanie, napis1, NULL, &r1 );

            SDL_Rect r2 = {wymaz.x1 + 30, wymaz.y1 + 15, 100, 35};
            SDL_RenderCopy( renderowanie, napis2, NULL, &r2 );
        }
        SDL_FreeSurface( surface1 );
    }
    TTF_CloseFont( f );
}

/* funkcja rysuje przycisk */
void rysuj_przycisk( int x1, int y1, int x2, int y2 ) {
    SDL_RenderDrawLine( renderowanie, x1, y1, x2, y1 );
    SDL_RenderDrawLine( renderowanie, x1, y2, x2, y2 );
    SDL_RenderDrawLine( renderowanie, x1, y1, x1, y2 );
    SDL_RenderDrawLine( renderowanie, x2, y1, x2, y2 );
}

/* funkcja pokazujaca menu */
void pokaz_menu( ) {
    rysuj_przycisk( start.x1, start.y1, start.x2, start.y2 );

    rysuj_przycisk( wymaz.x1, wymaz.y1, wymaz.x2, wymaz.y2 );

    rysuj_przycisk( kolor1.x1, kolor1.y1, kolor1.x2, kolor1.y2 );

    SDL_SetRenderDrawColor( renderowanie, 255, 255, 0, SDL_ALPHA_OPAQUE );
    SDL_Rect r1 = {
        kolor1.x1,
        kolor1.y1,
        kolor1.x2 - kolor1.x1,
        kolor1.y2 - kolor1.y1
    };
    SDL_RenderFillRect( renderowanie, &r1 );

    rysuj_przycisk( kolor2.x1, kolor2.y1, kolor2.x2, kolor2.y2 );

    SDL_SetRenderDrawColor( renderowanie, 0, 0, 255, SDL_ALPHA_OPAQUE );
    SDL_Rect r2 = {
        kolor2.x1,
        kolor2.y1,
        kolor2.x2 - kolor2.x1,
        kolor2.y2 - kolor2.y1
    };
    SDL_RenderFillRect( renderowanie, &r2 );

    rysuj_przycisk( kolor3.x1, kolor3.y1, kolor3.x2, kolor3.y2 );

    SDL_SetRenderDrawColor( renderowanie, 255, 165, 0, SDL_ALPHA_OPAQUE );
    SDL_Rect r3 = {
        kolor3.x1,
        kolor3.y1,
        kolor3.x2 - kolor3.x1,
        kolor3.y2 - kolor3.y1
    };
    SDL_RenderFillRect( renderowanie, &r3 );

    SDL_SetRenderDrawColor( renderowanie, 131, 137, 150, SDL_ALPHA_OPAQUE );
    if( animacja == true ) {
        SDL_Rect r = {
            start.x1,
            start.y1,
            start.x2 - start.x1,
            start.y2 - start.y1
        };
        SDL_RenderFillRect( renderowanie, &r );
    }
    tekst( );
}

/* funkcja pokazujaca siatke */
void pokaz_siatke ( Komorka siatka[][SIATKA_ROZMIAR], int rozmiar ) {
    SDL_SetRenderDrawColor( renderowanie, 255, 255, 255, SDL_ALPHA_OPAQUE ); /* bialy kolor */
    SDL_RenderClear( renderowanie ); /* wyczyszczenie ekranu */
    SDL_SetRenderDrawColor( renderowanie, 0, 0, 0, SDL_ALPHA_OPAQUE ); /* czarny kolor */
    /* wyrysowanie kolejno wierszy i kolumn */
    for( int i = 0; i < rozmiar; i++) {
        SDL_RenderDrawLine( renderowanie, 0, KOMORKA_ROZMIAR * i, OKNO_ROZMIAR, KOMORKA_ROZMIAR * i );
    }
    for( int i = 0; i <= rozmiar; i++ ) {
        SDL_RenderDrawLine( renderowanie, KOMORKA_ROZMIAR * i, 0, KOMORKA_ROZMIAR * i, OKNO_ROZMIAR );
    }

    pokaz_menu( );

    SDL_SetRenderDrawColor(renderowanie, kolor[0], kolor[1], kolor[2], SDL_ALPHA_OPAQUE); /* zolty kolor (zaznaczona komorka) */
    /* Renderowanie */
    for( int x = 0; x < rozmiar; x++ ) {
        for( int y = 0; y < rozmiar; y++) {
            if( siatka[y][x].stan > MARTWA_KOMORKA ) {
                SDL_SetRenderDrawColor( renderowanie, siatka[y][x].kolor[0], siatka[y][x].kolor[1], siatka[y][x].kolor[2], SDL_ALPHA_OPAQUE );
                SDL_Rect r = {
                    x * KOMORKA_ROZMIAR, /* x */
                    y * KOMORKA_ROZMIAR, /* y */
                    KOMORKA_ROZMIAR,    /* szerokosc komorki */
                    KOMORKA_ROZMIAR     /* wysokosc komorki */
                };
                SDL_RenderFillRect( renderowanie, &r );
            }
        }
    }

    SDL_RenderPresent( renderowanie );
}

/* funckja reaguje na interakcje uzytkownika i zarzadza symulacja */
void interakcja( Komorka siatka[][SIATKA_ROZMIAR], int rozmiar ) {
    int x, y, wartosc = 1;
    SDL_Event zdarzenie;
    while( SDL_PollEvent( &zdarzenie ) ) {
        if ( zdarzenie.type == SDL_QUIT ) {
            koniec_gry = true;
        } else if( zdarzenie.type == SDL_MOUSEBUTTONDOWN ) {
            x = zdarzenie.button.x;
            y = zdarzenie.button.y;
            if( zdarzenie.button.button == SDL_BUTTON_LEFT ) {
                if( x > start.x1 && x < start.x2 && y > start.y1 && y < start.y2 ) {
                    animacja =! animacja;
                }
                if( x > kolor1.x1 && x < kolor1.x2 && y > kolor1.y1 && y < kolor1.y2 ) {
                    kolor[0] = 255;
                    kolor[1] = 255;
                    kolor[2] = 0;
                    wartosc = 1;
                }
                if( x > kolor2.x1 && x < kolor2.x2 && y > kolor2.y1 && y < kolor2.y2 ) {
                    kolor[0] = 0;
                    kolor[1] = 0;
                    kolor[2] = 255;
                    wartosc = 2;
                }
                if( x > kolor3.x1 && x < kolor3.x2 && y > kolor3.y1 && y < kolor3.y2 ) {
                    kolor[0] = 255;
                    kolor[1] = 165;
                    kolor[2] = 0;
                    wartosc = 3;
                }
                if( x > wymaz.x1 && x < wymaz.x2 && y > wymaz.y1 && y < wymaz.y2 ) {
                    zaladuj_siatke( siatka, rozmiar );
                    animacja = false;
                }
            }
            /* mozna ozywic lub zabic komorki klikajac na nie kursorem */
            zaladuj_komorke( siatka, rozmiar, zdarzenie.button.x / KOMORKA_ROZMIAR, zdarzenie.button.y / KOMORKA_ROZMIAR, (zdarzenie.button.button == SDL_BUTTON_LEFT) ? wartosc : MARTWA_KOMORKA, kolor);
        } else if( zdarzenie.type == SDL_KEYDOWN ) {
            if ( zdarzenie.key.keysym.sym == SDLK_SPACE ) {
                /* rozpoczecie i zakonczenie animacji za pomoca spacji */
                animacja =! animacja;
            } else if ( zdarzenie.key.keysym.sym == SDLK_BACKSPACE ) {
                 /* wyczyszczenie ekranu za pomoca backspace */
                zaladuj_siatke( siatka, rozmiar );
                animacja = false;
            }
        }
    }
}

/* funkcja dzieki, ktorej po zamknieciu okna wyjdziemy z gry */
void zakoncz_wyswietlanie( ) {
    SDL_DestroyRenderer( renderowanie );
    SDL_DestroyWindow( okno );
    SDL_Quit( );
}
