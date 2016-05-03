#include "gfx.h"
#include "syscall.h"

static struct graphics_color draw_color = {0,0,0};
static int width = -1;
static int height = -1;

static struct event e;
static int e_valid = 0;

void gfx_open( int w, int h, const char *title ) {
	create_window(0, 0, w, h);
	width = w;
	height = h;
}

void gfx_point( int x, int y ) {
	draw_line(x, y, x, y, &draw_color);
}

void gfx_line( int x1, int y1, int x2, int y2 ) {
	draw_line(x1, y1, x2, y2, &draw_color);
}

void gfx_color( int red, int green, int blue ) {
	draw_color.r = red;
	draw_color.g = green;
	draw_color.b = blue;
}

void gfx_clear() {
	// TODO: Implement once clear is merged
}

void gfx_clear_color( int red, int green, int blue ) {
	// Not implemented
	// TODO: implement once syscall for background color is added
}

/* Wait for the user to press a key or mouse button. */
char gfx_wait() {
	if (e_valid) {
		e_valid = 0;
		return e.character;
	} else {
		// Busy wait for an event to appear
		while(get_event(&e) != 0) {}
		return e.character;
	}
	
	return '\0';
}

// TODO: Implement these once mouse events are done
int gfx_xpos() {
	return 0;
}
int gfx_ypos() {
	return 0;
}

int gfx_xsize() {
	return width;
}

int gfx_ysize() {
	return height;
}

/* Check to see if an event is waiting. */
int gfx_event_waiting() {
	if (get_event(&e) == 0) {
		e_valid = 1;
		return 1;
	}
	
	return 0;
}

void gfx_flush() {
	// Do nothing
}
