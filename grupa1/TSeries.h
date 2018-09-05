#pragma once
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_ttf.h>
#include <string>
#include <vector>

using namespace std;

class TSeries
{
public:
	TSeries(string name, vector<string> v_dates, vector<double> v_prices, vector<double> v_dates_num);
	void change_data_range(string v_date, string v_type);
	vector<string> get_min_max_date();
	void draw_chart(int middle_x, int middle_y, int length_x, int length_y, ALLEGRO_COLOR series_color);
	void draw_statistics(int position_x, int position_y, ALLEGRO_COLOR series_color);
	void update_from_database(vector<string> v_dates, vector<double> v_prices, vector<double> v_dates_num);
	string data_range_from;
	string data_range_to;
private:
	vector<double> company_price;
	vector<string> company_date;
	vector<double> company_date_num;
	string number_to_string(double number, int precision);
	string name;
};

