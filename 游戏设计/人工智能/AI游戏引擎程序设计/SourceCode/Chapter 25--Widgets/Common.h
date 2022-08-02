#pragma once

// widget bank info
#define WIDGET_BANK_WIDTH 200

// widget info
#define MAX_NUM_WIDGETS 256

#define MAX_CHILD_GROUPS 64
#define MAX_CHILD_WIDGETS 64
#define MINIMIZED_WIDGET_HEIGHT 25

// scrubbers
#define WIDGET_SCRUBBER_HEIGHT 20
#define WIDGET_SCRUBBER_RIGHT_MARGIN 5
#define WIDGET_SCRUBBER_HOVER_WIDTH .60f

// scrubbing speeds
enum SCRUB_SPEED{
	SLOW_SPEED,
	REGULAR_SPEED,
	VERY_SLOW_SPEED };

/* The maximum number of widgets that will be displayed in the widget 
bank upon creation */
#define MAX_NUM_WIDGETS_DISPLAY 10
#define MAX_WIDGET_BANK_HEIGHT 800
#define WIDGETS_MARGIN 15

enum {	
		IDC_WIDGET_HEADER=1,
		IDC_TOGGLE_SWITCH,
		IDC_WIDGET,
		IDC_BASIC_BUTTON,
		IDC_WIDGET_SCRUBBER,
		IDC_WIDGET_ON_OFF,
		IDC_WIDGET_WATCHER,
		IDC_WIDGET_SCRUBBER_BUTTON,
		IDC_WIDGET_SCRUBBER_EDIT,
		IDC_WIDGET_RADIO,
		// the ordering of the following radio button group must be kept
		IDC_WIDGET_RADIO_GROUP,
		IDC_WIDGET_RADIO_LEFT,
		IDC_WIDGET_RADIO_RIGHT,
		// end group
};

// some colors
#define RED        RGB( 127,   0,   0 )
#define GREEN      RGB(   0, 127,   0 )
#define BLUE       RGB(   0,   0, 127 )
#define LIGHTRED   RGB( 255,   0,   0 )
#define LIGHTGREEN RGB(   0, 255,   0 )
#define LIGHTBLUE  RGB(   0,   0, 255 )
#define BLACK      RGB(   0,   0,   0 )
#define WHITE      RGB( 255, 255, 255 )
#define GRAY       RGB( 192, 192, 192 )
