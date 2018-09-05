#include "TSeries.h"
#include "TDatabase.h"
#include <sstream>
#include <iomanip>

using namespace std;

TSeries::TSeries(string v_name, vector<string> v_dates, vector<double> v_prices, vector<double> v_dates_num)
{
	name = v_name;
	company_date = v_dates;
	company_price = v_prices;
	company_date_num = v_dates_num;
	int min_date = v_dates_num[0];
	int max_date = v_dates_num[0];
	int j = 0;
	int k = 0;
	for (int i = 0; i < v_prices.size(); i++) {
		if (v_dates_num[i] < min_date) { min_date = v_dates_num[i]; j = i; }
		if (v_dates_num[i] > max_date) { min_date = v_dates_num[i]; k = i; }
	}

	data_range_from = v_dates[j];
	data_range_to = v_dates[k];
}

void TSeries::change_data_range(string v_date, string v_type) {
	string str_dates, str_price, str_dates_num;
	TDatabase database_temp = TDatabase("root", "password", "127.0.0.1", "mysql");
	if (v_type == "MIN") {
		data_range_from = v_date;
	}
	else {
		data_range_to = v_date;
	}

	str_dates = "Select Dates from mysql." + name + " where Dates >= '" + data_range_from + "' and Dates <= '" + data_range_to + "' and booking_date = (Select wew.booking_date from mysql." + name + " wew order by 1 desc limit 1)";
	str_price = "Select Price from mysql." + name + " where Dates >= '" + data_range_from + "' and Dates <= '" + data_range_to + "' and booking_date = (Select wew.booking_date from mysql." + name + " wew order by 1 desc limit 1)";
	str_dates_num = "Select Dates_num from mysql." + name + " where Dates >= '" + data_range_from + "' and Dates <= '" + data_range_to + "' and booking_date = (Select wew.booking_date from mysql." + name + " wew order by 1 desc limit 1)";
	company_date = database_temp.read_string(str_dates);
	company_price = database_temp.read_double(str_price);
	company_date_num = database_temp.read_double(str_dates_num);
}

vector<string> TSeries::get_min_max_date()
{
	int min_date = company_date_num[0];
	int max_date = company_date_num[0];
	int j, k;
	for (int i = 0; i < company_price.size(); i++) {
		if (company_date_num[i] < min_date) {min_date = company_date_num[i]; j = i;}
		if (company_date_num[i] > max_date) { min_date = company_date_num[i]; k = i;}
	}

	vector<string> result;
	result.push_back(company_date[j]);
	result.push_back(company_date[k]);
	return result;
}

void TSeries::draw_chart(int middle_x, int middle_y, int length_x, int length_y, ALLEGRO_COLOR series_color)
{

	const char *text1;
	double x1, x2, y1, y2, next_dec, min_price, max_price, min_date, max_date;
	ALLEGRO_TRANSFORM t;
	ALLEGRO_FONT *font = al_load_ttf_font("PTC55F.ttf", 14, 0);

	min_price = company_price[0];
	max_price = company_price[0];
	min_date = company_date_num[0];
	max_date = company_date_num[0];

	for (int i = 1; i < company_price.size(); i++) {
		if (company_price[i] < min_price) min_price = company_price[i];
		if (company_price[i] > max_price) max_price = company_price[i];
		if (company_date_num[i] < min_date) min_date = company_date_num[i];
		if (company_date_num[i] > max_date) max_date = company_date_num[i];
	}

	float step_x = (max_date - min_date) / (length_x - 50);
	float step_y = (max_price - min_price) / length_y;

	for (int i = 1; i < 10; ++i) {
		next_dec = min_price + (max_price - min_price) / 10 * i;
		auto x_str = std::to_string(int(next_dec));
		al_draw_text(font, al_map_rgb(0, 0, 0), middle_x, middle_y - (next_dec - min_price) / step_y - 15, ALLEGRO_ALIGN_RIGHT, x_str.c_str());
	}

	for (int i = 0; i < company_price.size() - 1; i++) {
		x1 = middle_x + 15 + (company_date_num[i] - min_date) / step_x;
		x2 = middle_x + 15 + (company_date_num[i + 1] - min_date) / step_x;
		y1 = middle_y - (company_price[i] - min_price) / step_y - 15;
		y2 = middle_y - (company_price[i + 1] - min_price) / step_y - 15;

		al_draw_line(x1, y1, x2, y2, al_map_rgb(0, 0, 0), 4);

		if (i % int((max_date - min_date) / 33) == 0) {
			al_translate_transform(&t, -x1, -middle_y);
			al_rotate_transform(&t, -0.5);
			al_translate_transform(&t, x1, middle_y);
			al_use_transform(&t);
			al_draw_text(font, al_map_rgb(0, 0, 0), x1, middle_y, ALLEGRO_ALIGN_RIGHT, company_date[i].c_str());
			al_identity_transform(&t);
			al_rotate_transform(&t, 0);
			al_use_transform(&t);
		}

	}
}

void TSeries::draw_statistics(int position_x, int position_y, ALLEGRO_COLOR series_color)
{

	ALLEGRO_FONT *font = al_load_ttf_font("PTC55F.ttf", 14, 0);
	vector<string> result;
	double avg_3M, avg_6M, last_price, irr_3M, irr_6M, min_price, max_price;
	int num_3M, num_6M, date_index_3M, date_index_6M, date_index_last;

	int max_date = company_date_num[0];

	for (int i = 0; i < company_date_num.size(); i++) {
		if (max_date < company_date_num[i]) {
			max_date = company_date_num[i];
			date_index_last = i;
		}
	}

	num_3M = 0;
	num_6M = 0;
	avg_3M = 0;
	avg_6M = 0;
	date_index_3M = date_index_last;
	date_index_6M = date_index_last;
	min_price = company_price[0];
	max_price = company_price[0];

	for (int i = 0; i < company_price.size(); i++) {

		if (max_date - company_date_num[i] <= 90 && company_date_num[i] < company_date_num[date_index_3M]) {
			date_index_3M = i;
		}

		if (max_date - company_date_num[i] <= 180 && company_date_num[i] < company_date_num[date_index_6M]) {
			date_index_6M = i;
		}

		if (max_date - company_date_num[i] <= 90) {
			avg_3M += company_price[i];
			num_3M += 1;
		}
		if (max_date - company_date_num[i] <= 180) {
			avg_6M += company_price[i];
			num_6M += 1;
		}

		if (min_price > company_price[i]) min_price = company_price[i];
		if (max_price < company_price[i]) max_price = company_price[i];
	}

	last_price = company_price[date_index_last];
	avg_3M = avg_3M / num_3M;
	avg_6M = avg_6M / num_6M;
	irr_3M = (company_price[date_index_last] / company_price[date_index_3M] - 1) * 4;
	irr_6M = (company_price[date_index_last] / company_price[date_index_6M] - 1) * 2;

	result.push_back(number_to_string(last_price, 2)); // [0]
	result.push_back(number_to_string(avg_3M, 2));	  //  [1]
	result.push_back(" (" + number_to_string(avg_6M, 2) + ")"); // [2]
	result.push_back(number_to_string(irr_3M, 4));			   // [3]
	result.push_back(" (" + number_to_string(irr_6M, 4) + ")"); // [4]
	result.push_back(number_to_string(min_price, 2)); // [5]
	result.push_back(number_to_string(max_price, 2)); // [6]

	ALLEGRO_COLOR avg_color, irr_3M_color, irr_6M_color;
	if (avg_3M > avg_6M) avg_color = al_map_rgb(250, 128, 114);
	else				 avg_color = al_map_rgb(50, 205, 50);

	if (irr_3M < 0) irr_3M_color = al_map_rgb(250, 128, 114);
	else			irr_3M_color = al_map_rgb(50, 205, 50);

	if (irr_6M < 0) irr_6M_color = al_map_rgb(250, 128, 114);
	else			irr_6M_color = al_map_rgb(50, 205, 50);

	al_draw_text(font, series_color, position_x, position_y, ALLEGRO_ALIGN_CENTER, company_date[date_index_last].c_str());
	al_draw_text(font, series_color, position_x, position_y + 15, ALLEGRO_ALIGN_CENTER, result[0].c_str());
	al_draw_text(font, avg_color, position_x, position_y + 30, ALLEGRO_ALIGN_RIGHT, result[1].c_str());
	al_draw_text(font, series_color, position_x, position_y + 30, ALLEGRO_ALIGN_LEFT, result[2].c_str());
	al_draw_text(font, irr_3M_color, position_x, position_y + 45, ALLEGRO_ALIGN_RIGHT, result[3].c_str());
	al_draw_text(font, irr_6M_color, position_x, position_y + 45, ALLEGRO_ALIGN_LEFT, result[4].c_str());
	al_draw_text(font, series_color, position_x, position_y + 60, ALLEGRO_ALIGN_CENTER, result[5].c_str());
	al_draw_text(font, series_color, position_x, position_y + 75, ALLEGRO_ALIGN_CENTER, result[6].c_str());
}

void TSeries::update_from_database(vector<string> v_dates, vector<double> v_prices, vector<double> v_dates_num)
{
	company_date = v_dates;
	company_price = v_prices;
	company_date_num = v_dates_num;
	int min_date = v_dates_num[0];
	int max_date = v_dates_num[0];
	int j, k;
	j = 0;
	k = 0;
	for (int i = 0; i < company_price.size(); i++) {
		if (v_dates_num[i] < min_date) { min_date = v_dates_num[i]; j = i; }
		if (v_dates_num[i] > max_date) { min_date = v_dates_num[i]; k = i; }
	}

	data_range_from = v_dates[j];
	data_range_to = v_dates[k];

}
string TSeries::number_to_string(double number, int precision)
{
	std::ostringstream ss;
	ss << std::fixed << setprecision(precision);
	ss << number;
	return ss.str();
}

