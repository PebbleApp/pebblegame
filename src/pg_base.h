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
/******************************************************************************
  Global Variables
******************************************************************************/
	
Window *g_windows[WINDOW_MAX];
MenuLayer *g_menulayers[MENULAYER_MAX];
uint8_t g_current_window;

/******************************************************************************
  Function Definitions
******************************************************************************/

int8_t show_window(const int8_t window_index, const bool animated);

/******************************************************************************
  Test Function Definitions
******************************************************************************/
#include <test_animation.h>
#include <test_sensorinput.h>
	
#endif // PG_BASE_H_
