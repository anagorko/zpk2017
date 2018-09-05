#pragma once
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_ttf.h>
#include <string>
#include <vector>

using namespace std;

class TButton
{
public:
	TButton(int v_position_x,int v_position_y,int v_width,int v_height,int v_font_size,const char * v_button_name, ALLEGRO_COLOR v_background_color, ALLEGRO_COLOR v_font_color);
	bool if_cursor_in_button(int cursor_x,int cursor_y);
	void change_font_colour(ALLEGRO_COLOR new_font_color);
	void redraw_button();
private:
	int position_x;
	int position_y;
	int width;
	int height;
	int font_size;
	const char * button_name;
	ALLEGRO_COLOR background_color;
	ALLEGRO_COLOR font_color;
};

