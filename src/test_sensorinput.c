#include <pebble.h>
#include "test_sensorinput.h"
  
#define MATH_PI 3.141592653589793238462
#define ACCEL_STEP_MS 50

typedef struct Balloon {
  Vec2d pos;
  double radius;
  short int anim_state;
  #ifdef PBL_COLOR
    GColor color;
  #endif
} Balloon;

float avg=0;  
int zeropoint=0;
int range = 150;
bool firstrun = 0;
static Window *s_main_window;
static Layer *s_balloon_layer;
static BitmapLayer *s_image_layer;
static GBitmap *dude1;
static GBitmap *dude2;
static TextLayer *s_text_layer;
static Balloon balloon;
static GRect window_frame;

/////////////////////////////////////////////////////////////////
/////////////////// SUPPORTING FUNCTIONS ////////////////////////
/////////////////////////////////////////////////////////////////

static int constrain(int value, int l1, int l2) {
  if(value<l1) value = l1;
  if(value>l2) value = l2;
  return value;
}

static int map(float value, int l1, int l2, int r1, int r2) {
  int lSpan = l2 - l1;
  int rSpan = r2 - r1; 
  return ( value - l1 )*rSpan / lSpan + r1;   
}

/////////////////////////////////////////////////////////////////
/////////////////////// Balloon Functions ///////////////////////
/////////////////////////////////////////////////////////////////

static void balloon_init(Balloon *balloon) 
{
  balloon->radius = 20;
  balloon->pos.x = 50;
  balloon->pos.y = 70;
  #ifdef PBL_COLOR
    //Init colour or graphics here
  #endif
}

static void balloon_update(Balloon *balloon, AccelData accel) 
{
  int accy = accel.y;
  accy = constrain(accy, zeropoint-range/2, zeropoint+range/2);
  avg = 0.2*accy + 0.8*avg;
  int posy = map(avg, zeropoint-range/2, zeropoint+range/2, 175, 16);
  
  balloon->pos.y = posy;
  
  // Print a message onto the text layer. Move to a function?
  char msg[128];
  snprintf(msg, 128, "%d", accy) ;
  text_layer_set_text(s_text_layer, msg);
}

static void balloon_draw(GContext *ctx, Balloon *balloon) {
#ifdef PBL_COLOR
  graphics_context_set_fill_color(ctx, balloon->color);
#else
  graphics_context_set_fill_color(ctx, GColorWhite);
#endif
  graphics_fill_circle(ctx, GPoint(balloon->pos.x-balloon->radius, balloon->pos.y-balloon->radius), balloon->radius);
  
  graphics_draw_bitmap_in_rect(ctx, dude1, GRect(balloon->pos.x-60, 
                                                 balloon->pos.y-60,
                                                 70, 
                                                 70)
                              );
}


/////////////////////////////////////////////////////////////////
///////////////////////// CALLBACKS /////////////////////////////
/////////////////////////////////////////////////////////////////

static void balloon_layer_update_callback(Layer *me, GContext *ctx) {
    balloon_draw(ctx, &balloon);
}

static void timer_callback(void *data) {
  AccelData accel = (AccelData) { .x = 0, .y = 0, .z = 0 };
  accel_service_peek(&accel);
  
  if(firstrun == 0) 
  {  
    zeropoint = accel.y;
    firstrun = 1;
  }

  balloon_update(&balloon, accel);
  layer_mark_dirty(s_balloon_layer);
  app_timer_register(ACCEL_STEP_MS, timer_callback, NULL);
}

/////////////////////////////////////////////////////////////////
///////////////// WINDOW LOAD AND UNLOAD ////////////////////////
/////////////////////////////////////////////////////////////////

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(s_text_layer, "Select pressed!");
  AccelData a = (AccelData) { .x = 0, .y = 0, .z = 0 };
  accel_service_peek(&a);
  zeropoint = a.y;
}

static void click_config_provider(void *context) {
  // Register the ClickHandlers
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
}

static void main_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect frame = window_frame = layer_get_frame(window_layer);
  window_set_click_config_provider(s_main_window, click_config_provider);

  s_balloon_layer = layer_create(frame);
  
  layer_set_update_proc(s_balloon_layer, balloon_layer_update_callback);
  layer_add_child(window_layer, s_balloon_layer);

  balloon_init(&balloon);
  
  s_text_layer = text_layer_create(GRect(120, 0, 40, 40));
  text_layer_set_font(s_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24));
  text_layer_set_text(s_text_layer, "Welcome to the Snail Cat game!");
  text_layer_set_overflow_mode(s_text_layer, GTextOverflowModeWordWrap);
  layer_add_child(window_layer, text_layer_get_layer(s_text_layer));
  
  dude1 = gbitmap_create_with_resource(RESOURCE_ID_DUDE_1);
  dude2 = gbitmap_create_with_resource(RESOURCE_ID_DUDE_2);
  
}

static void main_window_unload(Window *window) {
  layer_destroy(s_balloon_layer);
  text_layer_destroy(s_text_layer);
  //bitmap_layer_destroy(s_image_layer);
  gbitmap_destroy(dude1);
  gbitmap_destroy(dude2);
}

/////////////////////////////////////////////////////////////////
///////////////////// INIT and DE INIT //////////////////////////
/////////////////////////////////////////////////////////////////

void init_window_test_sensorinput(void)
{
	
}	

void deinit_window_test_sensorinput(void)
{
	
}

void set_window_test_sensorinput(void)
{
  s_main_window =g_windows[WINDOW_SENSORINPUT];
  window_set_background_color(s_main_window, GColorBlack);
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });
  window_stack_push(s_main_window, true);

  accel_data_service_subscribe(0, NULL);

  app_timer_register(ACCEL_STEP_MS, timer_callback, NULL);
}