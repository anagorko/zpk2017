#pragma once
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_ttf.h>
#include <string>
#include <vector>
#include "TDatabase.h"
#include "TSeries.h"

using namespace std;

class TTextinput
{
public:
	TTextinput(int v_position_x, int v_position_y, int v_height, int v_width,vector<TSeries*> v_series,string type);
	void change_actual_date(vector<TSeries*> v_series, int v_active_series);
	void change_actual_date_automatic(string v_series, int v_active_series);
	void redraw(int v_active_series);

private:
	bool if_date_correct(string v_date);
	vector<string> actual_date;
	int position_x;
	int position_y;
	int height;
	int width;
	string type;
};

