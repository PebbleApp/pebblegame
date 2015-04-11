/******************************************************************************
Function definitions of the basic app structure demo. The sources I read for it 
are as follows :
https://github.com/theDrake/pebblequest/blob/master/src/pebble_quest.c
https://github.com/rigel314/pebbleMenuExample/blob/master/src/menuExample.c
******************************************************************************/

#include "hello_world.h"

void listmenu_select_click(struct MenuLayer *menu_layer, MenuIndex *cell_index, void *callback_context){
	if (WINDOW_MAIN == cell_index->row) {
	    show_window(WINDOW_MAIN, ANIMATED);
    } else if (WINDOW_GRAPHIC == cell_index->row) {
		show_window(WINDOW_GRAPHIC, ANIMATED);
    }
}
void listmenu_draw_row(GContext *ctx, const Layer *cell_layer, MenuIndex *cell_index, void *callback_context){	
	const char* row_titles[] = {"Black", "White"};
	
	graphics_context_set_text_color(ctx, GColorBlack); // This is important.
	graphics_draw_text(ctx,
					   row_titles[cell_index->row],//hex+2*cell_index->row, 
					   fonts_get_system_font(FONT_KEY_GOTHIC_14), 
					   GRect(0,0,layer_get_frame(cell_layer).size.w,layer_get_frame(cell_layer).size.h), 
					   GTextOverflowModeTrailingEllipsis, GTextAlignmentCenter, 
					   NULL);
}
void listmenu_draw_header(GContext *ctx, const Layer *cell_layer, uint16_t section_index, void *callback_context){
	graphics_context_set_text_color(ctx, GColorBlack); // This is important.
	graphics_draw_text(ctx, 
					   "headers", 
					   fonts_get_system_font(FONT_KEY_GOTHIC_14_BOLD), 
					   GRect(0,0,layer_get_frame(cell_layer).size.w,layer_get_frame(cell_layer).size.h), 
					   GTextOverflowModeTrailingEllipsis, GTextAlignmentCenter, 
					   NULL);
}
int16_t listmenu_get_header_height(struct MenuLayer *menu_layer, uint16_t section_index, void *callback_context){
	return 30;
}
int16_t listmenu_get_cell_height(struct MenuLayer *menu_layer, MenuIndex *cell_index, void *callback_context){
	return 20;
}
uint16_t listmenu_get_num_rows_in_section(struct MenuLayer *menu_layer, uint16_t section_index, void *callback_context){
	return 1;
}
uint16_t listmenu_get_num_sections(struct MenuLayer *menu_layer, void *callback_context){
	return 1;
}
uint16_t listmenu_get_num_rows(MenuLayer *menu_layer,uint16_t section_index, void *data){
	return 2;
}

void init_window(const int8_t window_index) {
    g_windows[window_index] = window_create();
	
    if (WINDOW_GRAPHIC == window_index) {
		window_set_background_color(g_windows[window_index], GColorWhite);		
	} else if (WINDOW_MAIN == window_index) {
	    window_set_background_color(g_windows[window_index], GColorBlack);	
	} else if (WINDOW_LIST == window_index) {
	    window_set_background_color(g_windows[window_index], GColorWhite);	
		
 	    g_menulayers[MENULAYER_LIST] = menu_layer_create(FULL_SCREEN_FRAME);
		menu_layer_set_click_config_onto_window(g_menulayers[MENULAYER_LIST], g_windows[window_index]);
		menu_layer_set_callbacks(g_menulayers[MENULAYER_LIST], NULL, (MenuLayerCallbacks)
		{
			.get_num_sections = listmenu_get_num_sections,
			.get_num_rows = listmenu_get_num_rows,
			.get_cell_height = listmenu_get_cell_height,
			.get_header_height = listmenu_get_header_height,
			.select_click = listmenu_select_click,
			.draw_row = listmenu_draw_row,
			.draw_header = listmenu_draw_header,
		});
		
        layer_add_child(window_get_root_layer(g_windows[window_index]),
                    menu_layer_get_layer(g_menulayers[MENULAYER_LIST]));
					
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
	g_current_window = WINDOW_LIST;
	
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
