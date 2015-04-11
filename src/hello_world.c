#include "hello_world.h"

void init_window(const int8_t window_index) {
    g_windows[window_index] = window_create();
	
    if (WINDOW_GRAPHIC == window_index) {
		window_set_background_color(g_windows[window_index], GColorWhite);		
	} else if (WINDOW_MAIN == window_index) {
	    window_set_background_color(g_windows[window_index], GColorBlack);	
	}
}

int8_t show_window(const int8_t window_index, const bool animated) {
	if (!window_stack_contains_window(g_windows[window_index])) {
		window_stack_push(g_windows[window_index], animated);
	} else {
		while (window_stack_get_top_window() != g_windows[window_index]) {
			window_stack_pop(animated);
		}
	}
	
	return g_current_window = window_index;
}
			 
void init(void) {
	int8_t i;
	
	srand(time(NULL));
	g_current_window = WINDOW_GRAPHIC;
	
	for (i=0; i< WINDOW_MAX; ++i) {
		init_window(i);
	}
	
	show_window(g_current_window, ANIMATED);
	
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Initialized");
}

void deinit(void) {
	int8_t i;
	
	for (i=0; i<WINDOW_MAX; ++i) {
		window_destroy(g_windows[i]);	
	}
}

/******************************************************************************
   Function: main
Description: Main function for the app.
     Inputs: None.
    Outputs: Number of errors encountered.
******************************************************************************/
int main(void) {
	init();
	app_event_loop();
	deinit();
}
