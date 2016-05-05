void main();
void _start() {
    main();
}

#include "syscall.h"

#define LINE_HEIGHT 10

void main() {

	create_window(5, 5, 630, 470);
	// Want to be able to see the borders
	// create_window(1, 1, 639, 479);

	clear();

	struct graphics_color text_color = {255,255,255};
	struct graphics_color background_color = {0,0,0};

	char buffer[30];
	int buff_len = 0;

	int line = 0;

	struct event e;

	// Initialize the shell
	draw_string(0, line * LINE_HEIGHT, "Welcome to Nunya Shell!", &text_color, &background_color);
	line++;
    draw_char(0, line * LINE_HEIGHT, '>', &text_color, &background_color);
	while(1) {
		int res = get_event(&e);
        if (res == 0) {
        	if (e.type != EVENT_KEYBOARD_PRESS) {
        		continue;
        	}
        	char c = e.character;
        	if (c == '\r' || c == '\n') {
        		line++;
        		buffer[buff_len] = '\0';
        		// Execute the command
        		draw_string(0, line * LINE_HEIGHT, buffer, &text_color, &background_color);
        		line++;
        		buff_len = 0;
        		draw_char(0, line * LINE_HEIGHT, '>', &text_color, &background_color);

        		// Attempt the run
        		uint32_t identifier = permissions_capability_create();
        		if (run(buffer, identifier) == -1) {
        			// Error!
        			draw_string(0, line * LINE_HEIGHT, "Unable to run command ", &text_color, &background_color);
        			draw_string(23 * 8, line * LINE_HEIGHT, buffer, &text_color, &background_color);
        			line++;
        		}
		        permissions_capability_delete(identifier);

		        // Reset the console
		        buff_len = 0;
        		draw_char(0, line * LINE_HEIGHT, '>', &text_color, &background_color);
        	} else if (c == '\b') {
        		buff_len--;
        		draw_char(8*(buff_len + 1), line * LINE_HEIGHT, ' ', &text_color, &background_color);

        	} else {

        		// Need to echo the input
        		draw_char(8*(buff_len + 1), line * LINE_HEIGHT, c, &text_color, &background_color);
        		buffer[buff_len] = c;
        		buff_len++;
        	}
        }
	}

	exit(0);
}