#include "test_foodscoming.h"

#define NUM_FOODS_MAX 2 
	
void init_window_test_foodscoming(void)
{
	int x[NUM_FOODS_MAX] = {0,80};	
	int y[NUM_FOODS_MAX] = {0,80};	
	int size[NUM_FOODS_MAX] = {50,50};
	foods = malloc(NUM_FOODS_MAX * sizeof(struct Food));
	
	for (int i=0;i<NUM_FOODS_MAX;++i) {
        foods[i].pos = malloc(1 * sizeof(struct Vec2d)); 
        foods[i].pos->x = x[i];
        foods[i].pos->y = y[i];
        foods[i].size = size[i];

	    foods[i].img_bitmap = gbitmap_create_with_resource(RESOURCE_ID_FOOD_0);	
	    foods[i].img_layer = bitmap_layer_create(
			GRect(foods[i].pos->x, foods[i].pos->y, foods[i].size, foods[i].size));
        bitmap_layer_set_bitmap(foods[i].img_layer, foods[i].img_bitmap);
    }

}

void deinit_window_test_foodscoming(void)
{
	int i=0;
    int number_of_foods = 10;
    for (i=0;i<number_of_foods;++i) {
        free(foods[i].pos);
    }	
}

static void timer_callback(void *data) {
	for (int i=0;i<NUM_FOODS_MAX;++i) {
	   foods[i].pos->x = foods[i].pos->x - 10;
	   if (foods[i].pos->x < -10) {
		   foods[i].pos->x = 150;
	   } 
       layer_set_frame(bitmap_layer_get_layer(foods[i].img_layer), 
				GRect(foods[i].pos->x, foods[i].pos->y,foods[i].size,foods[i].size));	
    }
    app_timer_register(100, timer_callback, NULL);	
}

void set_window_test_foodscoming(void)
{
    window_set_background_color(g_windows[WINDOW_FOODSCOMING], GColorWhite);	
	for (int i=0;i<NUM_FOODS_MAX;++i) {
       layer_add_child(window_get_root_layer(g_windows[WINDOW_FOODSCOMING]), 
			bitmap_layer_get_layer(foods[i].img_layer));
    }
	
    app_timer_register(100, timer_callback, NULL);	
}
