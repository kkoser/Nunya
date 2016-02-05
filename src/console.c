/*
Copyright (C) 2015 The University of Notre Dame
This software is distributed under the GNU General Public License.
See the file LICENSE for details.
*/

#include "console.h"
#include "graphics.h"
#include "window.h"

static int xsize = 80;
static int ysize = 25;

static int xpos = 0;
static int ypos = 0;

static struct window *win = 0;

struct graphics_color bgcolor = { 0, 0, 0 };
struct graphics_color fgcolor = { 255, 0, 0 };

static void console_reset() {
    xpos = ypos = 0;
    graphics_clear(bgcolor);
}

static void console_writechar(int x, int y, char ch) {
    if(win == 0)
        graphics_char(x * 8, y * 8, ch, fgcolor, bgcolor);
    else
        window_draw_char(win, x * 8, y * 8, ch, fgcolor, bgcolor);
}

void console_heartbeat() {
    static int onoff = 0;
    if (onoff) {
        if(win == 0)
            graphics_char(xpos * 8, ypos * 8, '_', fgcolor, bgcolor);
        else 
            window_draw_char(win, xpos * 8, ypos * 8, '_', fgcolor, bgcolor);
    } else {
        if(win == 0)
            graphics_char(xpos * 8, ypos * 8, '_', bgcolor, bgcolor);
        else
            window_draw_char(win, xpos * 8, ypos * 8, '_', bgcolor, bgcolor);
    }
    onoff = !onoff;
}

void console_putchar(char c) {
    console_writechar(xpos, ypos, ' ');

    switch (c) {
        case 13:
        case 10:
            xpos = 0;
            ypos++;
            break;
        case '\f':
            console_reset();
            break;
        case '\b':
            xpos--;
            break;
        default:
            console_writechar(xpos, ypos, c);
            xpos++;
            break;
    }

    if (xpos < 0) {
        xpos = xsize - 1;
        ypos--;
    }

    if (xpos >= xsize) {
        xpos = 0;
        ypos++;
    }

    if (ypos >= ysize) {
        console_reset();
    }

    console_writechar(xpos, ypos, '_');
}

void console_putstring(const char *s) {
    while (*s) {
        console_putchar(*s);
        s++;
    }
}

int console_write(int unit, const void *buffer, int length, int offset) {
    char *cbuffer = (char *)buffer;
    while (length > 0) {
        console_putchar(*cbuffer);
        cbuffer++;
        length--;
    }
    return 1;
}

void console_init() {
    xsize = graphics_width() / 8;
    ysize = graphics_height() / 8;

    console_reset();
    console_putstring("\nconsole: initialized\n");
}

void console_window_start() {
    win = window_create(50, 50, 300, 300);
    xsize = (graphics_width() - 100) / 8;
    ysize = (graphics_height()) - 100 / 8;

    console_reset();
}

uint8_t console_verify_color_range(uint8_t x) {
    if (x < 0) {
        return 0;
    }
    if (x > 255) {
        return 255;
    }
    return x;
}

void console_set_fgcolor(uint8_t r, uint8_t g, uint8_t b) {
    r = console_verify_color_range(r);
    g = console_verify_color_range(g);
    b = console_verify_color_range(b);
    fgcolor.r = r;
    fgcolor.g = g;
    fgcolor.b = b;
}

void console_set_bgcolor(uint8_t r, uint8_t g, uint8_t b) {
    r = console_verify_color_range(r);
    g = console_verify_color_range(g);
    b = console_verify_color_range(b);
    bgcolor.r = r;
    bgcolor.g = g;
    bgcolor.b = b;
}
