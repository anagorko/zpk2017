#include "TWindow.h"

using namespace std;

TWindow::TWindow(int v_cross_axis_x_position, int v_cross_axis_y_position, int v_axis_x_length, int v_axis_y_length, int v_table_s_point_x, int v_table_s_point_y, int v_table_height, int v_table_width)
{
	ALLEGRO_FONT *font = al_load_ttf_font("PTC55F.ttf", 14, 0);
	company_currently_active = 0;
	cross_axis_x_position = v_cross_axis_x_position;
	cross_axis_y_position = v_cross_axis_y_position;
	axis_x_length = v_axis_x_length;
	axis_y_length = v_axis_y_length;
	al_draw_line(cross_axis_x_position, cross_axis_y_position - axis_y_length, cross_axis_x_position, cross_axis_y_position, al_map_rgb(0, 0, 0), 1);
	al_draw_line(cross_axis_x_position, cross_axis_y_position - axis_y_length, cross_axis_x_position - 5, cross_axis_y_position - axis_y_length + 20, al_map_rgb(0, 0, 0), 1);
	al_draw_line(cross_axis_x_position, cross_axis_y_position - axis_y_length, cross_axis_x_position + 5, cross_axis_y_position - axis_y_length + 20, al_map_rgb(0, 0, 0), 1);
	al_draw_line(cross_axis_x_position, cross_axis_y_position, cross_axis_x_position + axis_x_length, cross_axis_y_position, al_map_rgb(0, 0, 0), 1);
	al_draw_line(cross_axis_x_position + axis_x_length - 20, cross_axis_y_position - 5, cross_axis_x_position + axis_x_length, cross_axis_y_position, al_map_rgb(0, 0, 0), 1);
	al_draw_line(cross_axis_x_position + axis_x_length - 20, cross_axis_y_position + 5, cross_axis_x_position + axis_x_length, cross_axis_y_position, al_map_rgb(0, 0, 0), 1);
	table_s_point_x = v_table_s_point_x;
	table_s_point_y = v_table_s_point_y;
	table_height = v_table_height;
	table_width = v_table_width;
	al_draw_line(table_s_point_x, table_s_point_y, table_s_point_x, table_s_point_y + table_height, al_map_rgb(0, 0, 0), 1);
	al_draw_line(table_s_point_x + table_width / 2, table_s_point_y, table_s_point_x + table_width / 2, table_s_point_y + table_height, al_map_rgb(0, 0, 0), 1);
	al_draw_line(table_s_point_x + table_width, table_s_point_y, table_s_point_x + table_width, table_s_point_y + table_height, al_map_rgb(0, 0, 0), 1);
	al_draw_text(font, al_map_rgb(0, 0, 0), table_s_point_x + table_width / 4, table_s_point_y, ALLEGRO_ALIGN_CENTRE, "Ostatnia data");
	al_draw_text(font, al_map_rgb(0, 0, 0), table_s_point_x + table_width / 4, table_s_point_y + table_height /6, ALLEGRO_ALIGN_CENTRE, "Ostatnia cena");
	al_draw_text(font, al_map_rgb(0, 0, 0), table_s_point_x + table_width / 4, table_s_point_y + table_height / 3, ALLEGRO_ALIGN_CENTRE, "AVG 3M (6M)");
	al_draw_text(font, al_map_rgb(0, 0, 0), table_s_point_x + table_width / 4, table_s_point_y + 1 * table_height / 2, ALLEGRO_ALIGN_CENTRE, "IRR 3M (6M)");
	al_draw_text(font, al_map_rgb(0, 0, 0), table_s_point_x + table_width / 4, table_s_point_y + 2 * table_height / 3, ALLEGRO_ALIGN_CENTRE, "Minimalna cena");
	al_draw_text(font, al_map_rgb(0, 0, 0), table_s_point_x + table_width / 4, table_s_point_y + 5 * table_height / 6, ALLEGRO_ALIGN_CENTRE, "Maksymalna cena");
	al_flip_display();
}

int TWindow::company_get_active()
{
	return company_currently_active;
}

void TWindow::company_set_active(vector<TButton*> v_buttons, int mouse_x,int mouse_y)
{	
	int company_last_active = company_currently_active;
	for (int i = 0; i < v_buttons.size(); i++) {
		if (v_buttons[i]->if_cursor_in_button(mouse_x, mouse_y)) company_currently_active = i;
	}

	if (company_last_active != company_currently_active) {
		v_buttons[company_last_active]->change_font_colour(al_map_rgb(0, 0, 0));
		v_buttons[company_currently_active]->change_font_colour(al_map_rgb(14, 10, 200));
	}
	
}

void TWindow::draw_axis()
{
	al_draw_line(cross_axis_x_position, cross_axis_y_position - axis_y_length, cross_axis_x_position, cross_axis_y_position, al_map_rgb(0, 0, 0), 1);
	al_draw_line(cross_axis_x_position, cross_axis_y_position - axis_y_length, cross_axis_x_position - 5, cross_axis_y_position - axis_y_length + 20, al_map_rgb(0, 0, 0), 1);
	al_draw_line(cross_axis_x_position, cross_axis_y_position - axis_y_length, cross_axis_x_position + 5, cross_axis_y_position - axis_y_length + 20, al_map_rgb(0, 0, 0), 1);
	al_draw_line(cross_axis_x_position, cross_axis_y_position, cross_axis_x_position + axis_x_length, cross_axis_y_position, al_map_rgb(0, 0, 0), 1);
	al_draw_line(cross_axis_x_position + axis_x_length - 20, cross_axis_y_position - 5, cross_axis_x_position + axis_x_length, cross_axis_y_position, al_map_rgb(0, 0, 0), 1);
	al_draw_line(cross_axis_x_position + axis_x_length - 20, cross_axis_y_position + 5, cross_axis_x_position + axis_x_length, cross_axis_y_position, al_map_rgb(0, 0, 0), 1);
	al_flip_display();
}

void TWindow::draw_table()
{
	ALLEGRO_FONT *font = al_load_ttf_font("PTC55F.ttf", 14, 0);
	
	al_draw_line(table_s_point_x, table_s_point_y, table_s_point_x, table_s_point_y + table_height, al_map_rgb(0, 0, 0), 1);
	al_draw_line(table_s_point_x + table_width / 2, table_s_point_y, table_s_point_x + table_width / 2, table_s_point_y + table_height, al_map_rgb(0, 0, 0), 1);
	al_draw_line(table_s_point_x + table_width, table_s_point_y, table_s_point_x + table_width, table_s_point_y + table_height, al_map_rgb(0, 0, 0), 1);
	al_draw_text(font, al_map_rgb(0, 0, 0), table_s_point_x + table_width / 4, table_s_point_y, ALLEGRO_ALIGN_CENTRE, "Ostatnia data");
	al_draw_text(font, al_map_rgb(0, 0, 0), table_s_point_x + table_width / 4, table_s_point_y + table_height / 6, ALLEGRO_ALIGN_CENTRE, "Ostatnia cena");
	al_draw_text(font, al_map_rgb(0, 0, 0), table_s_point_x + table_width / 4, table_s_point_y + table_height / 3, ALLEGRO_ALIGN_CENTRE, "AVG 3M (6M)");
	al_draw_text(font, al_map_rgb(0, 0, 0), table_s_point_x + table_width / 4, table_s_point_y + 1 * table_height / 2, ALLEGRO_ALIGN_CENTRE, "IRR 3M (6M)");
	al_draw_text(font, al_map_rgb(0, 0, 0), table_s_point_x + table_width / 4, table_s_point_y + 2 * table_height / 3, ALLEGRO_ALIGN_CENTRE, "Minimalna cena");
	al_draw_text(font, al_map_rgb(0, 0, 0), table_s_point_x + table_width / 4, table_s_point_y + 5 * table_height / 6, ALLEGRO_ALIGN_CENTRE, "Maksymalna cena");


}
