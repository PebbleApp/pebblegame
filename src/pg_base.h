#ifndef PG_BASE_H_
#define PG_BASE_H_

#include <pebble.h>

/******************************************************************************
  Enum Definitions
******************************************************************************/
enum {
	WINDOW_MAIN,
	WINDOW_GRAPHIC,
	WINDOW_LIST,
  	WINDOW_ANIMATION,
  	WINDOW_SENSORINPUT,
  	WINDOW_FOODSCOMING,
	WINDOW_MAX
};

enum {
  	MENULAYER_LIST,
	MENULAYER_MAX,
};

#define STATUS_BAR_HEIGHT               16 // Applies to top and bottom status bars.
#define SCREEN_WIDTH                    144
#define SCREEN_HEIGHT                   168
#define SCREEN_CENTER_POINT_X           (SCREEN_WIDTH / 2)
#define SCREEN_CENTER_POINT_Y           (SCREEN_HEIGHT / 2 - STATUS_BAR_HEIGHT * 0.75)
#define SCREEN_CENTER_POINT             GPoint(SCREEN_CENTER_POINT_X, SCREEN_CENTER_POINT_Y)
#define FULL_SCREEN_FRAME               GRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT - STATUS_BAR_HEIGHT)
#define ANIMATED                        true
#define ANIMATED_NOT                    false
/******************************************************************************
  Structure Definitions
******************************************************************************/
/*	
typedef struct someStruct {
} __attribute__((__packed__)) struct_t;	
*/	
typedef struct Vec2d {
  double x;
  double y;
} Vec2d;	

typedef struct Food {
#ifdef PBL_COLOR
  GColor color;
#endif
  struct Vec2d* pos;
  int size;	
  BitmapLayer* img_layer;
  GBitmap *img_bitmap;
  bool is_good_food;
} Food;
	
/******************************************************************************
  Global Variables
******************************************************************************/
Window *g_windows[WINDOW_MAX];
MenuLayer *g_menulayers[MENULAYER_MAX];
uint8_t g_current_window;
struct Food* foods;

/******************************************************************************
  Function Definitions
******************************************************************************/
int8_t show_window(const int8_t window_index, const bool animated);

/******************************************************************************
  Test Function Definitions
******************************************************************************/
#include <test_animation.h>
#include <test_sensorinput.h>
#include <test_foodscoming.h>
	
#endif // PG_BASE_H_