#include "test_animation.h"

static BitmapLayer *s_background_layer;
static GBitmap *s_background_bitmap;
    
int num_of_food=3;

static void initAni(){
	/*
  food_array_ptr=(Food*)malloc(num_of_food*sizeof(Food));  //memory allocated using malloc
	APP_LOG(APP_LOG_LEVEL_DEBUG, "food array initialized");
    */	
}

static void food_init(Food *food,bool is_good_food_param) {
  /*BitmapLayer* layer = bitmap_layer_create(GRect(0, 0, 144, 168));
  GBitmap* img =  gbitmap_create_with_resource(RESOURCE_ID_FOOD_0);
  bitmap_layer_set_bitmap(layer, img);
  layer_add_child(window_get_root_layer(g_windows[WINDOW_ANIMATION]), bitmap_layer_get_layer(s_background_layer));
  */
	/*
  food->pos.x = 20;
  food->pos.y=30;
  food->is_good_food=is_good_food_param;
  */
 // food->img_layer= layer;
 // food->img =img;
}
//Visual Studio

void init_window_test_animation(void)
{
	
}	

void deinit_window_test_animation(void)
{
	
}	

void set_window_test_animation(void)
{
	window_set_background_color(g_windows[WINDOW_ANIMATION], GColorBlack);
  // Create GBitmap, then set to created BitmapLayer
 /* s_background_bitmap = gbitmap_create_with_resource(RESOURCE_ID_FOOD_0);
  s_background_layer = bitmap_layer_create(GRect(0, 0, 144, 168));
  bitmap_layer_set_bitmap(s_background_layer, s_background_bitmap);
  layer_add_child(window_get_root_layer(g_windows[WINDOW_ANIMATION]), bitmap_layer_get_layer(s_background_layer));

  initAni();
  Food *food = (Food*)malloc(sizeof(Food));
  food_init(food,true);
 */ 
}

static void deInitAni(){
  //free space
  //free(food_array_ptr);
  /*
  @ TODO unload bitmap layers
  static void main_window_unload(Window *window) {
  // Destroy GBitmap
  gbitmap_destroy(s_background_bitmap_arr[0]);
  gbitmap_destroy(s_background_bitmap_arr[1]);
  gbitmap_destroy(s_background_bitmap_arr[2]);

  //   Destroy BitmapLayer
  bitmap_layer_destroy(s_background_layer);
}
*/
}
