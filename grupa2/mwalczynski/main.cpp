/*##############################################
##                                            ##
##  Program: Symulacja grawitacji             ##
##  Inspiracja: https://pastebin.com/SU5KG8TE ##
##  Autor inspiracji: Curcudel Eugen          ##
##                                            ##
##############################################*/

#include <iostream>
#include <cmath>
#include <assert.h>
#include <vector>
#include <GL/glut.h>
#include <GL/glu.h>
#include "vector.hpp"
#include "point.hpp"
#include <time.h>

using namespace std;

const float g = 0.3; // w oryginale 0,03; tu inna wartosc empirycznie dobrana

void assert_with_msg (bool e, string msg){
 if (!e) {
     cout << "assertion failed" << endl << msg << endl;
     assert(e);
 	}
}

class Star {// klasa gwiazda
	public:
	Point *p; //polozenie
	int m; //masa
	int r; //promien
	float colour[3]; //kolory w rgb

	Star(Point *q) {
		p = q;
		m = 10000;
		r = 15;
		colour[0] = 1;
		colour[1] = .5;
		colour[2] = 0; //pomaranczowy
	};

	virtual string to_string() { return "Star(" + p->to_string() + ")"; }
	
	virtual bool can_move() { return false; } //gwiazdy nie poruszaja sie

	void draw(){ //rysowanie gwiazdy z biblioteki OpenGL
		glColor3f(colour[0], colour[1], colour[2]); //podane kolory
    glBegin(GL_POLYGON);
    for(float a = 0; a < 2*M_PI; a+=0.2) //rysowanie kola o znanym promieniu
      glVertex2f(r*cos(a) + p->x[0], r*sin(a) + p->x[1]);
    glEnd();
	}
};


class Planet : public Star {
	public:
	Vector *v; //predkosc, ktora jest wektorem 

	Planet(Vector *_v) : Star(_v -> p[0]) {//klasa planeta jest potem klasy gwiazda
		v = _v; //predkosc jest najistotniejsza roznica
		m = 10; //masa duzo mniejsza dla uproszczenia problemu
		if (v->d() > .001) // liczba zmiennoprzecinkowa, stad epsilon
			r = 8; //planeta z niezerowa predkoscia poczatkowa jest wieksza
		else
			r = 6;
		colour[0] = (float)(rand() % 200)/400 + 0.25; //losowy wybor kolorow z ograniczonej puli
		colour[1] = (float)(rand() % 200)/400 + 0.25;
		colour[2] = (float)(rand() % 200)/400 + 0.25;
	};

	void change_velocity(Star *s) { //funkcja zmiany predkosci ciala
		Vector *w = new Vector(p, s->p);
		float d = w->d();
		if(d > 0.001){ //byly problemy numeryczne, taki wentyl bezpieczenstwa
			w->as_versor(); //jw.
			w->multiply(g*s->m/(pow(d, 3)));
			v->plus(w);
		}
	}

	virtual string to_string() { return "Planet(" + v->to_string() + ")"; }
	
	virtual bool can_move() { return true; } //akurat planety poruszaja sie, roznica co do gwiazdy, wiec virtual

	//a teraz change_Point
	void change_velocity_and_point() {v->move_vector(v); } //zmiana puktow wektora predkosci, co wymusza tez zmiane polozenia

	void d_stars(Star *s) { Vector::d(p, s->p); } //funkcja do liczenia odleglosci przy innej koncepcji


};

class Space {//definicja klasy przestrzen
	public:
	vector<Star*> stars; //z biblioteki vector
	int window;

	Space(){
		stars = vector<Star*>();
	}

	void display(){
		for(auto it = stars.begin(); it != stars.end(); ++it){
			(*it)->draw();
		}
	}
	void timer(){
		for(auto moving_star_it = stars.begin(); moving_star_it != stars.end(); ++moving_star_it){
			bool destroyed = false;
			Star* moving_star = *moving_star_it;
			if(!moving_star->can_move())
				continue;
			Planet *planet = (Planet*) moving_star;
			for(auto star_it = stars.begin(); destroyed || star_it != stars.end(); ++star_it){
				Star* star = *star_it;
				if(moving_star != star){
					planet->change_velocity(star);
					if(Vector::d(planet->p, star->p) < 10){ //moglaby byc inna liczba 
						moving_star_it = stars.erase(moving_star_it);						
						destroyed = true;
						break; //wypadanie z petli
					}
				}
			}
			if(destroyed)
				break; //wypadanie z petli, jesli zniszczono planete
			planet->change_velocity_and_point();
		}
	}

	void add_star(Star* s){
		stars.push_back(s);
	}

	string to_string() {
		string s = "";
		for(auto it = stars.begin(); it != stars.end(); ++it){
			s += (*it)->to_string() + "\n";
		}
		return s;
	}
};

static Space* space = new Space();
static Planet* planet_with_speed = NULL;
void display(){ //OpenGL, Gravity simulation
  glClear(GL_COLOR_BUFFER_BIT);
  if(planet_with_speed){
		glColor3f(0, 0, 1); //kolor linii przeciagniecia -> niebieski
		glBegin(GL_LINES); //punkty linii
		  glVertex2f(planet_with_speed->p->x[0], planet_with_speed->p->x[1]); //poczatek
		  glVertex2f(planet_with_speed->v->p[1]->x[0], planet_with_speed->v->p[1]->x[1]); //koniec
		glEnd();
	}
	space->display();
	//cout << space->to_string();
	glFlush();
  glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {//mozliwosci myszki
float w = glutGet(GLUT_WINDOW_WIDTH); //szerokosc okna
	float h = glutGet(GLUT_WINDOW_HEIGHT); //wysokosc okna
	
	float Mx = x*500/w;// - 250; przeskalowanie w zaleznosci od okna innego od domyslnego
	float My = y*500/h;// - 500; domyslne okno jest podane nizej

	if(button == GLUT_LEFT_BUTTON){//jezeli lewy przycisk wybrany
		if(state == GLUT_DOWN){ //jesli jest przyciskniety
	    planet_with_speed = new Planet(new Vector(new Point(Mx, My), new Point(Mx, My)));
	  } else { //puszczony
	  	if(planet_with_speed){
		  	planet_with_speed->v->multiply(0.03); //przeskalowanie predkosci, inaczej za szybko byloby
		  	space->add_star(planet_with_speed);
		  	planet_with_speed = NULL;
		  }
	  }
	  
  }
	else if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){ //tutaj nie samo nacisniecie dodaje
		space->add_star(new Star(new Point(Mx, My)));
  } else if(button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN){ //jw.
  	space->stars.clear(); //wyczyszczenie ze wszystkich ciaal
  }
  

}
void mouseMotion(int x, int y){
float w = glutGet(GLUT_WINDOW_WIDTH);
	float h = glutGet(GLUT_WINDOW_HEIGHT); 
	
	float Mx = x*500/w;// - 250;
	float My = y*500/h;// - 500;

  //end of line with draging
  if(planet_with_speed){//przypisanie predkosci planecie na podstawie przeciagniecja myszka
  	Vector *v = new Vector(planet_with_speed->p, new Point(Mx, My));
  	//cout << "new planet speed" << v->d() << endl;
    planet_with_speed->v = v;
  }
}

void keyboard(unsigned char key, int x, int y){  } //z OpenGL, Gravity simulation
void timer(int);
void timer(int t){
	display();
	space->timer();
	glutTimerFunc(1, timer, 0);
}

void runGlut(int argc, char** argv){//OpenGL, Gravity simulation
	glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(500, 500); //domyslny rozmiar okna
	glutInitWindowPosition(500, 50); // domyslne polozenia okna
  space->window = glutCreateWindow("Symulator grawitacji"); //tytul na pasku

  glClearColor(0, 0, 0, 1); //kolor czarny planszy
	glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
	glOrtho(0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 0, 0, 1); //centrowanie
//	glOrtho(-1, 1, 1, -1, 0, 1);
	glutDisplayFunc(display);
  glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	glutKeyboardFunc(keyboard);
  timer(0);

	glutMainLoop();
}

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void test(){
	Vector* v = new Vector(new Point(250,250), new Point(250, 250));
	//assert(v->d() == 13.0);

	Planet* p = new Planet(v);
	assert(p->r == 6);

	v = new Vector(new Point(0, 0), new Point(0, 1));
	v->plus(new Vector(new Point(2,2), new Point(3, 2)));
	assert_with_msg(
		v->p[1]->x[0]==1,
		v->to_string()
	);
	assert(v->p[1]->x[1]==1);

	Star* s = new Star(new Point(10, 10));

	p->change_velocity(s);
	//assert(p->v->d() != 13.0);

	space->add_star(p);
	space->add_star(s);
	space->add_star(new Star(new Point(490, 490)));
	space->add_star(new Star(new Point(490, 10)));
	//cout << space->to_string();
	
	space->timer();
  space->timer();
	space->timer();
	//cout << "first planet speed" << ((Planet*)space->stars[0])->v->d() << endl;
}


int main(int argc, char** argv) {
	srand(time(NULL)); //losowanie do kolorow na podstawie czasu
	//test();
	runGlut(argc, argv);
	return 0;
}
