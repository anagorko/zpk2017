#include <iostream> 
#include "TButton.h"   // Object this class need to create nutton on which it is possibility to click
#include "Tdatabase.h" // Object this class gives us possibility to make interaction with database
#include "TSeries.h"   // Objects this class hold data about Time Series and is used to calculated based statistics
#include "TWindow.h"   // Object this class is used to hold info about actual TS and is used to create addtitional output (axis, tables)
#include "TTextinput.h" // Obejct in which user can change data range in program
#include "TCsvreader.h" // Object this class is needed to read data from csv
#include <vector>
#include <string> 
#include <sstream>
#include <iomanip>

using namespace std; 

int main(int argc, char * argv[]) {

	ALLEGRO_DISPLAY * display = NULL;

	/* Tworzymy zmienn¹ w której przechowamy adres kolejki */
	ALLEGRO_EVENT_QUEUE * kolejka = NULL;
	ALLEGRO_EVENT_QUEUE * kolejka2 = NULL;

	/* Tworzymy zmienn¹ w której przetrzymamy event do obs³u¿enia */
	ALLEGRO_EVENT ev1;
	ALLEGRO_EVENT ev2;

	if (!al_init())
	{
		fprintf(stderr, "Failed to initialize allegro!\n");
		return -1;
	}

	if (!al_init_primitives_addon())
	{
		fprintf(stderr, "Failed to initialize allegro!\n");
		return -1;
	}

	// initialize the font addon
	if (!al_init_font_addon()) 
	{
		fprintf(stderr, "Failed to initialize allegro!\n");
		return -1;
	}

	if (!al_init_ttf_addon()) {
		fprintf(stderr, "Failed to initialize allegro!\n");
		return -1;
	}
	
	if (!al_install_mouse()) {
		fprintf(stderr, "Failed to initialize allegro!\n");
		return -1;
	}

	if (!al_install_keyboard()) {
		fprintf(stderr, "Failed to initialize allegro!\n");
		return -1;
	}

	/* Allokujemy pamiêæ dla kolejki i sprawdzamy czy funkcja nie zwróci³a b³êdu */
	kolejka = al_create_event_queue();

	if (kolejka == NULL)
	{
		fprintf(stderr, "Failed to create event queue!\n");
		return -1;
	}

	display = al_create_display(1300, 600);

	if (display == NULL)
	{
		fprintf(stderr, "Failed to create display!\n");
		return -1;
	}

	/* If we have quee and display, we register display as event source */
	/* Additional we added mouse & keyboard as event source*/
	al_register_event_source(kolejka, al_get_display_event_source(display));
	al_register_event_source(kolejka, al_get_mouse_event_source());
	al_register_event_source(kolejka, al_get_keyboard_event_source());
	ALLEGRO_MOUSE_STATE *state = NULL;
	int mouse_x;
	int mouse_y;

	al_clear_to_color(al_map_rgb(255, 255, 255));
	al_show_mouse_cursor(display);
	al_flip_display();
	
	// Create object TDatabase class 
	TDatabase database = TDatabase("root", "password", "127.0.0.1", "mysql");
	ALLEGRO_TRANSFORM t;
	ALLEGRO_FONT *font = al_load_ttf_font("PTC55F.ttf", 18, 0);

//  Read data from .csv
	TCsvreader csv_read_api = TCsvreader("C:/Users/Adam/source/repos/ZPK PROJEKT ZALICZENIOWY", ",");
	vector<vector<string> > vector_to_get_data;
	string filename;
	vector<string> date_from_to;

//  Buttons to click
	TButton BWIG20 = TButton(50,  50, 80, 20, 16, "WIG-20", al_map_rgb(127, 127, 127), al_map_rgb(50, 50, 50) );
	TButton BPKO   = TButton(150, 50, 80, 20, 16,    "PKO", al_map_rgb(127, 127, 127), al_map_rgb(50, 50, 50) );
	TButton BPZU   = TButton(250, 50, 80, 20, 16,    "PZU", al_map_rgb(127, 127, 127), al_map_rgb(50, 50, 50) );
	TButton BmBank = TButton(350, 50, 80, 20, 16,  "mBank", al_map_rgb(127, 127, 127), al_map_rgb(50, 50, 50) );
	TButton BAlior = TButton(450, 50, 80, 20, 16,  "Alior", al_map_rgb(127, 127, 127), al_map_rgb(50, 50, 50) );
	TButton refresh_report = TButton(30, 20, 80, 20, 16, "Refresh", al_map_rgb(127, 127, 127), al_map_rgb(14, 10, 200));
	vector<TButton*> buttons;
	buttons.push_back(&BWIG20);
	buttons.push_back(&BPKO);
	buttons.push_back(&BPZU);
	buttons.push_back(&BmBank);
	buttons.push_back(&BAlior);

/***********************************************************************************************************/

//  Data Series 
	TSeries WIG20 = TSeries("WIG20", database.read_string("Select t.dates from mysql.WIG20 t where t.booking_date = (Select wew.booking_date from mysql.WIG20 wew order by 1 desc limit 1)"), database.read_double("Select t.price from mysql.WIG20 t where t.booking_date = (Select wew.booking_date from mysql.WIG20 wew order by 1 desc limit 1)"), database.read_double("Select t.dates_num from mysql.WIG20 t where t.booking_date = (Select wew.booking_date from mysql.WIG20 wew order by 1 desc limit 1)"));
	TSeries PKO = TSeries("PKO", database.read_string("Select t.dates from mysql.PKO t where t.booking_date = (Select wew.booking_date from mysql.PKO wew order by 1 desc limit 1)"), database.read_double("Select t.price from mysql.PKO t where t.booking_date = (Select wew.booking_date from mysql.PKO wew order by 1 desc limit 1)"), database.read_double("Select t.dates_num from mysql.PKO t where t.booking_date = (Select wew.booking_date from mysql.PKO wew order by 1 desc limit 1)"));
	TSeries PZU = TSeries("PZU", database.read_string("Select t.dates from mysql.PZU t where t.booking_date = (Select wew.booking_date from mysql.PZU wew order by 1 desc limit 1)"), database.read_double("Select t.price from mysql.PZU t where t.booking_date = (Select wew.booking_date from mysql.PZU wew order by 1 desc limit 1)"), database.read_double("Select t.dates_num from mysql.PZU t where t.booking_date = (Select wew.booking_date from mysql.PZU wew order by 1 desc limit 1)"));
	TSeries mBank = TSeries("mBank", database.read_string("Select t.dates from mysql.mBank t where t.booking_date = (Select wew.booking_date from mysql.mBank wew order by 1 desc limit 1)"), database.read_double("Select t.price from mysql.mBank t where t.booking_date = (Select wew.booking_date from mysql.mBank wew order by 1 desc limit 1)"), database.read_double("Select t.dates_num from mysql.mBank t where t.booking_date = (Select wew.booking_date from mysql.mBank wew order by 1 desc limit 1)"));
	TSeries Alior = TSeries("Alior", database.read_string("Select t.dates from mysql.Alior t where t.booking_date = (Select wew.booking_date from mysql.Alior wew order by 1 desc limit 1)"), database.read_double("Select t.price from mysql.Alior t where t.booking_date = (Select wew.booking_date from mysql.Alior wew order by 1 desc limit 1)"), database.read_double("Select t.dates_num from mysql.Alior t where t.booking_date = (Select wew.booking_date from mysql.Alior wew order by 1 desc limit 1)"));
	vector<TSeries*> companies;
	companies.push_back(&WIG20);
	companies.push_back(&PKO);
	companies.push_back(&PZU);
	companies.push_back(&mBank);
	companies.push_back(&Alior);
/**********************************************************************************************************/

/**********************************************************************************************************/

	// Draw text inputs

	TTextinput data_range_from = TTextinput(150, 10, 20, 100, companies,"MIN");
	TTextinput data_range_to = TTextinput(300, 10, 20, 100, companies, "MAX");

	// creating object class Window (handle output)
	TWindow window = TWindow(50, 550, 850, 450, 950, 20, 90, 300); 

	// Draw as Default Price of WIG with Statistic + mark WIG20 Button
	BWIG20.change_font_colour(al_map_rgb(14, 10, 200));
	BWIG20.redraw_button();
	WIG20.draw_chart(45, 550, 850, 450, al_map_rgb(0, 0, 0));
	WIG20.draw_statistics(1175, 20, al_map_rgb(0, 0, 0));
	data_range_from.redraw(window.company_get_active());
	data_range_to.redraw(window.company_get_active());

	al_flip_display();

	int last_active_tab;
	int current_active_tab;

	/* Main loop */
	while (1)
	{
		/* If event occur, we will send to ev1 variable */
		al_wait_for_event(kolejka, &ev1);
		//al_wait_for_event(kolejka2, &ev2);
		if (ev1.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			break;
		}
	// If left button of mmouse is clicked
		if (ev1.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
		{
	// Get coordinates of mouse
			mouse_x = ev1.mouse.x;
			mouse_y = ev1.mouse.y;
			last_active_tab = window.company_get_active();
			window.company_set_active(buttons, mouse_x, mouse_y);
			current_active_tab = window.company_get_active();
	// Check whether User click not the same button	
			if (last_active_tab != current_active_tab) {
				al_clear_to_color(al_map_rgb(255, 255, 255));
				window.draw_axis();
				window.draw_table();
				data_range_from.redraw(current_active_tab);
				data_range_to.redraw(current_active_tab);
				refresh_report.redraw_button();
	// Action depends on which button User last click
				switch (current_active_tab)
				{
				case 0:
					WIG20.draw_chart(45, 550, 850, 450, al_map_rgb(0, 0, 0));
					WIG20.draw_statistics(1175, 20, al_map_rgb(0, 0, 0));
					break;
				case 1:
					PKO.draw_chart(45, 550, 850, 450, al_map_rgb(0, 0, 0));
					PKO.draw_statistics(1175, 20, al_map_rgb(0, 0, 0));
					break;
				case 2:
					PZU.draw_chart(45, 550, 850, 450, al_map_rgb(0, 0, 0));
					PZU.draw_statistics(1175, 20, al_map_rgb(0, 0, 0));
					break;
				case 3:
					mBank.draw_chart(45, 550, 850, 450, al_map_rgb(0, 0, 0));
					mBank.draw_statistics(1175, 20, al_map_rgb(0, 0, 0));
					break;
				case 4:
					Alior.draw_chart(45, 550, 850, 450, al_map_rgb(0, 0, 0));
					Alior.draw_statistics(1175, 20, al_map_rgb(0, 0, 0));
					break;
				}

				BWIG20.redraw_button();
				BPKO.redraw_button();
				BPZU.redraw_button();
				BAlior.redraw_button();
				BmBank.redraw_button();
				al_flip_display();

			} // Check whether left side Text Input is clicked
			else if (mouse_x >= 150 && mouse_x <= 250 && mouse_y >= 10 && mouse_y <= 30) {
				current_active_tab = window.company_get_active();
				data_range_from.change_actual_date(companies, current_active_tab);
				al_clear_to_color(al_map_rgb(255, 255, 255));
				window.draw_axis();
				window.draw_table();
				data_range_from.redraw(current_active_tab);
				data_range_to.redraw(current_active_tab);
				refresh_report.redraw_button();
				BWIG20.redraw_button();
				BPKO.redraw_button();
				BPZU.redraw_button();
				BAlior.redraw_button();
				BmBank.redraw_button();
				switch (current_active_tab)
				{
				case 0:
					WIG20.draw_chart(45, 550, 850, 450, al_map_rgb(0, 0, 0));
					WIG20.draw_statistics(1175, 20, al_map_rgb(0, 0, 0));
					break;
				case 1:
					PKO.draw_chart(45, 550, 850, 450, al_map_rgb(0, 0, 0));
					PKO.draw_statistics(1175, 20, al_map_rgb(0, 0, 0));
					break;
				case 2:
					PZU.draw_chart(45, 550, 850, 450, al_map_rgb(0, 0, 0));
					PZU.draw_statistics(1175, 20, al_map_rgb(0, 0, 0));
					break;
				case 3:
					mBank.draw_chart(45, 550, 850, 450, al_map_rgb(0, 0, 0));
					mBank.draw_statistics(1175, 20, al_map_rgb(0, 0, 0));
					break;
				case 4:
					Alior.draw_chart(45, 550, 850, 450, al_map_rgb(0, 0, 0));
					Alior.draw_statistics(1175, 20, al_map_rgb(0, 0, 0));
					break;
				}
				al_flip_display();

			} // Check whether right side Text input is clicked
			else if (mouse_x >= 300 && mouse_x <= 400 && mouse_y >= 10 && mouse_y <= 30) {
				current_active_tab = window.company_get_active();
				data_range_to.change_actual_date(companies, current_active_tab);
				al_clear_to_color(al_map_rgb(255, 255, 255));
				window.draw_axis();
				window.draw_table();
				data_range_from.redraw(current_active_tab);
				data_range_to.redraw(current_active_tab);
				BWIG20.redraw_button();
				BPKO.redraw_button();
				BPZU.redraw_button();
				BAlior.redraw_button();
				BmBank.redraw_button();
				refresh_report.redraw_button();
				switch (current_active_tab)
				{
				case 0:
					WIG20.draw_chart(45, 550, 850, 450, al_map_rgb(0, 0, 0));
					WIG20.draw_statistics(1175, 20, al_map_rgb(0, 0, 0));
					break;
				case 1:
					PKO.draw_chart(45, 550, 850, 450, al_map_rgb(0, 0, 0));
					PKO.draw_statistics(1175, 20, al_map_rgb(0, 0, 0));
					break;
				case 2:
					PZU.draw_chart(45, 550, 850, 450, al_map_rgb(0, 0, 0));
					PZU.draw_statistics(1175, 20, al_map_rgb(0, 0, 0));
					break;
				case 3:
					mBank.draw_chart(45, 550, 850, 450, al_map_rgb(0, 0, 0));
					mBank.draw_statistics(1175, 20, al_map_rgb(0, 0, 0));
					break;
				case 4:
					Alior.draw_chart(45, 550, 850, 450, al_map_rgb(0, 0, 0));
					Alior.draw_statistics(1175, 20, al_map_rgb(0, 0, 0));
					break;
				}
				al_flip_display();
			} // Check whether refresh report button is clicked
			else if(refresh_report.if_cursor_in_button(mouse_x, mouse_y)) {
				current_active_tab = window.company_get_active();
				switch (current_active_tab)
				{
				case 0:
					filename = "wig20_d.csv";
					vector_to_get_data = csv_read_api.getdata(filename);
					database.write(vector_to_get_data[0], vector_to_get_data[4], "WIG20");
					companies[0]->update_from_database(database.read_string("Select t.dates from mysql.WIG20 t where t.booking_date = (Select wew.booking_date from mysql.WIG20 wew order by 1 desc limit 1)"), database.read_double("Select t.price from mysql.WIG20 t where t.booking_date = (Select wew.booking_date from mysql.WIG20 wew order by 1 desc limit 1)"), database.read_double("Select t.dates_num from mysql.WIG20 t where t.booking_date = (Select wew.booking_date from mysql.WIG20 wew order by 1 desc limit 1)"));
					data_range_from.change_actual_date_automatic(companies[0]->data_range_from, 0);
					data_range_to.change_actual_date_automatic(companies[0]->data_range_to, 0);
					al_clear_to_color(al_map_rgb(255, 255, 255));
					WIG20.draw_chart(45, 550, 850, 450, al_map_rgb(0, 0, 0));
					WIG20.draw_statistics(1175, 20, al_map_rgb(0, 0, 0));
					break;
				case 1:
					filename = "pko_d.csv";
					vector_to_get_data = csv_read_api.getdata(filename);
					database.write(vector_to_get_data[0], vector_to_get_data[4], "PKO");
					companies[1]->update_from_database(database.read_string("Select t.dates from mysql.PKO t where t.booking_date = (Select wew.booking_date from mysql.PKO wew order by 1 desc limit 1)"), database.read_double("Select t.price from mysql.PKO t where t.booking_date = (Select wew.booking_date from mysql.PKO wew order by 1 desc limit 1)"), database.read_double("Select t.dates_num from mysql.PKO t where t.booking_date = (Select wew.booking_date from mysql.PKO wew order by 1 desc limit 1)"));
					data_range_from.change_actual_date_automatic(companies[1]->data_range_from, 1);
					data_range_to.change_actual_date_automatic(companies[1]->data_range_to, 1);
					al_clear_to_color(al_map_rgb(255, 255, 255));
					PKO.draw_chart(45, 550, 850, 450, al_map_rgb(0, 0, 0));
					PKO.draw_statistics(1175, 20, al_map_rgb(0, 0, 0));
					break;
				case 2:
					filename = "pzu_d.csv";
					vector_to_get_data = csv_read_api.getdata(filename);
					database.write(vector_to_get_data[0], vector_to_get_data[4], "PZU");
					companies[2]->update_from_database(database.read_string("Select t.dates from mysql.PZU t where t.booking_date = (Select wew.booking_date from mysql.PZU wew order by 1 desc limit 1)"), database.read_double("Select t.price from mysql.PZU t where t.booking_date = (Select wew.booking_date from mysql.PZU wew order by 1 desc limit 1)"), database.read_double("Select t.dates_num from mysql.PZU t where t.booking_date = (Select wew.booking_date from mysql.PZU wew order by 1 desc limit 1)"));
					data_range_from.change_actual_date_automatic(companies[2]->data_range_from, 2);
					data_range_to.change_actual_date_automatic(companies[2]->data_range_to, 2);
					al_clear_to_color(al_map_rgb(255, 255, 255));
					PZU.draw_chart(45, 550, 850, 450, al_map_rgb(0, 0, 0));
					PZU.draw_statistics(1175, 20, al_map_rgb(0, 0, 0));
					break;
				case 3:
					filename = "mbk_d.csv";
					vector_to_get_data = csv_read_api.getdata(filename);
					database.write(vector_to_get_data[0], vector_to_get_data[4], "mBank");
					companies[3]->update_from_database(database.read_string("Select t.dates from mysql.mBank t where t.booking_date = (Select wew.booking_date from mysql.mBank wew order by 1 desc limit 1)"), database.read_double("Select t.price from mysql.mBank t where t.booking_date = (Select wew.booking_date from mysql.mBank wew order by 1 desc limit 1)"), database.read_double("Select t.dates_num from mysql.mBank t where t.booking_date = (Select wew.booking_date from mysql.mBank wew order by 1 desc limit 1)"));
					data_range_from.change_actual_date_automatic(companies[3]->data_range_from, 3);
					data_range_to.change_actual_date_automatic(companies[3]->data_range_to, 3);
					al_clear_to_color(al_map_rgb(255, 255, 255));
					mBank.draw_chart(45, 550, 850, 450, al_map_rgb(0, 0, 0));
					mBank.draw_statistics(1175, 20, al_map_rgb(0, 0, 0));
					break;
				case 4:
					filename = "alr_d.csv";
					vector_to_get_data = csv_read_api.getdata(filename);
					database.write(vector_to_get_data[0], vector_to_get_data[4], "Alior");
					companies[4]->update_from_database(database.read_string("Select t.dates from mysql.Alior t where t.booking_date = (Select wew.booking_date from mysql.Alior wew order by 1 desc limit 1)"), database.read_double("Select t.price from mysql.Alior t where t.booking_date = (Select wew.booking_date from mysql.Alior wew order by 1 desc limit 1)"), database.read_double("Select t.dates_num from mysql.Alior t where t.booking_date = (Select wew.booking_date from mysql.Alior wew order by 1 desc limit 1)"));
					data_range_from.change_actual_date_automatic(companies[4]->data_range_from, 4);
					data_range_to.change_actual_date_automatic(companies[4]->data_range_to, 4);
					al_clear_to_color(al_map_rgb(255, 255, 255));
					Alior.draw_chart(45, 550, 850, 450, al_map_rgb(0, 0, 0));
					Alior.draw_statistics(1175, 20, al_map_rgb(0, 0, 0));
					break;
				}
				window.draw_axis();
				window.draw_table();
				refresh_report.redraw_button();
				BWIG20.redraw_button();
				BPKO.redraw_button();
				BPZU.redraw_button();
				BAlior.redraw_button();
				BmBank.redraw_button();
				data_range_from.redraw(current_active_tab);
				data_range_to.redraw(current_active_tab);
				al_flip_display();
			}
				
		
	}

	}

	al_destroy_display(display);

	/* Zwalniamy pamiêæ po kolejce */
	al_destroy_event_queue(kolejka);
	return 0;

}