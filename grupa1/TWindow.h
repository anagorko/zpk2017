#pragma once
#include <vector>
#include <allegro5/allegro_font.h>
#include "TButton.h"


using namespace std;

class TWindow
{
public:
	TWindow(int v_cross_axis_x_position, int v_cross_axis_y_position, int v_axis_x_length, int v_axis_y_length, int v_table_s_point_x, int v_table_s_point_y, int v_table_height, int v_table_width);
	int company_get_active();
	void company_set_active(vector<TButton*> v_buttons, int mouse_x, int mouse_y);
	void draw_axis();
	void draw_table();

private:
	int cross_axis_x_position;
	int cross_axis_y_position;
	int axis_x_length;
	int axis_y_length;
	int table_s_point_x;
	int table_s_point_y;
	int table_height;
	int table_width;
	int company_currently_active;

};

