all: first_steps font close_window
	# Done
%: %.cpp
	g++ $< -o $@ `pkg-config --libs allegro-5 allegro_main-5 allegro_primitives-5 allegro_font-5 allegro_ttf-5`

