#include "TButton.h"
#include <math.h>
#include <sstream>
#include <iomanip>

using namespace std;

TButton::TButton(int v_position_x, int v_position_y, int v_width, int v_height, int v_font_size, const char * v_button_name, ALLEGRO_COLOR v_background_color, ALLEGRO_COLOR v_font_color)
{
	position_x = v_position_x;
	position_y = v_position_y;
	width = v_width;
	height = v_height;
	font_size = v_font_size;
	background_color = v_background_color;
	font_color = v_font_color;
	button_name = v_button_name;
	al_draw_filled_rectangle(position_x, position_y, position_x + width, position_y + height, background_color);
	ALLEGRO_FONT *font = al_load_ttf_font("PTC55F.ttf", 18, 0);
	al_draw_text(font, font_color, position_x, position_y, 0, button_name);
}

bool TButton::if_cursor_in_button(int cursor_x, int cursor_y)
{
	if (cursor_x >= position_x && cursor_x <= position_x + width && cursor_y >= position_y && cursor_y <= position_y + height) return true;
	else return false;
}

void TButton::change_font_colour(ALLEGRO_COLOR new_font_colour) 
{
	font_color = new_font_colour;
}

void TButton::redraw_button()
{
	al_draw_filled_rectangle(position_x, position_y, position_x + width, position_y + height, background_color);
	ALLEGRO_FONT *font = al_load_ttf_font("PTC55F.ttf", 18, 0);
	al_draw_text(font, font_color, position_x, position_y, 0, button_name);
}



