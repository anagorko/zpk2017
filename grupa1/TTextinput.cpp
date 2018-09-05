#include "TTextinput.h"
#include <sstream>
#include <iomanip>

using namespace std;

TTextinput::TTextinput(int v_position_x, int v_position_y, int v_height, int v_width, vector<TSeries*> v_series, string v_type)
{
	position_x = v_position_x;
	position_y = v_position_y;
	height = v_height;
	width = v_width;
	type = v_type;
	vector<string> v_to_get_result;

	for (int i = 0; i < v_series.size(); i++) {
		v_to_get_result = v_series[i]->get_min_max_date();
		if (type == "MIN") actual_date.push_back(v_to_get_result[0]);
		else actual_date.push_back(v_to_get_result[1]);
	}
}

void TTextinput::change_actual_date(vector<TSeries*> v_series, int v_active_series)
{
	ALLEGRO_FONT *font = al_load_ttf_font("PTC55F.ttf", 12, 0);
	ALLEGRO_EVENT_QUEUE * kolejka = NULL;
	ALLEGRO_EVENT ev;
	al_install_keyboard();
	kolejka = al_create_event_queue();
	al_register_event_source(kolejka, al_get_keyboard_event_source());
	string text;

	bool running = true;
	text = actual_date[v_active_series];

	while (1)
	{
		al_wait_for_event(kolejka, &ev);
		if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			if (ev.keyboard.keycode == ALLEGRO_KEY_MINUS) {
				text.append("-");
			}
			else if (ev.keyboard.keycode >= 27 && ev.keyboard.keycode <= 36) {
				std::ostringstream ss;
				ss << std::fixed << setprecision(0);
				ss << ev.keyboard.keycode - 27;
				text.append(ss.str());
			}
			else if (ev.keyboard.keycode == ALLEGRO_KEY_BACKSPACE) {
				if (text.size() > 0) text.pop_back();
			}
			else if (ev.keyboard.keycode == ALLEGRO_KEY_ENTER) {
				if (if_date_correct(text)) {
					actual_date[v_active_series] = text;
					v_series[v_active_series]->change_data_range(text, type);
				}
				al_draw_filled_rectangle(position_x + 1, position_y + 1, position_x + width - 1, position_y + height - 1, al_map_rgb(255, 255, 255));
				al_draw_text(font, al_map_rgb(0, 0, 0), position_x, position_y, ALLEGRO_ALIGN_LEFT, actual_date[v_active_series].c_str());
				al_flip_display();
				break;
			}

			al_draw_filled_rectangle(position_x + 1, position_y +1, position_x + width - 1, position_y + height - 1, al_map_rgb(255, 255, 255));
			al_draw_text(font, al_map_rgb(0, 0, 0), position_x, position_y, ALLEGRO_ALIGN_LEFT, text.c_str());
			al_flip_display();

		}
	}
}

void TTextinput::change_actual_date_automatic(string v_dates, int v_active_series)
{

	actual_date[v_active_series] = v_dates;

}

void TTextinput::redraw(int v_active_series)
{
	ALLEGRO_FONT *font = al_load_ttf_font("PTC55F.ttf", 12, 0);
	al_draw_filled_rectangle(position_x + 1, position_y + 1, position_x + width - 1, position_y + height - 1, al_map_rgb(255, 255, 255));
	al_draw_rectangle(position_x, position_y, position_x + width, position_y + height, al_map_rgb(0, 0, 0), 1);
	al_draw_text(font, al_map_rgb(0, 0, 0), position_x, position_y, ALLEGRO_ALIGN_LEFT, actual_date[v_active_series].c_str());
}

bool TTextinput::if_date_correct(string v_date) {
	int year, month, day;
	if (v_date.length() != 10) return false;
	else {
		std::istringstream(v_date.substr(0, 4)) >> year;
		std::istringstream(v_date.substr(5, 2)) >> month;
		std::istringstream(v_date.substr(8, 2)) >> day;
	}
if (month <= 12 && month >= 1 && day >= 1 && v_date.at(4) == '-' && v_date.at(7) == '-' &&
	(
		(
		(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
		&& day <= 31
		) || 
		(
		(month == 4 || month == 6 || month == 9 || month == 11)
				&& day <= 30
		) ||
		(year % 4 != 0 && month == 2 && day <= 28) ||
		(year % 4 == 0 && month == 2 && day <= 29)
	)
) return true;
else return false;
}


